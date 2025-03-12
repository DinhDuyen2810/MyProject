#ifndef CHOOSEINFORSORT_H
#define CHOOSEINFORSORT_H

#include <QWidget>

namespace Ui {
class chooseInforSort;
}

class chooseInforSort : public QWidget
{
    Q_OBJECT

public:
    explicit chooseInforSort(QWidget *parent = nullptr);
    ~chooseInforSort();

private:
    Ui::chooseInforSort *ui;
};

#endif // CHOOSEINFORSORT_H
