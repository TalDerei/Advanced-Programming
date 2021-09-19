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
 * Primes: 1009 (10^3), 1000003 (10^6), 1000000007 (10^9)
 */

#include <iostream>
#include <unistd.h>
#include <chrono>
#include <mutex>
#include <cassert>
#include <string>

#include "tbb.h"
#include "static_lb.h"

using namespace std;

/**
 * arg_t args struct for CLI parameters
 */
struct arg_t {
    /** Prime number size */
    int prime_size = 0;

    /** Parallelization method */
    string method = "";
};

void parse_args(int argc, char **argv, arg_t &args) {
    long opt;
    while ((opt = getopt(argc, argv, "a:b:c")) != -1) {
        switch (opt) {
            case 'a':
                args.method = std::string(optarg);
                break;
            case 'b':
                args.prime_size = atoi(optarg);
                break;
            default:
                std::cout << "One or more parameters invalid! Try again!";
                break;
        }
    }
}

int main(int argc, char **argv) {
    /** CLI configuration parameters */
    arg_t args;
    parse_args(argc, argv, args);

    /** Static and dynamic balancing objects */
    static_lb s;

    /** Start execution time */
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

    //  s.static_balancing(args.prime_size);
     
    if (args.method == "tbb") {
        tbb_lib(args.prime_size);
    } else if (args.method == "static") {
        s.static_balancing(args.prime_size);
    }
    // else if (args.method == "dynamic") {
    //     d.dynamic_balancing(args.prime_size);
    // }

    /** Finish execution time */
    std::chrono::time_point<std::chrono::high_resolution_clock> finish = std::chrono::high_resolution_clock::now();

    /** Duration represents time interval */
    std::chrono::duration<double> elapse_time = finish - start;

    std::cout << "Execution time elapsed is: " << elapse_time.count() << std::endl;
    
    return 0;
}