#include "outcomparion.h"
#include "ui_outcomparion.h"

outComparion::outComparion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::outComparion)
{
    ui->setupUi(this);
    connect(ui->btn_goHome, &QPushButton::clicked, this, &outComparion::goBackHome);
}

outComparion::~outComparion()
{
    delete ui;
}
void outComparion::setVector(vector<pair<int, long long>> &vec) {
    listComparion = &vec;

    // Cập nhật giá trị 'first' trong mỗi phần tử
    for (int i = 0; i < listComparion->size(); i++) {
        (*listComparion)[i].first = i + 1;  // Cập nhật 'first' theo chỉ số
    }

    // Sắp xếp vector dựa trên thời gian chạy (second) tăng dần
    std::sort(listComparion->begin(), listComparion->end(), [](const pair<int, long long>& a, const pair<int, long long>& b) {
        return a.second < b.second; // Sắp xếp tăng dần theo thời gian
    });

    updateTable();
}


void outComparion::updateTable() {
    if (!listComparion) {
        return;
    }

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"                                 Tên Thuật Toán                                 ", "Thời Gian Chạy"});

    for (size_t i = 0; i < listComparion->size(); ++i) {
        if ((*listComparion)[i].first > 0 && (*listComparion)[i].first <= 14 && (*listComparion)[i].second != 0) {
            QString algorithmName;
            switch ((*listComparion)[i].first) {
                case 1: algorithmName = "Bubble Sort"; break;
                case 2: algorithmName = "Heap Sort"; break;
                case 3: algorithmName = "Insertion Sort"; break;
                case 4: algorithmName = "Interchange Sort"; break;
                case 5: algorithmName = "Merge Sort"; break;
                case 6: algorithmName = "Quick Sort"; break;
                case 7: algorithmName = "Selection Sort"; break;
                case 8: algorithmName = "Shell Sort"; break;
                case 9: algorithmName = "Counting Sort"; break;
                case 10: algorithmName = "Radix Sort"; break;
                case 11: algorithmName = "Bucket Sort"; break;
                case 12: algorithmName = "Flash Sort"; break;
                case 13: algorithmName = "Shaker Sort"; break;
                case 14: algorithmName = "Cube Sort"; break;
                default: algorithmName = "Unknown"; break;
            }
            long long runTime = (*listComparion)[i].second;
            QString runtime = "";
            if (runTime < 1000) {
                runtime = "    " + QString::number(runTime) + " microseconds\n";
            } else if (runTime < 1000000) {
                runtime = "    " + QString::number(runTime / 1000.0) + " milliseconds\n";
            } else if (runTime < 1000000000) {
                runtime = "    " + QString::number(runTime / 1000000.0) + " seconds\n";
            }

            int currentRow = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(currentRow);

            QTableWidgetItem* nameItem = new QTableWidgetItem(algorithmName);
            ui->tableWidget->setItem(currentRow, 0, nameItem);

            QTableWidgetItem* timeItem = new QTableWidgetItem(runtime);
            ui->tableWidget->setItem(currentRow, 1, timeItem);

        }
    }

    ui->tableWidget->resizeColumnsToContents();
}
