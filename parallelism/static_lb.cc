 #include "static_lb.h"

void static_lb::static_balancing(int n) {
    /** Initialize the queue */
    init_queue(n);
    
    /** Spawn threads */
    spawn_threads(n);
}

void static_lb::init_queue(int n) {
    for (int i = 0; i <= n / 2; ++i) {
        queue_global.prime_queue.push(i);
    }
}

void static_lb::spawn_threads(int n) { 
    /** Vector of threads */
    std::vector<std::thread> threads;

    /** Spawn thread and insert into vector */
    for (int i = 0; i < THREADS; i++) {
        threads.push_back(std::thread(&static_lb::tasks, this, n));
    }

    /** Synchronize threads by joining them */
    for (int i = 0; i < THREADS; i++) {
        cout << "Waiting for threads to finish!" << endl;
        threads[i].join();
    }
    cout << "Done!" << endl;
}

void static_lb::tasks(int n) {
    cout << "entered tasks!" << endl;
    const int increment = queue_global.prime_queue.size() / THREADS;
    


        queue_global.m.lock();
        if (queue_global.prime_queue.size() != 0) {
            int * arr = new int [increment];
            int counter = 0;
            // cout << "????????????????? increment is: " << increment << endl;
            for (int i = 0; i < increment; i++) {


            
            // cout << ":)))))))" << endl;
            // if (queue_global.prime_queue.size() == 0) {
            //     cout << "oh no ;<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
            //     return 0;
            // } else {
            /** Lock the struct containing the queue and mutex lock */

            // cout << "entered while!" << endl;


            std::thread::id this_id = std::this_thread::get_id();

            // cout << "thread accessing the shared queue is: " << this_id << endl;

            // cout << "queue size is: " << queue_global.prime_queue.size() << endl;

            /** Acquire task from front of queue */
            int task = queue_global.prime_queue.front();
            arr[i] = task;
            
            // cout << "task is: " << task << endl;

            /** Pop front of queue */
            queue_global.prime_queue.pop();
            counter++;
            // cout << "!!!!!!!!!!!!!!!!" << endl;
            }

            // cout << "counter is: " << counter << endl;
            
            /** Unlock struct */
            queue_global.m.unlock();

            // cout << "arry contains: " << endl;
            // for (int i = 0; i < increment; i++) {
            //     cout << "num is: " << arr[i] << endl;
            // }

            /** Calculate primes */
            do_work(arr, increment); 
        }
}

void static_lb::do_work(int *n, int increment) { 
    int counter = 0;
    // cout << "entered do_work ???????????????????" << endl;
    // for (int i = 0; i < increment; i++) {
    //     cout << "n[i] is: " << n[i] << endl;
    // }
    bool isPrime = true;

    /** 0 and 1 are not prime numbers */
\
    for (size_t i = 2; i <= increment; ++i) {
        if (n[i] % i == 0) {
            isPrime = false;
            break;
        }
    }

    // cout << "counter is: " << counter << endl;

    // if (isPrime) {
    //     cout << "prime number!" << endl;
    // } else {
    //     cout << "not a prime number!" << endl;
    // }
}

void static_lb::print_queue() {
    while(!queue_global.prime_queue.empty()){
		cout << " " << queue_global.prime_queue.front() << endl;
		queue_global.prime_queue.pop();
	}
}


/**
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
 * Bottleneck is the queue!!!!!!!!
 * Only have one queue, and only one thread can access and lock the shared queue 
 * at a time.
 * 
 * Rather than having all 8 threads accessing the same shared queue, what if you had
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
 */