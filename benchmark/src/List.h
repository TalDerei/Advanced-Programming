/* Header file for List.cc */

#ifndef LIST_DEF
#define LIST_DEF

#include <list>
#include <iostream>

class List {
    /** List data structure */
    std::list<int> list;

    public:
        /** The constructor is implicitely empty */
        List() {}

        /** Insert key into list */
        void insert(int key) {
            list.push_front(key);
        }

        /** Remove key from set */
        void remove(int key) {
            std::list<int>::iterator removed = std::remove(list.begin(), list.end(), key);
            list.erase(removed, list.end());
        }

        /** Perform linear search lookup for key */
        bool lookup(int key) {
            if (std::find(list.begin(), list.end(), key) == list.end()) {
                return false;
            }
            else {
                return true;
            }
        }

        /** Hack for the benchmark harness.  It inserts without checking for duplicates */
        void append(int key) {
            list.push_back(key);
        }

        /** Print list */
        void print() {
            std::list<int>::iterator iterator;
            for (iterator = list.begin(); iterator != list.end(); ++iterator) {
                std::cout << *iterator << " " << std::endl;
            }
            std::cout << "size of list is: " << list.size() << std::endl;
        }
};

#endif 

