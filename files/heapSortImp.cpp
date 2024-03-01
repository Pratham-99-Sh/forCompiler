// c++ program to implement heap sort
#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i)
{
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < n and arr[l] < arr[smallest])
        smallest = l;

    if(r < n and arr[r] < arr[smallest])
        smallest = r;

    if(smallest != i)
    {
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void buildHeap(int arr[], int n)
{
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

void heapSort(int arr[], int n)
{
    buildHeap(arr, n);

    for(int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = 6;

    buildHeap(arr, n);
    heapSort(arr, n);

    for(auto x: arr)
        cout << x << " ";
    cout << endl;

    return 0;
}