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
        void insert(int key) {
            if (set.find(key) == set.end()) {
                set.insert(key);
            }
        }

        /** Remove key from set */
        void remove(int key) {
            if (set.find(key) != set.end()) {
                set.erase(key);
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

        /** Print set */
        void print() {
            std::set<int>::iterator iterator;
            for (iterator = set.begin(); iterator != set.end(); ++iterator) {
                std::cout << *iterator << " " << std::endl;
            }
            std::cout << "size of set is: " << set.size() << std::endl;
        }
};

#endif 

