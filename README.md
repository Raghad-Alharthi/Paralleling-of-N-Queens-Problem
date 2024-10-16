# Paralleling of N-Queens problem:


## About the project :

The N-Queens problem is a classical combinatorial problem where the goal is to place N queens on a chessboard of size N x N such that no queen can attack another. This project implements a solution in C++ using a recursive backtracking approach to find all possible solutions for a given board size N.

The project also includes a benchmarking feature to measure the performance of the sequential solution, which will later be used for comparison with a parallelized version of the code.

### Features: 
- Solves the N-Queens problem for any value of N.
- Efficient recursive backtracking algorithm.
- Benchmarking using C++'s <chrono> library to measure execution time.
- Prepares the groundwork for future parallelization using OpenMP or multithreading.

## About the Code:
all rights for this code is for GeeksForGeeks.org, find original code here https://www.geeksforgeeks.org/printing-solutions-n-queen-problem/
we only made some modifications sush as:
- Adding timers (for benchmarking purposes)
- Deleting vector that save all possible solutions and only printing number of possible solutions.

the code solve the problem using Naive Recursive Approach, The most simple way to solve the N-Queens problem is to generate
all possible permutations of [1, 2, 3, …, n] and then check if it represents a valid N-Queens configuration. 
Since each queen has to be in a different row and column, using permutations automatically takes care of those rules. 
But we still need to check that no two queens are on the same diagonal. (GeeksForGeeks)

### Requirements:
To compile and run this code, you'll need:
- A C++ compiler (such as g++ or clang++).
- C++11 or higher to support chrono for benchmarking.


### Dependencies:
No external libraries are required for this project; it uses the C++ standard library.

## Contributors

This project is a collaborative effort by:

- **Raghad Alharthi** (GitHub:(https://github.com/Raghad-Alharthi))
- **Rawdhah Mansour** (GitHub: (--))


NOTE: this project is for Parallel Computer Architecture course, with supervision of **Ms.Rabab Alkhalifah**
