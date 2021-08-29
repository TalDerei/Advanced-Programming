/* Header file for UnsortedVector.cc */

#ifndef UNORDEREDVECTOR_DEF
#define UNORDEREDVECTOR_DEF

#include <vector>

class UnsortedVector {
    public:
        void vector();
        void vector(int, int, int);
        void init_vector(std::vector<int>&, int);
        void insert_key(std::vector<int>&, int);
        void remove_key(std::vector<int>&, int);
        void lookup_key(std::vector<int>&, int);
};

#endif 