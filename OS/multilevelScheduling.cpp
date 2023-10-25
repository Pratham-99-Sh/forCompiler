// write code for multilevel scheduling algorithm

#include <iostream>
using namespace std;

// A structure to represent a process

struct Process {
    char pid; // Process ID
    int at; // Arrival Time
    int bt; // Burst Time
    int ct; // Completion Time
    int wt; // Waiting Time
    int tat; // Turnaround Time
};

// A function to swap two processes

void swap(Process& p1, Process& p2) {
    Process temp = p1;
    p1 = p2;
    p2 = temp;
}

// A function to sort the processes by arrival time

