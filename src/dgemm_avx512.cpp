#include "dgemm_avx512.h"
#include <x86intrin.h>

/*
Optimized version of DGEMM using C intrinsics to generate the AVX512.

To demonstrate the performance impact of subwordparallelism, we rerun the code using AVX.
While compiler writers may eventually be able to routinely produce high-quality code that uses the AVX
instructions of the x86, for now we must `cheat` by using C intrinsics that
more or less tell the compiler exactly how to produce good code.

Th declaration uses the __m512d data type, which tells the compiler the
variable will hold 8 double-precision floating-point values (8 × 64 bits =
512 bits). The intrinsic _mm512_load_pd() uses AVX
instructions to load 8 double-precision floating-point numbers in parallel ( _pd )
from the matrix C into c0. The address calculation C+i+j*n represents
element C[i+j*n]. Symmetrically, the final step uses the intrinsic
_mm512_store_pd() to store 8 double-precision floating-point numbers
from c0 into the matrix C. As we are going through 8 elements each
iteration, the outer for loop increments `i` by 8.

Inside the loops, we first load 8 elements of A again using
_mm512_ load_pd(). To multiply these elements by one element of B, we
first use the intrinsic _mm512_broadcast_sd(), which makes eight identical
copies of the scalar double precision number (in this case an element of B)
in one of the ZMM registers. We then use _mm512_fmadd_pd to
multiply the 8 double-precision results in parallel and then add the 8
products to the 8 sums in c0.

*/
void dgemm_avx512(const uint32_t n, const double* A, const double* B, double* C)
{
    for( uint32_t i = 0; i < n; i += 8)
    {
        for( uint32_t j = 0; j < n; ++j)
        {
            __m512d c0 = _mm512_load_pd(C + i + j * n); // c0 = C[i][j]
            for( uint32_t k = 0; k < n; k++)
            {
                // c0 += A[i][k] * B[k][j]
                __m512d bb = _mm512_broadcastsd_pd(_mm_load_sd(B + j * n + k));
                c0 = _mm512_fmadd_pd(_mm512_load_pd(A + n * k + i), bb, c0);
            }
            _mm512_store_pd(C + i + j * n, c0); // C[i][j] = c0
        }
    }
}
