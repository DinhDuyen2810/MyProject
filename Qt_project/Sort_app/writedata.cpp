#include "writedata.h"
#include "ui_writedata.h"
#include <QString>
#include <QStringList>
#include <QRegularExpression>

writeData::writeData(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::writeData)
    , theOriginVector(nullptr)
    , timer(new QTimer(this))
    , sortingStep(0) // Khởi tạo bước sorting
{
    ui->setupUi(this);

    // Kết nối sự kiện các nút giao diện
    connect(ui->btn_goHome, &QPushButton::clicked, this, &writeData::goBackHome);
    connect(ui->btn_goBack_writeNumber, &QPushButton::clicked, this, &writeData::goBackSelectSort);

    // Kết nối sự kiện cập nhật nhãn "Sorting"
    connect(timer, &QTimer::timeout, this, &writeData::updateSortingLabel);

    // Nút bắt đầu sắp xếp
    connect(ui->btn_start_sort, &QPushButton::clicked, this, [this]() {
        if (theOriginVector) {
            copToVecto();
            emit startSort(); // Phát tín hiệu bắt đầu sắp xếp
        }
    });
}
writeData::~writeData()
{
    delete ui;
}
// Bắt đầu luồng
void writeData::startUpdatingSortingLabel() {
    sortingStep = 0;
    timer->start(300);  // Cập nhật nhãn "Sorting..." mỗi 600ms
}

// Kết thúc luồng
void writeData::stopUpdatingSortingLabel() {
    timer->stop();  // Dừng timer khi không cần cập nhật nữa
    ui->lbl_ready->clear();  // Xóa nhãn "Sorting..."
    ui->txtToWrite->clear();
}


// Cập nhật trạng thái "Sorting"
void writeData::updateSortingLabel() {
    static const QStringList sortingTexts = { "Sorting", "Sorting.", "Sorting..", "Sorting..." };
    QMetaObject::invokeMethod(this, [this]() {
        ui->lbl_ready->setText(sortingTexts[sortingStep]);
        sortingStep = (sortingStep + 1) % sortingTexts.size();
    }, Qt::QueuedConnection);
}

// Sao chép dữ liệu từ QPlainTextEdit vào vector
void writeData::copToVecto() {
    if (!ui->txtToWrite || !theOriginVector) return;

    QString inputText = ui->txtToWrite->toPlainText().trimmed(); // Loại bỏ khoảng trắng thừa
    if (inputText.isEmpty()) {
        return; // Không có dữ liệu để xử lý
    }

    QStringList numberList = inputText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    theOriginVector->clear();
    theOriginVector->shrink_to_fit();

    for (const QString &number : numberList) {
        bool ok;
        int value = number.toInt(&ok);
        if (ok) {
            theOriginVector->push_back(value);
        } else {
            qDebug() << "Invalid input: " << number; // Ghi log lỗi nếu có ký tự không hợp lệ
        }
    }
    int n = theOriginVector->size();
    if(n >= 5000){
        emit setNumMethod(1);
    }
}



