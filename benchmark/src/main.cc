/**
 * @file main.cc
 * Implement an integer set in c++ using various data structures
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include "Set.h"
#include "List.h"
#include "SortedVector.h"
#include "UnsortedVector.h"

/**
 * arg_t args struct for CLI parameters
 */
struct arg_t {
    /** number of operations between insert, remove, and search */
    int iterations = 0;

    /** key to search for in the data structure */
    int key = 0;

    /** data structure between set, list, ordered-vector, and unordered-vector */
    std::string data_structure = "";

    /** percentage of the operations that are 'search' only */
    int read_only_ratio = 0;
};

/**
 * parse user-defined argments
 * @param argc 
 * @param argv 
 * @param args 
 */
void parse_args(int argc, char **argv, arg_t &args) {
    long opt;
    while ((opt = getopt(argc, argv, "a:b:c:d:e")) != -1) {
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
                args.key = atoi(optarg);
                break;
            default:
                std::cout << "One or more parameters invalid! Try again!";
                break;
        }
    }
}

int main(int argc, char **argv) {
    // CLI configuration parameters
    arg_t args;
    parse_args(argc, argv, args);

    if (args.data_structure == "set") {
        Set set;
        set.set(args.iterations, args.key, args.read_only_ratio);
    }
    else if (args.data_structure == "list") {
        List list;
        list.list(args.iterations, args.key, args.read_only_ratio);
    }
    else if (args.data_structure == "sorted_vector") {
        SortedVector sorted_vector;
        sorted_vector.vector(args.iterations, args.key, args.read_only_ratio);
    }
    else if (args.data_structure == "unsorted_vector") {
        UnsortedVector unsorted_vector;
        unsorted_vector.vector(args.iterations, args.key, args.read_only_ratio);
    }
    else {
        std::cout << "One or more parameters invalid! Try again!" << std::endl;
    }
}

// https://medium.com/@rodrigues.b.nelson/choosing-wisely-c-containers-and-big-oh-complexity-64f9bd1e7e4c
// https://medium.com/@gx578007/searching-vector-set-and-unordered-set-6649d1aa7752

// reserve() for vectors - 2-3x faster speedup potentially?