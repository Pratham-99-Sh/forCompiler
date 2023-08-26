#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &arr, int s, int e){
    int pivot = arr[e];
    int i = s-1;
    for(int j=s; j<e; j++){
        if(arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[e]);
    return i+1;
}

int quickSort(vector<int> &arr, int s, int e, const int key){
    if(s>e) return -1;
    int pvt = partition(arr, s, e);
    if(pvt == key) return arr[pvt];
    if(pvt > key)
    return quickSort(arr, s, pvt-1, key);
    else
    return quickSort(arr, pvt+1, e, key);
}

int main(){
    vector<int> arr = {10, 5, 2, 0, 7, 6, 4};
    int result =  quickSort(arr, 0, arr.size()-1, 5);
    for(int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout << endl;
    cout << result << endl;
    return 0;
}