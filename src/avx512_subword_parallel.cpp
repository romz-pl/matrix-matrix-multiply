#include "avx512_subword_parallel.h"
#include <x86intrin.h>

/*
Optimized version of DGEMM using C intrinsics to generate the AVX subword-parallel instructions
for the x86 and loop unrolling to create more opportunities for instruction-level parallelism.

We can see the impact of
instruction-level parallelism by unrolling the loop so that the multiple-issue,
out-of-order execution processor has more instructions to work with.
The function below is the unrolled version of function avx512, which contains
the C intrinsics to produce the AVX-512 instructions.
*/
void avx512_subword_parallel(const uint32_t n, const double* A, const double* B, double* C)
{
    constexpr uint32_t UNROLL = 4;

    for( uint32_t i = 0; i < n; i += UNROLL * 8)
    {
        for( uint32_t j = 0; j < n; ++j)
        {
            __m512d c[UNROLL];
            for( uint32_t r = 0; r < UNROLL; r++)
            {
                c[r] = _mm512_load_pd(C + i + r * 8 + j * n); //[ UNROLL];
            }

            for( uint32_t k = 0; k < n; k++ )
            {
                __m512d bb = _mm512_broadcastsd_pd(_mm_load_sd(B + j * n + k));
                for( uint32_t r = 0; r < UNROLL; r++)
                {
                    c[r] = _mm512_fmadd_pd(_mm512_load_pd(A + n * k + r * 8 + i), bb, c[r]);
                }
            }
            for( uint32_t r = 0; r < UNROLL; r++)
            {
                _mm512_store_pd(C + i + r * 8 + j * n, c[r]);
            }
        }
    }
}
