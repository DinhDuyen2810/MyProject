// Lấy các cặp câu hỏi-trả lời đã lưu
chrome.storage.sync.get(['questionAnswerPairs'], function(result) {
    if (chrome.runtime.lastError) {
        alert('Lỗi khi đọc dữ liệu từ storage: ' + chrome.runtime.lastError.message);
        return;
    }

    const pairs = result.questionAnswerPairs || [];

    if (pairs.length === 0) {
        alert('Không có câu hỏi nào được lưu trong extension!');
        return;
    }

    //alert('Bắt đầu quá trình điền form...\nTìm thấy ' + pairs.length + ' câu hỏi đã lưu');

    // Xác định loại form
    if (window.location.hostname.includes('google.com')) {
        fillGoogleForm(pairs);
    } else if (window.location.hostname.includes('office.com')) {
        fillMicrosoftForm(pairs);
    } else {
        alert('Không phải Google Form hay Microsoft Form!\nURL: ' + window.location.hostname);
    }
});

// Hàm điền vào Google Form
function fillGoogleForm(pairs) {
    const questions = document.querySelectorAll('[role="listitem"]');

    if (questions.length === 0) {
        //alert('Không tìm thấy câu hỏi nào trong Google Form!\nKiểm tra lại selector.');
        return;
    }

    //alert('Đang xử lý Google Form...\nTìm thấy ' + questions.length + ' câu hỏi trong form');

    let filledCount = 0;
    let unansweredCount = 0;

    questions.forEach((questionElement, index) => {
        const originalText = questionElement.textContent.trim();
        const cleanedText = cleanQuestionText(originalText);

        // Kiểm tra xem questionElement có chứa input hoặc textarea không
        const input = questionElement.querySelector('input, textarea');
        const radioGroup = questionElement.querySelector('[role="radiogroup"]');

        if (!input) {
            // Nếu không có input hoặc textarea, bỏ qua câu hỏi này
            //console.warn(`Bỏ qua câu hỏi ${index + 1}: "${originalText}" vì không có ô nhập liệu.`);
            return;
        }

        const matchedPair = findBestMatch(cleanedText, pairs);

        if (matchedPair) {
            if (input.type === 'date') {
                // Nếu là trường ngày tháng, điền ngày tháng
                fillDateOfBirth(questionElement, matchedPair.answer);
            } else if (radioGroup) {
                // Nếu là câu hỏi lựa chọn (radio hoặc checkbox)
                fillChoice(questionElement, matchedPair.answer);
            } else {
                // Nếu là trường văn bản, điền câu trả lời vào input
                input.value = matchedPair.answer;
                triggerInputEvent(input);
            }
            filledCount++;

            // Hiển thị thông tin chi tiết cho từng câu hỏi được điền
            // console.log(`Đã điền câu ${index + 1}:`, {
            //     'Câu hỏi trong form': originalText,
            //     'Câu hỏi đã làm sạch': cleanedText,
            //     'Câu hỏi đã lưu': matchedPair.question,
            //     'Câu trả lời': matchedPair.answer
            // });
        } else {
            unansweredCount++;
            //console.warn(`Không tìm thấy kết quả phù hợp cho câu hỏi ${index + 1}: "${originalText}"`);
        }
    });

    if (filledCount > 0) {
        alert('Đã điền thành công ' + filledCount + ' câu hỏi!');
    } else {
        //alert('Không điền được câu hỏi nào!\nNguyên nhân có thể do:\n1. Câu hỏi không khớp\n2. Không tìm thấy ô nhập liệu\n3. Selector không đúng\n\nXem chi tiết trong Console (F12)');
    }

    if (unansweredCount > 0) {
        console.log(`Có ${unansweredCount} câu hỏi không được trả lời.`);
    }
}

// Hàm điền vào Microsoft Form
function fillMicrosoftForm(pairs) {

    // Tìm tất cả các câu hỏi trong form, sử dụng selector đúng cho từng câu hỏi
    const questions = document.querySelectorAll('[data-automation-id="questionItem"]');

    if (questions.length === 0) {
        //alert('Không tìm thấy câu hỏi nào trong Microsoft Form! Kiểm tra lại selector.');
        return;
    }

    let filledCount = 0;
    let unansweredCount = 0;

    questions.forEach((questionElement, index) => {
        // Tìm phần tử chứa tiêu đề câu hỏi
        const titleElement = questionElement.querySelector('[data-automation-id="questionTitle"]');
        if (!titleElement) return; // Nếu không tìm thấy title, bỏ qua câu hỏi này.

        const originalText = titleElement.textContent.trim();
        const cleanedText = cleanQuestionText(originalText);

        // Tìm câu trả lời tương ứng với câu hỏi
        const matchedPair = findBestMatch(cleanedText, pairs);
        const input = questionElement.querySelector('input, textarea');
        const radioGroup = questionElement.querySelector('[role="radiogroup"]');

        if (matchedPair) {
            if (input) {
                if (input.type === 'date') {
                    // Nếu câu trả lời là ngày tháng, gọi hàm điền ngày sinh
                    fillDateOfBirth(questionElement, matchedPair.answer);
                } else {
                    // Điền câu trả lời vào ô input hoặc textarea
                    input.value = matchedPair.answer;
                    triggerInputEvent(input); // Gửi sự kiện input
                }
            } else if (radioGroup) {
                // Nếu câu trả lời là nhóm radio, điền vào radio button
                fillChoice(questionElement, matchedPair.answer);
            } else {
                // Cảnh báo khi không tìm thấy input hoặc radioGroup
                //console.warn(`Không có input phù hợp để điền cho câu ${index + 1}: "${originalText}"`);
                unansweredCount++;
                return;
            }

            filledCount++; // Cập nhật số câu đã điền
            // console.log(`Đã điền câu ${index + 1}:`, {
            //     'Câu hỏi trong form': originalText,
            //     'Câu hỏi đã làm sạch': cleanedText,
            //     'Câu hỏi đã lưu': matchedPair.question,
            //     'Câu trả lời': matchedPair.answer
            // });
        } else {
            // Nếu không tìm thấy câu trả lời phù hợp
            unansweredCount++;
            //console.warn(`Không tìm thấy kết quả phù hợp cho câu hỏi ${index + 1}: "${originalText}"`);
        }
    });

    // Thông báo kết quả
    if (filledCount > 0) {
        alert('Đã điền thành công ' + filledCount + ' câu hỏi!');
    }

    if (unansweredCount > 0) {
        console.log(`Có ${unansweredCount} câu hỏi không được trả lời.`);
    }
}


// Hàm làm sạch câu hỏi
function cleanQuestionText(text) {
    let cleaned = text.replace(/^\s*\d+[.)\-\s]*\s*/i, '');  // Loại bỏ số thứ tự
    cleaned = cleaned.replace(/[*\s]*(\(required\)|\(bắt buộc\)|\(required field\))[*\s]*$/i, '');  // Loại bỏ các từ "bắt buộc"
    cleaned = cleaned.replace(/\*+$/g, '');  // Loại bỏ dấu * cuối câu
    return cleaned.trim().replace(/\s+/g, ' ');  // Cắt khoảng trắng thừa
}

// Hàm tìm kết quả phù hợp nhất
function findBestMatch(cleanedText, pairs) {
    const cleanedLower = cleanedText.toLowerCase();
    let bestMatch = null;
    let bestScore = 0;

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
      

    // Tạo danh sách mở rộng từ các câu hỏi đã lưu
    pairs.forEach(pair => {
        const questionLower = pair.question.toLowerCase();
        const synonyms = synonymMap[questionLower] || [];

        let score = 0;

        if (cleanedLower === questionLower) {
            score = 100;
        } else if (cleanedLower.includes(questionLower) || questionLower.includes(cleanedLower)) {
            score = Math.max(cleanedLower.length, questionLower.length);
        } else if (synonyms.some(syn => cleanedLower.includes(syn) || syn.includes(cleanedLower))) {
            score = 80;
        }

        if (score > bestScore) {
            bestScore = score;
            bestMatch = pair;
        }
    });

    return bestMatch;
}

// Hàm kích hoạt sự kiện input
function triggerInputEvent(element) {
    const event = new Event('input', { bubbles: true });
    element.dispatchEvent(event);
    const changeEvent = new Event('change', { bubbles: true });
    element.dispatchEvent(changeEvent);
}

// Hàm xử lý câu hỏi lựa chọn (radio hoặc checkbox)
function fillChoice(questionElement, answer) {
    const choices = questionElement.querySelectorAll('[role="radio"], [role="checkbox"]'); // Lấy tất cả các lựa chọn radio hoặc checkbox
    let found = false;

    // Chuẩn hóa câu trả lời để tránh sự khác biệt về chữ hoa, chữ thường hoặc dấu cách
    const normalizedAnswer = answer.trim().toLowerCase();

    // Lấy phần lựa chọn từ câu hỏi
    const questionText = questionElement.textContent.trim().toLowerCase();

    // Lặp qua tất cả các lựa chọn để tìm kiếm phần tử phù hợp với câu trả lời
    choices.forEach(choice => {
        const role = choice.getAttribute('role'); // Kiểm tra thuộc tính role (radio hoặc checkbox)
        const choiceLabel = choice.getAttribute('aria-label').trim().toLowerCase();

        // Kiểm tra nếu phần tử có role là "radio" hoặc "checkbox"
        if ((role === 'radio' || role === 'checkbox') && choiceLabel === normalizedAnswer) {
            const isChecked = choice.getAttribute('aria-checked') === 'true'; // Kiểm tra xem đã được chọn chưa
            
            if (!isChecked) {
                try {
                    // Click vào lựa chọn để chọn
                    choice.click();

                    // Tạo sự kiện 'change' để đảm bảo form nhận thấy sự thay đổi
                    const changeEvent = new Event('change', {
                        bubbles: true,
                        cancelable: true
                    });

                    // Dispatch sự kiện 'change' để form nhận diện thay đổi
                    choice.dispatchEvent(changeEvent);

                    found = true;
                } catch (error) {
                    console.error('Error occurred while clicking:', error);
                }
            }
        }
    });

    if (!found) {
        console.warn(`Không tìm thấy lựa chọn phù hợp cho câu hỏi: "${questionElement.textContent.trim()}" với đáp án "${answer}"`);
    }
}

// Hàm điền vào ngày tháng năm sinh (đặc biệt đối với trường ngày tháng)
function fillDateOfBirth(questionElement, dateOfBirth) {
    const input = questionElement.querySelector('input[type="date"]');
    if (input) {
        // Chuyển đổi ngày tháng năm sinh sang định dạng yyyy-mm-dd
        const dateParts = dateOfBirth.split('/');
        const formattedDate = `${dateParts[2]}-${dateParts[1]}-${dateParts[0]}`;

        // Điền giá trị vào trường input
        input.value = formattedDate;

        // Kích hoạt sự kiện input nếu cần
        triggerInputEvent(input);
    } else {
        console.warn('Không tìm thấy trường ngày tháng năm.');
    }
}
