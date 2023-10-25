#include <iostream>
using namespace std;

struct process {
    char name;
    int AT, BT, WT, TAT, RT, CT;
} Q1[10], Q2[10], Q3[10]; // Three queues

int n;

void sortByArrival() {
    struct process temp;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (Q1[i].AT > Q1[j].AT) {
                temp = Q1[i];
                Q1[i] = Q1[j];
                Q1[j] = temp;
            }
        }
    }
}

int main() {
    int i, j, k = 0, r = 0, time = 0, tq1 = 5, tq2 = 8, flag = 0;
    char c;
    cout << "Enter the number of processes: ";
    cin >> n;
    for (i = 0, c = 'A'; i < n; i++, c++) {
        Q1[i].name = c;
        cout << "Enter the arrival time and burst time of process " << Q1[i].name << ": ";
        cin >> Q1[i].AT >> Q1[i].BT;
        Q1[i].RT = Q1[i].BT; /* save burst time in remaining time for each process */
    }
    sortByArrival();
    time = Q1[0].AT;
    cout << "Processes in the first queue following RR with quantum time 5\n";
    cout << "Process\tRT\tWT\tTAT\n";
    for (i = 0; i < n; i++) {
        if (Q1[i].RT <= tq1) {
            time += Q1[i].RT;
            Q1[i].RT = 0;
            Q1[i].WT = time - Q1[i].AT - Q1[i].BT;
            Q1[i].TAT = time - Q1[i].AT;
            cout << Q1[i].name << "\t" << Q1[i].BT << "\t" << Q1[i].WT << "\t" << Q1[i].TAT << endl;
        } else {
            Q2[k].WT = time;
            time += tq1;
            Q1[i].RT -= tq1;
            Q2[k].BT = Q1[i].RT;
            Q2[k].RT = Q2[k].BT;
            Q2[k].name = Q1[i].name;
            k = k + 1;
            flag = 1;
        }
    }
    if (flag == 1) {
        cout << "Processes in the second queue following RR with quantum time 8\n";
        cout << "Process\tRT\tWT\tTAT\n";
    }
    for (i = 0; i < k; i++) {
        if (Q2[i].RT <= tq2) {
            time += Q2[i].RT;
            Q2[i].RT = 0;
            Q2[i].WT = time - tq1 - Q2[i].BT;
            Q2[i].TAT = time - Q2[i].AT;
            cout << Q2[i].name << "\t" << Q2[i].BT << "\t" << Q2[i].WT << "\t" << Q2[i].TAT << endl;
        } else {
            Q3[r].AT = time;
            time += tq2;
            Q2[i].RT -= tq2;
            Q3[r].BT = Q2[i].RT;
            Q3[r].RT = Q3[r].BT;
            Q3[r].name = Q2[i].name;
            r = r + 1;
            flag = 2;
        }
    }
    if (flag == 2) {
        cout << "Processes in the third queue following FCFS\n";
        cout << "Process\tBT\tWT\tTAT\n";
    }
    for (i = 0; i < r; i++) {
        if (i == 0)
            Q3[i].CT = Q3[i].BT + time - tq1 - tq2;
        else
            Q3[i].CT = Q3[i - 1].CT + Q3[i].BT;

    }
    for (i = 0; i < r; i++) {
        Q3[i].TAT = Q3[i].CT;
        Q3[i].WT = Q3[i].TAT - Q3[i].BT;
        cout << Q3[i].name << "\t" << Q3[i].BT << "\t" << Q3[i].WT << "\t" << Q3[i].TAT << endl;
    }
}
