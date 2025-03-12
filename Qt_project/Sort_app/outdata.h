#ifndef OUTDATA_H
#define OUTDATA_H

#include <QWidget>
#include <vector>

using namespace std;

namespace Ui {
class outData;
}

class outData : public QWidget
{
    Q_OBJECT

public:
    explicit outData(QWidget *parent = nullptr);
    ~outData();
    void outTheData(const vector<int>& theVector);
    void outTheRunTime(const long long runTime);

signals:
    void goBackHome();

private:
    Ui::outData *ui;
};

#endif // OUTDATA_H
