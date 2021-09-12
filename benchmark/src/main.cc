/**
 * @file main.cc
 * Implement an integer set in c++ using various data structures
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <algorithm>

#include "Set.h"
#include "List.h"
#include "SortedVector.h"
#include "UnsortedVector.h"

/**
 * arg_t args struct for CLI parameters
 */
struct arg_t {
    /** Number of operations between insert, remove, and search */
    int iterations = 1000000;

    /** Key to search for in the data structure */
    int key_max = 256;

    /** Data structure between set, list, ordered-vector, and unordered-vector */
    std::string data_structure = "";

    /** Percentage of the operations that are 'search' only */
    int read_only_ratio = 0;

    /** Display help message */
    bool usage = false; 
};

/**
 * Parse user-defined argments
 * @param argc 
 * @param argv 
 * @param args 
 */
void parse_args(int argc, char **argv, arg_t &args) {
    long opt;
    while ((opt = getopt(argc, argv, "a:b:c:d:h:f")) != -1) {
        switch (opt) {
            case 'a':
                args.iterations = atoi(optarg);
                break;
            case 'b':
                args.data_structure = std::string(optarg);
                break;
            case 'c':
                args.read_only_ratio = atoi(optarg);
                break;
            case 'd':
                args.key_max = atoi(optarg);
                break;
            case 'h':
                args.usage = atoi(optarg);
                break;
            default:
                std::cout << "One or more parameters invalid! Try again!";
                break;
        }
    }
}

/** Templating in order to maximize inlining */
template <class T>
void run_test(arg_t &args) {
    /** Initialize data structure to half the size of the key_length */
    T ds;
    for (int i = 0; i < args.key_max; i += 2) {
        ds.append(i);
    }

    /** Start execution time */
    auto start = std::chrono::high_resolution_clock::now();

    /** Randomly call insert/remove/lookup APIs */ 
    srand(time(0));
    for (int counter = 0; counter < args.iterations; counter++) {
        int opt = rand() % 100;
        int key = rand() % args.key_max; 
        if (opt <= args.read_only_ratio) {
            ds.lookup(key);
        } else if (opt > args.read_only_ratio && opt <= (((100-args.read_only_ratio)/2)+args.read_only_ratio)) {
            ds.insert(key);
        } else if (opt > (((100-args.read_only_ratio)/2)+args.read_only_ratio) && opt <= 100) {
            ds.remove(key);
        }
    }

    /** Finish execution time */
    auto finish = std::chrono::high_resolution_clock::now();

    /** Duration represents time interval */
    std::chrono::duration<double> elapse_time = finish - start;

    /* Print elements of data structure */
    // ds.print();

    std::cout << "Execution time elapsed is: " << elapse_time.count() << std::endl;
}

int main(int argc, char **argv) {
    /** CLI configuration parameters */
    arg_t args;
    parse_args(argc, argv, args);

    if (args.data_structure == "set") {
        run_test<Set>(args);
    } else if (args.data_structure == "list") {
        run_test<List>(args);
    } else if (args.data_structure == "sorted_vector") {
        run_test<SortedVector>(args);
    } else if (args.data_structure == "unsorted_vector") {
        run_test<UnsortedVector>(args);
    } else {
        std::cout << "One or more parameters invalid! Try again!" << std::endl;
    }
}

/** 
 * https://medium.com/@rodrigues.b.nelson/choosing-wisely-c-containers-and-big-oh-complexity-64f9bd1e7e4c
 * https://medium.com/@gx578007/searching-vector-set-and-unordered-set-6649d1aa7752
 */
