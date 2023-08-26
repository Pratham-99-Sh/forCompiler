#include<iostream>
#include<vector>
using namespace std;


int invCout = 0;

void merge(vector<int> &arr, int s, int e){
    int mid = (s+e)/2;
    int i = s;
    int j = mid+1;


    vector<int> temp;

    while(i<=mid && j<=e){
        if(arr[i] > arr[j]){
            temp.push_back(arr[j]);
            j++;
            invCout += mid-i+1;
        }
        else{
            temp.push_back(arr[i]);
            i++;
        }
    }    

    while(i<=mid){
        temp.push_back(arr[i]);
        i++;
    }

    while(j<=e){
        temp.push_back(arr[j]);
        j++;
    }

    int k = 0;
    for(int idx = s; idx <= e; idx++)
        arr[idx] = temp[k++];
    
}

void mergeSort(vector<int> &arr, int s, int e){
    if(s>=e) return;
    int mid = (s+e)/2;

    mergeSort(arr, s, mid);
    mergeSort(arr, mid+1, e);
    merge(arr, s, e);
}

int main(){
    vector<int> arr = {10, 5, 2, 0, 7, 6, 4};
    mergeSort(arr, 0, arr.size()-1);
    cout<<"Inversion Count: "<<invCout<<endl;
    for(int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}