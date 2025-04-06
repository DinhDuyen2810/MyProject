#include "randomdata.h"
#include "ui_randomdata.h"
#include <cstdlib>
#include <ctime>

randomData::randomData(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::randomData)
    , theOriginVector(nullptr)
    , timer(new QTimer(this))
    , sortingStep(0) // Khởi tạo bước sorting
{
    ui->setupUi(this);
    // Kết nối sự kiện các nút giao diện
    connect(ui->btn_goHome, &QPushButton::clicked, this, &randomData::goBackHome);
    connect(ui->btn_goBack_randomData, &QPushButton::clicked, this, &randomData::goBackSelectSort);

    // Kết nối sự kiện cập nhật nhãn "Sorting"
    connect(timer, &QTimer::timeout, this, &randomData::updateSortingLabel);

    // Nút bắt đầu sắp xếp
    connect(ui->btn_start_sort, &QPushButton::clicked, this, [this]() {
        if (theOriginVector) {
            ui->lneRandom->setReadOnly(true);
            ui->lneBottom->setReadOnly(true);
            ui->lneTop->setReadOnly(true);
            randomTheData();
            emit startSort(); // Phát tín hiệu bắt đầu sắp xếp
        }
    });
}

randomData::~randomData()
{
    delete ui;
}

void randomData::startUpdatingSortingLabel() {
    sortingStep = 0;
    timer->start(300);  // Cập nhật nhãn "Sorting..." mỗi 600ms
}

void randomData::stopUpdatingSortingLabel() {
    timer->stop();  // Dừng timer khi không cần cập nhật nữa
    ui->lbl_ready->clear();  // Xóa nhãn "Sorting..."
    ui->lneRandom->setReadOnly(false);
    ui->lneBottom->setReadOnly(false);
    ui->lneTop->setReadOnly(false);
    ui->lneRandom->clear();
    ui->lneBottom->clear();
    ui->lneTop->clear();
}

// Cập nhật trạng thái "Sorting"
void randomData::updateSortingLabel() {
    static const QStringList sortingTexts = { "Sorting", "Sorting.", "Sorting..", "Sorting..." };
    QMetaObject::invokeMethod(this, [this]() {
        ui->lbl_ready->setText(sortingTexts[sortingStep]);
        sortingStep = (sortingStep + 1) % sortingTexts.size();
    }, Qt::QueuedConnection);
}

// random vào vector
void randomData::randomTheData() {
    int n = ui->lneRandom->text().toInt();
    int min = ui->lneBottom->text().toInt();
    int max = ui->lneTop->text().toInt();

    theOriginVector->clear();
    theOriginVector->shrink_to_fit();
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        int randomNumber = rand() % (max - min + 1) + min;
        theOriginVector->push_back(randomNumber);
    }
    if(n >= 5000){
        emit setNumMethod(1);
    } else {
        emit setNumMethod(2);
    }
}
