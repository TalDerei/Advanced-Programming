/**
 * Static Load Balancing involves spawning multiple threads to execute a 
 * collection of tasks, and splitting up the workload evenly amongst
 * those threads using a queuing system and scheduler. Using <Thread> library
 * to implement multithreading functionality. 
 */

#ifndef LB_DEF
#define LB_DEF

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include "config_t.h"

using namespace std;

class load_balance {
    struct queue_struct {
        /** Queue data structure */
        std::queue<int> prime_queue;

        /** Mutex for locking */
        std::mutex m;
    }; queue_struct queue_global;

    /** Global atomic int */
    std::atomic<int> atomic_int = 0;

    public:
        /** The constructor is implicitely empty */
        load_balance() {}

        /** Calls to initialize queue and spawn threads */
        void load_balancing(arg_t);

        /** Populate queue with N elements */
        int init_queue(arg_t);

        /** Spawn threads and call static_tasks or dynamic_tasks */
        void spawn_threads(arg_t, int);

        /** Lock queue and assign thread with static partition of the queue */
        void static_tasks(int, int);

        /** Lock queue and assign thread with dynamic partition of the queue */
        void dynamic_tasks(int);

        /** Prime number checker for range 1 to N */
        void calculate_static(int *, int);

        /** Prime number checker for range 1 to N */
        void calculate_dynamic(int);

        /** Print contents of the queue */
        void print_queue();
};

#endif