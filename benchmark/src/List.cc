/**
 * @file Lmist.cc
 * Lists are sequence containers that allow
 * non-contiguous memory allocation. Compared to a vector,
 * list-traversals are slow, but once a position has been found,
 * insertions and deletions are quick. Lists are typically
 * implemented as doubly-linked lists. And unlike sets, list
 * elements can be duplicates.
 * 
 * Time Complexity:
 * Insertion Time: O(1)
 * Deletiion Time: O(1)
 * Search Time: O(n)
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <algorithm>

#include "List.h"

using namespace std;

/* List interface logic */
void List::list(int iterations, int key, int read_only_ratio) {
    /* Initialize empty list of ints */
    std::list<int> mylist;

    /* List iterator */
    std::list<int>::iterator it;

    /* Populate list with key values */
    init_list(mylist, key);

    std::cout << "size of set after initialization: " << mylist.size();

    /* Start execution time */
    auto start = chrono::high_resolution_clock::now();
    
    /* Randomly switch between different list operations */
    srand(time(0));
    for (int counter = 0; counter < iterations; counter++) {
        long opt = rand() % 100;
        long rand_key = rand() % key; 
        if (opt <= read_only_ratio) {
            lookup_key(mylist, rand_key);
        } 
        else if (opt > read_only_ratio && opt <= (100-read_only_ratio)/2) {
            insert_key(mylist, rand_key);
        }
        else if (opt > (100-read_only_ratio)/2 && opt <= 100) {
            remove_key(mylist, rand_key);
        }
    }
    
    /* finish execution time */
    auto finish = chrono::high_resolution_clock::now();

    /* duration represents time interval */
    chrono::duration<double> elapse_time = finish - start;

    /* Print elements of set */
    for (it = mylist.begin(); it != mylist.end(); ++it) {
        cout << *it << " " << endl;
    }

    std::cout << "Execution time elapsed is: " << elapse_time.count() << endl;

    std::cout << "size of final set is: " << mylist.size();
}


/* Populate list to 50% of max capacity */
void List::init_list(std::list<int> &list, int key) {
    srand(time(0));
    for (int i = 0; i < key / 2; i++) {
        list.push_front(rand() % key);
    }
}

/* Insert new key */
void List::insert_key(std::list<int> &list, int key) {
    list.push_front(key);
}

/* Remove existing key */
void List::remove_key(std::list<int> &list, int key) {
    std::list<int>::iterator key_value = std::find(list.begin(), list.end(), key);
    if (key_value == list.end()) {
        /* cout << "Remove failed! Key " << key << " NOT found!" << endl; */
    }
    else {
    list.remove(key);
        /* cout << "Removed key!" << endl; */
    }
}

/* Look up if key exists */
bool List::lookup_key(std::list<int> &list, int key) {
    std::list<int>::iterator key_value = std::find(list.begin(), list.end(), key);
    if (key_value == list.end()) {
        // cout << "Key " << key << " NOT found!" << endl;
        return false;
    }
    else {
        // cout << "Key " << key << " found in the list!" << endl;
        return true;
    }
}


