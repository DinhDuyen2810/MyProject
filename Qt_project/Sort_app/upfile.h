#ifndef UPFILE_H
#define UPFILE_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class upFile;
}

class upFile : public QWidget
{
    Q_OBJECT

public:
    explicit upFile(QWidget *parent = nullptr);
    ~upFile();
    void startUpdatingSortingLabel(); // Phương thức bắt đầu cập nhật nhãn Sorting...
    void stopUpdatingSortingLabel(); // Phương thức dừng cập nhật nhãn Sorting...

signals:
    void goBackHome();
    void goBackSelectSort();
    void onOpenFileDialog();
    void startSort();

public slots:
    void updateStatus(bool success, const QString &filePath);

private:
    Ui::upFile *ui;
    QTimer *timer;
    void updateSortingLabel(); // Hàm cập nhật trạng thái "Sorting"
    int sortingStep; // Biến theo dõi trạng thái sorting
};

#endif // UPFILE_H
