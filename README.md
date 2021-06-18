# Algorithms for matrix matrix multiplication, dgemm

The algorithms are taken form the book David A. Patterson, John L. Hennessy "Computer Organization and Design. The hardware software interface. RISK-V Edition", 

## Thre are the following algorithm implemented:
1. Basic, unoptimized see src/basic.cpp
2. Using AVX with 256-bit intrinsics, see src/avx256.cpp
3. Using AVX with 512-bit intinsics, see src/avx512.cpp
4. Using AVX with 512-bit intinsics with loop unrolling, see src/avx512_subword_parallel.cpp
 
