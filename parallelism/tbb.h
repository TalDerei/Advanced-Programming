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
#include <oneapi/tbb/info.h>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/task_arena.h>
#include "config_t.h"

using namespace std;
using namespace tbb;

void tbb_lib(arg_t args) {
    int flag, counter;

    /** Number of threads */
    int num_threads = oneapi::tbb::info::default_concurrency();
    cout << "Default number of threads is: " << num_threads << endl;

    if (args.size == 0 || args.size == 1) {
         cout << "Neither prime nor composite!" << endl;
    } else {
        /** TBB breaks iteration space into chunks, and runs each chunk on a seperate thread */
        parallel_for(tbb::blocked_range<size_t>(2, args.size), [&](tbb::blocked_range<size_t> r) {
            /** 
             * Chunk sizes automated by auto_partitioner to achievie load balancing and limit overhead
             * Simple_partitioner defaults grainsize to 1. Smaller the grainsize = larger chunking
             * overhead. Larger grainsize = larger parallelism overhead (reduces parallelism)
             */
            for (size_t i = r.begin(); i < r.end(); ++i) {
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
        }, auto_partitioner());
    }
    cout << "counter is: " << counter;
}

#endif