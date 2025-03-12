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
void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void interchangeSort(int arr[], int n)
{
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(arr[j] < arr[i]){
                swap(arr, i, j);
            }    
            printArr(arr, n);
        }
    }
}

int main() {
    int arr[15];
    srand(time(NULL));

    for (int i = 0; i < 6; i++) {
        arr[i] = rand() % 50; 
    }
    interchangeSort(arr, 6);
    printArr(arr, 6);
    return 0;
}
