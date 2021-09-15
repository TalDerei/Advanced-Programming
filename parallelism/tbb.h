// /** 
//  * Compilation: g++ --std=c++17 -O3 prime.cc -ltbb -o parallel_for
//  * Primes: N = 1009 (10^3), 1000003 (10^6), 1000000007 (10^9)
//  * 
//  * TBB Reference:
//  * https://software.intel.com/content/www/us/en/develop/documentation/tbb-documentation/top/intel-threading-building-blocks-developer-guide/parallelizing-simple-loops/parallelfor.html
//  * https://software.intel.com/content/www/us/en/develop/documentation/tbb-documentation/top/intel-threading-building-blocks-developer-guide/parallelizing-simple-loops/parallelfor/controlling-chunking.html
//  * https://software.intel.com/content/www/us/en/develop/documentation/tbb-documentation/top/intel-threading-building-blocks-developer-guide/parallelizing-simple-loops/parallelfor/partitioner-summary.html
//  */

// #ifndef TBB_DEF
// #define TBB_DEF

// #include <iostream>
// #include <tbb/tbb.h>
// #include <oneapi/tbb/info.h>
// #include <oneapi/tbb/parallel_for.h>
// #include <oneapi/tbb/task_arena.h>

// using namespace std;
// using namespace tbb;

// void tbb_lib(size_t n) {
//     bool isPrime = true;

//     int num_threads = oneapi::tbb::info::default_concurrency();
//     cout << "Default number of threads is: " << num_threads << endl;

//     if (n == 0 || n == 1) {
//         isPrime = false;
//     } else {
//         /** TBB breaks iteration space into chunks, and runs each chunk on a seperate thread */
//         parallel_for(tbb::blocked_range<size_t>(2, n / 2), [&](tbb::blocked_range<size_t> r)
//         {
//             /** 
//              * Chunk sizes automated by auto_partitioner to achievie load balancing and limit overhead
//              * Simple_partitioner defaults grainsize to 1. Smaller the grainsize = larger chunking
//              * overhead. Larger grainsize = larger parallelism overhead (reduces parallelism)
//              */
//             for (size_t i = r.begin(); i < r.end(); ++i) {
//                 if (n % i == 0) {
//                     isPrime = false;
//                     break;
//                 }
//             }
//         }, auto_partitioner());
//     }

//     if (isPrime) {
//         std::cout << n << " is a prime number" << std::endl;
//     } else {
//         std::cout << n << " is not a prime number" << std::endl;
//     }
// }

// #endif