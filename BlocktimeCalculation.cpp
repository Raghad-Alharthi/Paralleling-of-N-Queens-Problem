#include <iostream>
#include <vector>
#include <chrono>  // Include for time measurement

using namespace std;

// Global variables to track isSafe function metrics
int isSafeCallCount = 0;  // Counter for isSafe calls
double totalIsSafeTime = 0.0;  // Total time for all isSafe calls

// Function to check if the current placement is safe
bool isSafe(const vector<int>& board, int currRow, int currCol) {
    isSafeCallCount++;  // Increment the isSafe call counter

    // Start timing for this isSafe call
    auto start = chrono::high_resolution_clock::now();

    for (int col = 0; col < currCol; ++col) {
        int placedRow = board[col];
        if (placedRow == currRow || abs(placedRow - currRow) == abs(col - currCol)) {
            // Stop timing for this isSafe call
            auto end = chrono::high_resolution_clock::now();
            totalIsSafeTime += chrono::duration<double>(end - start).count(); // Accumulate time
            return false; // Not safe
        }
    }

    // Stop timing for this isSafe call
    auto end = chrono::high_resolution_clock::now();
    totalIsSafeTime += chrono::duration<double>(end - start).count(); // Accumulate time
    return true; // Safe to place the queen
}

// Recursive function to generate all possible solutions
void nQueenUtil(int col, int n, vector<int>& board, int& solutionCount, int& callCount, double& totalRecursiveTime) {
    callCount++;  // Increment the call counter

    // Start timing for this recursive call
    auto start = chrono::high_resolution_clock::now();

    if (col == n) {
        solutionCount++;  // Increment the solution counter
    } else {
        for (int row = 0; row < n; ++row) {
            if (isSafe(board, row, col)) {
                board[col] = row;  // Place the queen
                nQueenUtil(col + 1, n, board, solutionCount, callCount, totalRecursiveTime);  // Recur to place the next queen
            }
        }
    }

    // Stop timing for this recursive call
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Add the elapsed time to the total recursive time
    totalRecursiveTime += elapsed.count();
}

// Main function to find all distinct solutions to the n-queens puzzle
int nQueen(int n) {
    vector<int> board(n, -1);  // Current board configuration (n columns, initialized to -1)
    int solutionCount = 0;
    int callCount = 0;  // Counter for recursive calls
    double totalRecursiveTime = 0.0;  // Total time for all recursive calls

    nQueenUtil(0, n, board, solutionCount, callCount, totalRecursiveTime);  // Start solving from the first column
    
    cout << "Total number of recursive calls: " << callCount << endl;  // Output the call count
    cout << "Total time from all recursive calls: " << totalRecursiveTime << " seconds" << endl;  // Print the total time
    cout << "Total number of isSafe calls: " << isSafeCallCount << endl; // Output the isSafe call count
    cout << "Total time from all isSafe calls: " << totalIsSafeTime << " seconds" << endl; // Print the total time for isSafe

    return solutionCount;
}

int main() {
    int n = 4;  // Example for N = 4 (can change to other values)
    
    // Start timing for the overall execution
    auto start = chrono::high_resolution_clock::now();
    
    // Call the N-Queen function
    int result = nQueen(n);
    
    // Stop timing for the overall execution
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> totalElapsed = end - start;

    // Output the results
    cout << "Number of solutions for " << n << "-Queens: " << result << endl;
    cout << "Total execution time: " << totalElapsed.count() << " seconds" << endl;

    return 0;
}
