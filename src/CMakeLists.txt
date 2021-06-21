SET( EXE_NAME dgemm )

add_executable( ${EXE_NAME}
    avx256.cpp
    avx512.cpp
    avx512_blocked.cpp
    avx512_subword_parallel.cpp
    dgemm_basic.cpp
    basic_blocked.cpp
    get_timestamp.cpp
    main.cpp
    mtx.cpp
    dgemm_openmp.cpp
)

