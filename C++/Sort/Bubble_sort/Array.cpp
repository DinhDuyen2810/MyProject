#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace chrono;

// In vector co n phan tu
void printArr(vector<int>& vectoInt)
{
    int n = vectoInt.size();
    for (int i = 0; i != n; ++i) {
        cout << vectoInt[i] << " ";
    }
    cout << endl;
}

// Doi vi tri i va j trong vector
void swap(vector<int>& vectoInt, int i, int j)
{
    int temp = vectoInt[i];
    vectoInt[i] = vectoInt[j];
    vectoInt[j] = temp;
}

// Sap xep noi bot
void bubbleSort(vector<int>& vectoInt) {
    int n = vectoInt.size();
    for (int i = 0; i != n; ++i) {
        bool checkSwap = false;
        for (int j = 0; j != n - i - 1; ++j) {
            if (vectoInt[j] > vectoInt[j + 1]) {
                swap(vectoInt, j, j + 1);
                checkSwap = true;
            }
        }
        if (!checkSwap) {
            break;
        }
    }
}

// In ra thoi gian chay
void printTime(long long time) {
    if (time < 1000) {
        cout << time << " nanoseconds" << endl;
    } else if (time < 1000000) {
        cout << time / 1000.0 << " microseconds" << endl;
    } else if (time < 1000000000) {
        cout << time / 1000000.0 << " milliseconds" << endl;
    } else {
        cout << time / 1000000000.0 << " seconds" << endl;
    }
}

// Doc du lieu tu file va gan vao vector
void readFromFile(vector<int>& vectoInt, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {  // Kiem tra neu khong mo duoc file
        cerr << "Khong mo duoc file " << filename << endl;
        return;
    }

    int n;
    file >> n;  // Doc so luong phan tu tu file
    if (file.fail()) {  // Kiem tra neu doc that bai
        cerr << "Loi dinh dang file: khong the doc so luong phan tu." << endl;
        return;
    }

    vectoInt.resize(n);  // Thiet lap kich thuoc vector
    for (int i = 0; i < n; ++i) {
        file >> vectoInt[i];
        if (file.fail()) {  // Kiem tra loi doc tung phan tu
            cerr << "Loi khi doc phan tu thu " << i << endl;
            vectoInt.clear();  // Xoa vector de tranh su dung du lieu khong day du
            return;
        }
    }

    file.close();
}

// Ghi du lieu ra file
void writeToFile(const vector<int>& vectoInt, const string& filename) {
    ofstream file(filename, ios::trunc); // Mo file o che do ghi de
    if (!file.is_open()) {  // Kiem tra neu khong mo duoc file
        cerr << "Khong mo duoc file " << filename << endl;
        return;
    }

    int n = vectoInt.size();
    for (int i = 0; i < n; ++i) {
        file << vectoInt[i];
        if (i != n - 1) {
            file << " ";  // Dau cach giua cac so
        }
    }

    file.close();
    cout << "Da ghi du lieu vao file " << filename << endl;
}

int main() {
    int choose;
    vector<int> vectoInt;
    cout << "Lua chon kieu du lieu:" << endl
         << "1. Doc tu file (input.txt)" << endl
         << "2. Tu nhap du lieu" << endl
         << "3. Random du lieu" << endl;
    cout << "Nhap lua chon (1, 2, hoac 3): ";
    cin >> choose;

    if (choose == 1) {
        readFromFile(vectoInt, "input.txt");
        if (vectoInt.empty()) {  // Neu doc file khong thanh cong
            cout << "Khong co du lieu trong vector." << endl;
            return 1;  
        }
    } else if (choose == 2 || choose == 3) {
        int n;
        cin >> n;
        vectoInt.resize(n);
        if (choose == 2) {
            for (int i = 0; i != n; i++) {
                cin >> vectoInt[i];
            }
        } else {
            srand(time(NULL));
            for (int i = 0; i < n; i++) {
                vectoInt[i] = rand() % 5000; 
            }
        }
        printArr(vectoInt);
    }

    auto start = high_resolution_clock::now();  // Do bat dau
    bubbleSort(vectoInt);
    auto end = high_resolution_clock::now();    // Do ket thuc
    cout << endl;

    if (choose != 1) {
        printArr(vectoInt);
    } else {
        // Ghi vao file output
        writeToFile(vectoInt, "output.txt");
    }

    // Tinh thoi gian chay
    auto duration = duration_cast<nanoseconds>(end - start);
    printTime(duration.count());
    return 0;
}
