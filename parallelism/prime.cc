 /**
 * CSE 411
 * Fall 2021
 * Project #1 -- Part #1 
 *
 * The purpose of this part is to assess the efficiency of TBB. 
 * This file implements a naive O(n) prime checker for integers 1--N. 
 * We are not going to try to change the algorithm to improve performance.  
 * Instead, we will try to parallelize it using three different approaches:
 * 
 * 1- TBB parallel_for.
 * 2- Manually using fork-join (std::thread) with static load balancing.
 * 3- Manually using fork-join (std::thread) with dynamic load balancing.
 * 
 * Keep in mind that for small problems, it's likely that different 
 * approaches perform similarly.  But for N = 10ˆ6 and 10ˆ9, it is possible 
 * to get a HUGE speedup and the differences between approaches should arise.
 *
 */

#include <iostream>
#include <chrono>
#include <tbb/tbb.h>
using namespace std;

int main() {
    using namespace tbb;

    size_t i, n;
    bool isPrime = true;

    cout << "Enter a positive integer: ";
    cin >> n;

    /** Start execution time */
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

    if (n == 0 || n == 1) {
        isPrime = false;
    } else {
        parallel_for(tbb::blocked_range<size_t>(2, n / 2), [&](tbb::blocked_range<size_t> r)
        {
            for (size_t i = r.begin(); i < r.end(); ++i) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
        });
    }

    /** Finish execution time */
    std::chrono::time_point<std::chrono::high_resolution_clock> finish = std::chrono::high_resolution_clock::now();

    /** Duration represents time interval */
    std::chrono::duration<double> elapse_time = finish - start;

    std::cout << "Execution time elapsed is: " << elapse_time.count() << std::endl;
    
    if (isPrime) {
        std::cout << n << " is a prime number" << std::endl;
    } else {
        std::cout << n << " is not a prime number" << std::endl;
    }

    return 0;
}

/**
 * g++ --std=c++17 -O3 prime.cc -ltbb -o parallel_for
 */