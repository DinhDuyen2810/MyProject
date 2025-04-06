#ifndef INFOROFSORT_H
#define INFOROFSORT_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <stack>
#include <vector>

using namespace std;


namespace Ui {
class inforOfSort;
}

class inforOfSort : public QWidget
{
    Q_OBJECT

public:
    explicit inforOfSort(QWidget *parent = nullptr);
    ~inforOfSort();
    void startAnimationSort();

signals:
    void goBackHome();
    void goBackChooseSort();

protected:
    void paintEvent(QPaintEvent *event) override;
    void paintEvent_Heap(QPaintEvent *event);
    void paintEvent_Merge(QPaintEvent *event);
    void paintEvent_Count(QPaintEvent *event);
    void paintEvent_Radix(QPaintEvent *event);
    void paintEvent_Flash(QPaintEvent *event);

public slots:
    void setNumSort(int num);

private:
    Ui::inforOfSort *ui;
    std::vector<int> numbers;        // Dữ liệu cần sắp xếp
    std::vector<QColor> colors;      // Màu sắc của từng cột
    QTimer *animationTimer;          // Timer để điều khiển animation
    int i, j;                        // Chỉ số của vòng lặp
    int numberToAnimation = 0;
    bool isSorting = false;
    int verticalOffset = 0;

    //BubbleSort
    bool isComparing;
    //InsertionSort
    int key, tempIndex;      // Biến lưu giá trị key và vị trí tạm thời
    int temp;
    bool movingUp;   // Trạng thái di chuyển lên
    //SelectionSort
    int minIdx;   // Vị trí phần tử nhỏ nhất
    bool isFindingMin; // Trạng thái tìm phần tử nhỏ nhất
    //QuickSort
    int pivotIndex;             // Vị trí pivot hiện tại
    int left;                   // Chỉ số bên trái đang kiểm tra
    int right;                  // Chỉ số bên phải đang kiểm tra
    std::stack<std::pair<int, int>> subarrays; // Stack lưu các đoạn cần xử lý
    bool isPartitioning;     // Trạng thái đang chia đoạn
    int lastSmall;              // Chỉ số phần tử bé hơn pivot
    int areadyStart;
    bool swapped;
    //ShellSort
    int gapIndex;               // Chỉ số của khoảng gap hiện tại
    int groupStart = 0;
    //HeapSort            // Trạng thái đang sắp xếp
    int heapSize = 0;                   // Kích thước heap
    int currentRoot = 0;                // Vị trí root hiện tại
    int swapIndex = 0;                  // Vị trí hoán đổi
    bool isHeapSortMode = false;
    bool isColorCur = false;
    bool isColorLeft = false;
    bool isColorRight = false;
    //MergeSort
    bool isMergeSortMode = false;
    std::stack<std::pair<int, int>> subarrays_support; // Stack lưu các đoạn cần xử lý
    //CountingSort
    std::vector<int> count;      // Mảng đếm
    std::vector<int> output;     // Mảng kết quả
    std::vector<QColor> colorsCount;      // Màu sắc của từng cột
    std::vector<QColor> colorsOutput;      // Màu sắc của từng cột
    int max, min;                // Giá trị lớn nhất và nhỏ nhất
    int currentInputIndex = -1;  // Chỉ số phần tử trong numbers đang xử lý
    int currentCountIndex = -1;  // Chỉ số phần tử trong count đang xử lý
    int currentOutputIndex = -1; // Chỉ số phần tử trong output đang xử lý
    int phase;               // Giai đoạn của thuật toán
    bool isCountingMode = false;
    //RadixSort
    vector<vector<int>> buckets;
    std::vector<QColor> colorsBucket;
    int currentDigitIndex;           // Chỉ số chữ số hiện tại (0: hàng đơn vị, 1: hàng chục,...)
    int currentNumberIndex;
    bool isRadixSortMode = false;
    //BucketSort
    int currentBucketIndex = 0;
    //FlashSort
    int currentIndex;
    int flashValue = 0;  // Giá trị flash ban đầu
    int numMoves = 0;
    double scaleFactor;
    bool isFlashSortMode = false;





    void BubbleAnimation();
    void InsertionSortAnimation();
    void ShellSortAnimation();
    void QuickSortAnimation();
    void InterchangeAnimation();
    void SelectionSortAnimation();
    void HeapSortAnimation();
    void ShakerSortAnimation();
    void MergeSortAnimation();
    void CountingSortAnimation();
    void RadixSortAnimation();
    void BucketSortAnimation();
    void FlashSortAnimation();
    void stopAnimation() ;
    void drawBinaryTree(QPainter &painter, int x, int y, int level, int index, int gapX, int gapY);
};

#endif // INFOROFSORT_H
