/* Header file for UnsortedVector.cc */

#ifndef UNORDEREDVECTOR_DEF
#define UNORDEREDVECTOR_DEF

#include <vector>

class UnsortedVector {
    /** Unsorted Vector data structure */
    std::vector<int> vector;

    public:
        /** The constructor is implicitely empty */
        UnsortedVector() {}

        /** Insert key into vector */
        bool insert(int key) {
            vector.push_back(key);
            return true;
        }

        /** Remove key from set */
        bool remove(int key) {
            std::vector<int>::iterator key_value = std::find(vector.begin(), vector.end(), key);
            *key_value = std::move(vector.back());    
            vector.pop_back();
            return true;
        }

        /** Perform linear search lookup for key */
        bool lookup(int key) {
            std::vector<int>::iterator key_value = std::find(vector.begin(), vector.end(), key);
            if (key_value == vector.end()) {
                return false;
            }
            else {
                return true;
            }
        }

        /** Hack for the benchmark harness.  It inserts without checking for duplicates */
        void append(int key) {
            vector.push_back(key);
        }
};

#endif 

