/* Header file for List.cc */

#ifndef VECTOR_DEF
#define VECTOR_DEF

#include <vector>

class Vector {
    public:
        void vector();
        void vector(int, int, int);
        void init_vector(std::vector<int>&, int);
        void insert_key(std::vector<int>&, int);
        void remove_key(std::vector<int>&, int);
        void lookup_key(std::vector<int>&, int);
};

#endif 