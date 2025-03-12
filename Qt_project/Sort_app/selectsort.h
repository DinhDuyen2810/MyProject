#ifndef SELECTSORT_H
#define SELECTSORT_H

#include <QWidget>

namespace Ui {
class selectSort;
}

class selectSort : public QWidget
{
    Q_OBJECT

public:
    explicit selectSort(QWidget *parent = nullptr);
    ~selectSort();

signals:
    void goBackHome();
    void goBackChooseSort();
    void goBackChooseComparion();
    void goToUpFile();
    void setNumMethod(int num);
    void goToWriteData();
    void goToRandomData();

public slots:
    void setNumSort(int num);

private:
    Ui::selectSort *ui;
};

#endif // SELECTSORT_H
