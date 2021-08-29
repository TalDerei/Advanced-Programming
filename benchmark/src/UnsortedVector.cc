/**
 * @file UnsortedVector.cc
 * Unsorted represetation of a vector
 * 
 * Time Complexity:
 * Insertion Time: O(1)
 * Deletiion Time: O(1)
 * Search Time: O(n) unsorted, O(log n) sorted
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <algorithm>

#include "UnsortedVector.h"

using namespace std;

/* Constructor for creating Vector objects */
void UnsortedVector::vector() {

}

/* Vector interface logic */
void UnsortedVector::vector(int iterations, int key, int read_only_ratio) {
    /* Start execution time */
    auto start = chrono::high_resolution_clock::now();

    /* Initialize empty vector of ints */
    std::vector<int> myvector;

    /* Vector iterator */
    std::vector<int>::iterator it;

    /* Populate vector with key values */
    init_vector(myvector, iterations);

    /* Randomly switch between different vector operations */
    srand(time(0));
    for (int counter = 0; counter < iterations; counter++) {
        long opt = rand() % 100;
        long rand_key = rand() % key; 
        cout << "opt is: " << opt << "\n";
        if (opt <= read_only_ratio) {
            lookup_key(myvector, rand_key);
        } 
        else if (opt > read_only_ratio && opt <= (100-read_only_ratio)/2) {
            insert_key(myvector, rand_key);
        }
        else if (opt > (100-read_only_ratio)/2 && opt <= 100) {
            remove_key(myvector, rand_key);
        }
    }
    
    /* finish execution time */
    auto finish = chrono::high_resolution_clock::now();

    /* duration represents time interval */
    chrono::duration<double> elapse_time = finish - start;

    cout << "Execution time elapsed is: " << elapse_time.count() << "\n";

    /* print elements of vector */
    for (it = myvector.begin(); it != myvector.end(); ++it) {
        cout << *it << " "; 
    }
    cout << "\n";
}

/* Populate vector to 50% of max capacity */
void UnsortedVector::init_vector(std::vector<int> &vector, int iterations) {
    srand(time(0));
    for (int i = 0; i < iterations / 2; i++) {
        vector.push_back(rand() % 100);
    }
}

/* Insert new key */
void UnsortedVector::insert_key(std::vector<int> &vector, int key) {
    vector.push_back(key);
    cout << "Inserted key!\n";
}

/* Remove existing key */
void UnsortedVector::remove_key(std::vector<int> &vector, int key) {
    vector.erase(vector.begin() + key);
    cout << "Removed key!\n";
}

/* Look up if key exists */
void UnsortedVector::lookup_key(std::vector<int> &vector, int key) {
    std::vector<int>::iterator key_value = std::find(vector.begin(), vector.end(), key);
    if (key_value == vector.end()) {
        cout << "Key " << key << " NOT found!\n";
    }
    else {
        cout << "Key " << key << " found in the vector!\n";
    }
}
