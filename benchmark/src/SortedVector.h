#ifndef SORTEDVECTOR_DEF
#define SORTEDVECTOR_DEF

#include <vector>

class SortedVector {
    /** Sorted Vector data structure */
    std::vector<int> vector;

    public:
        /** The constructor is implicitely empty */
        SortedVector() {}

        /** Insert key into vector */
        void insert(int key) {
            std::vector<int>::iterator iterator = std::lower_bound(vector.begin(), vector.end(), key);
            if (iterator != vector.end() && *iterator == key) {
                vector.insert(iterator, key);
            }
        }

        /** Remove key from vector */
        void remove(int key) {
            std::vector<int>::iterator iterator = std::lower_bound(vector.begin(), vector.end(), key);
            if (iterator != vector.end() && *iterator == key) {
                vector.erase(iterator);
            }
        }

        /** Perform linear search lookup for vector */
        bool lookup(int key) {
            /** implement lower_bound() function which is binary search */
            std::vector<int>::iterator iterator = std::lower_bound(vector.begin(), vector.end(), key);
            if (iterator != vector.end() && *iterator == key) {
                return true;
            }
            else {
                return false;
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
            std::cout << "size of sorted vector is: " << vector.size() << std::endl;
        }
};

#endif 

