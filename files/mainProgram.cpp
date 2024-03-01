#include <iostream>
#include <cmath>
using namespace std;

bool isSafe(int grid[9][9], int row, int col, int n, int num)
{
    // check row
    for(int i = 0; i < n; i++)
        if(grid[row][i] == num)
            return false;
    
    // check col
    for(int i = 0; i < n; i++)
        if(grid[i][col] == num)
            return false;

    // check subgrid
    int root = sqrt(n);
    int subRow = row - row%root;
    int subCol = col - col%root;
    for(int i = subRow; i < subRow + root; i++)
        for(int j = subCol; j < subCol + root; j++)
            if(grid[i][j] == num)
                return false;

    return true;
}

bool sudukoSolver(int grid[9][9], int row, int col, int n)
{
    // base case
    if (row == n)
        return true;

    // recursive case
    if(col == n)
        return sudukoSolver(grid, row + 1, 0, n);
    
    if(grid[row][col] != 0)
        return sudukoSolver(grid, row, col + 1, n);

    for(int i = 1; i <= n; i++)
    {
        if(isSafe(grid, row, col, n, i))
        {
            grid[row][col] = i;
            if(sudukoSolver(grid, row, col + 1, n))
                return true;
            grid[row][col] = 0;
        }
    }

    return false;
}

int main()
{
    int grid[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0}, 
        {6, 0, 0, 1, 9, 5, 0, 0, 0}, 
        {0, 9, 8, 0, 0, 0, 0, 6, 0}, 
        {8, 0, 0, 0, 6, 0, 0, 0, 3}, 
        {4, 0, 0, 8, 0, 3, 0, 0, 1}, 
        {7, 0, 0, 0, 2, 0, 0, 0, 6}, 
        {0, 6, 0, 0, 0, 0, 2, 8, 0}, 
        {0, 0, 0, 4, 1, 9, 0, 0, 5}, 
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };


    if(sudukoSolver(grid, 0, 0, 9))
    {
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++) 
                cout << grid[i][j] << " ";
            cout << endl;
        }
    }
    else
        cout << "No solution exists" << endl;
    return 0;
}