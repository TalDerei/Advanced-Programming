/* Header file for Set.cc */

#ifndef SET_DEF
#define SET_DEF

#include <set>

class Set {
    /* Initialize set to be empty */
    std::set<int> myset;

    public:
        /* The constructor is implicitely empty */
        Set() {
        
        }

        /* Wrapper function for calling APIs */
        void set(int, int, int);

        /* Initialize set to half the size of the key_length */
        void init_set(std::set<int>&, int);

        /* Insert key into set */
        void insert_key(std::set<int>&, int);

        /* Remove key from set */
        void remove_key(std::set<int>&, int);

        /* Perform linear search lookup for key */
        bool lookup_key_linear(std::set<int>&, int);

        /* perform binary search lookup for key */
        bool lookup_key_binary(std::set<int>&, int);
};

#endif 

