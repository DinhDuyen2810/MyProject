#ifndef SORTING_H
#define SORTING_H

#include <QObject>
#include <vector>

using namespace std;

class sorting : public QObject {
    Q_OBJECT
public:
    explicit sorting(QObject *parent = nullptr) : QObject(parent) {}
    // Hàm xử lý sắp xếp
    void executeSort(int sortType, std::vector<int>& numbers);

signals:
    void sortingCompleted(const std::vector<int>& sortedNumbers, long long runTime);
    void updateRunTime(long long runTime);
    void allSortingCompleted();

public slots:
    void startSorting(int sortType, std::vector<int>& numbers);

private:
    // Sap xep noi bot
    void bubbleSort(vector<int>& vectoInt);

    // Sap xep chen
    void insertionSort(vector<int>& vectoInt);

    //Tron
    void merge(vector<int>& vectoInt, int prev, int mid, int after);
    // Sap xep tron
    void mergeSort(vector<int>& vectoInt, int prev, int after);

    // Sap xep chon
    void selectionSort(vector<int>& vectoInt);

    //sap xep nhanh
    void quickSort(vector<int>& vectoInt, int prev, int after);

    //sap xep doi cho
    void interchangeSort(vector<int>& vectoInt);

    //vun
    void heapify(vector<int>& vectoInt, int i, int lastHeap);
    //day dung cay
    void buildHeap(vector<int>& vectoInt);
    //sap xep vun dong
    void heapSort(vector<int>& vectoInt);

    //InsertionSort cho ShellSort
    void insertion(vector<int>& vectoInt, int idx);
    //sap xep vo xo
    void shellSort(vector<int>& vectoInt);

    //sap xep dem
    void countingSort(vector<int>& vectoInt);

    // CountingSort ho tro sap xep theo co so
    void countingSortByDigit(vector<int>& vectoInt, int exp, bool isNegative);
    // RadixSort ho tro ca so am
    void radixSort(vector<int>& vectoInt);

    //sap xep thung
    void bucketSort(vector<int>& vectoInt);

    //sap xep flash
    void flashSort(vector<int>& vectoInt);

    //sap xep cocktail
    void shakerSort(vector<int>& vectoInt);

    // Ham Insertion Sort cho CubeSort
    void insertionOfCube(vector<int>& vectoInt, int left, int right);
    //Sap xep song song
    void cubeSort(vector<int>& vectoInt);
};

#endif // SORTING_H
