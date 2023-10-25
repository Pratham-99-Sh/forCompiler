#!/bin/bash

# declare an array of burst times
burst_time=(2 4 6 8)

# sort the array in descending order
sorted_burst_time=($(printf '%s\n' "${burst_time[@]}" | sort -nr))

# declare some variables for waiting time and turn-around time
total_waiting_time=0
total_turnaround_time=0
waiting_time=0
turnaround_time=0

# loop over the sorted array and execute each process
for i in "${sorted_burst_time[@]}"
do
  # print the process id and burst time
  echo "Executing process with burst time $i"
  
  # sleep for the burst time
  sleep $i
  
  # calculate the turn-around time and add it to the total
  turnaround_time=$((turnaround_time + i))
  total_turnaround_time=$((total_turnaround_time + turnaround_time))
  
  # calculate the waiting time and add it to the total
  waiting_time=$turnaround_time
  total_waiting_time=$((total_waiting_time + waiting_time))
done

# calculate the average waiting time and turn-around time
avg_waiting_time=$(echo "scale=2; $total_waiting_time / ${#burst_time[@]}" | bc)
avg_turnaround_time=$(echo "scale=2; $total_turnaround_time / ${#burst_time[@]}" | bc)


echo "Average waiting time: $avg_waiting_time"
echo "Average turn-around time: $avg_turnaround_time"