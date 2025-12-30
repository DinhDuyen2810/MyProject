'use strict'

const {
  bufferToString, genRandomSalt, generateEG, computeDH,
  verifyWithECDSA, HMACtoAESKey, HMACtoHMACKey, HKDF,
  encryptWithGCM, decryptWithGCM, cryptoKeyToJSON, govEncryptionDataStr
} = require('./lib')

class MessengerClient {
  constructor (caPublicKey, govPublicKey) {
    this.caPublicKey = caPublicKey
    this.govPublicKey = govPublicKey
    this.conns = {}
    this.certs = {}
    this.EGKeyPair = {}
  }

  async generateCertificate (username) {
    this.EGKeyPair = await generateEG()
    return { username, pub: this.EGKeyPair.pub }
  }

  async receiveCertificate (certificate, signature) {
    const isValid = await verifyWithECDSA(this.caPublicKey, JSON.stringify(certificate), signature)
    if (!isValid) throw new Error('Certificate verification failed!')
    this.certs[certificate.username] = certificate
  }

  async getKeyID (key) {
    const jwk = await cryptoKeyToJSON(key)
    return jwk.x + '_' + jwk.y
  }

  getSkippedKeyIndex (idStr, n) {
    return idStr + '_' + n
  }

  async KDF_CK (ck) {
    return Promise.all([
      HMACtoHMACKey(ck, 'HMAC-GENERATION'),
      HMACtoAESKey(ck, 'AES-GENERATION')
    ])
  }

  async KDF_RK (rootKey, dhOut) {
    return HKDF(dhOut, rootKey, 'ratchet-str')
  }

  async getOrCreateConnection (name) {
    if (this.conns[name]) return this.conns[name]
    const cert = this.certs[name]
    if (!cert) throw new Error(`Unknown user: ${name}`)
    const shared = await computeDH(this.EGKeyPair.sec, cert.pub)
    const remoteID = await this.getKeyID(cert.pub) 
    return (this.conns[name] = {
      RK: await HMACtoHMACKey(shared, 'ROOT-KEY'),
      CKs: null, CKr: null, Ns: 0, Nr: 0, PN: 0,
      DHs: this.EGKeyPair, DHr: cert.pub, remoteID: remoteID, skippedKeys: {}
    })
  }

  async trySkipMessageKeys (state, limit) {
    while (state.Nr < limit) {
      const [nextCKr, mk] = await this.KDF_CK(state.CKr)
      const idx = this.getSkippedKeyIndex(state.remoteID, state.Nr)
      state.skippedKeys[idx] = mk
      state.CKr = nextCKr
      state.Nr++
    }
  }

  async sendMessage (name, plaintext) {
    const govTask = (async () => {
      const pair = await generateEG()
      const shared = await computeDH(pair.sec, this.govPublicKey)
      const key = await HMACtoAESKey(shared, govEncryptionDataStr)
      const iv = genRandomSalt()
      return { pub: pair.pub, key, iv }
    })()

    const state = await this.getOrCreateConnection(name)

    if (!state.CKs) {
      if (state.Ns === 0 && state.PN === 0) state.DHs = await generateEG()
      const [newRK, newCKs] = await this.KDF_RK(state.RK, await computeDH(state.DHs.sec, state.DHr))
      state.RK = newRK; state.CKs = newCKs
    }

    const [nextCKs, mk] = await HMACtoHMACKey(state.CKs, 'HMAC-GENERATION').then(async n => [n, await HMACtoAESKey(state.CKs, 'AES-GENERATION')])
    const mkRaw = await HMACtoAESKey(state.CKs, 'AES-GENERATION', true)
    state.CKs = nextCKs

    const gov = await govTask
    const cGov = await encryptWithGCM(gov.key, Buffer.from(mkRaw), gov.iv)

    const receiverIV = genRandomSalt()
    const header = {
      dh: state.DHs.pub, pn: state.PN, n: state.Ns,
      receiverIV, vGov: gov.pub, cGov, ivGov: gov.iv
    }

    const ciphertext = await encryptWithGCM(mk, plaintext, receiverIV, JSON.stringify(header))
    state.Ns++
    return [header, ciphertext]
  }

  async receiveMessage (name, [header, ciphertext]) {
    const state = await this.getOrCreateConnection(name)

    const headerID = await this.getKeyID(header.dh)

    const msgIndex = this.getSkippedKeyIndex(headerID, header.n)
    if (state.skippedKeys[msgIndex]) {
      const mk = state.skippedKeys[msgIndex]
      delete state.skippedKeys[msgIndex]
      try {
        return bufferToString(await decryptWithGCM(mk, ciphertext, header.receiverIV, JSON.stringify(header)))
      } catch (e) { throw new Error('Decryption failed for skipped message') }
    }

    if (state.remoteID !== headerID) {
      await this.trySkipMessageKeys(state, header.pn)
      state.PN = state.Ns; state.Ns = 0; state.Nr = 0
      state.DHr = header.dh; state.remoteID = headerID 

      const [rk1, ckr] = await this.KDF_RK(state.RK, await computeDH(state.DHs.sec, state.DHr))
      state.RK = rk1; state.CKr = ckr

      state.DHs = await generateEG()
      const [rk2, cks] = await this.KDF_RK(state.RK, await computeDH(state.DHs.sec, state.DHr))
      state.RK = rk2; state.CKs = cks
    }

    await this.trySkipMessageKeys(state, header.n)

    if (header.n < state.Nr) throw new Error('Message replay detected!')

    const [nextCKr, mk] = await this.KDF_CK(state.CKr)
    state.CKr = nextCKr; state.Nr++

    try {
      return bufferToString(await decryptWithGCM(mk, ciphertext, header.receiverIV, JSON.stringify(header)))
    } catch (e) { throw new Error('Decryption failed!') }
  }
}

module.exports = { MessengerClient }