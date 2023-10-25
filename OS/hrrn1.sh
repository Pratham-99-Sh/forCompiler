#!/bin/bash

# Declare arrays for process id, arrival time, burst time, waiting time, turnaround time, and response ratio
pid=(1 2 3 4 5)
at=(0 2 4 6 8)
bt=(3 6 4 5 2)
wt=(0 0 0 0 0)
tat=(0 0 0 0 0)
rr=(0.0 0.0 0.0 0.0 0.0)

# Declare variables for total processes, current time, completed processes, and selected process
n=5
t=0
c=0
s=-1

# Define a function to calculate the response ratio for each process
calculate_rr() {
    for ((i=0; i<n; i++))
    do
        if [ ${at[i]} -le $t ] && [ ${bt[i]} -gt 0 ]
        then
            wt[i]=$((t - at[i]))
            rr[i]=$(echo "scale=2; (${wt[i]} + ${bt[i]}) / ${bt[i]}" | bc)
        fi
    done
}

# Define a function to find the process with the highest response ratio
find_highest_rr() {
    max=0.0
    s=-1
    for ((i=0; i<n; i++))
    do
        if [ $(echo "${rr[i]} > $max" | bc) -eq 1 ] && [ ${bt[i]} -gt 0 ]
        then
            max=${rr[i]}
            s=$i
        fi
    done
}

# Define a function to print the results in a table format
print_results() {
    echo "PID AT BT WT TAT RR"
    for ((i=0; i<n; i++))
    do
        echo "${pid[i]} ${at[i]} ${bt[i]} ${wt[i]} ${tat[i]} ${rr[i]}"
    done
}

# Main loop to simulate the HRRN algorithm
while [ $c -lt $n ]
do
    # Calculate the response ratio for each process at the current time
    calculate_rr

    # Find the process with the highest response ratio
    find_highest_rr

    # If no process is available, increment the current time by one
    if [ $s -eq -1 ]
    then
        t=$((t + 1))
        continue
    fi

    # Execute the selected process until completion
    t=$((t + bt[s]))
    bt[s]=0

    # Update the turnaround time and increment the completed processes by one
    tat[s]=$((t - at[s]))
    c=$((c + 1))
done

print_results
