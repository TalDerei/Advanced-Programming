/**
 * Dynamic Load Balancing involves spawning multiple threads to execute a 
 * collection of tasks, and splitting up the workload evenly amongst
 * those threads using a queuing system and scheduler. Using <Thread> library
 * to implement multithreading functionality. 
 */

#ifndef DYNAMIC_LB_DEF
#define DYNAMIC_LB_DEF

#include <thread>
#include <vector>
#include <array>
#include <vector>
#include <atomic>
#include <memory>
#include <algorithm>
#include "config_t.h"

using namespace std;

class dynamic_lb {
    struct array_struct {
        /** Array data structure */
        std::vector<std::unique_ptr<std::atomic<int>>> vector;

    }; array_struct global_array;

    /** Global atomic counters */
    std::atomic<int> atomic_counter = 0;
    std::atomic<int> prime_counter = 0;

    public:
        /** The constructor is implicitely empty */
        dynamic_lb() {}

        /** Calls to initialize vector and spawn threads */
        void load_balancing(arg_t);

        /** Populate vector with N elements */
        int initialize(arg_t);

        /** Spawn threads and call static_tasks or dynamic_tasks */
        void spawn_threads(arg_t, int);

        /** Assign thread with dynamic partition of the vector */
        void tasks(int);

        /** Prime number checker for range 1 to N */
        void calculate(std::atomic<int> *);

        /** Print contents of the vector */
        void print();

        /** Shuffle contents of the vector */
        void randomize();
};

#endif