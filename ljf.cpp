#include <iostream>
using namespace std;

// A structure to represent a process
struct Process {
    int pid; // Process ID
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
void sortByArrival(int n, Process p[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                swap(p[j], p[j + 1]);
            }
        }
    }
}

// A function to find the process with the longest burst time among the arrived processes
int findLongest(int n, Process p[], int cur_time) {
    int max_bt = 0;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= cur_time && p[i].bt > max_bt) {
            max_bt = p[i].bt;
            index = i;
        }
    }
    return index;
}

// A function to calculate the completion time, waiting time and turnaround time of each process
void calculateTimes(int n, Process p[]) {
    int cur_time = 0; // Current time
    int completed = 0; // Number of completed processes
    while (completed < n) {
        // Find the process with the longest burst time among the arrived processes
        int index = findLongest(n, p, cur_time);
        if (index != -1) {
            // Execute the process and update its completion time
            cur_time += p[index].bt;
            p[index].ct = cur_time;

            // Update the number of completed processes
            completed++;
        }
        else {
            // If no process has arrived, increment the current time by one unit
            cur_time++;
        }
    }

    // Calculate the waiting time and turnaround time of each process
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void printDetails(int n, Process p[]) {
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t\t" << p[i].at << "\t\t" << p[i].bt << "\t\t" << p[i].ct << "\t\t" << p[i].wt << "\t\t" << p[i].tat << "\n";
    }
}

int main() {
    // Number of processes
    int n = 4;

    // Array of processes
    Process p[n] = {{1, 0, 2}, {2, 2, 3}, {3, 4, 5}, {4, 6, 7}};

    // Sort the processes by arrival time
    sortByArrival(n, p);

    // Calculate the completion time, waiting time and turnaround time of each process
    calculateTimes(n, p);

    // Print the details of each process
    printDetails(n, p);

    return 0;
}