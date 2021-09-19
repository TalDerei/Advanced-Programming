/** 
 * Sequential Implementation
 * 
 * Code Referenced: https://www.geeksforgeeks.org/program-to-find-prime-numbers-between-given-interval/
 */

#ifndef SEQUENTIAL_DEF
#define SEQUENTIAL_DEF

#include <iostream>
#include "config_t.h"

using namespace std;

void sequential(arg_t args) {
    bool isPrime = true;
    int flag;
    int counter;

    if (args.size == 0 || args.size == 1) {
        cout << "Neither prime nor composite!" << endl;
    } 
    else {
         for (size_t i = 0; i < args.size; ++i) {
            flag = 1;
            for (int j = 2; j <= i / 2; ++j) {
                if (i % j == 0) {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) {
                cout << "Prime is: " << i << endl;
                counter++;
            }
        }
    }
    cout << "counter is: " << counter;
}

#endif