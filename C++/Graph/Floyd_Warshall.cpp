#include <iostream>

using namespace std;

int main (){
    int nodes, edges;
    cin >> nodes >> edges;
    int **arr = new int*[nodes];
    int u, v, w;
    for (int i = 0; i < nodes; i++){
        arr[i] = new int[nodes];
        for (int j = 0; j < nodes; j++){
            arr[i][j] = -1;
        }
    }
    for (int i = 0; i < edges; i++){
        cin >> u >> v >> w;
        arr[u - 1][v - 1] = w;
    }
    for(int i = 0; i < nodes; i++){
        arr[i][i] = 0;
    }
    for(int i = 0; i < nodes; i++){
        for(int j = 0; j < nodes; j++){
            for(int k = 0; k < nodes; k++){
                if(j == i || k == i || j == k){
                    continue;
                }
                if(arr[j][i] != -1 && arr[i][k] != -1){
                    if(arr[j][k] == -1){
                        arr[j][k] = arr[j][i] + arr[i][k];
                    } else {
                        arr[j][k] = min(arr[j][k], arr[j][i] + arr[i][k]);
                    }
                }    
            }
        }
    }
    for(int i = 0; i < nodes; i++, cout << endl){
        for(int j = 0; j < nodes; j++){
            cout << arr[i][j] << " ";
        }
    }
} 
