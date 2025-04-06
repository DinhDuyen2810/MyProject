#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QPixmap>
#include <QParallelAnimationGroup>
#include <QTimer>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QThread>
#include <Qdebug>
#include <QMutex>
#include <QDebug>
#include <QVector>

#include <iostream>
#include <vector>
#include <queue>


using namespace std;
using namespace chrono;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupPages();
}
int numberOfSort = 0;
int numberOfMethod = 0;
int threadUIinPage = 0;
vector<int> theOriginVector;
long long runTime = 0;
vector<pair<int, long long>> listComparion(14);
int isComparion = 0;

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setNumSort(int num){
    numberOfSort = num;
}
void MainWindow::setNumMethod(int num){
    numberOfMethod = num;
}
void MainWindow::setThreadUIinPage(int num){
    threadUIinPage = num;
}
void MainWindow::setfirstListComparion(vector<int> chooseSort){
    for(int i = 0; i < 14; i++){
        listComparion[i].first = chooseSort[i];
    }
}



// Khởi tạo các trang
void MainWindow::setupPages(){

    this->setFixedSize(766, 574);

    // Loại bỏ khả năng phóng to/thu nhỏ
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // Khởi tạo stackedWidget
    stackedWidget = ui->stackedWidget;
    setCentralWidget(stackedWidget);
    // Khởi tạo các page
    pageMainApp = new main_app(this);
    pageMainSort = new main_sort(this);
    pageChooseSort = new chooseSort(this);
    pageSelectSort = new selectSort(this);
    pageUpFile = new upFile(this);
    pageDownFile = new downFile(this);
    pageWriteData = new writeData(this);
    pageOutData = new outData(this);
    pageRandom = new randomData(this);
    pageInfor = new inforOfSort(this);
    pageChooseComparion = new chooseToComparion(this);
    pageOutComparion = new outComparion(this);

    // Thêm trang vào stackedWidget
    stackedWidget->addWidget(pageMainApp);
    stackedWidget->addWidget(pageMainSort);
    stackedWidget->addWidget(pageChooseSort);
    stackedWidget->addWidget(pageSelectSort);
    stackedWidget->addWidget(pageUpFile);
    stackedWidget->addWidget(pageDownFile);
    stackedWidget->addWidget(pageWriteData);
    stackedWidget->addWidget(pageOutData);
    stackedWidget->addWidget(pageRandom);
    stackedWidget->addWidget(pageInfor);
    stackedWidget->addWidget(pageChooseComparion);
    stackedWidget->addWidget(pageOutComparion);

    // Đặt trang đầu tiên là pageMainApp
    stackedWidget->setCurrentWidget(pageMainApp);
    // Kết nối các tín hiệu chuyển trang
    connect(pageMainApp, &main_app::goToMain_sort, this, [this]() { goToPage(pageMainSort); });

    connect(pageMainSort, &main_sort::goBackHome, this, [this]() { goBackPage(pageMainApp); });
    connect(pageMainSort, &main_sort::goToChooseSort, this, [this]() {
        pageChooseSort->setIsInfor(0),
        goToPage(pageChooseSort);
    });
    connect(pageMainSort, &main_sort::goToChooseSortInfor, this, [this]() {
        pageChooseSort->setIsInfor(1),
        goToPage(pageChooseSort);
    });
    connect(pageMainSort, &main_sort::goToChooseComparion, this, [this]() {
        isComparion = 1;
        goToPage(pageChooseComparion); });
    connect(pageMainSort, &main_sort::setNumSort, pageSelectSort, &selectSort::setNumSort);

    connect(pageChooseSort, &chooseSort::goBackHome, this, [this]() { goBackPage(pageMainApp); });
    connect(pageChooseSort, &chooseSort::goBackMain_Sort, this, [this]() { goBackPage(pageMainSort); });
    connect(pageChooseSort, &chooseSort::goToSelectSort, this, [this]() { goToPage(pageSelectSort); });
    connect(pageChooseSort, &chooseSort::setNumSort, pageSelectSort, &selectSort::setNumSort);
    connect(pageChooseSort, &chooseSort::setNumSort, this, &MainWindow::setNumSort);
    connect(pageChooseSort, &chooseSort::goToInforSort, this, [this]() { goToPage(pageInfor); });
    connect(pageChooseSort, &chooseSort::setNumSort, pageInfor, &inforOfSort::setNumSort);

    connect(pageSelectSort, &selectSort::goBackHome, this, [this]() { goBackPage(pageMainApp); });
    connect(pageSelectSort, &selectSort::goBackChooseSort, this, [this]() {
        goBackPage(pageChooseSort),
        numberOfSort = 0;
    });
    connect(pageSelectSort, &selectSort::goBackChooseComparion, this, [this]() {
        goBackPage(pageChooseComparion),
        numberOfSort = 0;
    });
    connect(pageSelectSort, &selectSort::setNumMethod, this, &MainWindow::setNumMethod);
    connect(pageSelectSort, &selectSort::setNumMethod, this, &MainWindow::setThreadUIinPage);

    connect(pageSelectSort, &selectSort::goToUpFile, this, [this]() { goToPage(pageUpFile); });
    connect(pageSelectSort, &selectSort::goToWriteData, this, [this]() {
        pageWriteData->setVector(theOriginVector);
        goToPage(pageWriteData);
    });
    connect(pageSelectSort, &selectSort::goToRandomData, this, [this]() {
        pageRandom->setVector(theOriginVector);
        goToPage(pageRandom);
    });

    connect(pageUpFile, &upFile::goBackHome, this, [this]() { goBackPage(pageMainApp); });
    connect(pageUpFile, &upFile::goBackSelectSort, this, [this]() {
        goBackPage(pageSelectSort),
        theOriginVector.clear();
        theOriginVector.shrink_to_fit();
        numberOfMethod = 0;
        threadUIinPage = 0;
    });
    connect(pageUpFile, &upFile::onOpenFileDialog, this, &MainWindow::onOpenFileDialog);
    connect(this, &MainWindow::fileUploadStatus, pageUpFile, &upFile::updateStatus);
    connect(pageUpFile, &upFile::startSort, this, [this]() {
        if(isComparion == 0){
            setTheThread();
        } else {
            setTheThreadComparion();
        }
    });

    connect(pageDownFile, &downFile::goBackHome, this, [this]() { goBackPage(pageMainApp); });
    connect(pageDownFile, &downFile::onDownFileDialog, this, &MainWindow::onDownFileDialog);
    connect(this, &MainWindow::fileDownloadStatus, pageDownFile, &downFile::updateStatus);

    connect(pageWriteData, &writeData::goBackHome, this, [this]() { goBackPage(pageMainApp); });
    connect(pageWriteData, &writeData::goBackSelectSort, this, [this]() {
        goBackPage(pageSelectSort),
        theOriginVector.clear();
        theOriginVector.shrink_to_fit();
        numberOfMethod = 0;
        threadUIinPage = 0;
    });
    connect(pageWriteData, &writeData::startSort, this, [this]() {
        if(isComparion == 0){
            setTheThread();
        } else {
            setTheThreadComparion();
        }
    });
    connect(pageWriteData, &writeData::setNumMethod, this, &MainWindow::setNumMethod);

    connect(pageOutData, &outData::goBackHome, this, [this]() { goBackPage(pageMainApp); });

    connect(pageRandom, &randomData::goBackHome, this, [this]() { goBackPage(pageMainApp); });
    connect(pageRandom, &randomData::goBackSelectSort, this, [this]() { goBackPage(pageSelectSort); });
    connect(pageRandom, &randomData::startSort, this, [this]() {
        if(isComparion == 0){
            setTheThread();
        } else {
            setTheThreadComparion();
        }
    });
    connect(pageRandom, &randomData::setNumMethod, this, &MainWindow::setNumMethod);

    connect(pageInfor, &inforOfSort::goBackHome, this, [this]() { goBackPage(pageMainApp); });
    connect(pageInfor, &inforOfSort::goBackChooseSort, this, [this]() {
        goBackPage(pageChooseSort),
        numberOfSort = 0;
    });

    connect(pageChooseComparion, &chooseToComparion::goBackHome, this, [this]() {
        isComparion = 0;
        goBackPage(pageMainApp);
    });
    connect(pageChooseComparion, &chooseToComparion::goBackMain_Sort, this, [this]() {
        isComparion = 0;
        goBackPage(pageMainSort);
    });
    connect(pageChooseComparion, &chooseToComparion::goToSelectSort, this, [this]() { goToPage(pageSelectSort); });
    connect(pageChooseComparion, &chooseToComparion::setComparion, this, &MainWindow::setfirstListComparion);

    connect(pageOutComparion, &outComparion::goBackHome, this, [this]() { goBackPage(pageMainApp); });
}

// Cài đặt luồng sắp xếp
void MainWindow::setTheThread() {

    // Kiểm tra nếu luồng đã tồn tại thì không tạo lại
    if (sortThread && sortThread->isRunning()) {
        qDebug() << "Thread already running. Skipping new thread creation.";
        return;
    }

    // Kiểm tra nếu luồng đã tồn tại, giải phóng nó trước khi tạo lại
    if (sortThread) {
        sortThread->quit();
        sortThread->wait(); // Chờ cho luồng dừng hoàn toàn
        delete sortThread;
        qDebug() << "delete";
        sortThread = nullptr;
    }
    sortThread = new QThread(this);
    worker = new sorting();
    worker->moveToThread(sortThread);

    // Kết nối signal-slot để bắt đầu sắp xếp
    connect(sortThread, &QThread::started, worker, [this]() {
        qDebug() << "started";
        worker->startSorting(numberOfSort, theOriginVector);
    }, Qt::QueuedConnection);

        // Kết nối tín hiệu khi sắp xếp hoàn tất
    connect(worker, &sorting::sortingCompleted, this, [this](const std::vector<int>& sortedNumbers, long long runT) {
        theOriginVector = sortedNumbers;
        runTime = runT;
        qDebug() << "sortingCompleted";
        sortThread->quit();
    }, Qt::QueuedConnection);

        // Kết nối tín hiệu khi luồng đã hoàn tất
    connect(sortThread, &QThread::finished, this, [this]() {
        qDebug() << "finished";
        worker->deleteLater();
        sortThread->deleteLater();
        sortThread = nullptr;  // Đặt nullptr để nhận diện trạng thái luồng
        worker = nullptr;

            // Dừng cập nhật giao diện
        if (threadUIinPage == 1) {
            pageUpFile->stopUpdatingSortingLabel();
        } else if (threadUIinPage == 2) {
            pageWriteData->stopUpdatingSortingLabel();
        } else if (threadUIinPage == 3) {
            pageRandom->stopUpdatingSortingLabel();
        }

            // Chuyển trang sau khi sắp xếp hoàn tất
        if (numberOfMethod == 1) {
            goToPage(pageDownFile);
        } else {
             goToPage(pageOutData);
            pageOutData->outTheRunTime(runTime);
            pageOutData->outTheData(theOriginVector);
        }
    }, Qt::QueuedConnection);



    // Bắt đầu luồng
    sortThread->start();
    qDebug() << "Started_sort_thread";
    // Bắt đầu cập nhật giao diện
    if (threadUIinPage == 1) {
        pageUpFile->startUpdatingSortingLabel();
    } else if (threadUIinPage == 2) {
        pageWriteData->startUpdatingSortingLabel();
    } else if (threadUIinPage == 3) {
        pageRandom->startUpdatingSortingLabel();
    }
}

// Cài đặt luồng sắp xếp để so sánh
void MainWindow::setTheThreadComparion() {
    qDebug() << "setTheThreadComparion";
    if (sortThread && sortThread->isRunning()) {
        qDebug() << "Thread already running. Skipping new thread creation.";
        return;
    }

    // Kiểm tra nếu luồng đã tồn tại, giải phóng nó trước khi tạo lại
    if (sortThread) {
        sortThread->quit();
        sortThread->wait(); // Chờ cho luồng dừng hoàn toàn
        delete sortThread;
        qDebug() << "delete";
        sortThread = nullptr;
    }

    sortThread = new QThread(this);
    worker = new sorting();
    worker->moveToThread(sortThread);

    int totalSorts = std::count_if(listComparion.begin(), listComparion.end(), [](const auto& pair) {
        return pair.first == 1;
    });

    int* completedSorts = new int(0);

    connect(sortThread, &QThread::started, this, [this, completedSorts, totalSorts]() {

            // Dùng một vòng lặp để thực hiện các thuật toán tuần tự
        for (int i = 0; i < listComparion.size(); ++i) {
            if (listComparion[i].first == 1) {
                int numberOfSort = i + 1;
                qDebug() << "Preparing sort for algorithm:" << numberOfSort;
                // Dùng QEventLoop để đợi tín hiệu hoàn thành cho mỗi thuật toán
                QEventLoop loop;

                    // Cần kết nối lại tín hiệu mỗi lần bắt đầu thuật toán
                connect(worker, &sorting::sortingCompleted, &loop, &QEventLoop::quit);

                    // Kết nối tín hiệu "sortingCompleted" để cập nhật kết quả và tiếp tục với thuật toán khác
                connect(worker, &sorting::sortingCompleted, this, [this, completedSorts, totalSorts, i](const std::vector<int>& sortedNumbers, double runTime) {
                    // Kiểm tra xem tín hiệu đã được xử lý chưa
                    if (listComparion[i].second == 0) {
                        qDebug() << "Sorting completed callback triggered for algorithm:" << i + 1;
                        listComparion[i].second = static_cast<int>(runTime);
                        (*completedSorts)++;

                        // Nếu tất cả các thuật toán hoàn thành, phát tín hiệu
                        if (*completedSorts == totalSorts) {
                            emit worker->allSortingCompleted();
                        }
                    }
                }, Qt::QueuedConnection);

                 // Bắt đầu thuật toán và chờ tín hiệu "sortingCompleted"
                QMetaObject::invokeMethod(worker, [numberOfSort, this]() {
                    std::vector<int> localVector = theOriginVector; // Tạo bản sao
                    worker->startSorting(numberOfSort, localVector);
                }, Qt::QueuedConnection);
                // Đợi cho thuật toán hoàn thành
                loop.exec();
            }
        }
    });

        // Kết nối và dọn dẹp sau khi tất cả các thuật toán hoàn thành
    connect(worker, &sorting::allSortingCompleted, this, [this, completedSorts]() {
        // Dọn dẹp kết nối và xóa bộ nhớ
        disconnect(worker, &sorting::sortingCompleted, this, nullptr);
        sortThread->quit();
        delete completedSorts;
    });

        // Xử lý kết thúc của worker và sortThread
    connect(sortThread, &QThread::finished, this, [this]() {
        worker->deleteLater();
        sortThread->deleteLater();
        sortThread = nullptr;  // Đặt nullptr để nhận diện trạng thái luồng
        worker = nullptr;

            // Log kết quả
        for (int i = 0; i < listComparion.size(); ++i) {
            if (listComparion[i].first == 1) {
                qDebug() << "Index:" << i + 1
                         << "First:" << listComparion[i].first
                         << "Second (runtime):" << listComparion[i].second;
            }
        }


            // Cập nhật UI
        if (threadUIinPage == 1) {
            pageUpFile->stopUpdatingSortingLabel();
        } else if (threadUIinPage == 2) {
            pageWriteData->stopUpdatingSortingLabel();
        } else if (threadUIinPage == 3) {
            pageRandom->stopUpdatingSortingLabel();
        }
        pageOutComparion->setVector(listComparion);
        goToPage(pageOutComparion);
    });

    // Khởi động thread và bắt đầu cập nhật UI
    sortThread->start();
    qDebug() << "Started_sort_thread_compare";

    // Bắt đầu cập nhật UI cho page tương ứng
    if (threadUIinPage == 1) {
        pageUpFile->startUpdatingSortingLabel();
    } else if (threadUIinPage == 2) {
        pageWriteData->startUpdatingSortingLabel();
    } else if (threadUIinPage == 3) {
        pageRandom->startUpdatingSortingLabel();
    }
}

// Hiệu ứng đi đến trang nextPage
void MainWindow::goToPage(QWidget *nextPage){
    QWidget *currentWidget = ui->stackedWidget->currentWidget(); // Trang hiện tại
    QWidget *nextWidget = nextPage;                              // Trang tiếp theo

    // Đặt vị trí của trang tiếp theo ngay ngoài ngoài khung của stackedWidget
    nextWidget->move(ui->stackedWidget->width(), 0);
    nextWidget->show();

    // Tạo hiệu ứng dịch chuyển cho trang hiện tại (trượt ra ngoài)
    QPropertyAnimation *currentAnimation = new QPropertyAnimation(currentWidget, "geometry");
    currentAnimation->setDuration(300);
    currentAnimation->setStartValue(currentWidget->geometry());
    currentAnimation->setEndValue(QRect(-ui->stackedWidget->width(), 0, currentWidget->width(), currentWidget->height()));

    // Tạo hiệu ứng dịch chuyển cho trang tiếp theo (trượt vào)
    QPropertyAnimation *nextAnimation = new QPropertyAnimation(nextWidget, "geometry");
    nextAnimation->setDuration(300);
    nextAnimation->setStartValue(QRect(ui->stackedWidget->width(), 0, nextWidget->width(), nextWidget->height()));
    nextAnimation->setEndValue(QRect(0, 0, nextWidget->width(), nextWidget->height()));

    // Gộp hai hiệu ứng để chạy đồng thời
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    group->addAnimation(currentAnimation);
    group->addAnimation(nextAnimation);

    // Kết thúc hiệu ứng: Đặt trang tiếp theo làm trang hiện tại
    connect(group, &QParallelAnimationGroup::finished, [this, nextWidget]() {
        ui->stackedWidget->setCurrentWidget(nextWidget);
    });

    // Chạy hiệu ứng
    group->start(QAbstractAnimation::DeleteWhenStopped);
}
// Hiệu ứng đi về trang nextPage
void MainWindow::goBackPage(QWidget *nextPage){
    if(nextPage == pageMainApp){
        freeData();
    }
    qDebug() << "go Back";
    QWidget *currentWidget = ui->stackedWidget->currentWidget(); // Trang hiện tại
    QWidget *nextWidget = nextPage;                              // Trang tiếp theo

    // Đặt vị trí của trang tiếp theo ngay ngoài ngoài khung của stackedWidget
    nextWidget->move(-ui->stackedWidget->width(), 0);
    nextWidget->show();

    // Tạo hiệu ứng dịch chuyển cho trang hiện tại (trượt ra ngoài)
    QPropertyAnimation *currentAnimation = new QPropertyAnimation(currentWidget, "geometry");
    currentAnimation->setDuration(300);
    currentAnimation->setStartValue(currentWidget->geometry());
    currentAnimation->setEndValue(QRect(ui->stackedWidget->width(), 0, currentWidget->width(), currentWidget->height()));

    // Tạo hiệu ứng dịch chuyển cho trang tiếp theo (trượt vào)
    QPropertyAnimation *nextAnimation = new QPropertyAnimation(nextWidget, "geometry");
    nextAnimation->setDuration(300);
    nextAnimation->setStartValue(QRect(-ui->stackedWidget->width(), 0, nextWidget->width(), nextWidget->height()));
    nextAnimation->setEndValue(QRect(0, 0, nextWidget->width(), nextWidget->height()));

    // Gộp hai hiệu ứng để chạy đồng thời
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    group->addAnimation(currentAnimation);
    group->addAnimation(nextAnimation);

    // Kết thúc hiệu ứng: Đặt trang tiếp theo làm trang hiện tại
    connect(group, &QParallelAnimationGroup::finished, [this, nextWidget]() {
        ui->stackedWidget->setCurrentWidget(nextWidget);
    });

    // Chạy hiệu ứng
    group->start(QAbstractAnimation::DeleteWhenStopped);
}
// Tải lên file
void MainWindow::onOpenFileDialog()
{
    theOriginVector.clear();
    theOriginVector.shrink_to_fit();
    // Hiển thị hộp thoại chọn file
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("Vui lòng chọn file .txt"),
                                                    QDir::homePath(),  // Thư mục mặc định mở
                                                    tr("Text Files (*.txt);;All Files (*)")); // Bộ lọc file

    // Kiểm tra xem người dùng đã chọn file chưa
    if (!filePath.isEmpty()) {
        // Thành công, gửi tín hiệu với trạng thái và đường dẫn file
        emit fileUploadStatus(true, filePath);

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            while (!in.atEnd()) {
                QString line = in.readLine(); // Đọc từng dòng
                QStringList numbers = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts); // Tách theo khoảng trắng

                for (const QString &number : numbers) {
                    bool ok;
                    int value = number.toInt(&ok); // Chuyển thành số nguyên
                    if (ok) {
                        theOriginVector.push_back(value); // Thêm vào vector nếu chuyển đổi thành công
                    }
                }
            }
            file.close();
            qDebug() << "upFile_done";
        }

    } else {
        // Không thành công, gửi tín hiệu với trạng thái thất bại
        emit fileUploadStatus(false, QString());
    }
}
// Tải về file
void MainWindow::onDownFileDialog() {
    // Hiển thị hộp thoại lưu file
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    tr("Vui lòng chọn nơi lưu file"),
                                                    QDir::homePath() + "/output.txt", // Tên file mặc định
                                                    tr("Text Files (*.txt);;All Files (*)")); // Bộ lọc file

    if (!filePath.isEmpty()) {
        emit fileDownloadStatus(true, filePath);
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            if (runTime < 1000) {
                out << runTime << " microseconds\n";
            } else if (runTime < 1000000) {
                out << runTime / 1000.0 << " milliseconds\n";
            } else if (runTime < 1000000000) {
                out << runTime / 1000000.0 << " seconds\n";
            }
            qDebug() << "downFile_done";

            // Ghi dữ liệu từ theOriginVector
            for (int value : theOriginVector) {
                out << value << " "; // Ghi mỗi giá trị cách nhau bởi dấu cách
            }
            file.close();
        } else {
            emit fileDownloadStatus(false, QString());
        }
    }
}

// Giải phóng dung lượng
void MainWindow::freeData() {
    // Giải phóng và reset dữ liệu
    qDebug() << "freeData_done";
    theOriginVector.clear();
    theOriginVector.shrink_to_fit();  // Đảm bảo giải phóng bộ nhớ
    numberOfSort = 0;
    numberOfMethod = 0;
    threadUIinPage = 0;
    runTime = 0;
    isComparion = 0;
    for (int i = 0; i < listComparion.size(); ++i) {
        listComparion[i].first = 0;
        listComparion[i].second = 0;
    }
}



