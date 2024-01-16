#include<iostream>
#include<vector>
using namespace std;


int minPages(vector<int> books, int m){
    int s = 0, e = 0, rslt;
    for (auto x : books) e+=x;

    while(s<=e){
        int mid = (s+e)/2;

        int sum = 0, cnt = 1;
        for(auto x : books)
        {
            if(sum+x > mid)
            {
                cnt++;
                sum = x;

                if(sum > mid) cnt = m+1;
            }
            else sum+=x;
        }

        if(cnt > m) s = mid+1;
        else {e = mid-1; rslt = mid;}
    }
   return rslt; 
}

int main()
{
    vector<int> books = {12,34,67,90,10,20,30,40,20,250,100};
    cout<<minPages(books, 4)<<endl;
    return 0;
}