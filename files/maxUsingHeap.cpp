#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < n and arr[l] > arr[largest])
        largest = l;

    if(r < n and arr[r] > arr[largest])
        largest = r;

    if(largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n)
{
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = 6;

    buildHeap(arr, n);

    cout << "maxElement: " << arr[0] << endl;

    return 0;
}