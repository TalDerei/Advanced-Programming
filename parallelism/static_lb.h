/**
 * Static Load Balancing involves spawning multiple threads to execute a 
 * collection of tasks, and splitting up the workload evenly amongst
 * those threads using a queuing system and scheduler. Using <Thread> library
 * to implement multithreading functionality. 
 */

#ifndef STATIC_LB_DEF
#define STATIC_LB_DEF

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>

#define THREADS 8

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

        void static_balancing(int);

        void init_queue(int);

        void spawn_threads(int);

        void tasks(int);

        void do_work(int *, int);

        void print_queue();
};

#endif