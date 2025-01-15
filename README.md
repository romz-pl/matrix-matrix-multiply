# Algorithms for matrix matrix multiplication, dgemm

The algorithms are taken form the books:
1. David A. Patterson, John L. Hennessy "Computer Organization and Design. The hardware software interface. RISK-V Edition", 
2. David A. Patterson, John L. Hennessy "Computer Organization and Design. The hardware software interface. MIPS Edition"

## There are the following algorithms implemented:
1. Basic, unoptimized, [dgemm_basic.cpp](./src/dgemm_basic.cpp)
2. Using AVX 256-bit intrinsics, [dgemm_avx256.cpp](./src/dgemm_avx256.cpp)
3. Using AVX 512-bit intinsics, [dgemm_avx512.cpp](./src/dgemm_avx512.cpp)
4. Using AVX 512-bit intinsics with loop unrolling, [dgemm_unrolled.cpp](./src/dgemm_unrolled.cpp)
5. Blocked version, unoptimized, [dgemm_basic_blocked.cpp](./src/dgemm_basic_blocked.cpp)
6. Blocked version with AVX 512-bit intinsics [dgemm_blocked.cpp](./src/dgemm_blocked.cpp)

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

1. For Core i7 CPU, with matrix size equal to `128`, I obtained the following results averaged over `1000` randomly generated matrices:
```
         dgemm_basic:  elapsed-time=      1661
 dgemm_basic_blocked:  elapsed-time=      1260     speed-up=   1.31825
        dgemm_avx256:  elapsed-time=       443     speed-up=   3.74944
        dgemm_avx512:  elapsed-time=       233     speed-up=   7.12876
      dgemm_unrolled:  elapsed-time=       106     speed-up=   15.6698
       dgemm_blocked:  elapsed-time=       100     speed-up=     16.61
```

2. For Core i7 CPU, with matrix size equal to `640`, I obtained the following results averaged over `10` randomly generated matrices:
```
         dgemm_basic:  elapsed-time=    241958
 dgemm_basic_blocked:  elapsed-time=    162224     speed-up=   1.49151
        dgemm_avx256:  elapsed-time=     66246     speed-up=   3.65242
        dgemm_avx512:  elapsed-time=     35604     speed-up=   6.79581
      dgemm_unrolled:  elapsed-time=     16634     speed-up=    14.546
       dgemm_blocked:  elapsed-time=     12981     speed-up=   18.6394
```

3. For Core i7 CPU, with matrix size equal to `1280`, I obtained the following results averaged over `5` randomly generated matrices:
```
         dgemm_basic:  elapsed-time=   4592295
 dgemm_basic_blocked:  elapsed-time=   1626700     speed-up=   2.82307
        dgemm_avx256:  elapsed-time=   1227037     speed-up=   3.74259
        dgemm_avx512:  elapsed-time=    637091     speed-up=   7.20822
      dgemm_unrolled:  elapsed-time=    558080     speed-up=   8.22874
       dgemm_blocked:  elapsed-time=    181634     speed-up=   25.2832
```
4. For Core i7 CPU, with matrix size equal to `2560`, I obtained the following results for one randomly generated matrices:
```
         dgemm_basic:  elapsed-time=  62731813
 dgemm_basic_blocked:  elapsed-time=  16474759     speed-up=   3.80775
        dgemm_avx256:  elapsed-time=  17050012     speed-up=   3.67928
        dgemm_avx512:  elapsed-time=   9012450     speed-up=   6.96057
      dgemm_unrolled:  elapsed-time=   5958033     speed-up=   10.5289
       dgemm_blocked:  elapsed-time=   1837494     speed-up=   34.1399
```

5. For Core i7 CPU, with matrix size equal to `5120`, I obtained the following results for one randomly generated matrices:
```
        dgemm_basic:  elapsed-time=1154120417
 dgemm_basic_blocked:  elapsed-time= 137582063     speed-up=    8.3886
        dgemm_avx256:  elapsed-time= 297156247     speed-up=   3.88388
        dgemm_avx512:  elapsed-time= 144941094     speed-up=   7.96269
      dgemm_unrolled:  elapsed-time=  97428303     speed-up=   11.8458
       dgemm_blocked:  elapsed-time=  18558107     speed-up=   62.1896
```
