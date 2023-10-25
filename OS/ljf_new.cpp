#include <iostream>
using namespace std;
int main()
{
int p[20], bt[20], wt[20], tat[20], i, k, n, temp; float wtavg, tatavg; 
cout<<endl<<"Enter the number of processes:"; 
cin>>n; 
for(i=0;i<n;i++) 
{ 
p[i]=i; 
cout<<"Enter Burst Time for Process "<<i<<": "; 
cin>>bt[i]; 
} 
for(i=0;i<n;i++) 
for(k=i+1;k<n;k++) 
if(bt[i]>bt[k]) 
{ 
temp=bt[i]; 
bt[i]=bt[k]; 
bt[k]=temp; 
}
temp=p[i]; 
p[i]=p[k]; 
p[k]=temp; 

wt[0] = wtavg = 0; 
tat[0] = tatavg = bt[0]; 
for(i=1;i<n;i++) 
{ 
wt[i] = wt[i-1] +bt[i - 1]; 
tat[i] = tat[i -1] +bt[i]; 
wtavg = wtavg + wt[i]; 
tatavg = tatavg + tat[i]; 
} 
cout<<"\n\t PROCESS \tBURST TIME \t WAITING TIME\t TURNAROUND TIME \n"; 
for(i=0;i<n;i++)    
cout<<endl<<"          "<<p[i]<<"                    "<< bt[i]<<"               "<< wt[i]<<"            "<<tat[i]; 
cout<<endl<<"Average Waiting Time -"<<wtavg/n; 
cout<<endl<<"Average Turnaround Time -"<<tatavg/n;

return 0;
}
