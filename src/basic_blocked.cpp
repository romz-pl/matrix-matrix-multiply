#include "basic_blocked.h"

/*

Cache blocked version of DGEMM.

Assume matrix C is initialized to zero. The `do_block` function is basic DGEMM with new parameters
to specify the starting positions of the submatrices of BLOCKSIZE.
The gcc optimizer can remove the function overhead instructions by inlining the do_block function.

Instead of operating on entire rows or columns of an array, blocked algorithms
operate on submatrices or blocks. The goal is to maximize accesses to the data
loaded into the cache before the data are replaced; that is, improve temporal locality
to reduce cache misses.

It reads all N-by-N elements of B, reads the same N elements in what corresponds to
one row of A repeatedly, and writes what corresponds to one row of N elements of C.
If the cache can hold one N-by-N matrix and one row of N, then at least the i-th
row of A and the array B may stay in the cache. Less than that and misses may
occur for both B and C. In the worst case, there would be 2*N^3 + N^2 memory words
accessed for N^3 operations.

To ensure that the elements being accessed can fit in the cache, the original code
is changed to compute on a submatrix. Hence, we essentially invoke the version of
DGEMM repeatedly on matrices of size BLOCKSIZE by BLOCKSIZE.
BLOCKSIZE is called the blocking factor.

The function `do_block` is DGEMM with three new parameters si, sj, and sk to specify
the starting position of each submatrix of A, B, and C. The two inner loops of the
`do_block` now compute in steps of size BLOCKSIZE rather than the full length of
B and C . The gcc optimizer removes any function call overhead by `inlining` the
function; that is, it inserts the code directly to avoid the conventional parameter
passing and return address bookkeeping instructions.

Looking only at capacity misses, the total number of memory words accessed
is 2*N^3 / BLOCKSIZE + N^2 . This total is an improvement by about a factor of
BLOCKSIZE. Hence, blocking exploits a combination of spatial and temporal
locality, since A benefits from spatial locality and B benefits from temporal
locality. Depending on the computer and size of the matrices, blocking can
improve performance by about a factor of 2 to more than a factor of 10.

Although we have aimed at reducing cache misses, blocking can also be used to
help register allocation. By taking a small blocking size, such that the block can be
held in registers, we can minimize the number of loads and stores in the program,
which again improves performance.
*/

static constexpr uint32_t BLOCKSIZE = 32;

static void do_block (const uint32_t n, const uint32_t si, const uint32_t sj, const uint32_t sk, const double *A, const double*B, double *C)
{
    for( uint32_t i = si; i < si + BLOCKSIZE; ++i )
    {
        for( uint32_t j = sj; j < sj + BLOCKSIZE; ++j )
        {
            double cij = C[i + j * n];/* cij = C[i][j] */
            for( uint32_t k = sk; k < sk + BLOCKSIZE; k++ )
            {
                cij += A[i + k * n] * B[k + j * n];/* cij+=A[i][k]*B[k][j] */
            }
            C[i + j * n] = cij;/* C[i][j] = cij */
        }
    }
}


void basic_blocked(const uint32_t n, const double* A, const double* B, double* C)
{
    for( uint32_t sj = 0; sj < n; sj += BLOCKSIZE )
    {
        for( uint32_t si = 0; si < n; si += BLOCKSIZE )
        {
            for( uint32_t sk = 0; sk < n; sk += BLOCKSIZE )
            {
                do_block(n, si, sj, sk, A, B, C);
            }
        }
    }
}
