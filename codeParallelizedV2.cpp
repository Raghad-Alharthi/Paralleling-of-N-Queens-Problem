#include <vector>
#include <iostream>
#include <chrono>
#include <omp.h>
using namespace std;

// Function to check if the current placement is safe
bool isSafe(const vector<int> &board, int currRow, int currCol)
{
    for (int i = 0; i < board.size(); ++i)
    {
        int placedRow = board[i];
        int placedCol = i + 1;

        // Check if the queen is on the same diagonal
        if (abs(placedRow - currRow) == abs(placedCol - currCol))
        {
            return false;
        }
    }
    return true;
}

// Recursive function to generate all possible placements
void nQueenUtil(int col, int n, vector<int> &board, vector<vector<int>> &result, vector<bool> &visited)
{
    if (col > n)
    {
// Use critical section to protect the shared result
#pragma omp critical
        {
            result.push_back(board);
        }
        return;
    }

    for (int row = 1; row <= n; ++row)
    {
        if (!visited[row])
        {
            if (isSafe(board, row, col))
            {
                visited[row] = true;

                board.push_back(row);
                nQueenUtil(col + 1, n, board, result, visited);

                board.pop_back();
                visited[row] = false;
            }
        }
    }
}

// Main function to find all distinct solutions to the n-queens problem
vector<vector<int>> nQueen(int n)
{
    vector<vector<int>> result;

// Parallel section using OpenMP
#pragma omp parallel
    {
#pragma omp single
        {
            // Create OpenMP tasks for each starting row of the first column
            for (int i = 1; i <= n; ++i)
            {
#pragma omp task
                {
                    vector<int> board;                  // Each task has its own board
                    vector<bool> visited(n + 1, false); // Each task has its own visited
                    board.push_back(i);                 // Start with a different first row
                    visited[i] = true;

                    // Start solving from the second column since the first column is handled
                    nQueenUtil(2, n, board, result, visited);
                }
            }
        }
    }

    return result;
}

int main()
{
    int n = 12;

    // Start timing
    auto start = chrono::high_resolution_clock::now();

    vector<vector<int>> result = nQueen(n);

    // Print results
    for (const auto &res : result)
    {
        cout << "[";
        for (int i = 0; i < res.size(); ++i)
        {
            cout << res[i];
            if (i != res.size() - 1)
                cout << ", ";
        }
        cout << "]\n";
    }

    // Stop timing
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Execution time: " << elapsed.count() << " seconds" << endl;

    return 0;
}
