#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QString"
#include "QMessageBox"
#include "QCloseEvent"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentText = "";   // Hiển thị trên màn hình nhập
    currentNumber = 0;  // Giá trị phép tính

    connect(ui->btnNumOne, SIGNAL(clicked()), this, SLOT(clickNumOne()));
    connect(ui->btnNumTwo, SIGNAL(clicked()), this, SLOT(clickNumTwo()));
    connect(ui->btnNumThree, SIGNAL(clicked()), this, SLOT(clickNumThree()));
    connect(ui->btnNumFour, SIGNAL(clicked()), this, SLOT(clickNumFour()));
    connect(ui->btnNumFive, SIGNAL(clicked()), this, SLOT(clickNumFive()));
    connect(ui->btnNumSix, SIGNAL(clicked()), this, SLOT(clickNumSix()));
    connect(ui->btnNumSeven, SIGNAL(clicked()), this, SLOT(clickNumSeven()));
    connect(ui->btnNumEight, SIGNAL(clicked()), this, SLOT(clickNumEight()));
    connect(ui->btnNumNine, SIGNAL(clicked()), this, SLOT(clickNumNine()));
    connect(ui->btnNumZero, SIGNAL(clicked()), this, SLOT(clickNumZero()));
    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(clickPlus()));
    connect(ui->btnMinus, SIGNAL(clicked()), this, SLOT(clickMinus()));
    connect(ui->btnMulti, SIGNAL(clicked()), this, SLOT(clickMulti()));
    connect(ui->btnDivine, SIGNAL(clicked()), this, SLOT(clickDivine()));
    connect(ui->btnUndo, SIGNAL(clicked()), this, SLOT(clickUndo()));
    connect(ui->btnDel, SIGNAL(clicked()), this, SLOT(clickDel()));
    connect(ui->btnEqual, SIGNAL(clicked()), this, SLOT(clickEqual()));
    connect(ui->btnExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnChangeBinary, SIGNAL(clicked()), this, SLOT(changeTobinary()));
    connect(ui->btnFParen, SIGNAL(clicked()), this, SLOT(clickFParen()));
    connect(ui->btnSParen, SIGNAL(clicked()), this, SLOT(clickSParen()));
    connect(ui->btnPow, SIGNAL(clicked()), this, SLOT(clickPow()));
}

void MainWindow::clickNumOne() {
    currentText += "1";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickNumTwo() {
    currentText += "2";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickNumThree() {
    currentText += "3";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickNumFour() {
    currentText += "4";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickNumFive() {
    currentText += "5";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickNumSix() {
    currentText += "6";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickNumSeven() {
    currentText += "7";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickNumEight() {
    currentText += "8";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickNumNine() {
    currentText += "9";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickNumZero() {
    currentText += "0";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickPlus() {
    currentText += "+";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickMinus() {
    currentText += "-";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickMulti() {
    currentText += "*";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickDivine() {
    currentText += "/";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickPow(){
    currentText += "^";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickUndo() {
    if(!currentText.isEmpty()){
        currentText.chop(1);
    }
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickDel() {
    currentText = "";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickFParen() {
    currentText += "(";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickSParen() {
    currentText += ")";
    ui->lineEdit->setText(currentText);
}

void MainWindow::clickEqual() {
    currentText = ui->lineEdit->text();
    if(currentText != ""){
        QString theResuilt = QString::fromStdString(calTheResuilt.theResult(currentText.toStdString()));
        if(theResuilt != "ERR"){
            ui->lblNumber->setText(theResuilt);
        } else {
            ui->lblNumber->setText("ERR");
        }
        currentText = "";
        ui->lineEdit->setText(currentText);
    } else {
        ui->lblNumber->setText("0");
    }
}

void MainWindow::changeTobinary() {
    currentText = ui->lineEdit->text();
    currentNumber = currentText.toInt();
    QString theBinary = QString::fromStdString(calTheBinary.decimalToBinary(currentNumber));
    ui->lblNumber->setText(theBinary);
    currentText = "";
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(QMessageBox::question(this, "Confirm", "Do you want to exit?") == QMessageBox::No){
        event->ignore();
    }
}

void MainWindow::clickExit(){
    if(QMessageBox::question(this, "Confirm", "Do you want to exit?") == QMessageBox::Yes){
        close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}






