# Algorithms for matrix matrix multiplication, dgemm

The algorithms are taken form the books:
1. David A. Patterson, John L. Hennessy "Computer Organization and Design. The hardware software interface. RISK-V Edition", 
2. David A. Patterson, John L. Hennessy "Computer Organization and Design. The hardware software interface. MIPS Edition"

## There are the following algorithms implemented:
1. Basic, unoptimized, see src/basic.cpp
2. Using AVX with 256-bit intrinsics, see src/avx256.cpp
3. Using AVX with 512-bit intinsics, see src/avx512.cpp
4. Using AVX with 512-bit intinsics with loop unrolling, see src/avx512_subword_parallel.cpp
5. Basic, unoptimized with blocking (use blocks), see src/basic_blocked.cpp

## How to build?
To build the system, execute the following commands:
1. git clone https://github.com/romz-pl/matrix-matrix-multiply
2. cd matrix-matrix-multiply
3. mkdir build
4. cd build
5. cmake ..
6. make
7. ./src/dgemm
 
The command `./src/dgemm` executes the programm. 

## Results
For Core i7 CPU, with matrix size equal to `640`, I obtained the following results averaged over `11` randomly generated matrices:
```
         dgemm_basic:  elapsed-time=    241958
 dgemm_basic_blocked:  elapsed-time=    162224     speed-up=   1.49151
        dgemm_avx256:  elapsed-time=     66246     speed-up=   3.65242
        dgemm_avx512:  elapsed-time=     35604     speed-up=   6.79581
      dgemm_unrolled:  elapsed-time=     16634     speed-up=    14.546
       dgemm_blocked:  elapsed-time=     12981     speed-up=   18.6394
```
