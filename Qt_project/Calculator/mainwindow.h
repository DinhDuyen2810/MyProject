#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dectobin.h"
#include "calresult.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void clickNumOne();
    void clickNumTwo();
    void clickNumThree();
    void clickNumFour();
    void clickNumFive();
    void clickNumSix();
    void clickNumSeven();
    void clickNumEight();
    void clickNumNine();
    void clickNumZero();
    void clickPlus();
    void clickMinus();
    void clickMulti();
    void clickDivine();
    void clickUndo();
    void clickDel();
    void clickEqual();
    void clickFParen();
    void clickSParen();
    void clickPow();
    void changeTobinary();
    void clickExit();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QString currentText;
    int currentNumber;
    dectobin calTheBinary;
    calresult calTheResuilt;
};
#endif // MAINWINDOW_H
