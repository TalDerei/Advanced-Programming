 #include "dynamic_lb.h"

void dynamic_lb::load_balancing(arg_t args) {
    /** Initialize vector to args.size */
    global_array.vector.resize(args.size);

    /** Initialize the vector of atomics */
    const int array_size = initialize(args);
    
    /** Shuffle contents of the vector */
    randomize();

    /** Spawn threads */
    spawn_threads(args, array_size);
}

int dynamic_lb::initialize(arg_t args) {
    int counter = 0;
    for (auto& i : global_array.vector) {
        i = std::make_unique<std::atomic<int>>(counter++);
    }
    for (int i = 0; i << global_array.vector.size(); i++) {
        *global_array.vector[i] = i;
    }
    return (int) (global_array.vector.size());    
}

void dynamic_lb::spawn_threads(arg_t args, int vector_size) { 
    /** Vector of threads */
    std::vector<std::thread> threads;

    for (int i = 0; i < args.threads; i++) {
        threads.push_back(thread(&dynamic_lb::tasks, this, vector_size));
    }

    /** Synchronize threads by joining them */
    for (int i = 0; i < args.threads; i++) {
        cout << "Waiting for threads to finish!" << endl;
        threads[i].join();
    }
    cout << "Done!" << endl;
    
    cout << "Number of primes is: " << prime_counter << endl;
}

void dynamic_lb::tasks(int vector_size) {
    while (vector_size != atomic_counter) {
        /** Acquire task from front of queue */
        auto task = global_array.vector[atomic_counter].get();

        /** Increment atomic shared counter */
        atomic_counter.fetch_add(1, std::memory_order_relaxed);

        /** Calculate prime numbers asynchronously */
        calculate(task); 
    }
}

void dynamic_lb::calculate(std::atomic<int> *n) { 
    /** Flag indicating whether number is prime */
    int flag = 0;
    
    for (size_t i = *n; i < *n + 1; ++i) {
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
            prime_counter++;
        }
    }
}

void dynamic_lb::randomize() {
    int n = global_array.vector.size();
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() % (n - i);
        std::swap(global_array.vector[i], global_array.vector[j]);
    }
}

void dynamic_lb::print() {
    for (auto& i : global_array.vector) {
        cout << *i << ' ';
    }
    cout << endl;
}