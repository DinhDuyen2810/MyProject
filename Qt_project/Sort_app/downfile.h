#ifndef DOWNFILE_H
#define DOWNFILE_H

#include <QWidget>

namespace Ui {
class downFile;
}

class downFile : public QWidget
{
    Q_OBJECT

public:
    explicit downFile(QWidget *parent = nullptr);
    ~downFile();

signals:
    void goBackHome();
    void onDownFileDialog();

public slots:
    void updateStatus(bool success, const QString &filePath);

private:
    Ui::downFile *ui;
};

#endif // DOWNFILE_H
