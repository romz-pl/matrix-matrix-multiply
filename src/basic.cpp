#include "basic.h"

void basic(uint32_t n, double* A, double* B, double* C)
{
    for(uint32_t i = 0; i < n; ++i)
    {
        for(uint32_t j = 0; j < n; ++j)
        {
            double cij = C[i + j * n]; /* cij = C[i][j] */
            for(uint32_t k = 0; k < n; k++)
            {
                cij += A[i + k * n] * B[k + j * n]; /* cij += A[i][k]*B[k][j] */
            }
            C[i + j * n] = cij; /* C[i][j] = cij */
        }
    }
}

