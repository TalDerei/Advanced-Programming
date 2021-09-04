/**
 * @file Set.cc
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
 * 
 * binary_search() doesn’t work well with set/multiset iterators, because they don’t allow random access.
 * find() tends to work better as a targeted solution for sets
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <bits/stdc++.h>

#include "Set.h"

using namespace std;

/* Set interface logic */
void Set::set(int iterations, int key, int read_only_ratio) {
    /* Initialize set to be empty */
    std::set<int> myset;

    /* Set iterator */
    std::set<int>::iterator it;

    /* Populate set with key values */
    init_set(myset, key);

    /* Start execution time */
    auto start = chrono::high_resolution_clock::now();

    srand(time(0));
    /* Randomly switch between different set operations */
    for (int counter = 0; counter < iterations; counter++) {
        long opt = rand() % 100;
        long rand_key = rand() % key; 
        if (opt <= read_only_ratio) {
            lookup_key_linear(myset, rand_key);
        } 
        else if (opt > read_only_ratio && opt <= (((100-read_only_ratio)/2)+read_only_ratio)) {
            insert_key(myset, rand_key);
        }
        else if (opt > (((100-read_only_ratio)/2)+read_only_ratio) && opt <= 100) {
            remove_key(myset, rand_key);
        }
    }
    
    /* Finish execution time */
    auto finish = chrono::high_resolution_clock::now();

    /* Duration represents time interval */
    chrono::duration<double> elapse_time = finish - start;

    /* Print elements of set */
    // for (it = myset.begin(); it != myset.end(); ++it) {
    //     cout << *it << " " << endl;
    // }

    std::cout << "Execution time elapsed is: " << elapse_time.count() << endl;

    std::cout << "size of set is: " << myset.size();
}

/* Populate set to 50% of max capacity */
void Set::init_set(std::set<int> &set, int key) {
    int counter = 0;
    srand(time(0));
    while (counter != key / 2) {
        int key_insert = rand() % key;
        if (!lookup_key_linear(set, key_insert)) {
            set.insert(key_insert);
            counter++;
        }
        else {
            continue;
        }
    }
}

/* Insert new key */
void Set::insert_key(std::set<int> &set, int key) {
    auto key_value = set.find(key);
    if (key_value == set.end()) {
        set.insert(key);
        /* cout << "Inserted key!" << endl; */
    }
    else {
        /* cout << "Insert failed! Key " << key << " already exists!" << endl; */
    }
}

/* Remove existing key */
void Set::remove_key(std::set<int> &set, int key) {
    auto key_value = set.find(key);
    if (key_value == set.end()) {
        /* cout << "Remove failed! Key " << key << " NOT found!" << endl; */
    }
    else {
        set.erase(key);
        /* cout << "Removed key!" << endl; */
    }
}

/* Look up if key exists */
bool Set::lookup_key_linear(std::set<int> &set, int key) {
    auto key_value = set.find(key);
    if (key_value == set.end()) {
        /* cout << "Key " << key << " NOT found!" << endl; */
        return false;
    }
    else {
        /* cout << "Key " << key << " found in the set!" << endl; */
        return true;
    }
}
