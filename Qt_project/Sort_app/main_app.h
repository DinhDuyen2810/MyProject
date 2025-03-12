#ifndef MAIN_APP_H
#define MAIN_APP_H

#include <QWidget>

namespace Ui {
class main_app;
}

class main_app : public QWidget
{
    Q_OBJECT

public:
    explicit main_app(QWidget *parent = nullptr);
    ~main_app();

signals:
    void goToMain_sort();

private:
    Ui::main_app *ui;
};

#endif // MAIN_APP_H
