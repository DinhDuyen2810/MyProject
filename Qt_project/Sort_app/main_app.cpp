#include "main_app.h"
#include "./ui_main_app.h"

main_app::main_app(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::main_app)
{
    ui->setupUi(this);
    connect(ui->btn_main_start, &QPushButton::clicked, this, &main_app::goToMain_sort);
}

main_app::~main_app()
{
    delete ui;
}
