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

void insertionSort(int arr[], int n)
{
    for(int i = 1; i < n; i++){
        int key = arr[i];
        for(int j = i; j >= 0; j--){
            if(arr[j - 1] > key){
                arr[j] = arr[j - 1];
            } else {
                arr[j] = key;
                break;
            }
        }
        
        printArr(arr, 6);
    }
}

int main() {
    int arr[6];
    srand(time(NULL));

    for (int i = 0; i < 6; i++) {
        arr[i] = rand() % 100; 
    }
    printArr(arr, 6);
    insertionSort(arr, 6);
    printArr(arr, 6);
    return 0;
}
