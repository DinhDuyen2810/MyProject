#include "chooseinforsort.h"
#include "ui_chooseinforsort.h"

chooseInforSort::chooseInforSort(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chooseInforSort)
{
    ui->setupUi(this);
}

chooseInforSort::~chooseInforSort()
{
    delete ui;
}
