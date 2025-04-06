#include "selectsort.h"
#include "ui_selectsort.h"

selectSort::selectSort(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selectSort)
{
    ui->setupUi(this);
    connect(ui->btn_goHome, &QPushButton::clicked, this, &selectSort::goBackHome);
    connect(ui->btn_chooseUpFile, &QPushButton::clicked, this, [this]() {
        emit setNumMethod(1);
        emit goToUpFile();
    });
    connect(ui->btn_chooseWrite, &QPushButton::clicked, this, [this]() {
        emit setNumMethod(2);
        emit goToWriteData();
    });
    connect(ui->btn_chooseRandom, &QPushButton::clicked, this, [this]() {
        emit setNumMethod(3);
        emit goToRandomData();
    });
}

selectSort::~selectSort()
{
    delete ui;
}

void selectSort::setNumSort(int num){
    if(num == -1){
        connect(ui->btn_goBack_selectsort, &QPushButton::clicked, this, &selectSort::goBackChooseComparion);
    } else {
        connect(ui->btn_goBack_selectsort, &QPushButton::clicked, this, &selectSort::goBackChooseSort);
    }
    switch (num){
    case 1:
        ui->lblNameOfSort->setText("Bubble Sort(Sắp xếp nổi bọt)");
        break;
    case 2:
        ui->lblNameOfSort->setText("Heap sort (Sắp xếp vun đống)");
        break;
    case 3:
        ui->lblNameOfSort->setText("Insertion sort (Sắp xếp chèn)");
        break;
    case 4:
        ui->lblNameOfSort->setText("Interchange sort (Sắp xếp đổi chỗ)");
        break;
    case 5:
        ui->lblNameOfSort->setText("Merge sort (Sắp xếp trộn)");
        break;
    case 6:
        ui->lblNameOfSort->setText("Quick sort (Sắp xếp nhanh)");
        break;
    case 7:
        ui->lblNameOfSort->setText("Selection sort (Sắp xếp chọn)");
        break;
    case 8:
        ui->lblNameOfSort->setText("Shell sort (Sắp xếp vỏ sò)");
        break;
    case 9:
        ui->lblNameOfSort->setText("Counting Sort (Sắp xếp đếm)");
        break;
    case 10:
        ui->lblNameOfSort->setText("Radix sort (Sắp xếp theo cơ số)");
        break;
    case 11:
        ui->lblNameOfSort->setText("Bucket sort (Sắp xếp thùng)");
        break;
    case 12:
        ui->lblNameOfSort->setText("Flash sort (Sắp xếp phân phối)");
        break;
    case 13:
        ui->lblNameOfSort->setText("Shaker Sort (Sắp xếp cocktai)");
        break;
    case 14:
        ui->lblNameOfSort->setText("Cube sort (Sắp xếp song song)");
        break;
    default:
        ui->lblNameOfSort->setText("So sánh thuật toán");
        break;
    }
}
