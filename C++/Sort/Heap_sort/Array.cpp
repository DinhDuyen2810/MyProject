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

void heapify(int arr[], int i, int n)
{
    int L = 2 * i + 1;
    int R = 2 * i + 2;
    int max = i;
    if(L <= n && arr[L] > arr[i]){
        max = L;
    }
    if(R <= n && arr[R] > arr[max]){
        max = R;
    }
    if(max != i){
        swap(arr, i, max);
        heapify(arr, max, n);
    }
}

void buildHeap(int arr[], int n)
{
    for(int i = (n - 1) / 2 ; i >= 0; i--){
        heapify(arr, i, n);
    }
}

void heapSort(int arr[], int n)
{
    buildHeap(arr, n);
    for(int i = n - 1; i >= 0; i--){
        swap(arr, 0, i);
        heapify(arr, 0, i - 1);
    }
}

int main() {
    int arr[15];
    srand(time(NULL));

    for (int i = 0; i < 15; i++) {
        arr[i] = rand() % 50; 
    }
    heapSort(arr, 15);
    printArr(arr, 15);
    return 0;
}
