#include <iostream>
using namespace std;
int sum = 0;
int check(int x, int y, int t, int n, int mt1[][9])
{
    int i, j, min_h, max_h, min_c, max_c;
    for(i = 0; i < n; i++)
    {
        if(mt1[i][y] == t) return 0;
        if(mt1[x][i] == t) return 0;
    }
    min_h = (x / 3) * 3; max_h = min_h + 2;
    min_c = (y / 3) * 3; max_c = min_c + 2;
    for(i = min_h; i <= max_h; i++)
        for(j = min_c; j <= max_c; j++)
          if(mt1[i][j] == t) return 0;
    return 1;
}

void Try(int i, int j, int mt1[][9], int n) {
    if (i == n){ 
        sum++; 
        return;
    }
    if (mt1[i][j] != 0){
        if(j == n - 1){
            Try(i + 1, 0, mt1, n); 
        } else {
            Try(i, j + 1, mt1, n);
        }
    } else {
        for(int t = 1; t <= n; t++){
            if (check(i , j , t, n, mt1)){  
                mt1[i][j] = t;
                if(j == n - 1){
                    Try(i + 1, 0, mt1, n);
                } else {
                    Try(i, j + 1, mt1, n); 
                }
                mt1[i][j] = 0;
            }
        }
    }
}
int main()
{
    int n = 9;
    int mt1[9][9];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> mt1[i][j];
        }
    }
    Try(0, 0, mt1 ,n);
    cout << sum;
    return 0;
}
