#include<iostream>
#include<vector>
using namespace std;

int rotatedBinSearch(vector<int> &arr, int key){
    int low = 0;
    int high = arr.size()-1;
 
    while(low <= high){
        int mid = (low + high)/2;
        if(arr[mid] == key) return mid;

        if(arr[mid] >= arr[low]){
            if(key >= arr[low] and key <= arr[mid])
                high = mid-1;
            else
                low = mid+1;
        }

        if(arr[mid] <= arr[high]){
            if(key >= arr[mid] and key <= arr[high])
                low = mid+1;
            else
                high = mid-1;
        }

    }

    return -1;
    
}

int main(){
    vector<int> arr = {4,5,6,7,0,1,2};
    int key = 0;
    cout<<rotatedBinSearch(arr, key);
    return 0;
}
