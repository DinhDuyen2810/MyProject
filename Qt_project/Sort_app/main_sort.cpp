#include "main_sort.h"
#include "./ui_main_sort.h"

main_sort::main_sort(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::main_sort)
{
    ui->setupUi(this);
    connect(ui->btn_goHome, &QPushButton::clicked, this, &main_sort::goBackHome);
    connect(ui->btn_goBack_mainsort, &QPushButton::clicked, this, &main_sort::goBackHome);
    connect(ui->btn_chooseSort, &QPushButton::clicked, this, &main_sort::goToChooseSort);
    connect(ui->btn_information, &QPushButton::clicked, this, &main_sort::goToChooseSortInfor);
    connect(ui->btn_comparison, &QPushButton::clicked, this, [this]() {
        emit setNumSort(-1);
        emit goToChooseComparion();
    });
}

main_sort::~main_sort()
{
    delete ui;
}



