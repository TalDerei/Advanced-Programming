/**
 * CSE 411
 * Fall 2021
 * Project #1 -- Part #2
 * Tal Derei
 *
 * The purpose of this assignment is to make correct code run faster.  This file
 * (gauss.cc) file implements the O(n^3) Gaussian Elimination algorithm.  We are
 * not going to try to change the algorithm to improve performance.  Instead, we
 * will try to use a variety of techniques, to include improving locality, using
 * SIMD operations, and exploiting multicore, to accelerate the program.
 *
 * Keep in mind that for small problems, it's likely not possible to get a
 * parallel speedup.  But for 2048 and 4096, it is possible to get a HUGE
 * speedup.
 * 
 * COMPILATION : g++ --std=c++17 -O3 gauss.cc -ltbb -o gauss_exe
 */

#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <unistd.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include <tbb/global_control.h>

using namespace std;
using namespace tbb;

/**
 * matrix_t represents a 2-d (square) array of doubles
 */
class matrix_t {
  /**
   * M is the matrix.  It is an array of arrays, so that we can swap row
   * pointers in O(1) instead of swapping rows in O(n)
   */
  double **M;

  /** the # rows / # columns / sqrt(# elements) */
  unsigned int size;

public:
  /** Construct by allocating the matrix */
  matrix_t(unsigned int n) : M(new double *[n]), size(n) {
    for (unsigned i = 0; i < size; ++i)
      M[i] = new double[size];
  }

  /** Destruct by de-allocating */
  ~matrix_t() {
    for (unsigned i = 0; i < size; ++i)
      delete M[i];
    delete M;
  }

  /** Give the illusion of this being a simple array */
  double *&operator[](std::size_t idx) { return M[idx]; };
  double *const &operator[](std::size_t idx) const { return M[idx]; };
  unsigned int getSize() { return size; }
};

/**
 * vector_t represents a 1-d array of doubles
 */
class vector_t { 
  /** simple array of doubles */
  double *V;

  /** size of V */
  unsigned int size;

public:
  /** Construct by allocating the vector */
  vector_t(unsigned int n) : V(new double[n]), size(n) {}

  /** Destruct by freeing the vector */
  ~vector_t() { delete V; }

  /** Give the illusion of this being a simple array */
  double &operator[](std::size_t idx) { return V[idx]; };
  const double &operator[](std::size_t idx) const { return V[idx]; };
  unsigned int getSize() { return size; }
};

/**
 * Given a random seed, populate the elements of A and then B with a
 * sequence of random numbers in the range (-range...range)
 */
void initializeFromSeed(int seed, matrix_t &A, vector_t &B,
                        double range) {
  // Use a Mersenne Twister to create doubles in the requested range
  std::mt19937 seeder(seed);
  auto mt_rand =
      std::bind(std::uniform_real_distribution<double>(-range, range),
                std::mt19937(seed));
  // populate A
  for (unsigned i = 0; i < A.getSize(); ++i)
    for (unsigned j = 0; j < A.getSize(); ++j)
      A[i][j] = (double)(mt_rand());
  // populate B
  for (unsigned i = 0; i < B.getSize(); ++i)
    B[i] = (double)(mt_rand());
}

/** Print the matrix and array in a form that looks good */
void print(matrix_t &A, vector_t &B) {
  for (unsigned i = 0; i < A.getSize(); ++i) {
    for (unsigned j = 0; j < A.getSize(); ++j)
      std::cout << (double) A[i][j] << "\t";
    std::cout << " | " << (double) B[i] << "\n";
  }
  std::cout << std::endl;
}

void gauss(matrix_t &A, vector_t &B, vector_t &X) {
  // iterate over rows
  for (unsigned i = 0; i < A.getSize(); ++i) {
    // NB: we are now on the ith column

    // For numerical stability, find the largest value in this column
    double big = abs(A[i][i]);
    int row = i;
    for (unsigned k = i + 1; k < A.getSize(); ++k) {
      if (abs(A[k][i]) > big) {
        big = abs(A[k][i]);
        row = k;
      }
    }
    // Given our random initialization, singular matrices are possible!
    if (big == 0.0) {
      std::cout << "The matrix is singular!" << std::endl;
      exit(-1);
    }

    // swap so max column value is in ith row
    std::swap(A[i], A[row]);
    std::swap(B[i], B[row]);

    // Eliminate the ith row from all subsequent rows
    //
    // NB: this will lead to all subsequent rows having a 0 in the ith
    // column
    for (unsigned k = i + 1; k < A.getSize(); ++k) {
      double c = -A[k][i] / A[i][i];
      for (unsigned j = i; j < A.getSize(); ++j)
        if (i == j)
          A[k][j] = 0;
        else
          A[k][j] += c * A[i][j];
      B[k] += c * B[i];
    }
  }

  // NB: A is now an upper triangular matrix

  // Use back substitution to solve equation A * x = b
  for (int i = A.getSize() - 1; i >= 0; --i) {
    X[i] = B[i] / A[i][i];
    for (int k = i - 1; k >= 0; --k)
      B[k] -= A[k][i] * X[i];
  }
}

/**
 * For a system of equations A * x = b, with Matrix A and Vectors B and X,
 * and assuming we only know A and b, compute x via the Gaussian Elimination
 * technique
 */
void tbb_gauss(matrix_t &A, vector_t &B, vector_t &X, int threads) {
  cout << "Number of threads used for TBB is: " << threads << endl;
  tbb::global_control global_limit(tbb::global_control::max_allowed_parallelism, threads);
  parallel_for(tbb::blocked_range<unsigned>(0, A.getSize()), [&](tbb::blocked_range<unsigned> r) {
  // iterate over rows
  for (unsigned i = r.begin(); i < r.end(); ++i) {
    // NB: we are now on the ith column

    // For numerical stability, find the largest value in this column
    double big = abs(A[i][i]);
    int row = i;
    for (unsigned k = i + 1; k < A.getSize(); k+=2) {
      if (abs(A[k][i]) > big) {
        big = abs(A[k][i]);
        row = k;
      }
    }
    // Given our random initialization, singular matrices are possible!
    if (big == 0.0) {
      std::cout << "The matrix is singular!" << std::endl;
      exit(-1);
    }

    // swap so max column value is in ith row
    std::swap(A[i], A[row]);
    std::swap(B[i], B[row]);

    // Eliminate the ith row from all subsequent rows
    //
    // NB: this will lead to all subsequent rows having a 0 in the ith
    // column
    for (unsigned k = i + 1; k < A.getSize(); ++k) {
      double c = -A[k][i] / A[i][i];
      for (unsigned j = i; j < A.getSize(); ++j)
        if (i == j)
          A[k][j] = 0;
        else
          A[k][j] += c * A[i][j];
      B[k] += c * B[i];
    }
  }
  }, auto_partitioner());

    // Use back substitution to solve equation A * x = b
    for (int i = A.getSize() - 1; i >= 0; --i) {
        X[i] = B[i] / A[i][i];
        for (int k = i - 1; k >= 0; --k) {
            B[k] -= A[k][i] * X[i];
        }
    }
}

/**
 * Make sure that the values in X actually satisfy the equation A * x = b
 *
 * Unfortunately, this check isn't so simple.  Even with double precision
 * floating point, we lose some significant digits, and thus a naive check
 * won't pass.
 */
void check(matrix_t &A, vector_t &B, vector_t &X) {
  for (unsigned i = 0; i < A.getSize(); ++i) {
    // compute the value of B based on X
    double ans = 0;
    for (unsigned j = 0; j < A.getSize(); ++j)
      ans += (double) A[i][j] * (double) X[j];

    // we can't just compare ans to B[i].  But if the two are close, then
    // their ratio will compute to 1 even at double precision
    double ratio = (double) std::max(abs(ans / B[i]), abs(B[i] / ans));
    if (ratio != 1) {
      std::cout << "Verification failed for index = " << i << "." << std::endl;
      std::cout << ans << " != " << B[i] << std::endl;
      return;
    }
  }
  std::cout << "Verification succeeded" << std::endl;
}

/** Print some helpful usage information */
void usage() {
  using std::cout;
  cout << "Gaussian Elimination Solver\n";
  cout << "  Usage: gauss [options]\n";
  cout << "    -r <int> : seed for the random number generator (default 411)\n";
  cout << "    -n <int> : number of rows in the matrix (default 256)\n";
  cout << "    -g <int> : range for values in the matrix (default 65536)\n";
  cout << "    -t <int> : number of threads for tbb\n";
  cout << "    -v       : toggle verbose output (default false)\n";
  cout << "    -p       : toggle parallel mode (default false)\n";
  cout << "    -c       : toggle verifying the result (default true)\n";
  cout << "    -h       : print this message\n";
}

int main(int argc, char *argv[]) {
  using std::chrono::duration;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;

  // Config vars that we get via getopt
  int seed = 411; // random seed
  int size = 256; // # rows in the matrix
  double range = 65536.0; // matrix elements will have values between -range and range
  bool verbose = false;  // should we print some diagnostics?
  bool docheck = true;   // should we verify the output?
  bool parallel = false; // use parallelism?
  int threads = 1; // number of threads for tbb

  // Parse the command line options:
  int o;
  while ((o = getopt(argc, argv, "r:n:g:t:hvcp")) != -1) {
    switch (o) {
    case 'r':
      seed = atoi(optarg);
      break;
    case 'n':
      size = atoi(optarg);
      break;
    case 'g':
      range = atoi(optarg);
      break;
    case 't':
      threads = atoi(optarg);
      break;
    case 'h':
      usage();
      break;
    case 'v':
      verbose = !verbose;
      break;
    case 'c':
      docheck = !docheck;
      break;
    case 'p':
      parallel = !parallel;
      break;
    default:
      usage();
      exit(-1);
    }
  }

  // Print the configuration... this makes results of scripted experiments
  // much easier to parse
  std::cout << "r,n,g,p,t = " << seed << ", " << size << ", " << range << ", " 
            << parallel << ", " << threads << std::endl;

  // Create our matrix and vectors, and populate them with default values
  matrix_t A(size);
  vector_t B(size);
  vector_t X(size);
  initializeFromSeed(seed, A, B, range);

  // Print initial matrix
  if (verbose) {
    std::cout << "Matrix (A) | B" << std::endl;
    print(A, B);
  }

  // Calculate solution
  auto starttime = high_resolution_clock::now();
  
  if (parallel) {
    tbb_gauss(A, B, X, threads);
    std::cout << "Parallel version not yet implemented" << std::endl;
  }
  else {
    gauss(A, B, X);
  }
  auto endtime = high_resolution_clock::now();

  // Print result
  if (verbose) {
    std::cout << "Result X" << std::endl;
    for (unsigned i = 0; i < A.getSize(); ++i)
      std::cout << X[i] << " ";
    std::cout << std::endl << std::endl;
  }

  // Check the solution?
  if (docheck) {
    // Pseudorandom number generators are nice... We can re-create A and
    // B by re-initializing them from the same seed as before
    initializeFromSeed(seed, A, B, range);
    check(A, B, X);
  }

  // Print the execution time
  duration<double> time_span =
      duration_cast<duration<double>>(endtime - starttime);
  std::cout << "Total execution time: " << time_span.count() << " seconds"
            << std::endl;
}
