// Background script có thể để trống hoặc thêm các sự kiện cần thiết
console.log('Background script đang chạy');

// Ví dụ: Xử lý khi extension được cài đặt
chrome.runtime.onInstalled.addListener(() => {
  console.log('Extension đã được cài đặt');
});