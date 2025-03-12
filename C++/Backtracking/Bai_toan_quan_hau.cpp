#include <iostream>

using namespace std;
int **a;
int n;
bool check(int x, int y){
    for(int i = 0; i < n; ++i){
        if(a[x][i] == 1 || a[i][y] == 1){
            return false;
        }
    }
    for(int i = 0; i < n; ++i){
        if(x + i < n && y + i < n && a[x + i][y + i] == 1){
            return false;
        }
        if(x - i >= 0 && y - i >= 0 && a[x - i][y - i] == 1){
            return false;
        }
        if(x + i < n && y - i >= 0 && a[x + i][y - i] == 1){
            return false;
        }
        if(x - i >= 0 && y + i < n && a[x - i][y + i] == 1){
            return false;
        }
    }
    return true;
}

void Try(int k){
    for(int i = k - 1; i < n; ++i){
        for(int j = 0; j < n; ++j){
            
            if(a[i][j] == 0){
                if(check(i, j)){
                    a[i][j] = 1;
                    if(k == n){
                        for(int i = 0; i < n; ++i){
                            for(int j = 0; j < n; ++j){
                                cout << a[i][j] << " ";
                            }
                            cout << endl;
                        }
                        cout << endl;
                    } else {
                        Try(k + 1);
                    }
                    a[i][j] = 0;
                }
            }
        }
        
    }
    return;
}

int main() {
    cin >> n;
    a = new int*[n];
    for(int i = 0; i < n; ++i){
        a[i] = new int[n];
        fill_n(a[i], n, 0);
    }
    Try(1);
    // Giải phóng bộ nhớ
    for(int i = 0; i < n; ++i) {
        delete[] a[i];
    }
    delete[] a;
    return 0;
}