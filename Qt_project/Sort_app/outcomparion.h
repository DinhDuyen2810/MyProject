#ifndef OUTCOMPARION_H
#define OUTCOMPARION_H

#include <QWidget>
#include <vector>

using namespace std;

namespace Ui {
class outComparion;
}

class outComparion : public QWidget
{
    Q_OBJECT

public:
    explicit outComparion(QWidget *parent = nullptr);
    ~outComparion();
    void setVector(vector<pair<int, long long>> &vec);

signals:
    void goBackHome();

private:
    Ui::outComparion *ui;
    vector<pair<int, long long>> *listComparion;
    void updateTable();
};

#endif // OUTCOMPARION_H
