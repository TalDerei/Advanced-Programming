/** 
 * Intel TBB Threading Library
 *
 * TBB Reference:
 * https://software.intel.com/content/www/us/en/develop/documentation/tbb-documentation/top/intel-threading-building-blocks-developer-guide/parallelizing-simple-loops
 */

#ifndef TBB_DEF
#define TBB_DEF

#include <iostream>
#include <tbb/tbb.h>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/task_arena.h>
#include <tbb/global_control.h>
#include "config_t.h"

using namespace std;
using namespace tbb;

void tbb_lib(arg_t args) {
    int flag = 0, counter = 0;

    /** Number of TBB threads */
    tbb::global_control global_limit(tbb::global_control::max_allowed_parallelism, args.threads);
    cout << "Number of threads used for TBB: " << args.threads << endl;

    if (args.size == 0 || args.size == 1) {
         cout << "Neither prime nor composite!" << endl;
    } else {
        /** TBB breaks iteration space into chunks, and runs each chunk on a seperate thread */
        parallel_for(tbb::blocked_range<size_t>(0, args.size), [&](tbb::blocked_range<size_t> r) {
            /** 
             * Chunk sizes are automated by auto_partitioner to achievie load balancing and limit overhead 
             */
            for (size_t i = r.begin(); i < r.end(); ++i) {
                flag = 1;
                for (int j = 2; j <= i / 2; ++j) { //outer loop only
                    if (i % j == 0) {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    /** UNCOMMENT TO PRINT PRIME NUMBERS */
                    // cout << "Prime is: " << i << endl;
                    counter++;
                }
            }
        }, auto_partitioner());
    }
    cout << "Number of primes is: " << counter << endl;
}

#endif