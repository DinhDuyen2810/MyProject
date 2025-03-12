#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include "main_app.h"
#include "main_sort.h"
#include "choosesort.h"
#include "selectsort.h"
#include "upfile.h"
#include "loadsorting.h"
#include "downfile.h"
#include <vector>
#include "writedata.h"
#include "outdata.h"
#include "sorting.h"
#include "randomdata.h"
#include "inforofsort.h"
#include "choosetocomparion.h"
#include "outcomparion.h"

using namespace std;

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

signals:
    void fileUploadStatus(bool success, const QString &filePath);
    void fileDownloadStatus(bool success, const QString &filePath);
    void allSortingCompleted();


private slots:
    void goToPage(QWidget *nextPage);
    void goBackPage(QWidget *nextPage);
    void setNumSort(int num);
    void setNumMethod(int num);
    void setThreadUIinPage(int num);
    void setfirstListComparion(vector<int> chooseSort);
    void onOpenFileDialog();
    void onDownFileDialog();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget; // Khai báo stackedWidget
    main_app *pageMainApp;
    main_sort *pageMainSort;
    chooseSort *pageChooseSort;
    selectSort *pageSelectSort;
    upFile *pageUpFile;
    downFile *pageDownFile;
    writeData *pageWriteData;
    outData *pageOutData;
    randomData *pageRandom;
    inforOfSort *pageInfor;
    chooseToComparion *pageChooseComparion;
    outComparion *pageOutComparion;


    void setupPages();
    void freeData();
    void resetUI();
    void setTheThread();
    void setTheThreadComparion();

    QThread* sortThread = nullptr; // Trỏ đến luồng sắp xếp
    sorting* worker = nullptr;
};
#endif // MAINWINDOW_H

