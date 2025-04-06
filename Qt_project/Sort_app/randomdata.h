#ifndef RANDOMDATA_H
#define RANDOMDATA_H

#include <QWidget>
#include <vector>
#include <QTimer>

using namespace std;

namespace Ui {
class randomData;
}

class randomData : public QWidget
{
    Q_OBJECT

public:
    explicit randomData(QWidget *parent = nullptr);
    ~randomData();
    void setVector(vector<int> &vec) { theOriginVector = &vec; }
    void startUpdatingSortingLabel();
    void stopUpdatingSortingLabel();

signals:
    void startSort();
    void goBackHome();
    void goBackSelectSort();
    void setNumMethod(int num);

private:
    Ui::randomData *ui;
    QTimer *timer;
    vector<int> *theOriginVector;
    void updateSortingLabel(); // Hàm cập nhật trạng thái "Sorting"
    int sortingStep; // Biến theo dõi trạng thái sorting
    void randomTheData();
};

#endif // RANDOMDATA_H
