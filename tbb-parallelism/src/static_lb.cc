 #include "static_lb.h"

void static_lb::load_balancing(arg_t args) {
    /** Initialize the queue */
    const int queue_size = init_queue(args);

    /** Spawn threads */
    spawn_threads(args, queue_size);
}

int static_lb::init_queue(arg_t args) {
    for (int i = 0; i <= args.size; ++i) {
        queue_global.prime_queue.push(i);
    }
    return (int) (queue_global.prime_queue.size() / args.threads);    
}

void static_lb::spawn_threads(arg_t args, int queue_size) { 
    /** Vector of threads */
    std::vector<std::thread> threads;

    /** Spawn thread and insert into vector */
    for (int i = 0; i < args.threads; i++) {
        threads.push_back(thread(&static_lb::tasks, this, queue_size));
    }

    /** Synchronize threads by joining them */
    for (int i = 0; i < args.threads; i++) {
        cout << "Waiting for threads to finish!" << endl;
        threads[i].join();
    }
    cout << "Done!" << endl;
}

void static_lb::tasks(int queue_size) {
    /** RATHER THAN IMPLEMENTING QUEUE, ANOTHER APPROACH IS TO PARTITION THE ARRAY ITSELF */
    
    /** Lock struct containing queue */
    queue_global.m.lock();

    if (queue_global.prime_queue.size() != 0) {
        int *array = new int [queue_size];
        for (int i = 0; i < queue_size; i++) {
            /** Acquire task from front of queue */
            array[i] = queue_global.prime_queue.front();
            
            /** Pop front of queue */
            queue_global.prime_queue.pop();
        }
        
    /** Unlock struct containing queue */
    queue_global.m.unlock();

    /** Calculate prime numbers asynchronously */
    calculate(array, queue_size); 
    }
}

void static_lb::calculate(int *array, int array_size) { 
    int flag = 0, counter = 0;

    /** Starting position for array */
    int starting = array[0];

    for (size_t i = starting; i < starting + array_size; ++i) {
        flag = 1;
        for (int j = 2; j <= i / 2; ++j) {
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            /** UNCOMMENT TO PRINT PRIME NUMBERS */
            // cout << i << " is prime" << endl;
            counter++;
        }
    }
    cout << "Number of primes is: " << counter << endl;
}

void static_lb::print() {
    while(!queue_global.prime_queue.empty()){
		cout << " " << queue_global.prime_queue.front() << endl;
		queue_global.prime_queue.pop();
	}
}
