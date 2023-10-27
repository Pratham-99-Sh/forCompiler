#include <bits/stdc++.h> 
using namespace std;

int main() { 
    int i, j, k; 
    int n = 4; //number of processes 
    int m = 3; //number of resources 
    int allocation[4][3] = {{2, 1, 0},   //Allocation Matrix 
                        {1, 2, 2},  
                        {0, 2, 0},  
                        {3, 0, 1}}; //Each row represents a process 
  
    int max[4][3] = {{8, 6, 3}, //MAX Matrix 
                      {9, 4, 3}, 
                      {5, 3, 3}, 
                      {4, 2, 3}}; //Maximum resources that can be allocated 
  
    int available[3] = {4, 3, 2};
  
    int finish[n] = {0};
    int ans[n] = {0};
    int idx =  0; 
    
    int need[n][m];  //Calculating Need matrix
    for(int i=0;i<n;i++)
    { 
        for(int j=0;j<m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        } 
    } 
    
    int y = 0; 
    for (int k=0;k<4;k++) 
    { 
        for(int i=0;i<n;i++)
        { 
            if(finish[i]==0)
            { 
                int flag = 0; 
                for(int j=0;j<m;j++)
                { 
                    if(need[i][j]>available[j])
                    { 
                        flag = 1; //if needed resources are more in number than the available ones, move to the next process
                        break; 
                    }
                } 
                
                if(flag==0)
                {  //if available resources fulfilled the need
                    ans[idx++] = i; //the index of process, that has been allocated the resources
                    for(int y=0;y<m;y++)
                    { 
                        available[y] += allocation[i][y]; 
                    }
                    finish[i] = 1; 
                } 
            } 
        } 
    } 
    
    bool flag = true;
    for(int i=0; i<n; i++)
    {
        if(finish[i] == 0)
        { 
            flag = false; 
            cout<<"System is in deadlock !!"<<endl<<endl; break; 
        }
    }
    
    if(flag==true)
    {
        cout<<"System is in safe state and following is the safe sequence: "<<endl;
        for(int i=0;i<n-1;i++)
        {
            cout<<"P"<<ans[i]<<" -> "; 
        }
        cout<<"P"<<ans[n-1]<<endl<<endl;
    }
    return 0; 
}