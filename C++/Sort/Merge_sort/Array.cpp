#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <algorithm>
using namespace std;

void printArr(int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void merge(int arr[], int prev, int mid, int after)
{
    if(mid == after){
        if(arr[prev] > arr[after]){
            swap(arr[prev], arr[after]);
        }
        return;
    }
    int brr[mid - prev];
    int crr[after - mid + 1];
    for(int i = 0; i < mid - prev; i++){
        brr[i] = arr[prev + i];
    }
    for(int i = mid; i <= after; i++){
        crr[i - mid] = arr[i];
    }
    int j, k, l;
    j = k = 0;
    l = prev;
    while(j < mid - prev && k < after - mid + 1){
        if(brr[j] < crr[k]){
            arr[l++] = brr[j++];
            continue;
        }
        arr[l++] = crr[k++];
    }
    while(j < mid - prev){
        arr[l++] = brr[j++];
    }
    while(k < after - mid + 1){
        arr[l++] = crr[k++];
    }
}
void mergeSort(int arr[], int prev, int after)
{
    if(prev < after){
        int mid = (after + prev + 1) / 2;
        mergeSort(arr, prev, mid - 1);
        mergeSort(arr, mid, after);
        merge(arr, prev, mid, after);
    }
    return;
}

int main() {
    int arr[15];
    srand(time(NULL));

    for (int i = 0; i < 15; i++) {
        arr[i] = rand() % 100; 
    }
    mergeSort(arr, 0, 14);
    printArr(arr, 15);
    return 0;
}
