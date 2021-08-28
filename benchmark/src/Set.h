/* Header file for Set.cc */

#ifndef SET_DEF
#define SET_DEF

#include <set>

class Set {
    public:
        void set();
        void set(int, int, int);
        void init_set(std::set<int>&, int);
        void insert_key(std::set<int>&, int);
        void remove_key(std::set<int>&, int);
        void lookup_key(std::set<int>&, int);
};

#endif 