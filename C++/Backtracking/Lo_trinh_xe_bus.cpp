#include <iostream>
#include <climits>

using namespace std;

const int n = 5; // 5 hành khách -> 2n = 10 điểm + điểm xuất phát
const int K = 3; // Sức chứa tối đa của xe
int dis[11][11] = {
    {  0, 12, 10, -1, 30, 25, -1, 20, -1, -1, 15},
    { 12,  0, 18, 16, -1, 35, 40, -1, 22, -1, 28},
    { 10, 18,  0, 14, 22, -1, 20, 30, -1, 26, -1},
    { -1, 16, 14,  0, 12, 24, 28, -1, 35, 40, 18},
    { 30, -1, 22, 12,  0, 18, -1, 26, 28, -1, 24},
    { 25, 35, -1, 24, 18,  0, 16, 20, -1, 30, 26},
    { -1, 40, 20, 28, -1, 16,  0, 22, 18, 14, 12},
    { 20, -1, 30, -1, 26, 20, 22,  0, 24, 18, 10},
    { -1, 22, -1, 35, 28, -1, 18, 24,  0, 20, 14},
    { -1, -1, 26, 40, -1, 30, 14, 18, 20,  0, 16},
    { 15, 28, -1, 18, 24, 26, 12, 10, 14, 16,  0}
};

int X[2 * n + 1]; // Lưu đường đi tạm thời
int bestPath[2 * n + 1]; // Lưu đường đi tối ưu
int path, real_path = INT_MAX; // Lưu đường đi tối ưu
bool visited[11] = {false}; // Đánh dấu điểm đã đi
int load = 0; // Số hành khách trên xe
int Cmin = INT_MAX; // Cạnh nhỏ nhất (để cắt nhánh hiệu quả)

void updateBest(){
    if(path + dis[X[2 * n]][0] < real_path){
        real_path = path + dis[X[2 * n]][0];
        for(int i = 0; i <= 2 * n; i++){
            bestPath[i] = X[i];
        }
    }
}

bool check(int v){
    if(visited[v]){
        return false;
    }
    if(v > n){
        if(!visited[v - n]){
            return false;
        }
    } else {
        if(load + 1 > K){
            return false;
        }
    }
    return true;
}

void Try(int k){
    for(int v = 1; v <= 2 * n; v++){
        if(check(v)){
            X[k] = v;
            visited[v] = true;
            path += dis[X[k - 1]][v];
            if(v > n){
                load--;
            } else {
                load++;
            }
            if(k == 2 * n){
                updateBest();
            } else {
                if(path + (2 * n - k + 1) * Cmin < real_path){
                    Try(k + 1);
                }
            }
            if(v > n){
                load++;
            } else {
                load--;
            }
            visited[v] = false;
            path -= dis[X[k - 1]][v];
        }
    }
}




int main(){
    // Tìm giá trị nhỏ nhất của ma trận d để cắt nhánh hiệu quả
    for (int i = 0; i <= 2 * n; i++) {
        for (int j = 0; j <= 2 * n; j++) {
            if (i != j && dis[i][j] < Cmin) {
                Cmin = dis[i][j];
            }
        }
    }

    X[0] = 0; // Xuất phát từ điểm 0
    visited[0] = true;

    Try(1);

    // In kết quả
    cout << "Chi phi toi uu: " << real_path << endl;
    cout << "Duong di toi uu: ";
    for (int i = 0; i <= 2 * n; i++) {
        cout << bestPath[i] << " -> ";
    }
    cout << "0" << endl;

    return 0;
}