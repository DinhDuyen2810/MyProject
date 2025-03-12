#include <iostream>

using namespace std;
int *a;
int *used;
int n;
void Try(int k){
    int choose = 0;
    for(int i = 1; i <= n; ++i){
        if(used[i - 1] != 0){
            continue;
        }
        choose = i;
        if(choose != 0){
            a[k - 1] = choose;
            used[choose - 1] = 1;
            if(k == n){
                for(int j = 0; j < n; ++j){
                    cout << a[j] << " ";
                }
                cout << endl;
            }
            else{
                Try(k + 1);
            }
            used[choose - 1] = 0;
        }
    }
    return;
}

int main() {
    cin >> n;
    a = new int[n];
    used = new int[n];
    fill_n(a, n, 0);
    fill_n(used, n, 0);
    Try(1);
    return 0;
}