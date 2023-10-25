//An array arr of integers is to be divided into different groups such that each element belongs to exactly one group and the size of each group is at least m.
//The cost of the division is defined as the maximum value of the difference between the maximum and minimum elements of a particular group. For example, if an array [1, 2, 3, 4, 5] is divided into two groups [1,3], [2, 4, 5], the cost is max(3-1,5-2) = 3.
//Given arr and an integer m, find the minimum possible cost of dividing the array into groups of size greater than or equal to m.

//Suppose n=5, arr = [5, 11, 13, 4, 12], and m = 2.

//It is optimal to divide the array into two groups [5, 4] and [11, 13, 12] with the cost max(5-4, 13-11)= 2.

//Function Description
//Complete the function getMinimumCost in the editor below.

//getMinimumCost has the following parameter(s):
//int arr[n]: an array of integers
//int m: the minimum group size

//Returns:
//int: the minimum cost of dividing the array into groups of size greater than or equal to m

//Constraints
//1 ≤ n ≤ 105
//1 ≤ m ≤ 105
//1 ≤ arr[i] ≤ 109
//Sample Input For Custom Testing
//STDIN Function
//5 → arr[] size n = 5
//5 → arr = [5, 11, 13, 4, 12]
//11
//13
//4
//12
//2 → m = 2
//Sample Output
//2
//Explanation
//It is optimal to divide the array into two groups [5, 4] and [11, 13, 12] with the cost max(5-4, 13-11)= 2.
//std::vector<int> arr = {3, 5, 6, 0, 7};
//std::vector<int> power = {3, 1, 0, 2};
//getMaximumPower(arr, power) = 19
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int getMinimumCost(vector<int>& arr, int m) {
  // Create a priority queue to store the powers in decreasing order.
  priority_queue<pair<int, int>> queue;
  for (int i = 0; i < arr.size(); i++) {
    queue.push({-arr[i], i});
  }

  // Initialize the maximum power.
  int minCost = 0;
  int groupSize = 0;
  int min = 0;
  int max = 0;
  while (!queue.empty()) {
    // Get the two largest powers.
    pair<int, int> power1 = queue.top();
    queue.pop();
    pair<int, int> power2 = queue.top();
    queue.pop();
    if (groupSize == 0) {
      min = power1.first;
      max = power1.first;
    }
    // Calculate the sum of the subarray arr[power1]...arr[power2].
    min = std::min(min, power2.first);
    max = std::max(max, power2.first);
    groupSize++;
    if (groupSize == m) {
      minCost += max - min;
      groupSize = 0;
    }
    }
    return minCost;
}

int main() {
  int n = 5;
  vector<int> arr = {5, 11, 13, 4, 12};
  int m = 2;

  cout << getMinimumCost(arr, m) << endl;
}