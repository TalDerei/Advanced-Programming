/* Header file for List.cc */

#ifndef LIST_DEF
#define LIST_DEF

#include <list>

class List {
    public:
        void list();
        void list(int, int, int);
        void init_list(std::list<int>&, int);
        void insert_key(std::list<int>&, int);
        void remove_key(std::list<int>&, int);
        void lookup_key(std::list<int>&, int);
};

#endif 