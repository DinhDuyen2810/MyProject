#include <iostream>
#include <map>
#include <list>
#include <stack>

using namespace std;

bool checkDIRAC(int **arr, int nodes){
    int count;
    for(int i = 0; i < nodes; i++){
        count = 0;
        for(int j = 0; j < nodes; j++){
            if(arr[i][j] == 1){
                count ++;
            }
        }
        if(count < nodes / 2){
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int nodes, edges;
        cin >> nodes >> edges;
        int **arr = new int*[nodes];
        for(int j = 0; j < nodes; j++){
            arr[j] = new int[nodes];
            for(int k = 0; k < nodes; k++){
                arr[j][k] = 0;  
            }
        }
        for(int j = 0; j < edges; j++){
            int a, b;
            cin >> a >> b;
            arr[a - 1][b - 1] = 1;
            arr[b - 1][a - 1] = 1;
        }
        if(nodes >= 3 && !checkDIRAC(arr, nodes)){
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
        }

        for(int j = 0; j < nodes; j++) {
            delete[] arr[j];
        }
        delete[] arr;
    }  
    return 0;
}

