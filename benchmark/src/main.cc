/**
 * @file main.cc
 * Implement an integer set in c++
 */

#include <iostream>
#include <string>
#include <unistd.h>

#include "Set.h"
#include "List.h"

using namespace std;

/**
 * arg_t args struct for CLI parameters
 */
struct arg_t {
    /** number of operations between insert, remove, and search */
    int iterations = 0;

    /** key to search for in the data structure */
    int key = 0;

    /** data structure between set, list, ordered-vector, and unordered-vector */
    string data_structure = "";

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
                args.data_structure = string(optarg);
                break;
            case 'c':
                args.read_only_ratio = atoi(optarg);
                break;
            case 'd':
                args.key = atoi(optarg);
                break;
            default:
                cout << "One or more parameters invalid!";
                break;
        }
    }
}

int main(int argc, char **argv) {
    arg_t args;
    parse_args(argc, argv, args);
    if (args.data_structure == "set") {
        Set s;
        s.set(args.iterations, args.key, args.read_only_ratio);
    }
    else if (args.data_structure == "list") {
        List l;
        l.list(args.iterations, args.key, args.read_only_ratio);
    }
    else {
        cout << "Error!";
    }
}