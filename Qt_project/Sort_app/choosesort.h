#ifndef CHOOSESORT_H
#define CHOOSESORT_H

#include <QWidget>

namespace Ui {
class chooseSort;
}

class chooseSort : public QWidget
{
    Q_OBJECT

public:
    explicit chooseSort(QWidget *parent = nullptr);
    ~chooseSort();
    void setIsInfor(int num);

signals:
    void goBackHome();
    void goBackMain_Sort();
    void setNumSort(int num);
    void goToSelectSort();
    void goToInforSort();

private:
    Ui::chooseSort *ui;
};

#endif // CHOOSESORT_H
