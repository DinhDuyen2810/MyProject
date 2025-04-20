# Sorting Algorithms Visualizer

Ứng dụng minh họa trực quan các thuật toán sắp xếp được phát triển bằng ngôn ngữ C++ trên nền tảng Qt.

## 📌 Giới thiệu

Đây là phần mềm mô phỏng hoạt động của nhiều thuật toán sắp xếp từ cơ bản đến nâng cao, kèm theo khả năng đo thời gian thực thi và so sánh hiệu năng. Phần mềm có thể được sử dụng cho mục đích học tập, giảng dạy và nghiên cứu.

## 🛠 Công nghệ sử dụng

- **Ngôn ngữ:** C++
- **Framework:** Qt (Qt Widgets, QThread, QFileDialog, QVector, v.v.)
- **IDE:** Qt Creator

## ✨ Tính năng chính

- ✅ Minh họa trực quan quá trình sắp xếp với animation sinh động
- ✅ Hỗ trợ 3 phương thức nhập dữ liệu: tự nhập, random, hoặc tải từ file `.txt`
- ✅ Hỗ trợ xuất kết quả ra file khi dữ liệu lớn (trên 5000 phần tử)
- ✅ So sánh hiệu năng giữa các thuật toán
- ✅ Hiển thị thông tin chi tiết về từng thuật toán

## 📊 Thuật toán hỗ trợ

- Bubble Sort
- Selection Sort
- Insertion Sort
- Interchange Sort
- Heap Sort
- Merge Sort
- Quick Sort
- Shell Sort
- Counting Sort
- Radix Sort
- Bucket Sort
- Flash Sort
- Shaker Sort
- Cube Sort

## 🖼 Giao diện người dùng

Giao diện trực quan với các widget như Label, Button, TextEdit, CheckBox. Animation sử dụng màu sắc để biểu diễn quá trình sắp xếp:
- 🟩 Phần tử đã sắp xếp
- 🔴/🟡 Phần tử đang được so sánh

## 📥 Đầu vào và 📤 Đầu ra

- Đầu vào:
  - Tự nhập số
  - Random dãy số
  - Tải từ file `.txt`
- Đầu ra:
  - In ra màn hình nếu < 5000 phần tử
  - Xuất file kết quả nếu ≥ 5000 phần tử
  - Hiển thị thời gian thực thi (giây, ms, μs)

## 🔁 So sánh thuật toán

Chức năng quan trọng giúp so sánh hiệu năng các thuật toán sắp xếp trên cùng một tập dữ liệu. Kết quả được hiển thị dạng bảng sắp xếp theo thời gian tăng dần.

## 🔍 Thông tin thuật toán

Cung cấp mô tả chi tiết, ưu – nhược điểm và animation trực quan cho từng thuật toán, hỗ trợ người học dễ dàng hiểu và so sánh.

## 💾 Tải về và chạy phần mềm

Bạn có thể tải phần mềm đã biên dịch sẵn tại:

🔗 [Download SortApp.zip](https://github.com/DinhDuyen2810/MyProject/raw/Qt_project/Sort_app/build/Desktop_Qt_6_8_0_MinGW_64_bit-Release/SortApp.zip)

**Hướng dẫn chạy phần mềm:**

1. Tải file `.zip` ở link trên và giải nén.
2. Chạy file `SortApp.exe` trong thư mục vừa giải nén.
3. Nếu hệ thống báo thiếu thư viện `.dll`, đảm bảo bạn đã cài đặt Qt Runtime tương ứng hoặc copy các thư viện `.dll` cần thiết từ thư mục Qt.

> ⚠️ Lưu ý: Phiên bản hiện tại chỉ hỗ trợ hệ điều hành Windows (64-bit).

## 💡 Hướng phát triển tương lai

- Mở rộng xử lý số thực hoặc xâu ký tự
- Thêm các thuật toán mới
- Tăng tính tương tác của giao diện
- Tối ưu hóa hiệu suất animation

---

📁 *Project này được thực hiện như một phần của đồ án môn học năm 3, với mục tiêu minh họa thuật toán sắp xếp một cách trực quan và dễ hiểu.*
