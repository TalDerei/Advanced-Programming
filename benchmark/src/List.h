/* Header file for List.cc */

#ifndef LIST_DEF
#define LIST_DEF

#include <list>

class List {
    public:
        /* The constructor is implicitely empty */
        List() {
        
        }

        /* Wrapper function for calling APIs */
        void list(int, int, int);

        /* Initialize list to half the size of the key_length */
        void init_list(std::list<int>&, int);

        /* Insert key into list */
        void insert_key(std::list<int>&, int);

        /* Remove key from set */
        void remove_key(std::list<int>&, int);

        /* Perform linear search lookup for key */
        bool lookup_key(std::list<int>&, int);
};

#endif 

