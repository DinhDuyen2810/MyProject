#include <bits/stdc++.h>

using namespace std;
// M[i][j]: min tinh tu arr[j] voi do rong 2^i
void prepare(vector<vector<int>> &M, vector<int> &arr){
    int n = arr.size();
    for(int i = 0; i < n; i++){
        M[0][i] = i;
    }
    for(int i = 1; (1 << i) <= n; ++i){
        for(int j = 0; j + (1 << i) - 1 < n; ++j){
            if(arr[M[i - 1][j]] < arr[M[i - 1][j + (1 << (i - 1))]]){
                M[i][j] = M[i - 1][j];
            } else {
                M[i][j] = M[i - 1][j + (1 << (i - 1))];
            }
        }
    }
}

int RMQ(int i, int j, vector<vector<int>> &M, vector<int> &arr){
    int k = log2(j - i + 1);
    return min(arr[M[k][i]], arr[M[k][j - (1 << k) + 1]]);
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
    vector<vector<int>> M(log2(n) + 1, vector<int>(n));
    prepare(M, arr);
    cout << "Nhap khoang cach i, j: ";
    cin >> i >> j;
    cout << "Ket qua: " << RMQ(i, j, M, arr) << endl;
}