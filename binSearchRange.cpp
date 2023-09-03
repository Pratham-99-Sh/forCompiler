#include <iostream>
#include <vector>
using namespace std;

// to find first occurence of number in sorted array
int f_o(vector<int> arr, int k){
    int s = 0, e = arr.size()-1;
    int mid = (s+e)/2;
    int ans = -1;
    while(s<=e){
        if(arr[mid] == k){
            ans = mid;
            e = mid-1;
        }
        else if(arr[mid] > k) e = mid-1;
        else s = mid+1;
        mid = (s+e)/2;
        }
        return ans;
}

// to find last occurence of number in sorted array
int l_o(vector<int> arr, int k){
    int s = 0, e = arr.size()-1;
    int mid = (s+e)/2;
    int ans = -1;
    while(s<=e){
        if(arr[mid] ==k)
        {
            ans = mid;
            s = mid+1;
        }
        else if(arr[mid] > k) e = mid-1;
        else s = mid+1;
        mid = (s+e)/2;
    } 
    return ans;
}

int main(){
    vector<int> arr = {1,2,3,4,5,6,7,8,8,8,8,8,8,8,8,9,10};
    int k = 8;
    cout<<f_o(arr,k)<<endl;
    cout<<l_o(arr,k)<<endl;
    return 0;
}