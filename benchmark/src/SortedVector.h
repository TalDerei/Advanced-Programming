#ifndef SORTEDVECTOR_DEF
#define SORTEDVECTOR_DEF

#include <vector>

class SortedVector {
    public:
        /* The constructor is implicitely empty */
        SortedVector() {
        
        }

        /* Wrapper function for calling APIs */
        void vector(int, int, int);

        /* Initialize vector to half the size of the key_length */
        void init_vector(std::vector<int>&, int);

        /* Insert key into vector */
        void insert_key(std::vector<int>&, int);

        /* Remove key from set */
        void remove_key(std::vector<int>&, int);

        /* Perform linear search lookup for key */
        bool lookup_key(std::vector<int>&, int);
};

#endif 

