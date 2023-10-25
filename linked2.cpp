#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Process {
public:
    int id;
    int burstTime;
    int arrivalTime;
    int priority;
    int remainingTime;

    Process(int _id, int _burstTime, int _arrivalTime, int _priority)
        : id(_id), burstTime(_burstTime), arrivalTime(_arrivalTime), priority(_priority), remainingTime(_burstTime) {}

    bool operator<(const Process& other) const {
        return arrivalTime > other.arrivalTime;
    }
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<Process> processes;
    
    for (int i = 0; i < n; i++) {
        int burstTime, arrivalTime, priority;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> burstTime;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> arrivalTime;
        cout << "Enter priority for Process " << i + 1 << ": ";
        cin >> priority;
        processes.push_back(Process(i + 1, burstTime, arrivalTime, priority));
    }

    int choice;
    cout << "\nSelect Scheduling Algorithm:\n";
    cout << "1. FCFS\n";
    cout << "2. SJF (Non-Preemptive)\n";
    cout << "3. SJF (Preemptive)\n";
    cout << "4. Priority Scheduling\n";
    cout << "5. Round Robin Scheduling (RRS)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    vector<int> waitingTime(n, 0);

    if (choice == 1) {
        // FCFS
         sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
    int currentTime = processes[0].arrivalTime;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime > currentTime) {
            currentTime = processes[i].arrivalTime;
        }
        waitingTime[processes[i].id - 1] = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
    }
    } else if (choice == 2 || choice == 3) {
        // SJF (Non-Preemptive) or SJF (Preemptive)
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.burstTime < b.burstTime;
        });
        int currentTime = processes[0].arrivalTime;
        while (!processes.empty()) {
            auto it = min_element(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
                return a.burstTime < b.burstTime;
            });
            int idx = it - processes.begin();
            Process& currentProcess = processes[idx];
            processes.erase(it);
            if (choice == 3 && currentProcess.remainingTime > 1) {
                // Preemptive SJF
                currentTime++;
                currentProcess.remainingTime--;
                processes.push_back(currentProcess);
            } else {
                // Non-Preemptive SJF
                currentTime += currentProcess.remainingTime;
                waitingTime[currentProcess.id - 1] = currentTime - currentProcess.arrivalTime - currentProcess.burstTime;
            }
        }
    } else if (choice == 4) {
        // Priority Scheduling
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.priority < b.priority;
        });
        int currentTime = processes[0].arrivalTime;
        while (!processes.empty()) {
            auto it = min_element(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
                return a.priority < b.priority;
            });
            int idx = it - processes.begin();
            Process& currentProcess = processes[idx];
            processes.erase(it);
            currentTime += currentProcess.remainingTime;
            waitingTime[currentProcess.id - 1] = currentTime - currentProcess.arrivalTime - currentProcess.burstTime;
        }
    } else if (choice == 5) {
    // Round Robin Scheduling (RRS)
    int timeQuantum;
    cout << "Enter time quantum for Round Robin Scheduling (RRS): ";
    cin >> timeQuantum;
    queue<Process> q;
    int currentTime = 0;
    int remainingProcesses = n;
    int currentProcessIndex = 0;

    while (remainingProcesses > 0) {
        Process& currentProcess = processes[currentProcessIndex];
        if (currentProcess.remainingTime > 0) {
            int executionTime = min(timeQuantum, currentProcess.remainingTime);
            currentTime += executionTime;
            currentProcess.remainingTime -= executionTime;

            if (currentProcess.remainingTime == 0) {
                remainingProcesses--;
                waitingTime[currentProcess.id - 1] = currentTime - currentProcess.arrivalTime - currentProcess.burstTime;
            }

            while (currentProcessIndex < n && processes[currentProcessIndex].arrivalTime <= currentTime) {
                q.push(processes[currentProcessIndex]);
                currentProcessIndex++;
            }

            q.push(currentProcess);
        } else {
            currentProcessIndex++;
        }

        if (q.empty()) {
            // No processes in the queue, find the next arriving process
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].arrivalTime > currentTime && processes[i].arrivalTime < nextArrival) {
                    nextArrival = processes[i].arrivalTime;
                }
            }
            currentTime = nextArrival;
        }
    }
}

    // Calculate average waiting time
    double averageWaitingTime = 0.0;
    for (int i = 0; i < n; i++) {
        averageWaitingTime += waitingTime[i];
    }
    averageWaitingTime /= n;

    // Display results
    cout << "\nExecution Sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << " ";
    }
    cout << "\n\nWaiting Time for Each Process:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << ": " << waitingTime[i] << " units\n";
    }
    cout << "\nAverage Waiting Time: " << averageWaitingTime << " units\n";

    return 0;
}
