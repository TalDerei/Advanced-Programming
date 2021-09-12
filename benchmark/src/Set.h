/* Set Data Structure */

#ifndef SET_DEF
#define SET_DEF

#include <set>

class Set {
    /** Tree data structure */
    std::set<int> set;
    
    public:
        /** The constructor is implicitely empty */
        Set() {}

        /** Insert key into set */
        bool insert(int key) {
            if (set.find(key) == set.end()) {
                set.insert(key);
                return true;
            }
            else {
                return false;
            }
        }

        /** Remove key from set */
        bool remove(int key) {
            if (set.find(key) == set.end()) {
                return false;
            }
            else {
                set.erase(key);
                return true;
            }
        }

        /** Perform binary search lookup for key */
        bool lookup(int key) {
            if (set.find(key) == set.end()) {
                return false;
            }
            else {
                return true;
            }
        }

        /** Hack for the benchmark harness.  It inserts without checking for duplicates */
        void append(int key) {
            set.insert(key);
        }
};

#endif 

