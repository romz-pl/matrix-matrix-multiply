#include "avx256.h"
#include <x86intrin.h>

/*
The declaration uses the __m256d datatype, which tells the compiler the variable will
hold four double-precision floating-point values. The intrinsic _mm256_load_pd()
uses AVX instructions to load four double-precision floating-point numbers in parallel (_pd)
from the matrix C into c0. The address calculation C+i+j*n represents elementC[i+j*n].
Symmetrically, the final step uses the intrinsic_mm256_store_pd() to store four double-precision
floating-pointnumbers from c0 into the matrix C. As we’re going through four elements each iteration,
the outer for loop increments i by 4 instead of by 1.

Inside the loops, we first load four elements of A againusing _mm256_load_pd().
To multiply these elements by one elementof B, we first use the intrinsic _mm256_broadcast_sd(), which
makes four identical copies of the scalar double precision number - in this case an element of B -
in one of the YMM registers. We then use _mm256_mul_pd() to multiply the four double-precision results
in parallel. Finally, _mm256_add_pd() adds the four products to the four sums in c0.

For matrices of dimensions of 32 by 32, the unoptimized DGEMM (function called `basic`) runs at 1.7 GigaFLOPS
(FLoating point OperationsPer Second) on one core of a 2.6 GHz Intel Core i7 (Sandy Bridge).
The optimized code (function called `avx256`) performs at 6.4 GigaFLOPS. The AVX-256 version
is 3.85 times as fast, which is very close to the factor of 4.0 increase that you might hope for
from performing four times as many operations at a time by using subword parallelism.
*/
void avx256(uint32_t n, const double* A, const double* B, double* C)
{

    for( uint32_t i = 0; i < n; i += 4 )
    {
        for( uint32_t j = 0; j < n; j++ ) 
        {
            __m256d c0 = _mm256_load_pd(C + i + j * n); /* c0 = C[i][j] */
            for( uint32_t k = 0; k < n; k++ )
            {
                c0 = _mm256_add_pd(c0, /* c0 += A[i][k]*B[k][j] */
                        _mm256_mul_pd( _mm256_load_pd(A + i + k * n), _mm256_broadcast_sd(B + k + j * n) ) );
            }

            _mm256_store_pd(C+i+j*n, c0); /* C[i][j] = c0 */
        }
    }
}
