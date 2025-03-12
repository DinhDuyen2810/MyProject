#include <cstdlib> 
#include <ctime> 
#include <algorithm>
#include <cmath>
#include "Sort.h"

using namespace std;

// Sap xep noi bot
void bubbleSort(vector<int>& vectoInt) {
    int n = vectoInt.size();
    for (int i = 0; i != n; ++i) {
        bool checkSwap = false;
        for (int j = 0; j != n - i - 1; ++j) {
            if (vectoInt[j] > vectoInt[j + 1]) {
                swap(vectoInt[j], vectoInt[j + 1]);
                checkSwap = true;
            }
        }
        if (!checkSwap) {
            break;
        }
    }
}

// Sap xep chen
void insertionSort(vector<int>& vectoInt) {
    int n = vectoInt.size();
    for (int i = 1; i < n; i++) {
        int key = vectoInt[i];
        int j = i - 1;
        // Di chuyen phan tu > key sang phai
        while (j >= 0 && vectoInt[j] > key) {
            vectoInt[j + 1] = vectoInt[j];
            j--;
        }
        // gan key o vi tri cuoi
        vectoInt[j + 1] = key;
    }
}

//Tron
void merge(vector<int>& vectoInt, int prev, int mid, int after)
{
    if(mid == after){
        if(vectoInt[prev] > vectoInt[after]){
            swap(vectoInt[prev], vectoInt[after]);
        }
        return;
    }
    vector<int> leftVector(mid - prev);
    vector<int> rightVector(after - mid + 1);
    for(int i = 0; i < mid - prev; i++){
        leftVector[i] = vectoInt[prev + i];
    }
    for(int i = mid; i <= after; i++){
        rightVector[i - mid] = vectoInt[i];
    }
    int j, k, l;
    j = k = 0;
    l = prev;
    while(j < mid - prev && k < after - mid + 1){
        if(leftVector[j] < rightVector[k]){
            vectoInt[l++] = leftVector[j++];
            continue;
        }
        vectoInt[l++] = rightVector[k++];
    }
    while(j < mid - prev){
        vectoInt[l++] = leftVector[j++];
    }
    while(k < after - mid + 1){
        vectoInt[l++] = rightVector[k++];
    }
}
// Sap xep tron
void mergeSort(vector<int>& vectoInt, int prev, int after)
{
    if(prev < after){
        int mid = (after + prev + 1) / 2;
        mergeSort(vectoInt, prev, mid - 1);
        mergeSort(vectoInt, mid, after);
        merge(vectoInt, prev, mid, after);
    }
    return;
}

// Sap xep chon
void selectionSort(vector<int>& vectoInt) {
    int n = vectoInt.size();
    for(int i = 0; i < n; i++){
        int minIdx = i;
        for(int j = i + 1; j < n; j++){
            if(vectoInt[j] < vectoInt[minIdx]){
                minIdx = j;
            }    
        }
        if(i != minIdx){
            swap(vectoInt[i], vectoInt[minIdx]);
        }
    }
}

//sap xep nhanh
void quickSort(vector<int>& vectoInt, int prev, int after){
    if(prev < after){
        srand(time(0));
        int pivotIndex = prev + rand() % (after - prev + 1); // Chon pivot ngau nhien
        swap(vectoInt[prev], vectoInt[pivotIndex]); // Chuyen pivot
        int lastOfsmall = prev + 1;
        for(int i = lastOfsmall; i <= after; i++){
            if(vectoInt[i] <= vectoInt[prev]){
                if(i != lastOfsmall){
                    swap(vectoInt[i], vectoInt[lastOfsmall]);
                }
                lastOfsmall++;
            } 
        }
        swap(vectoInt[lastOfsmall - 1], vectoInt[prev]);
        quickSort(vectoInt, prev, lastOfsmall - 2);
        quickSort(vectoInt, lastOfsmall, after);
    }
}

//sap xep doi cho
void interchangeSort(vector<int>& vectoInt)
{
    int n = vectoInt.size();
    for(int i = 0; i < n; i++){
        bool swapped = false; //kiem tra xem co doi cho khong
        for(int j = i + 1; j < n; j++){
            if(vectoInt[j] < vectoInt[i]){
                swap(vectoInt[j], vectoInt[i]);
                swapped = true;
            }    
        }
        if (!swapped) {
            break; 
        }
    }
}

//vun
void heapify(vector<int>& vectoInt, int i, int lastHeap)
{
    int L = 2 * i + 1;
    int R = 2 * i + 2;
    int max = i;
    if(L < lastHeap && vectoInt[L] > vectoInt[i]){
        max = L;
    }
    if(R < lastHeap && vectoInt[R] > vectoInt[max]){
        max = R;
    }
    if(max != i){
        swap(vectoInt[i], vectoInt[max]);
        heapify(vectoInt, max, lastHeap);
    }
}
//day dung cay
void buildHeap(vector<int>& vectoInt)
{
    int n = vectoInt.size();
    for(int i = n / 2 - 1 ; i >= 0; i--){
        heapify(vectoInt, i, n);
    }
}
//sap xep vun dong
void heapSort(vector<int>& vectoInt)
{
    buildHeap(vectoInt);
    int n = vectoInt.size();
    for(int i = n - 1; i >= 0; i--){
        swap(vectoInt[0], vectoInt[i]);
        heapify(vectoInt, 0, i);
    }
}

//InsertionSort cho ShellSort
void insertion(vector<int>& vectoInt, int idx)
{
    int n = vectoInt.size();
    for(int i = 0; i < idx; i++){
        for(int j = i + idx; j < n; j += idx){
            int key = vectoInt[j];
            while((j - idx) >= 0 && key < vectoInt[j - idx]){
                vectoInt[j] = vectoInt[j - idx];
                j = j - idx;
            }
            vectoInt[j] = key;
        }
    }
}
//sap xep vo xo
void shellSort(vector<int>& vectoInt)
{
    int n = vectoInt.size();
    int k = 10;
    while(k > 0){
        int gap = pow(2, k) - 1; // chon gap theo day hibbard
        if(gap > n / 2){
            --k;
            continue;
        }
        insertion(vectoInt, gap);
        --k;
    }
}

//sap xep dem
void countingSort(vector<int>& vectoInt){
    int max = *max_element(vectoInt.begin(), vectoInt.end());
    int min = *min_element(vectoInt.begin(), vectoInt.end());
    int n = vectoInt.size();
    vector<int> count(max - min + 1, 0);
    for(int i = 0; i < n; i++){
        count[vectoInt[i] - min]++;
    }
    for(int i = 1; i < count.size(); i++){
        count[i] += count[i - 1];
    }
    vector<int> output(n);
    for(int i = n - 1; i >= 0; i--){
        output[count[vectoInt[i] - min] - 1] = vectoInt[i];
        --count[vectoInt[i] - min];
    }
    vectoInt = output;
}

// CountingSort ho tro sap xep theo co so
void countingSortByDigit(vector<int>& vectoInt, int exp, bool isNegative){
    int n = vectoInt.size();
    vector<int> count(10, 0);
    vector<int> output(n);

    // Dem so lan xuat hien cua cac chu so (tai vi tri exp)
    for (int i = 0; i < n; i++) {
        int digit = abs(vectoInt[i] / exp) % 10;  // Lay gia tri tuyet doi
        count[digit]++;
    }

    // Tich luy (cumulative sum) neu la so duong, nguoc lai neu la so am
    if (!isNegative) {
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
    } else {
        for (int i = 8; i >= 0; i--) {  // Tich luy tu cuoi ve dau (dao nguoc)
            count[i] += count[i + 1];
        }
    }

    // Xay dung mang output
    for (int i = n - 1; i >= 0; i--) {
        int digit = abs(vectoInt[i] / exp) % 10;
        output[--count[digit]] = vectoInt[i];
    }

    vectoInt = output;
}

//sap xep theo co so
void radixSort(vector<int>& vectoInt){
    // Tach so am va so duong
    vector<int> negatives, positives;
    for (int num : vectoInt) {
        if (num < 0) {
            negatives.push_back(num);
        } else {
            positives.push_back(num);
        }
    }

    // Sap xep so duong
    int maxPositive = positives.empty() ? 0 : *max_element(positives.begin(), positives.end());
    for (int exp = 1; maxPositive / exp > 0; exp *= 10) {
        countingSortByDigit(positives, exp, false);
    }

    // Sap xep so am
    int maxNegative = negatives.empty() ? 0 : abs(*min_element(negatives.begin(), negatives.end()));
    for (int exp = 1; maxNegative / exp > 0; exp *= 10) {
        countingSortByDigit(negatives, exp, true);
    }

    // Ket hop so am (dao nguoc thu tu) va so duong
    vectoInt.clear();
    reverse(negatives.begin(), negatives.end());  // So am can dao nguoc
    vectoInt.insert(vectoInt.end(), negatives.begin(), negatives.end());
    vectoInt.insert(vectoInt.end(), positives.begin(), positives.end());
}

//sap xep thung
void bucketSort(vector<int>& vectoInt){
    int max = *max_element(vectoInt.begin(), vectoInt.end());
    int min = *min_element(vectoInt.begin(), vectoInt.end());
    int bucketCount = 100;
    int delta = (max - min + 1) / bucketCount; // dai gia tri moi bucket
    if(delta == 0){
        delta = 1;
    }
    vector<vector<int>> buckets(bucketCount);
     for (int num : vectoInt) {
        int index = (num - min) / delta;
        if (index == bucketCount) { 
            index--;
        }
        buckets[index].push_back(num);
    }
    for (auto& bucket : buckets) {
        insertionSort(bucket);
    }
    vectoInt.clear();
    for (const auto& bucket : buckets) {
        vectoInt.insert(vectoInt.end(), bucket.begin(), bucket.end());
    }
}

//sap xep flash
void flashSort(vector<int>& vectoInt){
    int n = vectoInt.size();
    if (n <= 1) return;

    // Tim gia tri nho nhat va lon nhat
    int minValue = *min_element(vectoInt.begin(), vectoInt.end());
    int maxIndex = max_element(vectoInt.begin(), vectoInt.end()) - vectoInt.begin();
    int maxValue = vectoInt[maxIndex];

    // Neu tat ca gia tri giong nhau, khong can sap xep
    if (minValue == maxValue) return;

    // So luong nhom (bucket)
    int bucketCount = int(0.45 * n);
    vector<int> bucketCounts(bucketCount, 0);

    // Tinh ty le de xac dinh chi so nhom
    double scaleFactor = (double)(bucketCount - 1) / (maxValue - minValue);

    // Phan phoi phan tu vao cac nhom
    for (int i = 0; i < n; i++) {
        int bucketIndex = int(scaleFactor * (vectoInt[i] - minValue));
        bucketCounts[bucketIndex]++;
    }
    for (int i = 1; i < bucketCount; i++) {
        bucketCounts[i] += bucketCounts[i - 1];
    }

    // Dua phan tu lon nhat ve dau mang
    swap(vectoInt[maxIndex], vectoInt[0]);

    // Hoan vi cac phan tu trong mang
    int numMoves = 0; // Dem so lan hoan vi
    int currentIndex = 0; // Vi tri hien tai
    int currentBucket = bucketCount - 1; // Nhom hien tai
    int flashValue; // Gia tri flash

    while (numMoves < n - 1) {
        // Di chuyen den nhom tiep theo neu can
        while (currentIndex > bucketCounts[currentBucket] - 1) {
            currentIndex++;
            currentBucket = int(scaleFactor * (vectoInt[currentIndex] - minValue));
        }
        flashValue = vectoInt[currentIndex]; // Gia tri flash hien tai

        // Hoan vi vong tron trong nhom
        while (currentIndex != bucketCounts[currentBucket]) {
            currentBucket = int(scaleFactor * (flashValue - minValue));
            int temp = vectoInt[--bucketCounts[currentBucket]];
            vectoInt[bucketCounts[currentBucket]] = flashValue;
            flashValue = temp;
            numMoves++;
        }
    }
    insertionSort(vectoInt); // Sap xep mang khi da hoan vi
}

//sap xep cocktail
void shakerSort(vector<int>& vectoInt){
    int left = 0;
    int right = vectoInt.size() - 1;
    bool swapped = false;
    while(left < right){
        swapped = false;
        for(int i = left; i < right; i++){
            if(vectoInt[i] > vectoInt[i + 1]){
                swap(vectoInt[i], vectoInt[i + 1]);
                swapped = true;
            }
        } 
        if(!swapped){
            break;
        }
        right--;
        swapped = false;
        for(int i = right; i > left; i--){
            if(vectoInt[i] < vectoInt[i - 1]){
                swap(vectoInt[i], vectoInt[i - 1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
        left++;
    }                             
}

const int CUBE_SIZE = 8;
// Ham Insertion Sort cho CubeSort
void insertionOfCube(vector<int>& vectoInt, int left, int right){
    for (int i = left + 1; i <= right; ++i) {
        int key = vectoInt[i];
        int j = i - 1;
        while (j >= left && vectoInt[j] > key) {
            vectoInt[j + 1] = vectoInt[j];
            --j;
        }
        vectoInt[j + 1] = key;
    }
}
//Sap xep song song
void cubeSort(vector<int>& vectoInt){
    int n = vectoInt.size();

    // Phan chia mang thanh cac cubes
    for (int i = 0; i < n; i += CUBE_SIZE) {
        int end = min(i + CUBE_SIZE, n);  // Dam bao khong vuot qua pham vi mang
        insertionOfCube(vectoInt, i, end - 1); 
    }

    // Hop nhat cac khoi bang mot cach thu cong
    vector<int> temp(n);
    int len = CUBE_SIZE;
    
    while (len < n) {
        for (int i = 0; i < n; i += 2 * len) {
            int mid = min(i + len, n); 
            int end = min(i + 2 * len, n);
            
            // Hop nhat 2 mang con da sap xep vao mang tam thoi
            merge(vectoInt.begin() + i, vectoInt.begin() + mid,
                       vectoInt.begin() + mid, vectoInt.begin() + end,
                       temp.begin() + i);
        }
        copy(temp.begin(), temp.end(), vectoInt.begin());  // Copy lai vao mang goc
        len *= 2;  // Tang kich thuoc khoi hop nhat
    }
}

