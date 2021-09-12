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
        bool insert(int key) {
            list.push_front(key);
            return true;
        }

        /** Remove key from set */
        bool remove(int key) {
            auto removed = std::remove(list.begin(), list.end(), key);
            list.erase(removed, list.end());
            return true;
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
};

#endif 

