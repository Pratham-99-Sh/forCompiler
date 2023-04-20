#include<iostream>
#include<vector>
using namespace std;

class Heap{
    vector<int> arr;
    bool mode;  // 1 for min heap and 0 for max heap

    bool compare(int a, int b, bool type){
        if(type)
        return a<b;
        else
        return a>b;
    }

    void heapify(int i){
        int left = 2*i;
        int right = 2*i+1;
        int minIdx = i;
        if(left<arr.size() && compare(arr[left], arr[minIdx], mode)){
            minIdx = left;
        }
        if(right<arr.size() && compare(arr[right], arr[minIdx], mode)){
            minIdx = right;
        }
        if(minIdx!=i){
            swap(arr[i], arr[minIdx]);
            heapify(minIdx);
        }
    }

    public:
    Heap(int defSize = 10, bool type = true){   //type ==1 for min heap and 0 for max heap
        arr.reserve(defSize+1);
        arr.push_back(-1);
        mode = type;
    }

    void push(int data){
        arr.push_back(data);
        int idx = arr.size()-1;
        int parent = idx/2;
        while(idx>1 && compare(arr[idx], arr[parent], mode)){
            swap(arr[idx], arr[parent]);
            idx = parent;
            parent = parent/2;
        }
    }

    int top(){
        return arr[1];
    }

    void pop(){
        if(this->empty()) return;
        int lastIdx = arr.size()-1;    
        swap(arr[1], arr[lastIdx]);
        arr.pop_back();
        heapify(1);
    }

    bool empty(){
        return arr.size()==1;
    }
};

int main()
{
    Heap h;
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        int no;
        cin>>no;
        h.push(no);
    }
    cout<<endl;
    while(!h.empty()){
        cout<<h.top()<<" ";
        h.pop();
    }
    return 0;
}