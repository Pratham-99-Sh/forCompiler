#include<iostream>
#include<vector>
using namespace std;

int stringBinarySearch(vector<string> &arr, int s, int e, string key){
if(s>e) return -1;
int mid = (s+e)/2;
if(arr[mid] == " "){
    int left = mid-1;
    int right = mid+1;
    while(true){
        if(left<s && right>e) return -1;
        else if(right<=e && arr[right]!=" "){
            mid = right;
            break;
        }
        else if(left>=s && arr[left]!=" "){
            mid = left;
            break;
        }
        left--;
        right++;
    }
}
if(arr[mid] == key) return mid;
if(arr[mid] > key) return stringBinarySearch(arr, s, mid-1, key);
return stringBinarySearch(arr, mid+1, e, key);
}

int main(){
vector<string> arr = {"at", " ", " ", " ", "ball", " ", " ", "car", " ", " ", "dad", " ", " "};

cout<<stringBinarySearch(arr, 0, arr.size()-1, "at");
return 0;
}