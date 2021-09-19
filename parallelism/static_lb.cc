 #include "static_lb.h"

void static_lb::static_balancing(int n) {
    /** Initialize the queue */
    const int queue_size = init_queue(n);

    /** Spawn threads */
    spawn_threads(n, queue_size);
}

int static_lb::init_queue(int n) {
    for (int i = 0; i <= n; ++i) {
        queue_global.prime_queue.push(i);
    }
    return (int) (queue_global.prime_queue.size() / THREADS);    
}

void static_lb::spawn_threads(int n, int queue_size) { 
    /** Vector of threads */
    std::vector<std::thread> threads;

    /** Spawn thread and insert into vector */
    for (int i = 0; i < THREADS; i++) {
        threads.push_back(std::thread(&static_lb::assignment, this, n, queue_size));
    }

    /** Synchronize threads by joining them */
    for (int i = 0; i < THREADS; i++) {
        cout << "Waiting for threads to finish!" << endl;
        threads[i].join();
    }
    cout << "Done!" << endl;
}

void static_lb::assignment(int n, int queue_size) {
    /** Lock struct containing queue */
    queue_global.m.lock();

    if (queue_global.prime_queue.size() != 0) {
        int counter = 0;
        int *array = new int [queue_size];
        for (int i = 0; i < queue_size; i++) {
            /** Acquire task from front of queue */
            int task = queue_global.prime_queue.front(); 
            array[i] = task;
            
            /** Pop front of queue */
            queue_global.prime_queue.pop();
            counter++;
        }
        
        /** Unlock struct containing queue */
        queue_global.m.unlock();

        /** RATHER THAN QUEUE, CAN JUST PARTITION THE ARRAY ITSELF */
        // int *array = new int [queue_size]; 

        /** Calculate prime numbers asynchronously */
        calculate(array, queue_size); 
    }
}

void static_lb::calculate(int *array, int array_size) { 
    /** Starting position for array */
    int starting = array[0];

    /** Flag indicating whether number is prime */
    int flag;
    
    for (size_t i = starting; i < starting + array_size; i++) {
        if (i == 1 || i == 0) {
            continue;
        }
        flag = 1;
        for (size_t j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                flag = 0;
                // cout << "NOT prime: " << i << endl;
                break;
            }
        }
        if (flag == 1) {
            // cout << "prime: " << i << endl;
        }
    }
}

void static_lb::print_queue() {
    while(!queue_global.prime_queue.empty()){
		cout << " " << queue_global.prime_queue.front() << endl;
		queue_global.prime_queue.pop();
	}
}


/**
 * ---------------- Q. Why queue?
 * 
 * How to split up tasks?
 * Each worker has one int. Push work orders to queue.
 * Each thread retrirves one work order and executes do_work.
 * Why do we need atomic counter?
 * For dynamic paritioning:
 * atomic int incremenet by every threads...partitioned
 * range as a function of atomic int + rand() to generate
 * "even" sized windows
 * 
 * add n/2 "units of work" to queue
 * 
 * Q. Why is load balancing neccessary?
 * To evenly split up the workload amongst threads in order
 * to avoid threads being idle. 
 * 
 * ----------------- Bottleneck is the queue!!!!!!!!
 * Only have one queue, and only one thread can access and lock the shared queue 
 * at a time.
 * 
 * ---------------------- Rather than having all 8 threads accessing the same shared queue, what if you had
 * them accessing their own individual queue in parallel, with static partiioning
 * of the data before runtime?
 * 
 * Implement buffering of data into array's
 * 
 * do_work runs asynchronously, but access to shared queue is still a bottleneck, as every
 * thrreads n eeds to access the queue.
 * 
 * Need to understand algorithm, and then understand how the buffering system know's only top look at
 * the last element to determine primeness or not.
 * 
 * One thread might break, but the other's will continue to run in do_work
 * 
 * Ideas:
 * - Static load balancing run as tbb::parallel_for
 * - multiple queues and each buffer ocupies that queue
 * - don't need queue, just partition an int
 * - need to test against all possible primes
 * 
 * Need to check against all possible primes:
 * means we need to do a double for loop to check if all numbers up to the number we're checking is prime or not...
 * so we're pushing n rather than n / 2 into a queue, and doing a double for loop 
 */