/**
 * @file SortedVector.cc
 * Sorted Vectors are dynamic arrays with the ability to resize itself automatically
 * when elements are inserted and deleted. Vector elements are placed in contiguous 
 * storage so that they can be accessed and traversed using iterators, and their
 * storage is handled automatically by the container. And unlike sets, vector
 * elements can be duplicates. 
 * 
 * Time Complexity:
 * Insertion Time: O(1) + rebalancing/shifting vector
 * Deletiion Time: O(1) + rebalancing/shifting vector
 * Search Time: O(n) unsorted, O(log n) sorted
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <algorithm>

#include "SortedVector.h"

using namespace std;

/* Vector interface logic */
void SortedVector::vector(int iterations, int key, int read_only_ratio) {
    /* Initialize empty vector of ints */
    std::vector<int> myvector;

    /* Vector iterator */
    std::vector<int>::iterator it;

    /* Populate vector with key values */
    init_vector(myvector, key);

    /* Sort the vector initially */
    sort(myvector.begin(), myvector.end());

    /* Start execution time */
    auto start = chrono::high_resolution_clock::now();

    /* Randomly switch between different vector operations */
    srand(time(0));
    for (int counter = 0; counter < iterations; counter++) {
        long opt = rand() % 100;
        long rand_key = rand() % key; 
        if (opt <= read_only_ratio) {
            lookup_key(myvector, rand_key);
        } 
        else if (opt > read_only_ratio && opt <= (((100-read_only_ratio)/2)+read_only_ratio)) {
            insert_key(myvector, rand_key);
        }
        if (opt > (((100-read_only_ratio)/2)+read_only_ratio) && opt <= 100) {
            remove_key(myvector, rand_key);
        }
    }

    /* finish execution time */
    auto finish = chrono::high_resolution_clock::now();

    /* duration represents time interval */
    chrono::duration<double> elapse_time = finish - start;

    /* print elements of vector */
    // for (auto i = myvector.begin(); i != myvector.end(); ++i) {
    //     std::cout << *i << ' ';
    // } 
    // std::cout << endl;

    std::cout << "size of final vector is: " << myvector.size() << endl;

    std::cout << "Execution time elapsed is: " << elapse_time.count() << endl;
}

/* Populate vector to 50% of max capacity */
void SortedVector::init_vector(std::vector<int> &vector, int key) {
    srand(time(0));
    for (int i = 0; i < key / 2; i++) {
        vector.push_back(rand() % key);
    }
}

/* Insert new key */
void SortedVector::insert_key(std::vector<int> &vector, int key) {
    std::vector<int>::iterator iterator = std::lower_bound(vector.begin(), vector.end(), key);
    if (iterator != vector.end() && *iterator == key) {
        vector.insert(iterator, key);
    /* cout << "Inserted key!" << endl; */
    }
}

/* Remove existing key */
void SortedVector::remove_key(std::vector<int> &vector, int key) {
    std::vector<int>::iterator iterator = std::lower_bound(vector.begin(), vector.end(), key);
    if (iterator != vector.end() && *iterator == key) {
        vector.erase(iterator);
        /* cout << "Removed key!" << endl; */
    }
}

/* Look up if key exists */
bool SortedVector::lookup_key(std::vector<int> &vector, int key) {
    /* implement lower_bound() function which is binary search */
    std::vector<int>::iterator iterator = std::lower_bound(vector.begin(), vector.end(), key);
    if (iterator != vector.end() && *iterator == key) {
        /* std:: cout << "found key! " << key << endl; */
        return true;
    }
    else {
        /* std:: cout << "did not find key! " << key << endl; */
        return false;
    }
}
