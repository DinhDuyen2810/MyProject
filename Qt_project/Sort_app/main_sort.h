#ifndef MAIN_SORT_H
#define MAIN_SORT_H

#include <QWidget>

namespace Ui {
class main_sort;
}

class main_sort : public QWidget
{
    Q_OBJECT

public:
    explicit main_sort(QWidget *parent = nullptr);
    ~main_sort();

signals:
    void goBackHome();
    void goToChooseSort();
    void goToChooseSortInfor();
    void goToChooseComparion();
    void setNumSort(int num);

private:
    Ui::main_sort *ui;
};

#endif // MAIN_SORT_H
