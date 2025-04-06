#include "choosesort.h"
#include "ui_choosesort.h"

int isInformation = 0;

chooseSort::chooseSort(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chooseSort)
{
    ui->setupUi(this);
    connect(ui->btn_goHome, &QPushButton::clicked, this, &chooseSort::goBackHome);
    connect(ui->btn_goBack_choosesort, &QPushButton::clicked, this, &chooseSort::goBackMain_Sort);
    connect(ui->btn_Sort_1, &QPushButton::clicked, this, [this]() {
        emit setNumSort(1);  // Emit tín hiệu setNumSort với giá trị 1
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_2, &QPushButton::clicked, this, [this]() {
        emit setNumSort(2);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_3, &QPushButton::clicked, this, [this]() {
        emit setNumSort(3);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_4, &QPushButton::clicked, this, [this]() {
        emit setNumSort(4);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_5, &QPushButton::clicked, this, [this]() {
        emit setNumSort(5);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_6, &QPushButton::clicked, this, [this]() {
        emit setNumSort(6);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_7, &QPushButton::clicked, this, [this]() {
        emit setNumSort(7);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_8, &QPushButton::clicked, this, [this]() {
        emit setNumSort(8);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_9, &QPushButton::clicked, this, [this]() {
        emit setNumSort(9);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_10, &QPushButton::clicked, this, [this]() {
        emit setNumSort(10);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_11, &QPushButton::clicked, this, [this]() {
        emit setNumSort(11);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_12, &QPushButton::clicked, this, [this]() {
        emit setNumSort(12);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_13, &QPushButton::clicked, this, [this]() {
        emit setNumSort(13);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
    connect(ui->btn_Sort_14, &QPushButton::clicked, this, [this]() {
        emit setNumSort(14);
        if(isInformation == 0){
            emit goToSelectSort();
        } else {
            emit goToInforSort();
        }
    });
}

chooseSort::~chooseSort()
{
    delete ui;
}

void chooseSort::setIsInfor(int num){
    isInformation = num;
    if(isInformation == 0){
        ui->lblMainSort->setText("Sắp xếp dữ liệu");
    } else {
        ui->lblMainSort->setText("Thông tin thuật toán");
    }
}

