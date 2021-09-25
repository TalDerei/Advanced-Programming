/**
 * Static Load Balancing involves spawning multiple threads to execute a 
 * collection of tasks, and splitting up the workload evenly amongst
 * those threads using a queuing system and scheduler. Using <Thread> library
 * to implement multithreading functionality. 
 */

#ifndef STATIC_LB_DEF
#define STATIC_LB_DEF

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include "config_t.h"

using namespace std;

class static_lb {
    struct queue_struct {
        /** Queue data structure */
        std::queue<int> prime_queue;

        /** Mutex for locking */
        std::mutex m;
    }; queue_struct queue_global;

    public:
        /** The constructor is implicitely empty */
        static_lb() {}

        /** Calls to initialize queue and spawn threads */
        void load_balancing(arg_t);

        /** Populate queue with N elements */
        int init_queue(arg_t);

        /** Spawn threads and call static_tasks or dynamic_tasks */
        void spawn_threads(arg_t, int);

        /** Lock queue and assign thread with static partition of the queue */
        void tasks(int);

        /** Prime number checker for range 1 to N */
        void calculate(int *, int);

        /** Print contents of the queue */
        void print();
};

#endif