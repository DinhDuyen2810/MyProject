#include "loadsorting.h"
#include "ui_loadsorting.h"
#include <QTimer>
#include <QPixmap>
#include <QTransform>
#include <vector>
#include "sorting.h"

using namespace std;

loadSorting::loadSorting(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loadSorting)
    , rotationAngle(0)      // Góc xoay bắt đầu từ 0
{
    ui->setupUi(this);
    rotationTimer = new QTimer(this);
    ui->lblLoading->setScaledContents(true);
    connect(rotationTimer, &QTimer::timeout, this, &loadSorting::rotateLoadingIcon);

    // Bắt đầu timer, xoay mỗi 50ms
    rotationTimer->start(50);
}

loadSorting::~loadSorting()
{
    delete ui;
}

void loadSorting::SortTheNumber(int numberOfSort, vector<int>& theOriginVector){
    int n = theOriginVector.size();
    switch(numberOfSort){
        case 1:
            bubbleSort(theOriginVector);
            break;
        case 2:
            heapSort(theOriginVector);
            break;
        case 3:
            insertionSort(theOriginVector);
            break;
        case 4:
            interchangeSort(theOriginVector);
            break;
        case 5:
            mergeSort(theOriginVector, 0, n - 1);
            break;
        case 6:
            quickSort(theOriginVector, 0, n - 1);
            break;
        case 7:
            selectionSort(theOriginVector);
            break;
        case 8:
            shellSort(theOriginVector);
            break;
        case 9:
            countingSort(theOriginVector);
            break;
        case 10:
            radixSort(theOriginVector);
            break;
        case 11:
            bucketSort(theOriginVector);
            break;
        case 12:
            flashSort(theOriginVector);
            break;
        case 13:
            shakerSort(theOriginVector);
            break;
        case 14:
            cubeSort(theOriginVector);
            break;
    }
    //emit goToPage();
}

void loadSorting::rotateLoadingIcon()
{
    // Lấy hình ảnh gốc
    QPixmap pixmap(":/image/image/loading.png"); // Đường dẫn đến ảnh

    // Tạo đối tượng QTransform để xoay hình
    QTransform transform;
    transform.translate(pixmap.width() / 2, pixmap.height() / 2);
    transform.rotate(rotationAngle);
    transform.translate(-pixmap.width() / 2, -pixmap.height() / 2);


    // Tạo ảnh xoay
    QPixmap rotatedPixmap = pixmap.transformed(transform, Qt::SmoothTransformation);

    // Điều chỉnh kích thước ảnh xoay để giữ cố định kích thước của QLabel
    QSize fixedSize = ui->lblLoading->size(); // Kích thước của QLabel
    QPixmap scaledPixmap = rotatedPixmap.scaled(fixedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Gán lại hình xoay cho QLabel
    ui->lblLoading->setPixmap(scaledPixmap);

    // Tăng góc xoay
    rotationAngle = (rotationAngle + 10) % 360; // Xoay 10 độ mỗi lần, giữ trong khoảng 0-359
}

void loadSorting::startLoadingEffect()
{
    rotationAngle = 0; // Đặt góc xoay về 0
    rotationTimer->start(50); // Bắt đầu lại timer
}

void loadSorting::stopLoadingEffect()
{
    rotationTimer->stop(); // Dừng timer
}
