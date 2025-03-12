#ifndef WRITEDATA_H
#define WRITEDATA_H

#include <QWidget>
#include <vector>
#include <QTimer>

using namespace std;

namespace Ui {
class writeData;
}

class writeData : public QWidget
{
    Q_OBJECT

public:
    explicit writeData(QWidget *parent = nullptr);
    ~writeData();
    void setVector(vector<int> &vec) { theOriginVector = &vec; }
    void startSorting();
    void startUpdatingSortingLabel(); // Phương thức bắt đầu cập nhật nhãn Sorting...
    void stopUpdatingSortingLabel(); // Phương thức dừng cập nhật nhãn Sorting...

signals:
    void startSort();
    void goBackHome();
    void goBackSelectSort();
    void setNumMethod(int num);

private:
    Ui::writeData *ui;
    vector<int> *theOriginVector;
    QTimer *timer;

    void copToVecto(); // Hàm sao chép dữ liệu từ giao diện vào vector
    void updateSortingLabel(); // Hàm cập nhật trạng thái "Sorting"
    int sortingStep; // Biến theo dõi trạng thái sorting

};

#endif // WRITEDATA_H
