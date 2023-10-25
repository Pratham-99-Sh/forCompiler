#include <iostream>
using namespace std;

float squareRoot(int n, int p)
{
    int s = 0, e = n;
    float res = 0;
    while(s <= e){
        int mid = (s+e)/2;
        if(mid*mid == n)
            return mid;
        if(mid*mid > n)
            e = mid-1;
        if(mid*mid < n){
            s = mid+1;
            res = mid;
        }
    }


    float inc = 0.1;
    for(int i=0; i<p; i++){
        while(res*res <= n){
            res += inc;
        }
        res -= inc;
        inc /= 10;
    }
    return res;
}

int main()
{
    int n, p;
    cin >> n >> p;
    cout << squareRoot(n, p) << endl;
    return 0;
}
