#include "inforofsort.h"
#include "ui_inforofsort.h"
#include <QThread>
#include <stack>
#include <QDebug>

inforOfSort::inforOfSort(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::inforOfSort)
{
    ui->setupUi(this);

    connect(ui->btn_goHome, &QPushButton::clicked, [this]() {
        stopAnimation();
        goBackHome();
    });

    connect(ui->btn_goBack_inforsort, &QPushButton::clicked, [this]() {
        stopAnimation();
        goBackChooseSort();
    });

    ui->txt_infor->setReadOnly(true);
    connect(ui->btn_start, &QPushButton::clicked, this, &inforOfSort::startAnimationSort);
}

inforOfSort::~inforOfSort()
{
    delete ui;
}

 // Độ dịch chuyển theo phương thẳng đứng


// Bắt đầu animation
void inforOfSort::startAnimationSort() {
    if (isSorting) {
        return;
    }
    isHeapSortMode = false;
    isMergeSortMode = false;
    isCountingMode = false;
    isRadixSortMode = false;
    isFlashSortMode = false;
    isSorting = true;

    switch(numberToAnimation){
        case 1 : // BubbleSort
            {numbers = {13, 17, 24, 38, 45, 2, 23, 32, 41, 4};
            colors.resize(numbers.size(), Qt::gray);
            update(); // Vẽ lại widget cha với dữ liệu ban đầu
            i = 0;
            j = 0;
            isComparing = true;
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::BubbleAnimation);
            animationTimer->start(400); // Cài đặt khoảng thời gian mỗi bước
            break;}

        case 2: // HeapSort
            {numbers = {31, 4, 3, 27, 28, 15, 45, 41, 11, 19};
            colors.resize(numbers.size(), Qt::gray);
            update(); // Vẽ lại widget cha với dữ liệu ban đầu

            isHeapSortMode = true;
            // Khởi tạo trạng thái cho Heap Sort
            isSorting = true;
            heapSize = numbers.size();
            currentRoot = heapSize / 2 - 1;
            swapIndex = heapSize - 1;
            isColorCur = false;
            isColorLeft = false;
            isColorRight = false;
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc
            // Tạo QTimer để điều khiển animation
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::HeapSortAnimation);
            animationTimer->start(400); // Cài đặt khoảng thời gian mỗi bước
            break;}

        case 3: // InsertionSort
            {numbers = {31, 4, 3, 27, 28, 15, 45, 41, 11, 19};
            colors.resize(numbers.size(), Qt::gray);
            update(); // Vẽ lại widget cha với dữ liệu ban đầu
            i = 1; // Bắt đầu từ phần tử thứ 2
            isComparing = true;  // Trạng thái so sánh hoặc chèn
            movingUp = false;   // Trạng thái di chuyển lên
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::InsertionSortAnimation);
            animationTimer->start(400); // Cài đặt khoảng thời gian mỗi bước
            break;}

        case 4: // InterchangeSort
            {numbers = {31, 4, 3, 27, 28, 15, 45, 41, 11, 19};
            colors.resize(numbers.size(), Qt::gray);
            update(); // Vẽ lại widget cha với dữ liệu ban đầu
            i = 0;
            j = 1;
            isComparing = true;  // Trạng thái so sánh hoặc chènc
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::InterchangeAnimation);
            animationTimer->start(400); // Cài đặt khoảng thời gian mỗi bước
            break;}

        case 5: // Merge Sort
            {numbers = {31, 4, 3, 27, 28, 15, 45, 41, 11, 19}; // Dữ liệu ban đầu cho Merge Sort
            colors.resize(numbers.size(), Qt::gray); // Thiết lập màu sắc ban đầu cho các phần tử
            update(); // Vẽ lại widget với dữ liệu ban đầu

            // Khởi tạo lại chỉ số bước
            isSorting = false;
            isMergeSortMode = true;
            areadyStart = 0;
            j = 0;
            movingUp = false;
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc
            // Khởi tạo và kết nối animation timer
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::MergeSortAnimation);
            animationTimer->start(400); // Cài đặt khoảng thời gian mỗi bước
            break;}

        case 6: // QuickSort
            {numbers = {23, 34, 18, 36, 38, 15, 10, 20, 30, 19};
            colors.resize(numbers.size(), Qt::gray);
            update(); // Vẽ lại widget cha với dữ liệu ban đầu
            i = 0;
            pivotIndex = -1;             // Vị trí pivot hiện tại
            left = -1;                   // Chỉ số bên trái đang kiểm tra
            right = -1;                  // Chỉ số bên phải đang kiểm tra
            isPartitioning = false;     // Trạng thái đang chia đoạn
            lastSmall = -1;              // Chỉ số phần tử bé hơn pivot
            areadyStart = 0;
            swapped = true;
            // Khởi tạo và kết nối animation timer
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::QuickSortAnimation);
            animationTimer->start(400); // Cài đặt khoảng thời gian mỗi bước
            break;}

        case 7: // SelectionSort
            {numbers = {13, 17, 24, 38, 45, 2, 23, 32, 41, 4};
            colors.resize(numbers.size(), Qt::gray);
            update(); // Vẽ lại widget cha với dữ liệu ban đầu
            i = 0;
            j = 0;
            minIdx = -1;   // Vị trí phần tử nhỏ nhất
            isFindingMin = true; // Trạng thái tìm phần tử nhỏ nhất
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::SelectionSortAnimation);
            animationTimer->start(400); // Cài đặt khoảng thời gian mỗi bước
            break;}

        case 8: // ShellSort
            {numbers = {31, 4, 3, 27, 28, 15, 45, 41, 11, 19};
            colors.resize(numbers.size(), Qt::gray);
            update(); // Vẽ lại widget cha với dữ liệu ban đầu
            i = 5;
            isComparing = true;
            movingUp = false;
            gapIndex = 0;
            groupStart = 0;
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::ShellSortAnimation);
            animationTimer->start(400); // Cài đặt khoảng thời gian mỗi bước
            break;}

        case 9: // Counting Sort
            {numbers = {5, 4, 8, 5, 5, 1, 2, 1, 7, 7};
            colors.resize(numbers.size(), Qt::gray); // Reset màu sắc ban đầu
            colorsCount.resize(count.size(), Qt::gray); // Reset màu sắc ban đầu
            colorsOutput.resize(output.size(), Qt::gray); // Reset màu sắc ban đầu
            update(); // Vẽ lại widget với dữ liệu ban đầu
            max = *std::max_element(numbers.begin(), numbers.end());
            min = *std::min_element(numbers.begin(), numbers.end());
            count.resize(max - min + 1, 0);
            output.resize(numbers.size(), 0);
            currentInputIndex = 0;
            currentCountIndex = 0;
            currentOutputIndex = -1;
            isCountingMode = true;
            phase = 0; // Giai đoạn khởi tạo của Counting Sort
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc ban đầu
            colorsCount.assign(count.size(), Qt::gray); // Reset màu sắc ban đầu
            colorsOutput.assign(output.size(), Qt::gray); // Reset màu sắc ban đầu
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::CountingSortAnimation);
            animationTimer->start(400); // Mỗi bước thực hiện trong 400ms
            break;}

        case 10: //Radix Sort
            {numbers = {1399, 8047, 9739, 2657, 600, 3288, 998, 5575, 1140, 6304};
            colorsBucket.resize(10, Qt::black); // Reset màu sắc ban đầu
            colors.resize(numbers.size(), Qt::white); // Reset màu sắc ban đầu
            isRadixSortMode = true;
            buckets.resize(10); // 10 khay từ 0 đến 9
            currentDigitIndex = 0;
            currentNumberIndex = 0;
            phase = 0;
            i = 0;
            tempIndex = 0;
            colorsBucket.assign(10, Qt::black); // Reset màu sắc ban đầu
            colors.assign(numbers.size(), Qt::white);
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::RadixSortAnimation);
            animationTimer->start(400); // Mỗi bước thực hiện trong 400ms
            break;}

        case 11: //BucketSort
            {numbers = {31, 4, 3, 27, 28, 15, 45, 41, 11, 19};
            // Reset trạng thái ban đầu
            buckets.resize(10);  // 10 khay từ 0 đến 9
            colorsBucket.resize(5, Qt::black); // Reset màu sắc ban đầu
            colors.resize(numbers.size(), Qt::white); // Reset màu sắc ban đầu
            isRadixSortMode = true;
            currentNumberIndex = 0;
            currentBucketIndex = 0;
            currentDigitIndex = 3;
            phase = 0;  // Giai đoạn thêm số vào khay
            i = 0;
            key = 0;
            tempIndex = 1;
            colors.assign(numbers.size(), Qt::white);  // Màu mặc định cho mảng
            colorsBucket.assign(5, Qt::black);  // Màu mặc định cho khay
            // Thiết lập timer cho animation
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::BucketSortAnimation);
            animationTimer->start(400);  // Tốc độ mỗi bước 400ms
            break;}

        case 12: // FlashSort
            {numbers = {31, 4, 3, 27, 28, 15, 45, 41, 11, 19};
            // Reset trạng thái ban đầu
            colors.assign(numbers.size(), Qt::white); // Reset màu sắc ban đầu
            colorsCount.assign(5, Qt::black);       // Reset màu sắc các bucket
            count.clear();

            // // Thiết lập các biến cần thiết
            phase = 0;
            currentNumberIndex = 0;
            currentBucketIndex = 0;
            currentCountIndex = 0;
            currentIndex = 0;
            flashValue = 0;
            numMoves = 0;
            isFlashSortMode = true;

            // Tính toán giá trị nhỏ nhất và lớn nhất
            min = *std::min_element(numbers.begin(), numbers.end());
            max = *std::max_element(numbers.begin(), numbers.end());
            scaleFactor = (double)(5 - 1) / (max - min);

            // Khởi tạo bucket và count
            count.resize(5, 0);
            colorsCount.resize(5, Qt::white);

            // Thiết lập timer cho animation
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::FlashSortAnimation);
            animationTimer->start(400); // Tốc độ mỗi bước 400ms
            break;
        }

        case 13: // ShakerSort
            {numbers = {31, 4, 3, 27, 28, 15, 45, 41, 11, 19};
            colors.resize(numbers.size(), Qt::gray);
            update(); // Vẽ lại widget cha với dữ liệu ban đầu
            i = 0;
            j = 0;
            left = 0;
            right = numbers.size() - 1;
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc
            isSorting = true; // Bắt đầu quá trình sắp xếp
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &inforOfSort::ShakerSortAnimation);
            animationTimer->start(400); // Cài đặt khoảng thời gian mỗi bước
            break;}

        default:
            qDebug() << "Unsupported algorithm selected.";
            break;
    }
}


// Animation của BubbleSort
void inforOfSort::BubbleAnimation() {
    if (i >= numbers.size() - 1) {
        animationTimer->stop(); // Dừng khi hoàn tất
        delete animationTimer;
        animationTimer = nullptr;

        // Đánh dấu tất cả cột thành màu xanh lá (đã sắp xếp)
        std::fill(colors.begin(), colors.end(), Qt::green);
        update(); // Vẽ lại toàn bộ widget
        isSorting = false;       // Đặt lại trạng thái
        return;
    }
    if (j < numbers.size() - i - 1) {
        if (isComparing) {
            // Đánh dấu cột đang so sánh bằng màu đỏ
            colors[j] = Qt::red;
            colors[j + 1] = Qt::red;
            update(); // Cập nhật giao diện để hiển thị màu đỏ
            isComparing = false; // Chuyển sang bước tiếp theo
            return;
        }

        // Tiến hành so sánh và đổi chỗ nếu cần
        if (numbers[j] > numbers[j + 1]) {
            std::swap(numbers[j], numbers[j + 1]);
        }

        // Reset màu sau khi xử lý
        colors[j] = Qt::gray;
        colors[j + 1] = Qt::gray;

        // Đánh dấu màu xanh lá cho phần tử đã hoàn tất
        if (j + 1 == numbers.size() - i - 1) {
            colors[j + 1] = Qt::green;
        }

        ++j;
        isComparing = true; // Quay lại bước so sánh
    } else {
        colors[j] = Qt::green; // Hoàn tất cho phần tử đang xét
        j = 0;
        ++i;
    }

    update(); // Vẽ lại toàn bộ widget
}

// Animation của InsertionSort
void inforOfSort::InsertionSortAnimation() {
    if (i >= numbers.size()) {
        // Dừng khi hoàn tất sắp xếp
        animationTimer->stop();
        delete animationTimer;
        animationTimer = nullptr;

        // Đánh dấu tất cả các cột thành màu xanh lá (đã sắp xếp)
        std::fill(colors.begin(), colors.end(), Qt::green);
        update();
        isSorting = false; // Đặt lại trạng thái
        return;
    }

    if (isComparing) {
        // Lấy key và bắt đầu so sánh
        key = numbers[i];
        tempIndex = i - 1;

        // Đánh dấu phần tử đang được xét để chèn bằng màu đỏ
        colors.assign(numbers.size(), Qt::gray);  // Reset màu sắc
        for (int k = 0; k < i; ++k) {
            colors[k] = Qt::yellow;  // Tô màu vàng cho các phần tử đã sắp xếp
        }
        colors[i] = Qt::red;  // Tô màu đỏ cho phần tử đang xét
        update();

        isComparing = false; // Chuyển sang trạng thái chèn
        movingUp = true;     // Chuẩn bị di chuyển lên
        verticalOffset = 0;  // Reset độ dịch chuyển
        return;
    }

    if (movingUp) {
        // Di chuyển cột đang xét lên trên
        if (verticalOffset < 5) {
            verticalOffset = 5;
            update(); // Vẽ lại với độ dịch chuyển
            movingUp = false; // Bắt đầu trạng thái chèn
        }
        return;
    }

    if (tempIndex >= 0 && numbers[tempIndex] > key) {
        // Dịch chuyển phần tử lớn hơn sang phải
        temp = numbers[tempIndex + 1];
        numbers[tempIndex + 1] = numbers[tempIndex];
        numbers[tempIndex] = temp;
        // Đánh dấu phần tử đang so sánh
        colors[tempIndex] = Qt::red;  // Phần tử đang so sánh
        colors[tempIndex + 1] = Qt::yellow;  // Phần tử được dịch chuyển
        update();

        --tempIndex; // Lùi vị trí để so sánh tiếp
    } else {
        // Chèn key vào vị trí đúng (hạ xuống)
        if (verticalOffset > 0) {
            verticalOffset = 0; // Hạ dần
            numbers[tempIndex + 1] = key;

            // Reset màu sắc và tô màu vàng cho các phần tử đã sắp xếp
            colors.assign(numbers.size(), Qt::gray);
            for (int k = 0; k <= i; ++k) {
                colors[k] = Qt::yellow;  // Tô màu vàng cho các phần tử đã sắp xếp
            }
            update();

            ++i;          // Chuyển sang phần tử tiếp theo
            isComparing = true; // Quay lại trạng thái so sánh
        }
    }
}

// Animation của SelectionSort
void inforOfSort::SelectionSortAnimation() {
    if (i >= numbers.size()) {
        // Dừng khi hoàn tất sắp xếp
        animationTimer->stop();
        delete animationTimer;
        animationTimer = nullptr;

        // Tô màu xanh tất cả các phần tử đã sắp xếp
        std::fill(colors.begin(), colors.end(), Qt::green);
        update();
        isSorting = false; // Đặt lại trạng thái
        return;
    }

    if (isFindingMin) {
        // Giai đoạn tìm phần tử nhỏ nhất
        if (j < numbers.size()) {
            if (numbers[j] < numbers[minIdx] || minIdx == -1) {
                if (minIdx != -1) {
                    colors[minIdx] = Qt::gray; // Reset màu của phần tử trước đó
                }
                minIdx = j; // Cập nhật chỉ số nhỏ nhất
                colors[minIdx] = Qt::red; // Tô màu đỏ phần tử nhỏ nhất hiện tại
            }
            ++j; // Tiếp tục tìm kiếm

            if(minIdx != j - 1){
                colors[j - 1] = Qt::gray;
            }
            if(j == numbers.size()){
                isFindingMin = false;
                j = i; // Reset j để sử dụng trong bước đổi chỗ
            } else {
                colors[j] = Qt::yellow;
            }
        }
    } else {
        // Giai đoạn đổi chỗ
        if (minIdx != i) {
            std::swap(numbers[i], numbers[minIdx]);
        }

        // Đặt màu xanh cho phần tử đã sắp xếp
        colors[minIdx] = Qt::gray; // Reset màu cho minIdx (nếu không phải i)
        colors[i] = Qt::green;

        // Chuyển sang phần tử tiếp theo
        ++i;
        j = i; // Bắt đầu tìm minIdx từ i+1
        minIdx = -1;
        isFindingMin = true; // Quay lại tìm phần tử nhỏ nhất
    }
    update(); // Cập nhật giao diện
}

// Animation của QuickSort
void inforOfSort::QuickSortAnimation() {
    // Trạng thái ban đầu là toàn mảng
    if (subarrays.empty() && areadyStart == 0 && lastSmall == -1) {
        subarrays.push({0, numbers.size() - 1});
    }
    // Trạng thái kết thúc
    if (subarrays.empty() && areadyStart == 1 && isPartitioning == false) {
        // Nếu không còn đoạn nào để xử lý, hoàn tất sắp xếp
        animationTimer->stop();
        delete animationTimer;
        animationTimer = nullptr;
        pivotIndex = -1;             // Vị trí pivot hiện tại
        left = -1;                   // Chỉ số bên trái đang kiểm tra
        right = -1;
        lastSmall = -1;                   // Chỉ số phần tử bé hơn pivot
        areadyStart = 0;
        // Tô màu xanh cho tất cả phần tử (đã sắp xếp)
        std::fill(colors.begin(), colors.end(), Qt::green);
        update();
        isSorting = false;
        return;
    } else {
        if (!isPartitioning) {
            auto [start, end] = subarrays.top();
            subarrays.pop();
            if (start >= end) {
                // Nếu đoạn chỉ có 1 phần tử, đánh dấu màu xanh
                colors[start] = Qt::green;
                update();
                return;
            }

            // Thiết lập trạng thái cho việc phân đoạn
            pivotIndex = start;
            left = start + 1;
            right = end;
            i = left;
            lastSmall = left;

            // Tô màu đỏ cho pivot
            colors[pivotIndex] = Qt::red;
            isPartitioning = true; // Bắt đầu phân đoạn
            update();
            return;
        }

        if (isPartitioning) {
            while(i <= right){
                if (numbers[i] > numbers[pivotIndex]){
                    colors[i] = Qt::magenta;
                    update();
                    ++i;
                    return;
                } else {
                    colors[i] = Qt::yellow;
                    update();
                    if (i != lastSmall){
                        if(swapped){
                            swapped = false;
                            return;
                        }
                        std::swap(numbers[i], numbers[lastSmall]);
                        std::swap(colors[i], colors[lastSmall]);
                        swapped = true;
                        lastSmall++;
                        ++i;
                        return;
                    } else {
                        lastSmall++;
                        ++i;
                        return;
                    }
                }
            }
            // Đưa pivot về đúng vị trí
            std::swap(numbers[pivotIndex], numbers[lastSmall - 1]);
            colors[lastSmall - 1] = Qt::green;      // Pivot ở đúng vị trí -> màu xanh
            update();

            // Tô lại màu xám cho các phần tử chưa xử lý
            for (int k = pivotIndex; k <= right; ++k) {
                if (colors[k] != Qt::green) {
                    colors[k] = Qt::gray;
                }
            }

            // Chia thành 2 đoạn bên trái và phải
            subarrays.push({lastSmall, right});
            subarrays.push({pivotIndex, lastSmall - 2});
            areadyStart = 1;
            // Reset trạng thái
            isPartitioning = false;
            pivotIndex = -1;
            update();
        }
    }
}

// Animation của InterchangeSort
void inforOfSort::InterchangeAnimation() {
    if (i >= numbers.size() - 1) {
        animationTimer->stop(); // Stop when finished
        delete animationTimer;
        animationTimer = nullptr;

        // Mark all columns as green (sorted)
        std::fill(colors.begin(), colors.end(), Qt::green);
        update(); // Redraw the entire widget
        isSorting = false; // Reset the state
        return;
    }

    if (j < numbers.size()) {
        if (isComparing) {
            // Highlight the columns being compared in red
            colors[i] = Qt::red;
            colors[j] = Qt::red;
            update(); // Update the interface to show red
            isComparing = false; // Move to the next step
            return;
        }

        // Perform the comparison and swap if necessary
        if (j > i && numbers[j] < numbers[i]) {
            std::swap(numbers[j], numbers[i]);
        }

        // Reset color after processing
        colors[i] = Qt::gray;
        colors[j] = Qt::gray;

        // Mark the element as green if it is in the correct position
        if (j == numbers.size() - 1) {
            colors[i] = Qt::green; // Mark the current element as sorted
            ++i; // Move to the next element
            j = i + 1; // Start comparing with the next element
        } else {
            ++j; // Move to the next element for comparison
        }

        isComparing = true; // Go back to the comparison step
    }

    update(); // Redraw the entire widget
}

// Animation của ShellSort
void inforOfSort::ShellSortAnimation() {
    static std::vector<int> gaps = {5, 3, 1}; // Các khoảng gap cố định

    int gap = gaps[gapIndex]; // Khoảng gap hiện tại

    if (groupStart >= gap) {
        if(gapIndex + 1 == 3){
            // Hoàn tất tất cả các khoảng gap
            animationTimer->stop();
            delete animationTimer;
            animationTimer = nullptr;

            // Đánh dấu tất cả các cột thành màu xanh lá (đã sắp xếp)
            std::fill(colors.begin(), colors.end(), Qt::green);
            update();

            // Reset trạng thái
            gapIndex = 0;
            groupStart = 0;
            i = 0;
            isSorting = false;
            return;
        }
        // Chuyển sang khoảng gap tiếp theo
        groupStart = 0;
        gap = gaps[++gapIndex];
        i = gaps[gapIndex];

    }

    if (i >= numbers.size()) {
        // Chuyển sang nhóm tiếp theo
        groupStart++;
        if(groupStart < gap){
            i = groupStart + gap;
            colors.assign(numbers.size(), Qt::gray);
            for (int k = groupStart; k < numbers.size(); k += gap) {
                colors[k] = Qt::yellow; // Nhóm đang xử lý
            }
            update();
        } else if(gapIndex + 1 < 3) {
            colors.assign(numbers.size(), Qt::gray);
            for (int k = 0; k < numbers.size(); k += gaps[gapIndex + 1]) {
                colors[k] = Qt::yellow; // Nhóm đang xử lý
            }
            update();
        }
        return;
    }

    if (isComparing) {
        // Tô màu nhóm hiện tại
        colors.assign(numbers.size(), Qt::gray);
        for (int k = groupStart; k < numbers.size(); k += gap) {
            colors[k] = Qt::yellow; // Nhóm đang xử lý
        }
        colors[i] = Qt::red; // Phần tử đang xét
        update();

        // Kiểm tra xem có cần nâng không
        if (i >= gap && numbers[i - gap] > numbers[i]) {
            // Lấy phần tử key để chèn
            key = numbers[i];
            tempIndex = i - gap;
            isComparing = false; // Chuyển sang trạng thái chèn
            movingUp = true;
            verticalOffset = 0;
        } else {
            // Không cần chèn, chuyển sang phần tử tiếp theo
            i += gap;
        }
        return;
    }

    if (movingUp) {
        verticalOffset = 5; // Đảm bảo luôn đặt giá trị cố định
        update();
        movingUp = false; // Bắt đầu trạng thái chèn
        return;
    }

    if (tempIndex >= groupStart && numbers[tempIndex] > key) {
        // Dịch chuyển phần tử lớn hơn sang phải
        std::swap(numbers[tempIndex + gap], numbers[tempIndex]);
        // Tô màu phần tử đang di chuyển
        colors[tempIndex] = Qt::red;          // Đang so sánh
        colors[tempIndex + gap] = Qt::yellow; // Đã dịch chuyển
        update();

        tempIndex -= gap; // Tiếp tục so sánh
    } else {
        verticalOffset = 0;
        // Chèn phần tử key vào vị trí đúng
        numbers[tempIndex + gap] = key;

        // Reset màu sắc
        colors.assign(numbers.size(), Qt::gray);
        for (int k = groupStart; k < numbers.size(); k += gap) {
            colors[k] = Qt::yellow; // Đánh dấu đã sắp xếp
        }
        update();

        i += gap;          // Chuyển sang phần tử tiếp theo trong nhóm
        isComparing = true; // Quay lại trạng thái so sánh
    }
}

// Animation của HeapSort
void inforOfSort::HeapSortAnimation() {
    static int largest;
    static int left;
    static int right;
    if (heapSize <= 1) {
        // Hoàn tất sắp xếp
        animationTimer->stop();
        delete animationTimer;
        animationTimer = nullptr;

        std::fill(colors.begin(), colors.end(), Qt::green);
        update();

        // Reset lại trạng thái
        isColorCur = false;
        isColorLeft = false;
        isColorRight = false;
        heapSize = numbers.size();
        currentRoot = heapSize / 2 - 1;
        swapIndex = heapSize - 1;
        isSorting = false;
        return;
    }

    if (currentRoot >= 0) {
        // Thực hiện heapify từ root hiện tại
        if(!isColorCur){
            largest = currentRoot;
            left = 2 * currentRoot + 1;
            right = 2 * currentRoot + 2;
            colors[largest] = Qt::red;
            update();
            isColorCur = true;
            return;
        }
        if (largest != currentRoot) {
            std::swap(numbers[currentRoot], numbers[largest]);
            colors[currentRoot] = Qt::cyan;
            colors[largest] = Qt::cyan;
            largest = currentRoot;
            update();
            return;
        }
        if(!isColorLeft){
            if (left < heapSize){
                colors[left] = Qt::yellow;
                if (numbers[left] > numbers[largest]) {
                    largest = left;
                }
            }
            isColorLeft = true;
            update();
            return;
        }

        if(!isColorRight){
            if (right < heapSize){
                colors[left] = Qt::gray;
                colors[right] = Qt::yellow;
                colors[largest] = Qt::red;
                if (numbers[right] > numbers[largest]) {
                    largest = right;
                }
            }
            isColorRight = true;
            update();
            return;
        }

        currentRoot--;
        colors[currentRoot] = Qt::red;
        isColorCur = false;
        isColorLeft = false;
        isColorRight = false;
        if (right < heapSize){
            colors[right] = Qt::gray;
        }
        if (left < heapSize){
            colors[left] = Qt::gray;
        }
        colors[largest] = Qt::gray;
    } else if (swapIndex > 0) {
        // Hoán đổi phần tử đầu tiên với phần tử cuối
        std::swap(numbers[0], numbers[swapIndex]);
        colors[swapIndex] = Qt::green; // Đánh dấu phần tử đã cố định
        colors[0] = Qt::gray;
        update();

        // Giảm kích thước heap và reset root
        heapSize--;
        currentRoot = heapSize / 2 - 1;
        swapIndex--;
    }
}

// Animation của ShakerSort
void inforOfSort::ShakerSortAnimation() {
    if (i >= numbers.size() - 1) {
        animationTimer->stop(); // Dừng khi hoàn tất
        delete animationTimer;
        animationTimer = nullptr;

        // Đánh dấu tất cả cột thành màu xanh lá (đã sắp xếp)
        std::fill(colors.begin(), colors.end(), Qt::green);
        update(); // Vẽ lại toàn bộ widget
        isSorting = false; // Đặt lại trạng thái
        return;
    }

    if (left < right) {
        // Tiến hành từ trái qua phải
        if (j < right) {
            if (isComparing) {
                // Đánh dấu cột đang so sánh bằng màu đỏ
                colors[j] = Qt::red;
                colors[j + 1] = Qt::red;
                update(); // Cập nhật giao diện
                isComparing = false;
                return;
            }

            // Tiến hành so sánh và đổi chỗ nếu cần
            if (numbers[j] > numbers[j + 1]) {
                std::swap(numbers[j], numbers[j + 1]);
            }

            // Reset màu sau khi xử lý
            colors[j] = Qt::gray;
            colors[j + 1] = Qt::gray;

            ++j; // Di chuyển sang phần tử tiếp theo
            isComparing = true;
        } else {
            // Khi hoàn thành một vòng từ trái qua phải, giảm chỉ số phải
            colors[right] = Qt::green;
            right--;
            j = right; // Đặt lại chỉ số j
            i++;
            std::swap(left, right);
        }
        update(); // Vẽ lại widget sau mỗi bước
    }

    if (left > right) {
        // Tiến hành từ phải qua trái
        if (j > right) {
            if (isComparing) {
                // Đánh dấu cột đang so sánh bằng màu đỏ
                colors[j] = Qt::red;
                colors[j - 1] = Qt::red;
                update(); // Cập nhật giao diện
                isComparing = false;
                return;
            }

            // Tiến hành so sánh và đổi chỗ nếu cần
            if (numbers[j] < numbers[j - 1]) {
                std::swap(numbers[j], numbers[j - 1]);
            }

            // Reset màu sau khi xử lý
            colors[j] = Qt::gray;
            colors[j - 1] = Qt::gray;

            --j; // Di chuyển sang phần tử tiếp theo
            isComparing = true;
        } else {
            // Khi hoàn thành một vòng từ phải qua trái, tăng chỉ số trái
            colors[right] = Qt::green;
            right++;
            i++;
            j = right; // Đặt lại chỉ số j
            std::swap(left, right);
        }
        update(); // Vẽ lại widget sau mỗi bước
    }
}

// Animation của MergeSort
void inforOfSort::MergeSortAnimation() {
    // Mảng lưu các màu sắc
    static std::vector<QColor> theColors = {Qt::darkGreen, Qt::blue, Qt::magenta, Qt::lightGray, Qt::red,
                                     Qt::green, Qt::white, Qt::darkYellow, Qt::darkCyan,Qt::darkBlue, Qt::darkGray};

    // Nếu chưa bắt đầu, khởi tạo stack với khoảng ban đầu
    if (subarrays.empty() && areadyStart == 0) {
        subarrays.push({0, numbers.size() - 1});
        colors.assign(numbers.size(), Qt::gray); // Màu xám ban đầu cho tất cả phần tử
    }

    // Trạng thái kết thúc
    if (subarrays.empty() && areadyStart == 1 && !isSorting) {
        areadyStart = 0;
        animationTimer->stop();
        delete animationTimer;
        animationTimer = nullptr;
        std::fill(colors.begin(), colors.end(), Qt::green); // Tô màu xanh cho toàn bộ mảng
        update();
        movingUp = false;
        return;
    }

    // Xử lý chia mảng
    if (!isSorting && !subarrays.empty()) {
        // Lấy một khoảng từ stack
        auto [start, end] = subarrays.top();
        subarrays.pop();
        areadyStart = 1;
        if (start < end) {
            int mid = (start + end) / 2;

            // Đưa các khoảng con vào stack
            subarrays.push({start, mid});
            subarrays.push({mid + 1, end});
            subarrays_support.push({start, end});
            // Đánh dấu màu sắc cho khoảng hiện tại
            for (int i = mid + 1; i <= end; ++i) {
                colors[i] = theColors[j % theColors.size()];
            }
            j++; // Chuyển sang màu tiếp the
            for (int i = start + 1; i <= mid; ++i) {
                colors[i] = theColors[j % theColors.size()];
            }
            j++; // Chuyển sang màu tiếp theo

            update(); // Cập nhật giao diện
            return;
        }

        // Nếu không còn mảng con nào để chia, chuyển sang trạng thái sắp xếp
        if (subarrays.empty()) {
            isSorting = true;
        }
    }

    // Khi tất cả các khoảng đã được chia hết, bắt đầu sắp xếp
    if (isSorting) {
        // Lấy một khoảng từ stack
        auto [start, end] = subarrays_support.top();

        if(!movingUp){
            for (int i = start; i <= end; ++i) {
                colors[i] = Qt::yellow;
            }
            verticalOffset = 5;
            update();
            movingUp = true;

            return;
        }
        // Sử dụng std::sort để sắp xếp khoảng hiện tại
        std::sort(numbers.begin() + start, numbers.begin() + end + 1);
        if(movingUp){
            for (int i = start; i <= end; ++i) {
                if(start == 0 && end == numbers.size() - 1){
                    colors[i] = Qt::green;
                } else {
                    colors[i] = Qt::cyan;
                }
            }
            verticalOffset = 0;
            update();

            movingUp = false;
            subarrays_support.pop();
            if (subarrays_support.empty()) {
                isSorting = false;
            }
            return;
        }
    }
}

// Animation của CountingSort
void inforOfSort::CountingSortAnimation() {
    if (phase == 0) {
        // Giai đoạn 1: Đếm số lượng
        if (currentInputIndex < numbers.size()) {
            count[numbers[currentInputIndex] - min]++;
            colors[currentInputIndex] = Qt::yellow; // Highlight phần tử đang được đếm
            currentInputIndex++;
            update();
        } else {
            currentInputIndex = 0;
            currentCountIndex = 0;
            phase = 1;
            for(int i = 0; i < numbers.size(); ++i){
                colors[i] = Qt::gray;
            }
        }
        return;
    }

    if (phase == 1) {
        // Giai đoạn 2: Tính tích lũy
        if (currentCountIndex < count.size() - 1) {
            count[currentCountIndex + 1] += count[currentCountIndex];
            colorsCount[currentCountIndex + 1] = Qt::cyan;
            colorsCount[currentCountIndex] = Qt::gray;
            currentCountIndex++;
            update();
        } else {
            colorsCount[currentCountIndex] = Qt::gray;
            currentInputIndex = numbers.size() - 1;
            phase = 2;
        }
        return;
    }

    if (phase == 2) {
        // Giai đoạn 3: Xây dựng mảng output
        if (currentInputIndex >= 0) {
            if(colors[currentInputIndex] != Qt::red){
                colors[currentInputIndex] = Qt::red;
                update();
                return;
            }
            if(colorsCount[numbers[currentInputIndex] - min] != Qt::cyan){
                colorsCount[numbers[currentInputIndex] - min] = Qt::cyan;
                update();
                return;
            }
            output[count[numbers[currentInputIndex] - min] - 1] = numbers[currentInputIndex];
            if(colorsOutput[count[numbers[currentInputIndex] - min] - 1] != Qt::green){
                colorsOutput[count[numbers[currentInputIndex] - min] - 1] = Qt::green;
                update();
                return;
            }
            if(colorsCount[numbers[currentInputIndex] - min] == Qt::cyan){
                colorsCount[numbers[currentInputIndex] - min] = Qt::gray;
                colors[currentInputIndex] = Qt::gray;
                count[numbers[currentInputIndex] - min] --;
                currentInputIndex--;
                update();
                return;
            }
        } else {
            phase = 3;
            colors.assign(numbers.size(), Qt::gray); // Reset màu sắc
            currentOutputIndex = 0;
            currentInputIndex = 0;
            return;
        }
    }

    if (phase == 3) {
        // Giai đoạn 4: Sao chép mảng output vào numbers
        if(currentInputIndex < numbers.size()){
            numbers[currentInputIndex] = output[currentOutputIndex];
            colors[currentInputIndex] = colorsOutput[currentOutputIndex];
            colorsOutput[currentOutputIndex] = Qt::yellow;
            currentInputIndex++;
            currentOutputIndex++;
            update();
            return;
        }
        std::fill(colors.begin(), colors.end(), Qt::green); // Tô màu xanh cho mảng đã sắp xếp
        std::fill(colorsCount.begin(), colorsCount.end(), Qt::gray);
        update();
        isSorting = false;
        animationTimer->stop();
        delete animationTimer;
        animationTimer = nullptr;
        output.clear();
        colorsOutput.clear();
        count.clear();
        colorsCount.clear();
        return;
    }
}

// Animation của RadixSort
void inforOfSort::RadixSortAnimation() {
    if (phase == 0) {
        // Chuyển số vào khay
        if (currentNumberIndex < numbers.size()) {
            int number = numbers[currentNumberIndex];
            int digit = (number / static_cast<int>(pow(10, currentDigitIndex))) % 10; // Lấy chữ số
            buckets[digit].push_back(number); // Thêm vào khay tương ứng
            numbers[currentNumberIndex] = 0;
            currentNumberIndex++;
        } else {
            // Chuyển sang giai đoạn lấy số từ khay
            currentNumberIndex = 0;
            phase = 1;
            i = 0;
        }
    } else if (phase == 1) {
        // Lấy số ra từ khay
        if (currentNumberIndex < 10) {
            colorsBucket[currentNumberIndex] = Qt::yellow;
            if(!buckets[currentNumberIndex].empty()) {
                numbers[i++] = buckets[currentNumberIndex][0]; // Lấy từ khay ra
                buckets[currentNumberIndex].erase(buckets[currentNumberIndex].begin()); // Xóa phần tử đầu tiên
                update();
                return;
            }
            currentNumberIndex++;
        } else {
            colorsBucket.assign(numbers.size(), Qt::black); // Reset màu sắc ban đầu
            colors.assign(numbers.size(), Qt::white);
            // Chuyển sang chữ số tiếp theo hoặc kết thúc
            currentDigitIndex++;
            if (currentDigitIndex >= 4) { // 4 chữ số đã hoàn tất
                colors.assign(numbers.size(), Qt::green);
                update();
                animationTimer->stop();
                delete animationTimer;
                animationTimer = nullptr;
                isSorting = false;
                return;
            } else {
                phase = 0;
                currentNumberIndex = 0;
            }
        }
    }
    update(); // Vẽ lại giao diện
}

// Animation của BucketSort
void inforOfSort::BucketSortAnimation() {
    if (phase == 0) {
        // Thêm số vào khay
        if (currentNumberIndex < numbers.size()) {
            int number = numbers[currentNumberIndex];
            int bucketIndex = number / 10;  // Số thuộc khay tương ứng (giả định chia cho 10 để lấy bucket)
            buckets[bucketIndex].push_back(number);  // Thêm số vào khay
            numbers[currentNumberIndex] = 0;
            colors[currentNumberIndex] = Qt::yellow;  // Đánh dấu số đang xử lý
            currentNumberIndex++;
        } else {
            // Chuyển sang phase lấy số từ khay
            phase = 1;
            currentNumberIndex = 0;
            currentBucketIndex = 0;
            colors.assign(numbers.size(), Qt::white);  // Reset màu sắc của mảng
        }
    } else if (phase == 1) {
        // Lấy số ra từ khay
        if (currentBucketIndex < 5 && buckets[currentBucketIndex].empty()) {
            currentBucketIndex++;  // Bỏ qua khay rỗng
        }
        if (currentBucketIndex < 5) {
            if(currentBucketIndex == 0){
                colorsBucket[4] = Qt::black;
                update();
            }
            if(key == 0){
                std::sort(buckets[currentBucketIndex].begin(), buckets[currentBucketIndex].end());
                for(int idx = 0; idx < 5; ++idx){
                    colorsBucket[idx] = Qt::black;
                }
                colorsBucket[currentBucketIndex] = Qt::yellow;
                currentBucketIndex++;
                if(currentBucketIndex == 5){
                    key = 1;
                    currentBucketIndex = 0;
                }
                update();
                return;
            }
            // Lấy số từ khay hiện tại
            numbers[i++] = buckets[currentBucketIndex].front();  // Lấy phần tử đầu tiên
            buckets[currentBucketIndex].erase(buckets[currentBucketIndex].begin());  // Xóa phần tử đầu tiên
            colors[i - 1] = Qt::green;  // Đánh dấu số đã lấy
            colorsBucket[currentBucketIndex] = Qt::yellow;  // Khay đang xử lý
        } else {
            // Hoàn tất bucket sort
            animationTimer->stop();
            delete animationTimer;
            animationTimer = nullptr;
            isSorting = false;
            phase = 0;
            // Reset trạng thái
            colorsBucket.assign(10, Qt::black);  // Khay trở về màu mặc định
            colors.assign(numbers.size(), Qt::green);  // Toàn bộ số có màu xanh (đã sắp xếp)
            qDebug() << "Bucket sort done!";
        }
    }

    update();  // Vẽ lại giao diện
}

// Animation của FlashSort
void inforOfSort::FlashSortAnimation() {
    if (phase == 0) {
        // Gán số lượng phần tử cho mỗi bucket
        if (currentNumberIndex < numbers.size()) {
            int number = numbers[currentNumberIndex];
            int bucketIndex = int(scaleFactor * (number - min));
            count[bucketIndex]++; // Đếm số lượng phần tử trong bucket
            colors[currentNumberIndex] = Qt::yellow; // Đổi màu phần tử đang xử lý
            currentNumberIndex++;
        } else {
            phase = 1; // Chuyển sang phase tính tích lũy
            currentNumberIndex = 0;
            currentCountIndex = 0;
        }
    } else if (phase == 1) {
        // Tích lũy số lượng
        if (currentCountIndex < count.size() - 1) {
            count[currentCountIndex + 1] += count[currentCountIndex];
            colorsCount[currentCountIndex + 1] = Qt::red; // Đổi màu bucket đang xử lý
            colorsCount[currentCountIndex] = Qt::black; // Đổi màu bucket đã xử lý
            currentCountIndex++;
        } else {
            colorsCount[4] = Qt::black;
            update();
            phase = 2; // Chuyển sang phase hoán vị
            currentIndex = 0;
            currentBucketIndex = 5 - 1;
            flashValue = 0;
            numMoves = 0;
        }
    } else if (phase == 2) {
        // Hoán vị vòng tròn
        if (numMoves < numbers.size() - 1) {
            while (currentIndex >= count[currentBucketIndex] && currentIndex < numbers.size()) {
                currentIndex++;
                currentBucketIndex = int(scaleFactor * (numbers[currentIndex] - min));
            }

            if (currentIndex < numbers.size()) {
                flashValue = numbers[currentIndex];
                while (currentIndex != count[currentBucketIndex]) {
                    currentBucketIndex = int(scaleFactor * (flashValue - min));
                    int temp = numbers[--count[currentBucketIndex]];
                    numbers[count[currentBucketIndex]] = flashValue;
                    flashValue = temp;
                    numMoves++;

                    // Đổi màu hiển thị
                    colors[currentIndex] = Qt::red; // Đánh dấu phần tử đang được flash
                    colors[count[currentBucketIndex]] = Qt::yellow; // Đánh dấu phần tử đích
                    update();
                }
            }
        } else {
            phase = 3; // Chuyển sang phase sắp xếp chèn
            currentNumberIndex = 1;
            colors.assign(numbers.size(), Qt::white); // Reset màu sắc
            update();
        }
    } else if (phase == 3) {
        // Sắp xếp chèn
        if (currentNumberIndex < numbers.size()) {
            key = numbers[currentNumberIndex];
            if(colors[currentNumberIndex] != Qt::red && colors[currentNumberIndex] != Qt::yellow){
                colors[currentNumberIndex] = Qt::red;
                j = currentNumberIndex - 1;
                update();
                return;
            }

            if (j >= 0 && numbers[j] > key) {
                // Dịch chuyển phần tử lớn hơn sang phải
                temp = numbers[j + 1];
                numbers[j + 1] = numbers[j];
                numbers[j] = temp;
                // Đánh dấu phần tử đang so sánh
                colors[j] = Qt::red;  // Phần tử đang so sánh
                colors[j + 1] = Qt::yellow;  // Phần tử được dịch chuyển
                update();

                --j; // Lùi vị trí để so sánh tiếp
            } else {
                for(int o = 0; o <= currentNumberIndex; ++o){
                    colors[o] = Qt::yellow;
                }
                currentNumberIndex++;
            }
        } else {
            animationTimer->stop();
            delete animationTimer;
            animationTimer = nullptr;
            isSorting = false;
            phase = 0;
            colors.assign(numbers.size(), Qt::green); // Toàn bộ số có màu xanh
            qDebug() << "Flash sort done!";
        }
    }
    update();
}






// Khung animation cho cột
void inforOfSort::paintEvent(QPaintEvent *event) {
    if (isHeapSortMode) {
        paintEvent_Heap(event); // Gọi chế độ Heap Sort
    } else if(isMergeSortMode){
        paintEvent_Merge(event);
    } else if(isCountingMode){
        paintEvent_Count(event);
    } else if(isRadixSortMode){
        paintEvent_Radix(event);
    } else if(isFlashSortMode){
        paintEvent_Flash(event);
    } else {
        QPainter painter(this);

        if (numbers.empty()) return;

        int widgetWidth = this->width() / 2;
        int widgetHeight = this->height() / 3;
        int startX = (this->width() - widgetWidth) / 2;
        int startY = (this->height() - widgetHeight) / 5;

        int columnWidth = widgetWidth / numbers.size();
        int maxNumber = *std::max_element(numbers.begin(), numbers.end());

        for (size_t k = 0; k < numbers.size(); ++k) {
            int columnHeight = (widgetHeight * numbers[k]) / maxNumber;

            int offset = (colors[k] == Qt::red) ? verticalOffset * 5 : 0;
            // Thiết lập màu sắc và vẽ
            painter.setBrush(colors[k]);
            // Vẽ hình chữ nhật với tọa độ gốc đã được dịc
            painter.drawRect(
                startX + k * columnWidth,
                startY + (widgetHeight - columnHeight) - offset,
                columnWidth - 5,
                columnHeight
                );

            painter.setPen(Qt::black);
            // Hiển thị số u mỗi cột
            painter.drawText(
                startX + k * columnWidth + (columnWidth - 5) / 4,
                startY + (widgetHeight - columnHeight) - 10 - offset,
                QString::number(numbers[k])
                );
        }
    }
}

// Khung animation cho Heap
void inforOfSort::paintEvent_Heap(QPaintEvent *event) {
    QPainter painter(this);

    if (numbers.empty()) return;

    // Vẽ cây nhị phân
    int rootX = this->width() * 3 / 4;
    int rootY = 70;
    int gapX = this->width() / 4;
    int gapY = 50;
    drawBinaryTree(painter, rootX, rootY, 1, 0, gapX, gapY);

    // Vẽ mảng
    int widgetHeight = this->height() / 4;
    int startX = 40;
    int columnWidth = 30;

    for (size_t k = 0; k < numbers.size(); ++k) {
        painter.setBrush(colors[k]);
        painter.drawRect(
            startX + k * columnWidth,
            widgetHeight + 20,
            columnWidth - 5,
            25
            );

        painter.setPen(Qt::black);
        painter.drawText(
            startX + k * columnWidth + 7,
            widgetHeight + 15,
            QString::number(numbers[k])
            );
    }
}

// Vẽ cây nhị phân
void inforOfSort::drawBinaryTree(QPainter &painter, int x, int y, int level, int index, int gapX, int gapY) {
    if (index >= numbers.size()) return;

    // Vẽ nút hiện tại
    int radius = 20;
    painter.setBrush(colors[index]);
    painter.drawEllipse(QPoint(x, y), radius, radius);

    // Hiển thị giá trị
    painter.setPen(Qt::black);
    painter.drawText(x - 5, y + 5, QString::number(numbers[index]));

    // Vẽ cạnh tới các nút con
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < numbers.size()) {
        // Tính góc của cạnh nối tâm gốc tới tâm con trái
        double angle = atan2(gapY, -gapX / (1 << level));
        int startX = x + radius * cos(angle); // Điểm bắt đầu trên viền gốc
        int startY = y + radius * sin(angle);
        int endX = x - gapX / (1 << level) - radius * cos(angle); // Điểm kết thúc trên viền con
        int endY = y + gapY - radius * sin(angle);

        // Vẽ đường nối
        painter.drawLine(startX, startY, endX, endY);
        // Vẽ cây con trái
        drawBinaryTree(painter, x - gapX / (1 << level), y + gapY, level + 1, leftChild, gapX, gapY);
    }

    if (rightChild < numbers.size()) {
        // Tính góc của cạnh nối tâm gốc tới tâm con phải
        double angle = atan2(gapY, gapX / (1 << level));
        int startX = x + radius * cos(angle); // Điểm bắt đầu trên viền gốc
        int startY = y + radius * sin(angle);
        int endX = x + gapX / (1 << level) - radius * cos(angle); // Điểm kết thúc trên viền con
        int endY = y + gapY - radius * sin(angle);

        // Vẽ đường nối
        painter.drawLine(startX, startY, endX, endY);
        // Vẽ cây con phải
        drawBinaryTree(painter, x + gapX / (1 << level), y + gapY, level + 1, rightChild, gapX, gapY);
    }
}

// Khung animation cho mảng
void inforOfSort::paintEvent_Merge(QPaintEvent *event)
{
    QPainter painter(this);

    if (numbers.empty()) return;

    // Vẽ mảng với các cột màu sắc
    int widgetHeight = this->height() / 5;
    int columnWidth = 50;
    int startX = (this->width() - 10 * columnWidth) / 2 + 5;


    for (size_t k = 0; k < numbers.size(); ++k) {
        int offset = (colors[k] == Qt::yellow) ? verticalOffset * 5 : 0;
        painter.setBrush(colors[k]);
        painter.drawRect(
            startX + k * columnWidth ,
            widgetHeight + 20 - offset,
            columnWidth - 10,
            40
            );

        painter.setPen(Qt::black);
        painter.drawText(
            startX + k * columnWidth + 17 ,
            widgetHeight + 15 - offset,
            QString::number(numbers[k])
            );
    }
}

// Khung animation cho CountingSort
void inforOfSort::paintEvent_Count(QPaintEvent *event){
    QPainter painter(this);
    int rectWidth = 30;    // Chiều rộng mỗi cột
    int spacing = 10;      // Khoảng cách giữa các cột
    int padding = 20;      // Khoảng cách giữa các mảng
    int baseY = 60;        // Vị trí y cơ bản
    int maxHeight = this->height() / 7; // Chiều cao tối đa của mỗi mảng

    // Vẽ mảng đầu vào (Input Array)
    painter.setPen(Qt::black);
    painter.drawText(this->width() / 3 - 110, baseY, "Input Array:");
    for (int i = 0; i < numbers.size(); ++i) {
        int x = this->width() / 3 - 40 + i * (rectWidth + spacing);
        if (x + rectWidth > this->width() - 20) break; // Dừng vẽ nếu vượt khung
        int height = std::min(numbers[i] * 5, maxHeight - 10);
        int y = baseY + maxHeight - 40 - height; // Vẽ từ đáy lên
        QRect rect(x, y, rectWidth, height);
        painter.setBrush(colors[i]);
        painter.drawRect(rect);
        painter.drawText(QPoint(x + rectWidth / 2, y - 10), QString::number(numbers[i])); // Giá trị hiển thị phía trên đỉnh
    }

    // Vẽ mảng đếm (Count Array)
    int countY = baseY + maxHeight - 20 + padding;
    painter.drawText(this->width() / 3 - 110, countY, "Count Array:");
    for (int i = 0; i < count.size(); ++i) {
        int x = this->width() / 3 - 30 + i * (rectWidth + spacing);
        if (x + rectWidth > this->width() - 20) break; // Dừng vẽ nếu vượt khung
        int height = std::min(count[i] * 5, maxHeight - 10);
        int y = countY + maxHeight - 40 - height; // Vẽ từ đáy lên
        QRect rect(x, y, rectWidth, height);
        painter.setBrush(colorsCount[i]);
        painter.drawRect(rect);
        painter.drawText(QPoint(x + rectWidth / 2, y - 10), QString::number(count[i])); // Giá trị hiển thị phía trên đỉnh
        painter.drawText(
            QPoint(x + rectWidth / 2, countY + maxHeight - 27), // Tọa độ y phía dưới
            QString::number(i + 1) // Chỉ số từ 1 đến 8
        );
    }

    // Vẽ mảng kết quả (Output Array)
    int outputY = countY + maxHeight - 30 + padding;
    painter.drawText(this->width() / 3 - 110, outputY, "Output Array:");
    for (int i = 0; i < output.size(); ++i) {
        int x = this->width() / 3 - 40 + i * (rectWidth + spacing);
        if (x + rectWidth > this->width() - 20) break; // Dừng vẽ nếu vượt khung
        int height = std::min(output[i] * 5, maxHeight - 10);
        int y = outputY + maxHeight - 40 - height; // Vẽ từ đáy lên
        QRect rect(x, y, rectWidth, height);
        painter.setBrush(colorsOutput[i]);
        painter.drawRect(rect);
        painter.drawText(QPoint(x + rectWidth / 2, y - 7), QString::number(output[i])); // Giá trị hiển thị phía trên đỉnh
        painter.drawText(
            QPoint(x + rectWidth / 2, outputY + maxHeight - 27), // Tọa độ y phía dưới
            QString::number(i + 1) // Chỉ số từ 1 đến 8
        );
    }
}






// Khung animation cho RadixSort & BucketSort
void inforOfSort::paintEvent_Radix(QPaintEvent *event) {
    QPainter painter(this);

    int rectWidth = 50;     // Chiều rộng mỗi cột
    int spacing = 10;       // Khoảng cách giữa các cột
    int baseY = 100;        // Vị trí y cơ bản
    int bucketY = 250;      // Vị trí y của khay
    int bucketHeight = 3;   // Chiều cao của khay

    QFont font = painter.font();
    font.setPointSize(12); // Đặt kích thước font lớn hơn
    painter.setFont(font);

    // Vẽ mảng ban đầu
    painter.drawText(20, baseY - 20, "Numbers:");
    for (int i = 0; i < numbers.size(); ++i) {
        int x = this->width() / 8 + i * (rectWidth + spacing);
        QRect rect(x, baseY, rectWidth, 50);
        painter.setBrush(colors[i]);
        painter.drawRect(rect);

        if (numbers[i] != 0) {
            QString numberStr = QString::number(numbers[i]); // Chuyển số thành chuỗi
            for (int j = 0; j < numberStr.size(); ++j) {
                int digit = (numbers[i] / static_cast<int>(pow(10, numberStr.size() - j - 1))) % 10; // Lấy chữ số

                // Tọa độ để hiển thị chữ số
                int digitX = x + rectWidth / 4 + j * 10 - 7;
                int digitY = baseY + 25;

                // Chọn màu đỏ cho chữ số tại vị trí currentDigitIndex
                if (j == numberStr.size() - currentDigitIndex - 1) {
                    painter.setPen(Qt::red);
                } else {
                    painter.setPen(Qt::black);
                }

                painter.drawText(QPoint(digitX, digitY), QString::number(digit));
                painter.setPen(Qt::black);
            }
        }
    }

    painter.setPen(Qt::black); // Trở lại màu mặc định
    // Vẽ các khay
    if(tempIndex == 0){
        for (int i = 0; i < 10; ++i) {
            int x = this->width() / 8 + i * (rectWidth + spacing);
            QRect bucketRect(x, bucketY, rectWidth, bucketHeight);
            painter.drawText(
                QPoint(x + rectWidth / 2 - 6, bucketY + 18), // Tọa độ y phía dưới
                QString::number(i) // Chỉ số từ 0 đến 9
                );
            painter.setBrush(colorsBucket[i]);
            painter.drawRect(bucketRect);
            // Hiển thị các số trong khay
            for (int j = 0; j < buckets[i].size(); ++j) {
                int y = bucketY - (bucketHeight + 10) - j * 20;
                QString numberStr = QString::number(buckets[i][j]); // Chuyển số thành chuỗi

                for (int k = 0; k < numberStr.size(); ++k) {
                    int digit = (buckets[i][j] / static_cast<int>(pow(10, numberStr.size() - k - 1))) % 10; // Lấy chữ số

                    // Tọa độ để hiển thị chữ số trong khay
                    int digitX = x + rectWidth / 4 + k * 10 - 5; // Chỉnh vị trí theo chiều ngang
                    int digitY = y;

                    // Chọn màu đỏ cho chữ số tại vị trí currentDigitIndex
                    if (k == numberStr.size() - currentDigitIndex - 1) {
                        painter.setPen(Qt::red);
                    } else {
                        painter.setPen(Qt::black);
                    }

                    painter.drawText(QPoint(digitX, digitY), QString::number(digit));
                    painter.setPen(Qt::black);
                }
            }
        }
    } else if(tempIndex == 1) {
        for (int i = 0; i < 5; ++i) {
            int x = this->width() / 8 + i * (rectWidth + spacing) * 2;
            QRect bucketRect(x, bucketY, rectWidth, bucketHeight);
            painter.drawText(
                QPoint(x + rectWidth / 2 - 6, bucketY + 18), // Tọa độ y phía dưới
                QString::number(i) // Chỉ số từ 0 đến 4
                );
            painter.setBrush(colorsBucket[i]);
            painter.drawRect(bucketRect);
            // Hiển thị các số trong khay
            for (int j = 0; j < buckets[i].size(); ++j) {
                int y = bucketY - (bucketHeight + 10) - j * 20;
                painter.drawText(x + rectWidth / 4, y, QString::number(buckets[i][j]));
            }
        }
    }

}

void inforOfSort::paintEvent_Flash(QPaintEvent *event) {
    QPainter painter(this);

    int rectWidth = 50;     // Chiều rộng mỗi cột
    int spacing = 10;       // Khoảng cách giữa các cột
    int baseY = 100;        // Vị trí y cơ bản
    int bucketY = 230;      // Vị trí y của khay
    int bucketHeight = 3;   // Chiều cao của khay

    // Vẽ mảng ban đầu
    painter.drawText(20, baseY - 20, "Numbers:");
    for (int i = 0; i < numbers.size(); ++i) {
        int x = this->width() / 8 + i * (rectWidth + spacing);
        QRect rect(x, baseY, rectWidth, 50);
        painter.setBrush(colors[i]);
        painter.drawRect(rect);
        painter.drawText(x + rectWidth / 4, baseY + 25, QString::number(numbers[i]));
    }

    // Vẽ các bucket
    painter.drawText(20, bucketY + 10, "BucketsCount:");
    for (int i = 0; i < 5; ++i) {
        int x = this->width() / 8 + 25 + i * (rectWidth + spacing) * 2 ;
        QRect bucketRect(x, bucketY, rectWidth, bucketHeight);
        painter.setBrush(colorsCount[i]);
        painter.drawRect(bucketRect);
        painter.drawText(x + rectWidth / 4 + 7, bucketY + 15, QString::number(count[i]));
    }
}




// Dừng và xóa toàn bộ trạng thái animation
void inforOfSort::stopAnimation() {

    if (animationTimer) {
        animationTimer->stop();
        delete animationTimer;
        animationTimer = nullptr;
    }
    isSorting = false;


    isHeapSortMode = false;
    isMergeSortMode = false;
    isCountingMode = false;
    isRadixSortMode = false;
    numberToAnimation = 0;
    verticalOffset = 0;

    // Xóa dữ liệu và màu sắc
    numbers.clear();
    colors.clear();
    i = 0;
    j = 0;

    // Đặt lại các biến tĩnh trong BubbleAnimation
    isComparing = true;

    // Đặt lại các biến tĩnh trong InsertionSortAnimation
    movingUp = false;


    // Đặt lại các biến tĩnh trong SelectionSortAnimation
    minIdx = -1;   // Vị trí phần tử nhỏ nhất
    isFindingMin = true;

    // Đặt lại các biến tĩnh trong QuickSortAnimation
    pivotIndex = -1;             // Vị trí pivot hiện tại
    left = -1;                   // Chỉ số bên trái đang kiểm tra
    right = -1;                  // Chỉ số bên phải đang kiểm tra
    lastSmall = -1;              // Chỉ số phần tử bé hơn pivot
    areadyStart = 0;             // Trạng thái bắt đầu
    swapped = true;              // Trạng thái hoán đổi
    while (!subarrays.empty()) {
        subarrays.pop(); // Remove all elements from the stack
    }

    // Đặt lại các biến tĩnh trong HeapSortAnimation
    isColorCur = false;
    isColorLeft = false;
    isColorRight = false;

    // Đặt lại các biến tĩnh trong MergeSortAnimation
    while (!subarrays_support.empty()) {
        subarrays_support.pop(); // Remove all elements from the stack
    }

    // Đặt lại các biến tĩnh trong CountingSortAnimation
    phase = 0; // Reset trạng thái
    currentInputIndex = 0;
    currentCountIndex = 0;
    currentOutputIndex = -1;
    output.clear();
    colorsOutput.clear();
    count.clear();
    colorsCount.clear();
    // Đặt lại các biến tĩnh trong RadixSortAnimation
    currentDigitIndex = 0;
    currentNumberIndex = 0;
    phase = 0;
    buckets.clear();
    colorsBucket.clear();
    // Đặt lại các biến tĩnh trong FlashSortAnimation
    isFlashSortMode = false;
    update();
}

// In ra thông tin thuật toán
void inforOfSort::setNumSort(int num){
    numberToAnimation = num; // Lưu kiểu thuật toán
    switch (num){
    case 1:
        ui->lblinforSort->setText("Bubble Sort(Sắp xếp nổi bọt)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;<b>Cách hoạt động:</b> Thuật toán duyệt qua mảng, so sánh từng cặp phần tử liền kề và hoán đổi chúng nếu chúng không theo thứ tự mong muốn. "
            "Quá trình này tiếp tục cho đến khi không có sự hoán đổi nào xảy ra trong một vòng lặp, tức là mảng đã được sắp xếp.<br>"
            "<br><b style='font-size: x-large;'>Ưu điểm của Bubble Sort:</b><br>"
            "&emsp;&emsp;<b>1. Đơn giản và dễ hiểu:</b><br>"
            "&emsp;&emsp;&emsp;- Thuật toán rất dễ cài đặt và hiểu vì nó không đòi hỏi nhiều kỹ thuật phức tạp.<br>"
            "&emsp;&emsp;&emsp;- Dễ dàng triển khai và sử dụng cho các bài toán đơn giản.<br>"
            "&emsp;&emsp;<b>2. Không yêu cầu bộ nhớ bổ sung:</b><br>"
            "&emsp;&emsp;&emsp;- Bubble Sort không yêu cầu bộ nhớ bổ sung ngoài bộ nhớ của mảng cần sắp xếp.<br>"
            "&emsp;&emsp;&emsp;- Nó là một thuật toán ổn định, nghĩa là nếu hai phần tử có giá trị bằng nhau, chúng vẫn giữ nguyên thứ tự tương đối sau khi sắp xếp.<br>"
            "&emsp;&emsp;<b>3. Tối ưu hóa khi mảng đã sắp xếp:</b><br>"
            "&emsp;&emsp;&emsp;- Nếu trong một vòng lặp không có sự hoán đổi nào, thuật toán sẽ kết thúc sớm, giúp giảm số vòng lặp và tăng hiệu quả khi mảng gần như đã được sắp xếp.<br>"
            "<br><b style='font-size: x-large;'>Nhược điểm của Bubble Sort:</b><br>"
            "&emsp;&emsp;<b>1. Hiệu suất kém với độ phức tạp O(n²):</b><br>"
            "&emsp;&emsp;&emsp;- Độ phức tạp của Bubble Sort trong trường hợp tồi tệ và trung bình là O(n²), với n là số phần tử trong mảng. Điều này làm cho thuật toán không thích hợp cho mảng có số lượng phần tử lớn.<br>"
            "&emsp;&emsp;&emsp;- Mặc dù thuật toán có thể dừng sớm nếu không có sự hoán đổi, nhưng trong hầu hết các trường hợp, nó vẫn phải duyệt qua mảng nhiều lần, gây tốn thời gian.<br>"
            "&emsp;&emsp;<b>2. Chậm khi xử lý mảng lớn:</b><br>"
            "&emsp;&emsp;&emsp;- Với độ phức tạp O(n²), Bubble Sort trở nên rất chậm khi n tăng lên. Ví dụ, nếu mảng có 1000 phần tử, thuật toán sẽ phải thực hiện khoảng 1 triệu phép toán trong trường hợp xấu nhất.<br>"
            "&emsp;&emsp;<b>3. Không tối ưu với dữ liệu ngẫu nhiên:</b><br>"
            "&emsp;&emsp;&emsp;- Với các mảng ngẫu nhiên hoặc mảng lớn chưa được sắp xếp, thuật toán sẽ hoạt động kém hiệu quả hơn nhiều so với các thuật toán sắp xếp khác như Quick Sort, Merge Sort hay Heap Sort.<br>"
            );
        break;
    case 2:
        ui->lblinforSort->setText("Heap sort (Sắp xếp vun đống)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;<b>Cách hoạt động:</b> Đầu tiên chuyển đổi mảng thành một heap tối đa bằng cách sử dụng <i>heapify</i>. "
            "Xin lưu ý rằng điều này xảy ra tại chỗ. Các phần tử mảng được sắp xếp lại để tuân theo các thuộc tính heap. "
            "Sau đó, từng cái một xóa nút gốc của Max-heap và thay thế nó bằng nút cuối cùng và <i>heapify</i>. "
            "Lặp lại quá trình này trong khi kích thước của heap lớn hơn 1.<br>"
            "&emsp;&emsp;- Sắp xếp lại các phần tử mảng sao cho chúng tạo thành Max Heap.<br>"
            "&emsp;&emsp;- Lặp lại các bước sau cho đến khi đống chỉ chứa một phần tử:<br>"
            "&emsp;&emsp;&emsp;1. Hoán đổi phần tử gốc của heap (là phần tử lớn nhất trong heap hiện tại) với phần tử cuối cùng của heap.<br>"
            "&emsp;&emsp;&emsp;2. Xóa phần tử cuối cùng của heap (bây giờ ở đúng vị trí). Giảm kích thước heap và không xóa phần tử khỏi mảng thực tế.<br>"
            "&emsp;&emsp;&emsp;3. Xếp chồng các phần tử còn lại của heap.<br>"
            "&emsp;&emsp;- Cuối cùng chúng ta có được mảng đã được sắp xếp.<br>"
            "<br><b style='font-size: x-large;'>Ưu điểm của Heap Sort:</b><br>"
            "&emsp;&emsp;<b>1. Độ phức tạp thời gian hiệu quả:</b><br>"
            "&emsp;&emsp;&emsp;- Heap Sort có độ phức tạp thời gian là O(n log n) trong mọi trường hợp. "
            "Điều này làm cho nó hiệu quả khi sắp xếp các tập dữ liệu lớn. Hệ số log n xuất phát từ chiều cao của heap nhị phân và nó đảm bảo rằng thuật toán duy trì hiệu suất tốt ngay cả với số lượng phần tử lớn.<br>"
            "&emsp;&emsp;<b>2. Sử dụng bộ nhớ:</b><br>"
            "&emsp;&emsp;&emsp;- Sử dụng bộ nhớ có thể ở mức tối thiểu (bằng cách viết <i>heapify()</i> lặp lại thay vì đệ quy). "
            "Ngoài danh sách ban đầu các mục cần sắp xếp, nó không cần thêm không gian bộ nhớ để hoạt động.<br>"
            "&emsp;&emsp;<b>3. Tính đơn giản:</b><br>"
            "&emsp;&emsp;&emsp;- Dễ hiểu hơn các thuật toán sắp xếp hiệu quả tương đương khác vì nó không sử dụng các khái niệm khoa học máy tính nâng cao như đệ quy.<br>"
            "<br><b style='font-size: x-large;'>Nhược điểm của Heap Sort:</b><br>"
            "&emsp;&emsp;<b>1. Tốn kém:</b><br>"
            "&emsp;&emsp;&emsp;- Sắp xếp heap tốn kém hơn vì các hằng số cao hơn so với sắp xếp trộn ngay cả khi độ phức tạp thời gian là O(n log n) cho cả hai.<br>"
            "&emsp;&emsp;<b>2. Không ổn định:</b><br>"
            "&emsp;&emsp;&emsp;- Sắp xếp heap không ổn định. Nó có thể sắp xếp lại thứ tự tương đối.<br>"
            "&emsp;&emsp;<b>3. Không hiệu quả:</b><br>"
            "&emsp;&emsp;&emsp;- Sắp xếp heap không thực sự hiệu quả vì độ phức tạp thời gian có hằng số cao.<br>"
            );
        break;
    case 3:
        ui->lblinforSort->setText("Insertion sort (Sắp xếp chèn)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;<b>Cách hoạt động:</b><br>"
            "&emsp;&emsp;&emsp;- Bắt đầu với phần tử thứ hai (index 1) trong mảng, vì phần tử đầu tiên luôn coi như đã được sắp xếp.<br>"
            "&emsp;&emsp;&emsp;- So sánh phần tử hiện tại với các phần tử trước nó, và dịch chuyển các phần tử lớn hơn một vị trí về phía sau.<br>"
            "&emsp;&emsp;&emsp;- Chèn phần tử hiện tại vào đúng vị trí của nó trong dãy đã sắp xếp.<br>"
            "&emsp;&emsp;&emsp;- Tiếp tục với phần tử tiếp theo và lặp lại quá trình cho đến khi toàn bộ mảng được sắp xếp.<br>"
            "<br><b style='font-size: x-large;'>Ưu điểm của Insertion Sort:</b><br>"
            "&emsp;&emsp;<b>1. Đơn giản và dễ hiểu:</b><br>"
            "&emsp;&emsp;&emsp;- Thuật toán rất dễ triển khai và có thể dễ dàng giải thích.<br>"
            "&emsp;&emsp;<b>2. Sắp xếp tốt đối với dữ liệu đã gần như được sắp xếp:</b><br>"
            "&emsp;&emsp;&emsp;- Nếu mảng đã được sắp xếp gần như hoàn chỉnh (chỉ có vài phần tử sai vị trí), thuật toán sẽ hoạt động rất nhanh, với thời gian chạy gần như là O(n).<br>"
            "&emsp;&emsp;<b>3. Không yêu cầu không gian bổ sung:</b><br>"
            "&emsp;&emsp;&emsp;- Insertion Sort là một thuật toán sắp xếp tại chỗ (in-place), nghĩa là không cần bộ nhớ phụ ngoài các phần tử trong mảng.<br>"
            "&emsp;&emsp;<b>4. Tốt cho mảng nhỏ:</b><br>"
            "&emsp;&emsp;&emsp;- Đối với các mảng có số lượng phần tử nhỏ, Insertion Sort có thể nhanh hơn so với các thuật toán sắp xếp phức tạp hơn như Merge Sort hay Quick Sort.<br>"
            "<br><b style='font-size: x-large;'>Nhược điểm của Insertion Sort:</b><br>"
            "&emsp;&emsp;<b>1. Hiệu suất kém với mảng lớn:</b><br>"
            "&emsp;&emsp;&emsp;- Trong trường hợp mảng có kích thước lớn và không được sắp xếp sẵn, thời gian chạy của Insertion Sort sẽ là O(n²). Điều này khiến thuật toán kém hiệu quả với mảng có kích thước lớn.<br>"
            "&emsp;&emsp;<b>2. Thực hiện nhiều phép so sánh và dịch chuyển:</b><br>"
            "&emsp;&emsp;&emsp;- Nếu dữ liệu không gần như đã sắp xếp, thuật toán sẽ phải thực hiện nhiều phép so sánh và dịch chuyển, điều này làm giảm hiệu suất so với các thuật toán khác.<br>"
            "&emsp;&emsp;<b>3. Không thích hợp với mảng lớn và không thể song song hóa:</b><br>"
            "&emsp;&emsp;&emsp;- Vì việc sắp xếp là tuyến tính theo chiều dài của mảng, Insertion Sort không thể được tối ưu hóa tốt cho các hệ thống đa lõi.<br>"
            );
        break;
    case 4:
        ui->lblinforSort->setText("Interchange sort (Sắp xếp đổi chỗ)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;<b>Cách hoạt động:</b><br>"
            "&emsp;&emsp;&emsp;- Thuật toán duyệt qua tất cả các phần tử trong mảng.<br>"
            "&emsp;&emsp;&emsp;- Tại mỗi phần tử (vị trí i), thuật toán so sánh nó với tất cả các phần tử sau nó (vị trí j).<br>"
            "&emsp;&emsp;&emsp;- Nếu phần tử tại vị trí j nhỏ hơn phần tử tại vị trí i, hai phần tử này được hoán đổi chỗ cho nhau.<br>"
            "&emsp;&emsp;&emsp;- Tiếp tục quá trình này cho đến khi toàn bộ mảng được sắp xếp.<br>"
            "&emsp;&emsp;&emsp;- Quy trình này được lặp lại cho tất cả các phần tử trong mảng cho đến khi không còn sự thay đổi nào trong mảng, nghĩa là mảng đã được sắp xếp.<br>"
            "<br><b style='font-size: x-large;'>Ưu điểm của Interchange Sort:</b><br>"
            "&emsp;&emsp;1. <b>Đơn giản và dễ hiểu:</b><br>"
            "&emsp;&emsp;&emsp;- Thuật toán rất dễ cài đặt và hiểu, đặc biệt là đối với người mới học lập trình.<br>"
            "&emsp;&emsp;&emsp;- Mã nguồn của thuật toán rất đơn giản và trực quan.<br>"
            "&emsp;&emsp;2. <b>Không cần bộ nhớ phụ trợ (in-place sorting):</b><br>"
            "&emsp;&emsp;&emsp;- Interchange Sort không cần sử dụng bộ nhớ phụ ngoài mảng đã cho, tức là sắp xếp in-place.<br>"
            "&emsp;&emsp;&emsp;- Điều này giúp tiết kiệm bộ nhớ khi làm việc với các mảng lớn (mặc dù không hiệu quả về thời gian).<br>"
            "&emsp;&emsp;3. <b>Dễ dàng tối ưu:</b><br>"
            "&emsp;&emsp;&emsp;- Dễ dàng tối ưu bằng cách thêm một điều kiện để thoát khỏi vòng lặp nếu không có sự thay đổi nào trong một lần lặp qua mảng.<br>"
            "<br><b style='font-size: x-large;'>Nhược điểm của Interchange Sort:</b><br>"
            "&emsp;&emsp;1. <b>Độ phức tạp thời gian cao (O(n²)):</b><br>"
            "&emsp;&emsp;&emsp;- Thuật toán có độ phức tạp thời gian là O(n²), tức là thời gian thực hiện sẽ tăng theo cấp số bậc 2 khi số lượng phần tử tăng lên.<br>"
            "&emsp;&emsp;&emsp;- Điều này làm cho Interchange Sort không hiệu quả khi làm việc với các mảng lớn.<br>"
            "&emsp;&emsp;2. <b>Số lần hoán đổi cao:</b><br>"
            "&emsp;&emsp;&emsp;- Thuật toán thực hiện rất nhiều phép hoán đổi, đặc biệt đối với các mảng không sắp xếp, dẫn đến thời gian thực thi chậm.<br>"
            "&emsp;&emsp;3. <b>Không ổn định:</b><br>"
            "&emsp;&emsp;&emsp;- Interchange Sort không phải là một thuật toán ổn định, có nghĩa là thứ tự tương đối của các phần tử giống nhau có thể thay đổi trong quá trình sắp xếp.<br>"
            );
        break;
    case 5:
        ui->lblinforSort->setText("Merge sort (Sắp xếp trộn)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;1. <b>Cách hoạt động:</b><br>"
            "&emsp;&emsp;&emsp;- Chia: Mảng ban đầu được chia thành hai nửa cho đến khi mỗi mảng chỉ chứa một phần tử.<br>"
            "&emsp;&emsp;&emsp;- Sắp xếp: Các mảng con đã được chia này sau đó được sắp xếp. Vì mỗi mảng con chỉ có một phần tử, chúng đã được coi là đã được sắp xếp.<br>"
            "&emsp;&emsp;&emsp;- Trộn (Merge): Sau khi các mảng con được sắp xếp, thuật toán bắt đầu trộn chúng lại thành các mảng lớn hơn cho đến khi tất cả các phần tử được trộn vào một mảng duy nhất.<br>"
            "<br><b style='font-size: x-large;'>Ưu điểm của Merge Sort:</b><br>"
            "&emsp;&emsp;1. <b>Độ phức tạp thời gian ổn định:</b><br>"
            "&emsp;&emsp;&emsp;- Merge Sort có độ phức tạp thời gian là O(n log n) trong cả ba trường hợp (tốt nhất, trung bình và xấu nhất), làm cho nó rất ổn định trong các tình huống khác nhau.<br>"
            "&emsp;&emsp;2. <b>Sắp xếp ổn định:</b><br>"
            "&emsp;&emsp;&emsp;- Merge Sort là một thuật toán sắp xếp ổn định, có nghĩa là nếu hai phần tử có giá trị bằng nhau, chúng vẫn giữ nguyên thứ tự tương đối trong mảng.<br>"
            "&emsp;&emsp;3. <b>Thích hợp với sắp xếp các mảng lớn:</b><br>"
            "&emsp;&emsp;&emsp;- Với đặc điểm không bị ảnh hưởng bởi sắp xếp ban đầu của dữ liệu, Merge Sort rất hiệu quả đối với các mảng lớn.<br>"
            "<br><b style='font-size: x-large;'>Nhược điểm của Merge Sort:</b><br>"
            "&emsp;&emsp;1. <b>Cần bộ nhớ phụ:</b><br>"
            "&emsp;&emsp;&emsp;- Merge Sort yêu cầu một lượng bộ nhớ phụ lớn, vì cần phải sao chép các mảng con trong quá trình trộn. Điều này có thể là vấn đề trong các hệ thống với bộ nhớ hạn chế.<br>"
            "&emsp;&emsp;2. <b>Không phải là thuật toán \"sắp xếp tại chỗ\":</b><br>"
            "&emsp;&emsp;&emsp;- Merge Sort không phải là thuật toán sắp xếp tại chỗ (in-place sorting). Điều này có nghĩa là nó không sắp xếp trực tiếp trên mảng ban đầu mà phải sử dụng bộ nhớ phụ.<br>"
            "&emsp;&emsp;3. <b>Tốc độ:</b><br>"
            "&emsp;&emsp;&emsp;- Mặc dù Merge Sort có độ phức tạp thời gian tốt, nhưng trong thực tế, đối với các mảng nhỏ hoặc dữ liệu đã được sắp xếp gần như hoàn chỉnh, các thuật toán khác như Quick Sort hoặc Insertion Sort có thể hoạt động nhanh hơn.<br>"
            );
        break;
    case 6:
        ui->lblinforSort->setText("Quick Sort (Sắp xếp nhanh)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;Quick Sort là một thuật toán sắp xếp phân chia và trị hiệu quả, sử dụng kỹ thuật chia mảng thành hai phần và sắp xếp độc lập.<br>"
            "&emsp;&emsp;<b>Cách hoạt động:</b><br>"
            "&emsp;&emsp;&emsp;- Chọn một phần tử làm chốt (pivot).<br>"
            "&emsp;&emsp;&emsp;- Phân chia mảng thành hai phần: các phần tử nhỏ hơn chốt được đưa vào bên trái, lớn hơn chốt đưa vào bên phải.<br>"
            "&emsp;&emsp;&emsp;- Gọi đệ quy sắp xếp các phần còn lại.<br>"
            "<br><b style='font-size: x-large;'>Ưu điểm:</b><br>"
            "&emsp;&emsp;<b>1. Hiệu quả với mảng lớn:</b><br>"
            "&emsp;&emsp;&emsp;- Độ phức tạp trung bình là O(n log n), rất nhanh khi làm việc với mảng lớn.<br>"
            "&emsp;&emsp;<b>2. Sử dụng tốt bộ nhớ:</b><br>"
            "&emsp;&emsp;&emsp;- Không yêu cầu nhiều bộ nhớ phụ, chỉ cần không gian phụ thuộc vào độ sâu của đệ quy.<br>"
            "&emsp;&emsp;<b>3. Linh hoạt:</b><br>"
            "&emsp;&emsp;&emsp;- Hoạt động tốt trên nhiều loại dữ liệu và tình huống.<br>"
            "<br><b style='font-size: x-large;'>Nhược điểm:</b><br>"
            "&emsp;&emsp;<b>1. Phụ thuộc vào chốt (pivot):</b><br>"
            "&emsp;&emsp;&emsp;- Lựa chọn chốt không tốt có thể dẫn đến hiệu suất O(n²) trong trường hợp xấu nhất.<br>"
            "&emsp;&emsp;<b>2. Không ổn định:</b><br>"
            "&emsp;&emsp;&emsp;- Quick Sort không bảo toàn thứ tự của các phần tử bằng nhau.<br>"
            "&emsp;&emsp;<b>3. Cần đệ quy:</b><br>"
            "&emsp;&emsp;&emsp;- Đệ quy sâu có thể gây ra vấn đề về stack overflow với mảng rất lớn.<br>"
            );
        break;
    case 7:
        ui->lblinforSort->setText("Selection sort (Sắp xếp chọn)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;<b>Cách hoạt động:</b><br>"
            "&emsp;&emsp;&emsp;- Bắt đầu từ phần tử đầu tiên của mảng, tìm phần tử nhỏ nhất trong phần còn lại của mảng.<br>"
            "&emsp;&emsp;&emsp;- Đổi chỗ phần tử nhỏ nhất tìm được với phần tử ở vị trí đầu tiên.<br>"
            "&emsp;&emsp;&emsp;- Di chuyển chỉ số bắt đầu lên một vị trí tiếp theo và lặp lại quá trình tìm phần tử nhỏ nhất trong phần còn lại của mảng.<br>"
            "&emsp;&emsp;&emsp;- Quá trình lặp lại cho đến khi toàn bộ mảng đã được sắp xếp.<br>"
            "<br><b style='font-size: x-large;'>Ưu điểm:</b><br>"
            "&emsp;&emsp;<b>1. Đơn giản:</b><br>"
            "&emsp;&emsp;&emsp;- Thuật toán rất dễ hiểu và dễ cài đặt.<br>"
            "&emsp;&emsp;<b>2. Ít bộ nhớ:</b><br>"
            "&emsp;&emsp;&emsp;- Không cần bộ nhớ phụ (chỉ sử dụng một vài biến tạm để lưu trữ chỉ số), vì vậy thuật toán này không yêu cầu bộ nhớ bổ sung lớn.<br>"
            "<br><b style='font-size: x-large;'>Nhược điểm:</b><br>"
            "&emsp;&emsp;<b>1. Hiệu suất kém:</b><br>"
            "&emsp;&emsp;&emsp;- Độ phức tạp thời gian là O(n²), vì vậy thuật toán này không hiệu quả cho các mảng lớn.<br>"
            "&emsp;&emsp;<b>2. Không tận dụng được các tình huống đã sắp xếp:</b><br>"
            "&emsp;&emsp;&emsp;- Dù mảng đã gần như sắp xếp, thuật toán vẫn tiếp tục quét hết mảng và thực hiện các phép trao đổi không cần thiết.<br>"
            "&emsp;&emsp;<b>3. Tốn thời gian đổi chỗ:</b><br>"
            "&emsp;&emsp;&emsp;- Mặc dù số lượng trao đổi phần tử có thể ít hơn so với một số thuật toán khác (như Bubble Sort), nhưng vẫn còn khá nhiều trong các trường hợp mảng chưa sắp xếp.<br>"
            );
        break;
    case 8:
        ui->lblinforSort->setText("Shell sort (Sắp xếp vỏ sò)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;<b>1. Khởi tạo khoảng cách (gap):</b><br>"
            "&emsp;&emsp;&emsp;- Một dãy số (ví dụ: n/2, n/4, ..., 1 hoặc dãy Hibbard 2<sup>k</sup>-1) được sử dụng để xác định khoảng cách giữa các phần tử cần so sánh.<br>"
            "&emsp;&emsp;<b>2. Sắp xếp từng phần theo khoảng cách:</b><br>"
            "&emsp;&emsp;&emsp;- Với mỗi giá trị gap, chia mảng thành nhiều nhóm phần tử cách nhau gap. Thực hiện Insertion Sort trên các nhóm này.<br>"
            "&emsp;&emsp;<b>3. Giảm dần gap:</b><br>"
            "&emsp;&emsp;&emsp;- Giảm giá trị gap dần đến khi gap = 1. Khi đó, mảng đã gần như được sắp xếp, và Insertion Sort sẽ hoàn tất công việc.<br>"
            "&emsp;&emsp;<b>4. Hoàn tất:</b><br>"
            "&emsp;&emsp;&emsp;- Khi gap = 1, toàn bộ mảng được sắp xếp theo thứ tự tăng dần.<br>"
            "<br><b style='font-size: x-large;'>Ưu điểm của Shell Sort:</b><br>"
            "&emsp;&emsp;<b>1. Cải thiện so với Insertion Sort:</b><br>"
            "&emsp;&emsp;&emsp;- Ở bước cuối cùng (khi gap = 1), mảng đã gần như được sắp xếp, giúp Insertion Sort hoạt động hiệu quả hơn.<br>"
            "&emsp;&emsp;<b>2. Hiệu suất khá tốt trên các mảng kích thước trung bình:</b><br>"
            "&emsp;&emsp;&emsp;- Với dãy gap hợp lý, Shell Sort có thể đạt độ phức tạp tốt hơn O(n<sup>2</sup>), đặc biệt là khi sử dụng dãy Hibbard hoặc Sedgewick.<br>"
            "&emsp;&emsp;<b>3. Đơn giản và dễ triển khai:</b><br>"
            "&emsp;&emsp;&emsp;- Shell Sort không yêu cầu bộ nhớ bổ sung ngoài mảng gốc.<br>"
            "&emsp;&emsp;<b>4. Có thể tối ưu với các dãy gap khác nhau:</b><br>"
            "&emsp;&emsp;&emsp;- Hiệu năng phụ thuộc vào dãy gap được sử dụng. Dãy gap tốt có thể cải thiện đáng kể tốc độ sắp xếp.<br>"
            "<br><b style='font-size: x-large;'>Nhược điểm của Shell Sort:</b><br>"
            "&emsp;&emsp;<b>1. Phụ thuộc vào dãy gap:</b><br>"
            "&emsp;&emsp;&emsp;- Hiệu năng không ổn định nếu chọn dãy gap không tốt. Một dãy gap không tối ưu có thể dẫn đến hiệu năng tương đương O(n<sup>2</sup>).<br>"
            "&emsp;&emsp;<b>2. Không phải là thuật toán ổn định:</b><br>"
            "&emsp;&emsp;&emsp;- Shell Sort không đảm bảo giữ nguyên thứ tự các phần tử bằng nhau (vì các phần tử có thể được hoán đổi ở các bước với gap lớn).<br>"
            "&emsp;&emsp;<b>3. Hiệu suất kém trên mảng lớn:</b><br>"
            "&emsp;&emsp;&emsp;- Dù tốt hơn Insertion Sort, Shell Sort vẫn kém hơn các thuật toán sắp xếp hiệu quả hơn như Merge Sort hoặc Quick Sort khi làm việc với mảng lớn.<br>"
            "&emsp;&emsp;<b>4. Khó phân tích:</b><br>"
            "&emsp;&emsp;&emsp;- Độ phức tạp và hiệu năng của Shell Sort phụ thuộc nhiều vào dãy gap, làm cho việc phân tích và cải thiện khó khăn hơn so với các thuật toán khác.<br>"
            );
        break;
    case 9:
        ui->lblinforSort->setText("Counting Sort (Sắp xếp đếm)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;Counting Sort là thuật toán sắp xếp không so sánh (non-comparison sort), dựa trên việc đếm số lần xuất hiện của mỗi phần tử để xác định vị trí của chúng trong mảng đã sắp xếp.<br>"
            "<br><b style='font-size: large;'>Cách làm cụ thể:</b><br>"
            "&emsp;&emsp;<b>1.</b> Tìm giá trị lớn nhất và nhỏ nhất:<br>"
            "&emsp;&emsp;&emsp;- Tính khoảng giá trị (range = max - min + 1) để xây dựng mảng đếm.<br><br>"
            "&emsp;&emsp;<b>2.</b> Tạo mảng đếm (count array):<br>"
            "&emsp;&emsp;&emsp;- Với mỗi giá trị trong mảng đầu vào, tăng giá trị tương ứng tại vị trí (value - min) trong mảng đếm.<br><br>"
            "&emsp;&emsp;<b>3.</b> Tính mảng tổng tích lũy:<br>"
            "&emsp;&emsp;&emsp;- Tính tổng tích lũy từ mảng đếm để xác định vị trí cuối cùng của mỗi phần tử trong mảng đã sắp xếp.<br><br>"
            "&emsp;&emsp;<b>4.</b> Sắp xếp đầu ra:<br>"
            "&emsp;&emsp;&emsp;- Duyệt ngược mảng đầu vào để duy trì tính ổn định, sử dụng mảng tổng tích lũy để đặt từng phần tử vào đúng vị trí.<br><br>"
            "&emsp;&emsp;<b>5.</b> Cập nhật mảng gốc:<br>"
            "&emsp;&emsp;&emsp;- Sao chép mảng kết quả vào mảng đầu vào.<br><br>"
            "<b style='font-size: x-large;'>Ưu điểm của Counting Sort:</b><br><br>"
            "&emsp;&emsp;<b>1.</b> Độ phức tạp thấp:<br>"
            "&emsp;&emsp;&emsp;- Thời gian thực thi là O(n + k), trong đó:<br>"
            "&emsp;&emsp;&emsp;&emsp;+ n: số lượng phần tử.<br>"
            "&emsp;&emsp;&emsp;&emsp;+ k: phạm vi giá trị (max - min + 1).<br>"
            "&emsp;&emsp;&emsp;- Không cần so sánh trực tiếp giữa các phần tử.<br><br>"
            "&emsp;&emsp;<b>2.</b> Hiệu quả với dữ liệu nhỏ và phạm vi hẹp:<br>"
            "&emsp;&emsp;&emsp;- Khi giá trị lớn nhất và nhỏ nhất gần nhau (phạm vi nhỏ), thuật toán hoạt động rất nhanh.<br><br>"
            "&emsp;&emsp;<b>3.</b> Tính ổn định:<br>"
            "&emsp;&emsp;&emsp;- Counting Sort có thể duy trì thứ tự tương đối của các phần tử bằng nhau trong mảng gốc.<br><br>"
            "<b style='font-size: x-large;'>Nhược điểm của Counting Sort:</b><br><br>"
            "&emsp;&emsp;<b>1.</b> Không hiệu quả với phạm vi giá trị rộng:<br>"
            "&emsp;&emsp;&emsp;- Nếu phạm vi giá trị lớn so với số lượng phần tử, mảng đếm sẽ chiếm nhiều bộ nhớ, làm tăng chi phí lưu trữ.<br><br>"
            "&emsp;&emsp;<b>2.</b> Chỉ áp dụng cho dữ liệu rời rạc:<br>"
            "&emsp;&emsp;&emsp;- Counting Sort không phù hợp với dữ liệu liên tục (như số thực) mà chỉ áp dụng cho dữ liệu nguyên hoặc dữ liệu có thể ánh xạ sang số nguyên.<br><br>"
            "&emsp;&emsp;<b>3.</b> Không thích hợp cho các bài toán lớn:<br>"
            "&emsp;&emsp;&emsp;- Với mảng lớn hoặc dữ liệu có phạm vi giá trị rộng, thuật toán kém hiệu quả so với các phương pháp sắp xếp tiên tiến khác như Merge Sort hoặc Quick Sort.<br>"
            );
        break;
    case 10:
        ui->lblinforSort->setText("Radix Sort (Sắp xếp cơ sở)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;Radix Sort là thuật toán sắp xếp không so sánh, hoạt động bằng cách sắp xếp các phần tử theo từng chữ số của chúng, bắt đầu từ chữ số ít quan trọng nhất (least significant digit) cho đến chữ số quan trọng nhất (most significant digit).<br>"
            "<br><b style='font-size: large;'>Cách làm cụ thể:</b><br>"
            "&emsp;&emsp;<b>1.</b> Chọn chữ số (digit):<br>"
            "&emsp;&emsp;&emsp;- Sắp xếp các phần tử theo chữ số tại một vị trí nhất định (ví dụ: hàng đơn vị, hàng chục, hàng trăm).<br><br>"
            "&emsp;&emsp;<b>2.</b> Định dạng lại mảng:<br>"
            "&emsp;&emsp;&emsp;- Dùng một thuật toán sắp xếp ổn định (như Counting Sort) để sắp xếp các phần tử theo từng chữ số.<br><br>"
            "&emsp;&emsp;<b>3.</b> Tiến hành với các chữ số tiếp theo:<br>"
            "&emsp;&emsp;&emsp;- Tiến hành sắp xếp tiếp theo các chữ số quan trọng hơn cho đến khi tất cả các chữ số đều được xử lý.<br><br>"
            "&emsp;&emsp;<b>4.</b> Kết quả:<br>"
            "&emsp;&emsp;&emsp;- Sau khi sắp xếp hết tất cả các chữ số, mảng sẽ được sắp xếp hoàn chỉnh.<br><br>"
            "<b style='font-size: x-large;'>Ưu điểm của Radix Sort:</b><br>"
            "&emsp;&emsp;<b>1.</b> Hiệu suất tốt với các số nguyên:<br>"
            "&emsp;&emsp;&emsp;- Radix Sort có thể sắp xếp nhanh chóng khi số lượng chữ số ít và mảng không quá lớn.<br><br>"
            "&emsp;&emsp;<b>2.</b> Không yêu cầu so sánh trực tiếp:<br>"
            "&emsp;&emsp;&emsp;- Thuật toán không sử dụng các phép so sánh trực tiếp giữa các phần tử.<br><br>"
            "&emsp;&emsp;<b>3.</b> Ổn định:<br>"
            "&emsp;&emsp;&emsp;- Radix Sort là một thuật toán sắp xếp ổn định, nghĩa là các phần tử bằng nhau sẽ giữ nguyên thứ tự tương đối.<br><br>"
            "&emsp;&emsp;<b>4.</b> Hiệu quả với các mảng có phạm vi nhỏ:<br>"
            "&emsp;&emsp;&emsp;- Nếu các phần tử có số chữ số ít, Radix Sort có thể đạt được hiệu suất rất tốt.<br><br>"
            "<b style='font-size: x-large;'>Nhược điểm của Radix Sort:</b><br>"
            "&emsp;&emsp;<b>1.</b> Tốn bộ nhớ:<br>"
            "&emsp;&emsp;&emsp;- Radix Sort cần một lượng bộ nhớ lớn cho các mảng phụ trợ trong mỗi bước sắp xếp.<br><br>"
            "&emsp;&emsp;<b>2.</b> Không hiệu quả với số thực:<br>"
            "&emsp;&emsp;&emsp;- Radix Sort không thích hợp để sắp xếp số thực hoặc các loại dữ liệu không phải là số nguyên.<br><br>"
            "&emsp;&emsp;<b>3.</b> Giới hạn khi mảng có phạm vi quá lớn:<br>"
            "&emsp;&emsp;&emsp;- Nếu số lượng chữ số lớn hoặc phạm vi giá trị rất lớn, Radix Sort có thể không hiệu quả.<br>"
            );
        break;
    case 11:
        ui->lblinforSort->setText("Bucket sort (Sắp xếp thùng)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "<b style='font-size: large;'>Cách hoạt động:</b><br>"
            "&emsp;&emsp;<b>1. Chia dữ liệu vào các bucket:</b><br>"
            "&emsp;&emsp;&emsp;- Phân chia dãy số đầu vào thành các \"bucket\" nhỏ, mỗi bucket chứa các phần tử có giá trị trong một phạm vi nhỏ.<br>"
            "&emsp;&emsp;&emsp;- Các phần tử được phân phối vào các bucket theo công thức: "
            "<i>index = (value - min) / bucket size</i>, trong đó:<br>"
            "&emsp;&emsp;&emsp;&emsp;+ <i>min</i> là giá trị nhỏ nhất trong dãy số.<br>"
            "&emsp;&emsp;&emsp;&emsp;+ <i>bucket size</i> là kích thước của mỗi bucket.<br>"
            "&emsp;&emsp;<b>2. Sắp xếp các bucket:</b><br>"
            "&emsp;&emsp;&emsp;- Sau khi phân phối các phần tử vào các bucket, mỗi bucket sẽ được sắp xếp riêng biệt.<br>"
            "&emsp;&emsp;&emsp;- Phương pháp sắp xếp trong bucket có thể là Insertion Sort hoặc QuickSort.<br>"
            "&emsp;&emsp;<b>3. Gộp lại các bucket:</b><br>"
            "&emsp;&emsp;&emsp;- Sau khi sắp xếp các bucket, thuật toán gộp các phần tử đã được sắp xếp từ tất cả các bucket lại thành một dãy số duy nhất.<br>"
            "<br><b style='font-size: x-large;'>Ưu điểm của Bucket Sort:</b><br>"
            "&emsp;&emsp;<b>1. Hiệu suất tốt với dữ liệu phân bố đều:</b><br>"
            "&emsp;&emsp;&emsp;- Nếu dữ liệu phân bố đều, thuật toán có thể hoạt động với thời gian gần O(n).<br>"
            "&emsp;&emsp;<b>2. Đơn giản và dễ triển khai:</b><br>"
            "&emsp;&emsp;&emsp;- Các bước phân chia và gộp lại dữ liệu rất đơn giản, làm cho thuật toán dễ hiểu và dễ cài đặt.<br>"
            "&emsp;&emsp;<b>3. Tối ưu cho dữ liệu trong phạm vi hạn chế:</b><br>"
            "&emsp;&emsp;&emsp;- Nếu dữ liệu có giá trị nhỏ và phân bố đều trong một phạm vi, thuật toán có thể tối ưu hóa thời gian sắp xếp.<br>"
            "<br><b style='font-size: x-large;'>Nhược điểm của Bucket Sort:</b><br>"
            "&emsp;&emsp;<b>1. Không hiệu quả với dữ liệu phân bố không đều:</b><br>"
            "&emsp;&emsp;&emsp;- Nếu các phần tử phân bố không đồng đều, một số bucket có thể chứa rất nhiều phần tử, làm tăng độ phức tạp.<br>"
            "&emsp;&emsp;<b>2. Đòi hỏi bộ nhớ phụ lớn:</b><br>"
            "&emsp;&emsp;&emsp;- Thuật toán yêu cầu bộ nhớ để lưu các bucket, không hiệu quả khi xử lý tập dữ liệu lớn.<br>"
            "&emsp;&emsp;<b>3. Không phù hợp với dữ liệu không phải số:</b><br>"
            "&emsp;&emsp;&emsp;- Bucket Sort hoạt động tốt nhất với dữ liệu số và phân bố đều trong phạm vi xác định.<br>"
            "&emsp;&emsp;<b>4. Cần bước sắp xếp phụ trong mỗi bucket:</b><br>"
            "&emsp;&emsp;&emsp;- Nếu một bucket chứa nhiều phần tử, bước sắp xếp phụ có thể làm tăng độ phức tạp.<br>"
            );
        break;
    case 12:
        ui->lblinforSort->setText("Flash sort (Sắp xếp phân phối)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br><br>"
            "&emsp;&emsp;Flash Sort là một thuật toán phân phối nhanh, hoạt động bằng cách chia mảng thành các nhóm nhỏ dựa trên giá trị của các phần tử và sắp xếp các nhóm này bằng cách hoán vị vòng tròn và sử dụng một thuật toán sắp xếp đơn giản như Insertion Sort cho nhóm cuối cùng.<br><br>"
            "<br><b style='font-size: large;'>Cách hoạt động:</b><br>"
            "&emsp;&emsp;<b>1. Tạo nhóm:</b><br>"
            "&emsp;&emsp;&emsp;- Dựa trên giá trị nhỏ nhất và lớn nhất trong mảng, thuật toán chia mảng thành các nhóm giá trị liên tiếp (bucket). Các nhóm này sẽ đại diện cho các khoảng giá trị xác định.<br>"
            "&emsp;&emsp;<b>2. Phân phối phần tử:</b><br>"
            "&emsp;&emsp;&emsp;- Mỗi phần tử trong mảng được gán vào nhóm tương ứng dựa trên tỷ lệ của nó trong phạm vi giá trị.<br>"
            "&emsp;&emsp;<b>3. Hoán vị vòng tròn:</b><br>"
            "&emsp;&emsp;&emsp;- Các phần tử trong mỗi nhóm được di chuyển về đúng vị trí của chúng trong mảng dựa trên vị trí nhóm đã được xác định trước đó.<br>"
            "&emsp;&emsp;<b>4. Sắp xếp hoàn thiện:</b><br>"
            "&emsp;&emsp;&emsp;- Dùng thuật toán sắp xếp đơn giản (thường là Insertion Sort) để sắp xếp các phần tử trong nhóm cuối cùng, giúp đảm bảo mảng được sắp xếp hoàn chỉnh.<br><br>"
            "<br><b style='font-size: x-large;'>Ưu điểm:</b><br>"
            "&emsp;&emsp;<b>1. Rất nhanh với mảng có phân phối gần đều:</b><br>"
            "&emsp;&emsp;&emsp;- Flash Sort hoạt động hiệu quả với mảng mà các phần tử được phân phối gần đồng đều trong phạm vi giá trị.<br>"
            "&emsp;&emsp;<b>2. Hiệu quả với mảng lớn:</b><br>"
            "&emsp;&emsp;&emsp;- Phức tạp thời gian trung bình của thuật toán là O(n), điều này giúp Flash Sort rất hiệu quả với mảng lớn.<br><br>"
            "<br><b style='font-size: x-large;'>Nhược điểm:</b><br>"
            "&emsp;&emsp;<b>1. Không ổn định:</b><br>"
            "&emsp;&emsp;&emsp;- Flash Sort không bảo toàn thứ tự tương đối của các phần tử có giá trị bằng nhau.<br>"
            "&emsp;&emsp;<b>2. Không phù hợp với mảng có phân phối giá trị không đồng đều:</b><br>"
            "&emsp;&emsp;&emsp;- Thuật toán dễ bị thiên lệch khi các phần tử có giá trị phân phối không đều, dẫn đến việc nhóm bị phân chia không hợp lý.<br>"
            );
        break;
    case 13:
        ui->lblinforSort->setText("Shaker Sort (Sắp xếp cocktail)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "&emsp;&emsp;Shaker Sort (hay còn gọi là Cocktail Sort) là một biến thể của Bubble Sort, được cải tiến bằng cách thực hiện sắp xếp hai chiều. Quá trình làm việc của Shaker Sort có thể được mô tả như sau:<br>"
            "&emsp;&emsp;<b>1. Chia mảng thành các khối nhỏ:</b><br>"
            "&emsp;&emsp;&emsp;- Mảng được chia thành các khối nhỏ dựa trên giá trị của các phần tử để thuận tiện cho việc xử lý.<br>"
            "&emsp;&emsp;<b>2. Duyệt qua các khối:</b><br>"
            "&emsp;&emsp;&emsp;- Duyệt qua từng khối nhỏ để kiểm tra sự sắp xếp của các phần tử bên trong.<br>"
            "&emsp;&emsp;<b>3. Hoán đổi các phần tử nếu cần:</b><br>"
            "&emsp;&emsp;&emsp;- Nếu các phần tử không đúng thứ tự, chúng sẽ được hoán đổi với nhau để đạt được sự sắp xếp hợp lý.<br>"
            "&emsp;&emsp;<b>4. Tiếp tục cho đến khi mảng được sắp xếp:</b><br>"
            "&emsp;&emsp;&emsp;- Quá trình sẽ tiếp tục cho đến khi không còn hoán đổi nào được thực hiện.<br><br>"
            "<br><b style='font-size: x-large;'>Ưu Điểm của Shaker Sort:</b><br>"
            "&emsp;&emsp;<b>1. Nhanh hơn Bubble Sort:</b><br>"
            "&emsp;&emsp;&emsp; - Shaker Sort cải thiện Bubble Sort bằng cách duyệt cả từ trái sang phải và từ phải sang trái. "
            "Điều này giúp giảm số lần so sánh, vì phần tử lớn nhất sẽ nhanh chóng được đưa về cuối mảng và phần tử nhỏ nhất về đầu mảng, làm giảm phạm vi cần phải kiểm tra.<br>"
            "&emsp;&emsp;<b>2. Dễ hiểu và dễ cài đặt:</b><br>"
            "&emsp;&emsp;&emsp; - Thuật toán khá đơn giản và dễ hiểu, có thể được cài đặt dễ dàng trong nhiều ngôn ngữ lập trình.<br>"
            "&emsp;&emsp;<b>3. Hiệu quả đối với các dãy số gần như đã sắp xếp:</b><br>"
            "&emsp;&emsp;&emsp; - Nếu mảng đã gần như sắp xếp, thuật toán sẽ thực hiện rất ít bước duyệt và có thể dừng sớm khi không có hoán đổi.<br><br>"
            "<br><b style='font-size: x-large;'>Nhược Điểm của Shaker Sort:</b><br>"
            "&emsp;&emsp;<b>1. Phức tạp thời gian:</b><br>"
            "&emsp;&emsp;&emsp; - Shaker Sort có độ phức tạp thời gian là O(n²) trong trường hợp xấu nhất (khi mảng đã được sắp xếp ngược lại). "
            "Điều này khiến thuật toán không hiệu quả đối với các dãy số lớn.<br>"
            "&emsp;&emsp;<b>2. Không ổn định:</b><br>"
            "&emsp;&emsp;&emsp; - Shaker Sort không phải là một thuật toán ổn định, tức là nếu có hai phần tử có giá trị giống nhau, "
            "thì vị trí của chúng có thể thay đổi sau khi sắp xếp.<br>"
            "&emsp;&emsp;<b>3. Không phải lựa chọn tốt cho mảng lớn:</b><br>"
            "&emsp;&emsp;&emsp; - Với độ phức tạp O(n²), Shaker Sort không phải là lựa chọn tối ưu cho mảng có kích thước lớn. "
            "Các thuật toán như Quick Sort, Merge Sort hay Heap Sort thường sẽ hoạt động nhanh hơn.<br>"
            "&emsp;&emsp;<b>4. Chạy không hiệu quả với dãy số đã được sắp xếp đảo ngược hoàn toàn:</b><br>"
            "&emsp;&emsp;&emsp; - Trong trường hợp mảng đảo ngược hoàn toàn, thuật toán vẫn thực hiện nhiều lần hoán đổi và không tận dụng được khả năng tối ưu như với Insertion Sort hoặc Bubble Sort khi mảng đã gần như sắp xếp.<br>"
            );
        break;
    case 14:
        ui->lblinforSort->setText("Cube sort (Sắp xếp song song)");

        ui->txt_infor->setHtml(
            "<b style='font-size: x-large;'>Mô tả thuật toán:</b><br>"
            "<b style='font-size: large;'>Cách hoạt động:</b><br>"
            "&emsp;&emsp;CubeSort là một thuật toán sắp xếp dựa trên việc chia mảng thành các khối nhỏ (cubes), sau đó sắp xếp mỗi khối bằng một thuật toán sắp xếp đơn giản (như Insertion Sort), "
            "và cuối cùng hợp nhất các khối đã sắp xếp lại với nhau. Cách hoạt động chi tiết của CubeSort:<br>"
            "&emsp;&emsp;<b>1. Chia mảng thành các khối nhỏ:</b> Mảng được chia thành các khối có kích thước cố định (được xác định bởi CUBE_SIZE).<br>"
            "&emsp;&emsp;<b>2. Sắp xếp các khối:</b> Mỗi khối được sắp xếp độc lập, trong ví dụ trên, thuật toán Insertion Sort được sử dụng để sắp xếp mỗi khối.<br>"
            "&emsp;&emsp;<b>3. Hợp nhất các khối:</b> Sau khi sắp xếp các khối, thuật toán sẽ hợp nhất các khối này lại với nhau. "
            "Cách hợp nhất sử dụng một thuật toán hợp nhất (như std::merge) để tạo thành một dãy đã được sắp xếp.<br>"
            "<br><b style='font-size: x-large;'>Ưu điểm của CubeSort:</b><br>"
            "&emsp;&emsp;<b>1. Hiệu quả với mảng lớn:</b><br>"
            "&emsp;&emsp;&emsp;- CubeSort rất hiệu quả với các mảng lớn, do việc phân chia và sắp xếp khối làm giảm thời gian tính toán tổng thể.<br>"
            "&emsp;&emsp;<b>2. Giảm độ phức tạp thời gian cho một số tình huống:</b><br>"
            "&emsp;&emsp;&emsp;- Với dữ liệu phân bố đồng đều, CubeSort có thể giảm độ phức tạp lên tới O(n log n).<br>"
            "<br><b style='font-size: x-large;'>Nhược điểm của CubeSort:</b><br>"
            "&emsp;&emsp;<b>1. Không hiệu quả cho mảng nhỏ:</b><br>"
            "&emsp;&emsp;&emsp;- Không tối ưu cho mảng nhỏ vì thuật toán phân chia mảng tốn chi phí bộ nhớ và thời gian.<br>"
            "&emsp;&emsp;<b>2. Độ phức tạp khi gộp khối:</b><br>"
            "&emsp;&emsp;&emsp;- Phần gộp khối có thể phức tạp hơn so với các thuật toán như Merge Sort.<br>"
            "&emsp;&emsp;<b>3. Cần bộ nhớ phụ lớn:</b><br>"
            "&emsp;&emsp;&emsp;- Cần bộ nhớ để lưu trữ các khối, điều này có thể trở thành vấn đề với mảng lớn.<br>"
            );
        break;
    default:
        break;
    }
}

