#include "outdata.h"
#include "ui_outdata.h"
#include <QString>

QString outputData;

outData::outData(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::outData)
{
    ui->setupUi(this);
    connect(ui->btn_goHome, &QPushButton::clicked, this, [this] () {
        ui->txtoutPut->setPlainText("");
        outputData.clear();
        emit goBackHome();
    });
}

outData::~outData()
{
    delete ui;
}


void outData::outTheRunTime(const long long runTime){
    if (runTime < 1000) {
        outputData = "Run time: " + QString::number(runTime) + " microseconds\n";
    } else if (runTime < 1000000) {
        outputData = "Run time: " + QString::number(runTime / 1000.0) + " milliseconds\n";
    } else if (runTime < 1000000000) {
        outputData = "Run time: " + QString::number(runTime / 1000000.0) + " seconds\n";
    }
}

void outData::outTheData(const vector<int>& theVector) {
    for (int i : theVector) {
        outputData += QString::number(i) + " "; // Chuyển số thành chuỗi và thêm dấu cách
    }
    ui->txtoutPut->setPlainText(outputData.trimmed()); // Xóa dấu cách thừa ở cuối
}
