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

    pairs.forEach(pair => {
        const pairQuestionLower = pair.question.toLowerCase();
        let score = 0;

        if (cleanedLower.includes(pairQuestionLower) || pairQuestionLower.includes(cleanedLower)) {
            score = Math.max(cleanedLower.length, pairQuestionLower.length);
        }

        if (cleanedLower === pairQuestionLower) {
            score = 100;
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
