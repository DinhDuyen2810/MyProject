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
    if (!searchQuery) {
      loadSavedPairs(); // nếu không nhập gì thì hiển thị toàn bộ
      return;
    }
  
    const exactWordPattern = new RegExp(`\\b${searchQuery}\\b`, 'i');
  
    // Danh sách từ đồng nghĩa
    const synonymMap = {
      'họ tên': ['họ và tên', 'họ, tên', 'tên và họ', 'tên đầy đủ', 'your name', 'full name', 'hvt', 'hoten', 'ten day du', 'ten cua ban'],
      'ngày sinh': ['ngày tháng năm sinh', 'ngày, tháng, năm sinh', 'dob', 'birthdate', 'sinh nhật', 'ngaysinh', 'ns', 'birth day', 'ngay sinh nhat', 'birth'],
      'sdt': ['số điện thoại', 'điện thoại', 'phone number', 'mobile', 'liên lạc', 'sdt', 'so dt', 'so dien thoai', 'so di dong', 'phone'],
      'email': ['địa chỉ email', 'thư điện tử', 'email address', 'mail', 'e-mail', 'gmail', 'email của bạn', 'dc email', 'email cá nhân', 'dia chi mail'],
      'giới tính': ['giới', 'nam hay nữ', 'gender', 'sex', 'gioitinh', 'gt', 'nam nu', 'male or female', 'gioi', 'gioi tinh'],
      'địa chỉ': ['nơi ở', 'chỗ ở hiện tại', 'address', 'địa chỉ hiện tại', 'nơi cư trú', 'dia chi', 'address now', 'dia chi lien he', 'cho o', 'noio'],
      'ngành học': ['chuyên ngành', 'ngành bạn học', 'field of study', 'major', 'nganh', 'nganh hoc', 'nganh cua ban', 'study field', 'major name', 'chuyen nganh'],
      'trường học': ['tên trường', 'trường bạn đang học', 'university', 'school name', 'truong hoc', 'truong', 'school', 'uni', 'ten truong', 'trg'],
      'lớp': ['lớp học', 'tên lớp', 'class', 'lop', 'lop hoc', 'class name', 'ten lop', 'ma lop', 'classroom', 'class id'],
      'mã sinh viên': ['student id', 'mã số sinh viên', 'mssv', 'ma sinh vien', 'student code', 'student number', 'msv', 'studentid', 'ma sv', 'id sinh vien'],
      'ngày đăng ký': ['ngày ghi danh', 'registration date', 'ngày tham gia', 'ngay dang ky', 'ngay dk', 'registration', 'ngay vao', 'join date', 'dk ngay', 'register day'],
      'thời gian rảnh': ['khoảng thời gian rảnh', 'free time', 'thời gian trống', 'tgian ranh', 'tg rảnh', 'rảnh khi nào', 'thoi gian trong', 'tg trong', 'free period', 'luc ranh'],
      'sở thích': ['hobby', 'hoạt động yêu thích', 'interest', 'so thich', 'st', 'yeu thich', 'hoat dong ua thich', 'thu vui', 'sothich', 'favorite'],
      'câu hỏi bảo mật': ['security question', 'câu hỏi dự phòng', 'cau hoi bao mat', 'question for recovery', 'chbm', 'question to unlock', 'question de mo', 'question backup', 'ch an toan', 'phuc hoi cau hoi'],
      'mật khẩu': ['password', 'mật mã', 'pass', 'mat khau', 'pw', 'passwd', 'matma', 'pass code', 'pass word', 'ma bao mat'],
      'tình trạng hôn nhân': ['hôn nhân', 'marital status', 'độc thân hay đã kết hôn', 'hon nhan', 'tthn', 'married?', 'doc than/kethon', 'married status', 'hn', 'tthn'],
      'ngôn ngữ': ['language', 'ngôn ngữ sử dụng', 'ngon ngu', 'language used', 'lang', 'ngonngu', 'language select', 'language option', 'ngon ngu chinh', 'language preferred'],
      'mức thu nhập': ['thu nhập', 'income', 'khoảng lương', 'muc luong', 'thu nhap ca nhan', 'salary', 'income level', 'money earn', 'tn', 'luong'],
      'nơi sinh': ['quê quán', 'birthplace', 'quê', 'noi sinh', 'birth place', 'birth location', 'noi sinh song', 'que', 'nơi đẻ', 'place born'],
      'quốc tịch': ['nationality', 'tình trạng quốc tịch', 'quoc tich', 'qt', 'country', 'national', 'quoc gia', 'tich quoc', 'country of citizenship', 'citizen'],
      'cmnd': ['căn cước công dân', 'cccd', 'chứng minh nhân dân', 'id number', 'số cmnd/cccd', 'số cccd', 'cmnd/cccd', 'id', 'so cmnd', 'so cccd'],
      'mã số thuế': ['tax code', 'mst', 'ma so thue', 'ma thue', 'tax id', 'tax number', 'taxcode', 'ma so', 'mstn', 'id thue'],
      'tôn giáo': ['religion', 'đạo', 'ton giao', 'dao', 'religious belief', 'faith', 'giao phai', 'religion type', 'dao nao', 'tg'],
      'dân tộc': ['ethnicity', 'dân tộc thiểu số', 'dan toc', 'dt', 'race', 'ethnic', 'minority', 'nhom dan toc', 'ethnic group', 'dan toc nao'],
      'người liên hệ khẩn cấp': ['liên hệ khẩn cấp', 'emergency contact', 'nguoi lien he', 'nguoi lien he khan cap', 'lhkc', 'ec', 'nguoi khan cap', 'emergency person', 'lien lac gap', 'nguoi bao tin'],
      'sở trường': ['điểm mạnh', 'ưu điểm', 'strength', 'so truong', 'uu diem', 'ky nang manh', 'strong point', 'st', 'skillset', 'so truong chinh'],
      'kinh nghiệm làm việc': ['work experience', 'quá trình công tác', 'kinh nghiem lam viec', 'knlv', 'job history', 'work background', 'viec da lam', 'job exp', 'quá trình làm việc', 'work timeline'],
      'trình độ học vấn': ['trình độ', 'học vấn', 'education level', 'trinh do', 'hoc van', 'bang cap', 'academic level', 'trinh do hoc van', 'tdhv', 'education'],
      'kỹ năng': ['skills', 'năng lực', 'khả năng', 'ky nang', 'kỹ năng chuyên môn', 'skillset', 'ability', 'kn', 'nang luc', 'skills list'],
      'mục tiêu nghề nghiệp': ['career goals', 'định hướng nghề nghiệp', 'muc tieu', 'nghe nghiep', 'career objective', 'dinh huong', 'goal job', 'job goal', 'career aim', 'job dream'],
    };
    
    
  
    const getAllSynonyms = (term) => {
      const lowerTerm = term.toLowerCase();
      const result = [lowerTerm];
  
      for (const key in synonymMap) {
        if (key === lowerTerm || synonymMap[key].includes(lowerTerm)) {
          result.push(key, ...synonymMap[key]);
        }
      }
  
      // Loại bỏ trùng lặp
      return Array.from(new Set(result));
    };
  
    const expandedQueries = getAllSynonyms(searchQuery);
  
    chrome.storage.sync.get(['questionAnswerPairs'], function(result) {
      const pairs = result.questionAnswerPairs || [];
  
      const filteredPairs = pairs.filter(pair => {
        const questionText = pair.question.toLowerCase();
        const answerText = pair.answer.toLowerCase();
  
        // Kiểm tra từng cụm từ mở rộng
        return expandedQueries.some(q =>
          questionText.includes(q) ||
          answerText.includes(q) ||
          exactWordPattern.test(pair.question) ||
          exactWordPattern.test(pair.answer)
        );
      });
  
      renderPairsList(filteredPairs);
    });
  }
});
