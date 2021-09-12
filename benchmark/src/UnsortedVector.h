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
        void insert(int key) {
            vector.push_back(key);
        }

        /** Remove key from set */
        void remove(int key) {
            std::vector<int>::iterator key_value = std::find(vector.begin(), vector.end(), key);
            *key_value = std::move(vector.back());    
            vector.pop_back();
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

        /** Print vector */
        void print() {
            std::vector<int>::iterator iterator;
            for (iterator = vector.begin(); iterator != vector.end(); ++iterator) {
                std::cout << *iterator << " " << std::endl;
            }
            std::cout << "size of unsorted vector is: " << vector.size() << std::endl;
        }
};

#endif 

