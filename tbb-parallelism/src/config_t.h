#ifndef CONFIG_DEF
#define CONFIG_DEF

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>

using namespace std;

/**
 * arg_t args struct for CLI parameters
 */
struct arg_t {
    /** Prime number size */
    int size = 0;

    /** Parallelization method */
    string method = "";
    
    /** Number of execution threads */
    int threads = 0;

    /** Display help message */
    bool usage = false;
};

#endif
