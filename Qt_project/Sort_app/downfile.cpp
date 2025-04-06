#include "downfile.h"
#include "ui_downfile.h"

downFile::downFile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::downFile)
{
    ui->setupUi(this);
    connect(ui->btn_downFile, &QPushButton::clicked, this, &downFile::onDownFileDialog);
}

downFile::~downFile()
{
    delete ui;
}
void downFile::updateStatus(bool success, const QString &filePath)
{
    if (success) {
        ui->lbl_ready->setText(tr("Thành công: ") + filePath);

        disconnect(ui->btn_goHome, &QPushButton::clicked, nullptr, nullptr);

        connect(ui->btn_goHome, &QPushButton::clicked, this, [this]() {
            ui->lbl_ready->setText("");
            emit goBackHome();
        });
    } else {
        ui->lbl_ready->setText(tr("Không thành công"));
    }
}
