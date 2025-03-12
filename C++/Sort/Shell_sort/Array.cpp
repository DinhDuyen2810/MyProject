#include <iostream>
#include <cstdlib> 
#include <ctime>
using namespace std;

void printArr(int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void insertion(int arr[], int n, int idx)
{
    for(int i = 0; i < idx; i++){
        for(int j = i + idx; j < n; j += idx){
            int key = arr[j];
            while((j - idx) >=0 && key < arr[j - idx]){
                arr[j] = arr[j - idx];
                j = j - idx;
            }
            arr[j] = key;
        }
    }
}
void shellSort(int arr[], int n)
{
    insertion(arr, n, 10);
    insertion(arr, n, 4);
    insertion(arr, n, 1);
}

int main() {
    int arr[100];
    srand(time(NULL));

    for (int i = 0; i < 25; i++) {
        arr[i] = rand() % 500; 
    }
    shellSort(arr, 25);
    printArr(arr, 25);
    return 0;
}
