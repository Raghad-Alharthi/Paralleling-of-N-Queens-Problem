// NEW CODE FOR FINDING ALL POSSIBLE SOLUTIONS !!
//Naive Recursive Approach

#include <iostream>
#include <vector>
#include <chrono>  // Include for time measurement

using namespace std;

// Function to check if the current placement is safe
bool isSafe(const vector<int>& board, int currRow, int currCol) {
    for (int col = 0; col < currCol; ++col) {
        int placedRow = board[col];
        if (placedRow == currRow || abs(placedRow - currRow) == abs(col - currCol)) {
            return false; // Not safe
        }
    }
    return true; // Safe to place the queen
}

// Recursive function to generate all possible solutions
void nQueenUtil(int col, int n, vector<int>& board, int& solutionCount) {
    if (col == n) {
        solutionCount++;  // Increment the solution counter
        return;
    }

    for (int row = 0; row < n; ++row) {
        if (isSafe(board, row, col)) {
            board[col] = row;  // Place the queen
            nQueenUtil(col + 1, n, board, solutionCount);  // Recur to place the next queen
        }
    }
}

// Main function to find all distinct solutions to the n-queens puzzle
int nQueen(int n) {
    vector<int> board(n, -1);  // Current board configuration (n columns, initialized to -1)
    int solutionCount = 0;
    nQueenUtil(0, n, board, solutionCount);  // Start solving from the first column
    return solutionCount;
}

int main() {
    int n = 15;  // Example for N = 10 (can change to other values)
    
    // Start timing
    auto start = chrono::high_resolution_clock::now();
    
    // Call the N-Queen function
    int result = nQueen(n);
    
    // Stop timing
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Output the results
    cout << "Number of solutions for " << n << "-Queens: " << result << endl;
    cout << "Execution time: " << elapsed.count() << " seconds" << endl;

    return 0;
}

