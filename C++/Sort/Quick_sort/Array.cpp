#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <algorithm>
using namespace std;

void printArr(int arr[], int n)
{
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void quickSort(int arr[], int prev, int after)
{
    if(prev < after){
        int m = prev + 1;
        for(int i = m; i <= after; i++){
            if(arr[i] <= arr[prev]){
                if(i != m){
                    swap(arr[i], arr[m]);
                }
                m++;
            } 
        }
        swap(arr[m - 1], arr[prev]);
        quickSort(arr, prev, m - 2);
        quickSort(arr, m, after);
    }
}

int main() {
    int arr[15];
    srand(time(NULL));
    int n = 15;
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; 
    }
    printArr(arr, n);
    quickSort(arr, 0, n - 1);
    printArr(arr, n);
    return 0;
}
