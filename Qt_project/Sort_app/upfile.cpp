#include "upfile.h"
#include "ui_upfile.h"
#include <QTimer>
#include <QStringList>

upFile::upFile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::upFile)
    , timer(new QTimer(this))
    , sortingStep(0) // Khởi tạo bước sorting
{
    ui->setupUi(this);
    connect(ui->btn_goHome, &QPushButton::clicked, this, [this]() {
        ui->lbl_ready->setText("");
        stopUpdatingSortingLabel(); // Đảm bảo dừng mọi cập nhật nhãn
        emit goBackHome();
    });
    connect(ui->btn_goBack_upFile, &QPushButton::clicked, this, [this]() {
        ui->lbl_ready->setText("");
        stopUpdatingSortingLabel(); // Đảm bảo dừng mọi cập nhật nhãn
        emit goBackSelectSort();
    });
    connect(ui->btn_upFile, &QPushButton::clicked, this, &upFile::onOpenFileDialog);
    ui->lbl_ready->setText("");
    // Kết nối sự kiện cập nhật nhãn "Sorting"
    connect(timer, &QTimer::timeout, this, upFile::updateSortingLabel);
}

upFile::~upFile()
{
    delete ui;
}

void upFile::updateStatus(bool success, const QString &filePath)
{
    if (success) {
        ui->lbl_ready->setText(tr("Thành công: ") + filePath);

        // Ngắt kết nối cũ (nếu có) trước khi kết nối lại
        disconnect(ui->btn_start_sort, &QPushButton::clicked, nullptr, nullptr);
        qDebug() << "here";
        connect(ui->btn_start_sort, &QPushButton::clicked, this, [this]() {
            qDebug() << "or here";
            emit startSort(); // Phát tín hiệu bắt đầu sắp xếp
        });
    } else {
        ui->lbl_ready->setText(tr("Không thành công"));
    }
}

void upFile::startUpdatingSortingLabel() {
    sortingStep = 0;
    timer->start(300);  // Cập nhật nhãn "Sorting..." mỗi 600ms
}

void upFile::stopUpdatingSortingLabel() {
    timer->stop();  // Dừng timer khi không cần cập nhật nữa
    ui->lbl_ready->clear();  // Xóa nhãn "Sorting..."
}



// Cập nhật trạng thái "Sorting"
void upFile::updateSortingLabel() {
    static const QStringList sortingTexts = { "Sorting", "Sorting.", "Sorting..", "Sorting..." };
    QMetaObject::invokeMethod(this, [this]() {
        ui->lbl_ready->setText(sortingTexts[sortingStep]);
        sortingStep = (sortingStep + 1) % sortingTexts.size();
    }, Qt::QueuedConnection);
}


