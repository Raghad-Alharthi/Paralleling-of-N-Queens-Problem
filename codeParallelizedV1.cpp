#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// Function to check if the current placement is safe
bool isSafe(const vector<int>& board, int currRow, int currCol) {
    for (int i = 0; i < board.size(); ++i) {
        int placedRow = board[i];
        int placedCol = i + 1;

        // Check if the queen is on the same diagonal
        if (abs(placedRow - currRow) == abs(placedCol - currCol)) {
            return false;
        }
    }
    return true;
}

// Recursive function to generate all possible permutations
void nQueenUtil(int col, int n, vector<int>& board, vector<vector<int>>& result, vector<bool>& visited) {
    if (col > n) {
        try{
            result.push_back(board);  // RACE CONDITION
        }
        catch(...){

        }
        return;
    }

    for (int row = 1; row <= n; ++row) {
        if (!visited[row]) {  // RACE CONDITION
            if (isSafe(board, row, col)) {
                visited[row] = true;  // RACE CONDITION

                board.push_back(row); 
                nQueenUtil(col + 1, n, board, result, visited);

                board.pop_back(); 
                visited[row] = false;  // RACE CONDITION
            }
        }
    }
}

// Thread function to handle part of the search
void nQueenThread(int startCol, int n, vector<vector<int>>& result, vector<bool>& visited) {
    vector<int> board;  // board for each thread
    nQueenUtil(startCol, n, board, result, visited);
}

// Main function to find all distinct results to the n-queens
vector<vector<int>> nQueen(int n) {
    vector<vector<int>> result; 
    vector<bool> visited(n + 1, false); 
    vector<thread> threads;

    for (int i = 1; i <= n; ++i) {
        threads.emplace_back(nQueenThread, i, n, ref(result), ref(visited));
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    return result;
}

int main() {
    int n = 12; 

    // Start timing
    auto start = chrono::high_resolution_clock::now();

    vector<vector<int>> result = nQueen(n);


    // Print results
    for (const auto& res : result) {
        cout << "[";
        for (int i = 0; i < res.size(); ++i) {
            cout << res[i];
            if (i != res.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }

    // Stop timing
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Execution time: " << elapsed.count() << " seconds" << endl;

    return 0;
}
