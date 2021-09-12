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
 * g++ --std=c++17 -O3 prime.cc -ltbb -o parallel_for
 * N = 1009 (10^3), 1000003 (10^6), 1000000007 (10^9)
 * 
 * TBB Reference:
 * https://software.intel.com/content/www/us/en/develop/documentation/tbb-documentation/top/intel-threading-building-blocks-developer-guide/parallelizing-simple-loops/parallelfor.html
 * https://software.intel.com/content/www/us/en/develop/documentation/tbb-documentation/top/intel-threading-building-blocks-developer-guide/parallelizing-simple-loops/parallelfor/controlling-chunking.html
 * https://software.intel.com/content/www/us/en/develop/documentation/tbb-documentation/top/intel-threading-building-blocks-developer-guide/parallelizing-simple-loops/parallelfor/partitioner-summary.html
 */

#include <iostream>
#include <chrono>
#include <tbb/tbb.h>
#include <mutex>
#include <oneapi/tbb/info.h>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/task_arena.h>
#include <cassert>
using namespace std;

int main() {
    using namespace tbb;

    size_t i, n;
    bool isPrime = true;

    cout << "Enter a positive integer: ";
    cin >> n;

    int num_threads = oneapi::tbb::info::default_concurrency();
    cout << "Default number of threads is: " << num_threads << endl;
    
    /** Start execution time */
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

    if (n == 0 || n == 1) {
        isPrime = false;
    } else {
        /** TBB breaks iteration space into chunks, and runs each chunk on a seperate thread */
        parallel_for(blocked_range<size_t>(2, n / 2), [&](blocked_range<size_t> r)
        {
            /** Chunk sizes automated to achievie load balancing and limit overhead */
            for (size_t i = r.begin(); i < r.end(); ++i) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
        }, auto_partitioner());
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