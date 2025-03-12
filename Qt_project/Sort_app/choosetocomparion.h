#ifndef CHOOSETOCOMPARION_H
#define CHOOSETOCOMPARION_H

#include <QWidget>
#include <vector>

using namespace std;

namespace Ui {
class chooseToComparion;
}

class chooseToComparion : public QWidget
{
    Q_OBJECT

public:
    explicit chooseToComparion(QWidget *parent = nullptr);
    ~chooseToComparion();
    void clearData();
signals:
    void goBackHome();
    void goBackMain_Sort();
    void goToSelectSort();
    void setComparion(vector<int> chooseSort);

private:
    Ui::chooseToComparion *ui;
    void updateChooseSort();
};

#endif // CHOOSETOCOMPARION_H
