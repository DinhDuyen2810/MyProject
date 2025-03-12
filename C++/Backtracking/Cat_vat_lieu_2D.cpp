#include <iostream>

using namespace std;

const int W = 8; // Chiều rộng khung
const int H = 6; // Chiều cao khung
const int n = 6; // Số hình chữ nhật

int w[n] = {3, 4, 2, 5, 3, 1}; // Chiều rộng của từng hình chữ nhật
int h[n] = {2, 3, 4, 2, 3, 3}; // Chiều cao của từng hình chữ nhật

bool mark[W][H] = {false}; // Đánh dấu ô đã bị chiếm
int x[n], y[n], o[n]; // Lưu vị trí và hướng xoay

void print(){
    for (int k = 0; k < n; k++) {
        cout << "Hinh " << k + 1 << ": (" << x[k] << ", " << y[k] << ") ";
        cout << (o[k] == 1 ? "[xoay]\n" : "[nguyen]\n");
    }
    cout << "------------------------\n";
}

bool check(int vx, int vy, int vo, int k){
    int wk = w[k], hk = h[k];
    if(vo == 1){
        swap(wk, hk);
    }
    for(int i = vx; i < vx + wk; ++i){
        for(int j = vy; j < vy + hk; ++j){
            if(mark[i][j]){
                return false;
            }
        }
    }
    return true;
}

void doMark(int vx, int vy, int vo, int k, bool mark_value){
    int wk = w[k], hk = h[k];
    if(vo == 1){
        swap(wk, hk);
    }
    for(int i = vx; i < vx + wk; ++i){
        for(int j = vy; j < vy + hk; ++j){
            mark[i][j] = mark_value;
        }
    }
}

void Try(int k){
    for(int vo = 0; vo < 2; ++vo){
        int wk = w[k], hk = h[k];
        if(vo == 1){
            swap(wk, hk);
        }
        for(int vx = 0; vx <= W - wk; ++vx){
            for(int vy = 0; vy <= H - hk; ++vy){
                if(check(vx, vy, vo, k)){
                    x[k] = vx; 
                    y[k] = vy; 
                    o[k] = vo;
                    doMark(vx, vy, vo, k, true);
                    if(k + 1 == n){
                        print();
                        return;
                    }
                    Try(k + 1);
                    doMark(vx, vy, vo, k, false);
                }
            }
        }
    }
}


int main() {
    Try(0);
    return 0;
}