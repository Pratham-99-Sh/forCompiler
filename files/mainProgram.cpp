#include<bits/stdc++.h>
using namespace std;

int cntSubarrays(vector<int> arr,int k){
    //complete this method
    
    vector<int> csum;
    int stiln = 0, res = 0;
    for(auto x: arr)
    {
        if(x==k) res++;
        stiln+=x;
        csum.push_back(stiln);
    }
    int diff = 1;
    while(diff < arr.size())
    {
        int start = 0, end = start + diff;
        while(end < arr.size())
        {
            if(csum[end] - csum[start] == k) res++;
            start++;
            end++;
        }
        diff++;
    }
    
    return res;
    
}
 
int main()
{
    vector<int> arr = {10, 2, -2, -20, 10};
    int k = -10;
    cout<<cntSubarrays(arr,k)<<endl;
}