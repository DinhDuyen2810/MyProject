document.addEventListener('DOMContentLoaded', function() {
  const questionInput = document.getElementById('questionInput');
  const answerInput = document.getElementById('answerInput');
  const addBtn = document.getElementById('addBtn');
  const pairsList = document.getElementById('pairsList');
  const fillBtn = document.getElementById('fillBtn');
  const noPairsMessage = document.getElementById('noPairsMessage');
  const searchInput = document.getElementById('searchInput');  // Thêm phần tìm kiếm

  // Tải dữ liệu khi mở popup
  loadSavedPairs();

  // Sự kiện thêm cặp mới
  addBtn.addEventListener('click', addNewPair);

  // Sự kiện điền form
  fillBtn.addEventListener('click', fillForms);

  // Thêm bằng phím Enter
  answerInput.addEventListener('keypress', function(e) {
    if (e.key === 'Enter') {
      addNewPair();
    }
  });

  // Sự kiện tìm kiếm
  searchInput.addEventListener('input', filterPairs);

  // Hàm tải dữ liệu đã lưu
  function loadSavedPairs() {
    chrome.storage.sync.get(['questionAnswerPairs'], function(result) {
      if (chrome.runtime.lastError) {
        console.error('Lỗi khi đọc storage:', chrome.runtime.lastError);
        return;
      }

      const pairs = result.questionAnswerPairs || [];
      renderPairsList(pairs);
    });
  }

  // Hàm thêm cặp mới
  function addNewPair() {
    const question = questionInput.value.trim();
    const answer = answerInput.value.trim();

    if (!question || !answer) {
      alert('Vui lòng nhập cả câu hỏi và câu trả lời!');
      return;
    }

    chrome.storage.sync.get(['questionAnswerPairs'], function(result) {
      const pairs = result.questionAnswerPairs || [];
      pairs.push({ question, answer });

      chrome.storage.sync.set({ questionAnswerPairs: pairs }, function() {
        if (chrome.runtime.lastError) {
          console.error('Lỗi khi lưu storage:', chrome.runtime.lastError);
          return;
        }

        renderPairsList(pairs);
        questionInput.value = '';
        answerInput.value = '';
        questionInput.focus();
      });
    });
  }

  // Hàm hiển thị danh sách
  function renderPairsList(pairs) {
    pairsList.innerHTML = '';

    if (pairs.length === 0) {
      noPairsMessage.style.display = 'block';
      return;
    }

    noPairsMessage.style.display = 'none';

    pairs.forEach((pair, index) => {
      const li = document.createElement('li');
      li.className = 'pair-item';

      const pairText = document.createElement('span');
      pairText.textContent = `${cleanQuestionText(pair.question)} → ${pair.answer}`;

      const actionsDiv = document.createElement('div');
      actionsDiv.className = 'pair-actions';
      
      const editBtn = document.createElement('button');
      editBtn.textContent = 'Sửa';
      editBtn.className = 'edit-btn';
      editBtn.addEventListener('click', () => showEditDialog(index, pair.question, pair.answer));
      
      const deleteBtn = document.createElement('button');
      deleteBtn.textContent = 'Xóa';
      deleteBtn.className = 'delete-btn';
      deleteBtn.addEventListener('click', () => deletePair(index));
      
      actionsDiv.appendChild(editBtn);
      actionsDiv.appendChild(deleteBtn);
      
      li.appendChild(pairText);
      li.appendChild(actionsDiv);      
      pairsList.appendChild(li);
    });
  }

  function showEditDialog(index, oldQuestion, oldAnswer) {
    // Tạo overlay
    const overlay = document.createElement('div');
    overlay.className = 'edit-dialog';
  
    overlay.innerHTML = `
      <h3>Chỉnh sửa</h3>
      <div class="input-center-wrapper">
        <input type="text" id="editQuestion" value="${oldQuestion}">
        <input type="text" id="editAnswer" value="${oldAnswer}">
      </div>
      <div class="dialog-buttons">
        <button id="cancelEdit">Hủy</button>
        <button id="saveEdit">OK</button>
      </div>
    `;
  
    document.body.appendChild(overlay);
  
    document.getElementById('cancelEdit').addEventListener('click', () => {
      overlay.remove();
    });
  
    document.getElementById('saveEdit').addEventListener('click', () => {
      const newQuestion = document.getElementById('editQuestion').value.trim();
      const newAnswer = document.getElementById('editAnswer').value.trim();
  
      if (!newQuestion || !newAnswer) {
        alert('Vui lòng nhập cả câu hỏi và câu trả lời!');
        return;
      }
  
      chrome.storage.sync.get(['questionAnswerPairs'], function(result) {
        const pairs = result.questionAnswerPairs || [];
        pairs[index] = { question: newQuestion, answer: newAnswer };
  
        chrome.storage.sync.set({ questionAnswerPairs: pairs }, function() {
          overlay.remove();
          renderPairsList(pairs);
        });
      });
    });
  }
  

  // Hàm làm sạch văn bản câu hỏi (loại bỏ các phần không cần thiết)
  function cleanQuestionText(text) {
    return text.replace(/^\s*\d+[.)\-\s]*\s*/i, '')
               .replace(/[*\s]*(\(required\)|\(bắt buộc\))[*\s]*$/i, '')
               .replace(/\*+$/g, '')
               .trim();
  }

  // Hàm xóa cặp
  function deletePair(index) {
    chrome.storage.sync.get(['questionAnswerPairs'], function(result) {
      const pairs = result.questionAnswerPairs || [];
      pairs.splice(index, 1);

      chrome.storage.sync.set({ questionAnswerPairs: pairs }, function() {
        renderPairsList(pairs);
      });
    });
  }

  // Hàm sửa cặp
  function editPair(index, pair) {
    const newQuestion = prompt('Sửa câu hỏi:', pair.question);
    const newAnswer = prompt('Sửa câu trả lời:', pair.answer);

    if (newQuestion !== null && newAnswer !== null) {
      chrome.storage.sync.get(['questionAnswerPairs'], function (result) {
        const pairs = result.questionAnswerPairs || [];
        pairs[index] = { question: newQuestion.trim(), answer: newAnswer.trim() };

        chrome.storage.sync.set({ questionAnswerPairs: pairs }, function () {
          renderPairsList(pairs);
        });
      });
    }
  }

  // Hàm điền form tự động
  function fillForms() {
    chrome.tabs.query({ active: true, currentWindow: true }, function(tabs) {
      chrome.scripting.executeScript({
        target: { tabId: tabs[0].id },
        files: ['content.js']
      });
    });
  }

  // Hàm lọc cặp câu hỏi-trả lời theo từ khóa tìm kiếm
  function filterPairs() {
    const searchQuery = searchInput.value.trim().toLowerCase();
    
    chrome.storage.sync.get(['questionAnswerPairs'], function(result) {
      const pairs = result.questionAnswerPairs || [];

      // Lọc các cặp câu hỏi - trả lời dựa trên từ khóa tìm kiếm
      const filteredPairs = pairs.filter(pair => {
        const questionText = pair.question.toLowerCase();
        const answerText = pair.answer.toLowerCase();
        return questionText.includes(searchQuery) || answerText.includes(searchQuery);
      });

      renderPairsList(filteredPairs);
    });
  }
});
