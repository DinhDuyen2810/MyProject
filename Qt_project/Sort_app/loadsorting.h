#ifndef LOADSORTING_H
#define LOADSORTING_H

#include <QWidget>
#include "sorting.h"
#include <vector>

using namespace std;

namespace Ui {
class loadSorting;
}

class loadSorting : public QWidget
{
    Q_OBJECT

public:
    explicit loadSorting(QWidget *parent = nullptr);
    ~loadSorting();
    void SortTheNumber(int numOfSort, vector<int> &theOrigiVector);
    void startLoadingEffect();
    void stopLoadingEffect();

private slots:
    void rotateLoadingIcon(); // Thêm khai báo hàm ở đây

signals:
    void goToPage();

private:
    Ui::loadSorting *ui;
    QTimer *rotationTimer; // Timer để cập nhật góc xoay
    int rotationAngle;     // Góc xoay hiện tại


};

#endif // LOADSORTING_H
