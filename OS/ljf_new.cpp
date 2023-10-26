#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

bool compare(Process p1, Process p2) {
    // Sort processes first by arrival time and then by burst time
    if (p1.arrivalTime == p2.arrivalTime) {
        return p1.burstTime > p2.burstTime;
    }
    return p1.arrivalTime < p2.arrivalTime;
}

void LJF(std::vector<Process> processes) {
    std::sort(processes.begin(), processes.end(), compare);
    int currentTime = 0;

    // Print the table headers
    std::cout << std::left << std::setw(10) << "Process" << std::setw(15) << "Arrival Time" << std::setw(15) << "Burst Time" << std::setw(20) << "Completion Time" << std::endl;

    for (const Process& process : processes) {
        std::cout << std::left << std::setw(10) << process.id;
        std::cout << std::setw(15) << process.arrivalTime;
        std::cout << std::setw(15) << process.burstTime;

        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime;
        }

        currentTime += process.burstTime;
        std::cout << std::setw(20) << currentTime << std::endl;
    }

    double avgTurnaroundTime = 0;
    for (const Process& process : processes) {
        avgTurnaroundTime += (currentTime - process.arrivalTime);
    }
    avgTurnaroundTime /= processes.size();

    std::cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << std::endl;
}

int main() {
    std::vector<Process> processes = {
        {1, 1, 2},
        {2, 2, 4},
        {3, 3, 6},
        {4, 4, 8}
    };

    std::cout << "Longest Job First (LJF) Scheduling with Arrival Time\n";
    LJF(processes);

    return 0;
}
