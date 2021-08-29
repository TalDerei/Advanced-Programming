/**
 * @file set.cc
 * Sets are associative containers of the c++ std library
 * which stores elements in a sorted manner. All the elements of a set are 
 * unique and cannot be modified, but can be inserted and/or removed. 
 * Sets are typically implemented as balanced binary seaerch trees (BST),
 * like red-black trees. 
 * 
 * Time Complexity:
 * Search Time: O(log n)
 * Insertion Time: O(log n) + rebalancing
 * Deletiion Time: O(log n) + rebalancing
 * 
 * Unordered Sets: O(1) averages, O(n) worse-case for resizing (implemented as hash table)
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <chrono>

#include "Set.h"

using namespace std;

/* Constructor for creating Set objects */
void Set::set() {
}

/* Set interface logic */
void Set::set(int iterations, int key, int read_only_ratio) {
    /* Start execution time */
    auto start = chrono::high_resolution_clock::now();

    /* Initialize empty set of ints */
    std::set<int> myset;

    /* Set iterator */
    std::set<int>::iterator it;

    /* Populate set with key values */
    init_set(myset, iterations);

    srand(time(0));
    /* Randomly switch between different set operations */
    for (int counter = 0; counter < iterations; counter++) {
        long opt = rand() % 100;
        long rand_key = rand() % key; 
        cout << "opt is: " << opt << "\n";
        if (opt <= read_only_ratio) {
            lookup_key(myset, rand_key);
        } 
        else if (opt > read_only_ratio && opt <= (100-read_only_ratio)/2) {
            insert_key(myset, rand_key);
        }
        else if (opt > (100-read_only_ratio)/2 && opt <= 100) {
            remove_key(myset, rand_key);
        }
    }
    
    /* finish execution time */
    auto finish = chrono::high_resolution_clock::now();

    /* duration represents time interval */
    chrono::duration<double> elapse_time = finish - start;

    cout << "Execution time elapsed is: " << elapse_time.count() << "\n";

    /* print elements of set */
    for (it = myset.begin(); it != myset.end(); ++it) {
        cout << *it << " "; 
    }
    cout << "\n";
}

/* Populate set to 50% of max capacity */
void Set::init_set(std::set<int> &set, int iterations) {
    srand(time(0));
    for (int i = 0; i < iterations / 2; i++) {
        set.insert(rand() % 100);
    }
}

/* Insert new key */
void Set::insert_key(std::set<int> &set, int key) {
    auto key_value = set.find(key);
    if (key_value == set.end()) {
        set.insert(key);
        cout << "Inserted key!\n";
    }
    else {
        cout << "Insert failed! Key " << key << " already exists!\n";
    }
}

/* Remove existing key */
void Set::remove_key(std::set<int> &set, int key) {
    auto key_value = set.find(key);
    if (key_value == set.end()) {
        cout << "Remove failed! Key " << key << " NOT found!\n";
    }
    else {
        set.erase(key);
        cout << "Removed key!\n";
    }
}

/* Look up if key exists */
void Set::lookup_key(std::set<int> &set, int key) {
    auto key_value = set.find(key);
    if (key_value == set.end()) {
        cout << "Key " << key << " NOT found!\n";
    }
    else {
        cout << "Key " << key << " found in the set!\n";
    }
}
