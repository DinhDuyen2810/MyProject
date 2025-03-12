#include <bits/stdc++.h>

using namespace std;

void fillMaxVal(vector<int> &maxVal, int left, int right, vector<int> &arr, int index){
    if(left == right){
        maxVal[index] = arr[left];
    } else {
        int mid = (left + right) / 2;
        fillMaxVal(maxVal, left, mid, arr, 2 * index + 1);
        fillMaxVal(maxVal, mid + 1, right, arr, 2 * index + 2);
        maxVal[index] = max(maxVal[2 * index + 1], maxVal[2 * index + 2]);
    }
}

void updateMaxVal(vector<int> &maxVal, vector<int> &arr, int index, int value, int left, int right, int id){
    if(left == right){
        arr[index] = value;
        maxVal[id] = value;
    } else {
        int mid = (left + right) / 2;
        if(index > mid){
            updateMaxVal(maxVal, arr, index, value, mid + 1, right, 2 * id + 2);
        } else {
            updateMaxVal(maxVal, arr, index, value, left, mid, 2 * id + 1);
        }
        maxVal[id] = max(maxVal[2 * id + 1], maxVal[2 * id + 2]);
    }
}

int getMaxVal(vector<int> &maxVal, int left, int right, int index, int i, int j){
    
    if(i > right || j < left){
        return INT_MIN;
    }
    if(left >= i && right <= j){
        return maxVal[index];
    }
    int mid = (left + right) / 2;
    int maxLeft = getMaxVal(maxVal, left, mid, 2 * index + 1, i, j);
    int maxRight = getMaxVal(maxVal, mid + 1, right, 2 * index + 2, i, j);
    return max(maxLeft, maxRight);
    
}



int main(){
    vector<int> arr;
    int n;
    cout << "Nhap so phan tu: ";
    cin >> n;
    int i, j;
    for(i = 0; i < n; i++){
        cin >> j;
        arr.push_back(j);
    }
    vector<int> maxVal(2 * n - 1);
    fillMaxVal(maxVal, 0, n - 1, arr, 0);
    cout << "Nhap khoang cach: ";
    cin >> i >> j;
    cout << "Max: " << getMaxVal(maxVal, 0, n - 1, 0, i, j) << endl;

    cout << "Nhap toa do thay the va gia tri thay the:";
    cin >> i >> j;
    updateMaxVal(maxVal, arr, i, j, 0, n - 1, 0);

    cout << "Nhap khoang cach: ";
    cin >> i >> j;
    cout << "Max: " << getMaxVal(maxVal, 0, n - 1, 0, i, j) << endl;
}