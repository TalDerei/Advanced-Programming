/** 
 * Sequential Implementation
 * 
 * The sequential code below references: https://www.geeksforgeeks.org/program-to-find-prime-numbers-between-given-interval/
 * 
 * I referenced a known working code for my sequential baseline for "correctness", since there isn't many variations
 * to calculating all known primes in a given range.  
 */

#ifndef SEQUENTIAL_DEF
#define SEQUENTIAL_DEF

#include <iostream>
#include "config_t.h"

using namespace std;

void sequential(arg_t args) {
    int flag;
    int counter = 0;

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
                cout << i << " is prime" << endl;
                counter++;
            }
        }
    }
    cout << "Number of primes is: " << counter << endl;
}

#endif