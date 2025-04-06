#include "choosetocomparion.h"
#include "ui_choosetocomparion.h"
#include <vector>

using namespace std;

vector<int> chooseSort(14, 0);

chooseToComparion::chooseToComparion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chooseToComparion)
{
    ui->setupUi(this);

    connect(ui->btn_goHome, &QPushButton::clicked, this, [this](){
        clearData();
        goBackHome();
    });

    connect(ui->btn_goBack_chooseCom, &QPushButton::clicked, this, [this](){
        clearData();
        goBackMain_Sort();
    });
    connect(ui->btn_next, &QPushButton::clicked, this, [this](){
        emit setComparion(chooseSort);
        clearData();
        goToSelectSort();
    });

    // Kết nối các checkbox với hàm xử lý sự kiện
    connect(ui->box1, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box2, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box3, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box4, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box5, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box6, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box7, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box8, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box9, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box10, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box11, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box12, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box13, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
    connect(ui->box14, &QCheckBox::toggled, this, &chooseToComparion::updateChooseSort);
}

chooseToComparion::~chooseToComparion()
{
    delete ui;
}

// Hàm xử lý sự kiện khi checkbox được thay đổi
void chooseToComparion::updateChooseSort()
{
    // Cập nhật giá trị trong vector khi checkbox được chọn hoặc bỏ chọn
    chooseSort[0] = ui->box1->isChecked() ? 1 : 0;
    chooseSort[1] = ui->box2->isChecked() ? 1 : 0;
    chooseSort[2] = ui->box3->isChecked() ? 1 : 0;
    chooseSort[3] = ui->box4->isChecked() ? 1 : 0;
    chooseSort[4] = ui->box5->isChecked() ? 1 : 0;
    chooseSort[5] = ui->box6->isChecked() ? 1 : 0;
    chooseSort[6] = ui->box7->isChecked() ? 1 : 0;
    chooseSort[7] = ui->box8->isChecked() ? 1 : 0;
    chooseSort[8] = ui->box9->isChecked() ? 1 : 0;
    chooseSort[9] = ui->box10->isChecked() ? 1 : 0;
    chooseSort[10] = ui->box11->isChecked() ? 1 : 0;
    chooseSort[11] = ui->box12->isChecked() ? 1 : 0;
    chooseSort[12] = ui->box13->isChecked() ? 1 : 0;
    chooseSort[13] = ui->box14->isChecked() ? 1 : 0;
}
//Xóa các checkbox và vector
void chooseToComparion::clearData(){
    for(int i = 0; i < 14; i++){
        chooseSort[i] = 0;
    }
    ui->box1->setChecked(false);
    ui->box2->setChecked(false);
    ui->box3->setChecked(false);
    ui->box4->setChecked(false);
    ui->box5->setChecked(false);
    ui->box6->setChecked(false);
    ui->box7->setChecked(false);
    ui->box8->setChecked(false);
    ui->box9->setChecked(false);
    ui->box10->setChecked(false);
    ui->box11->setChecked(false);
    ui->box12->setChecked(false);
    ui->box13->setChecked(false);
    ui->box14->setChecked(false);
}
