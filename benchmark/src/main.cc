/**
 * @file main.cc
 */

#include <iostream>
#include <libgen.h>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

/**
 * arg_t args struct for CLI parameters
 */
struct arg_t {
    /** number of operations between insert, remove, and search */
    int operations = 0;

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
    while ((opt = getopt(argc, argv, "a:b:c")) != -1) {
        switch (opt) {
            case 'a':
                args.operations = atoi(optarg);
                break;
            case 'b':
                args.data_structure = string(optarg);
                break;
            case 'c':
                args.read_only_ratio = atoi(optarg);
                break;
        }
    }
}

int main(int argc, char **argv) {
    arg_t args;
    parse_args(argc, argv, args);
}