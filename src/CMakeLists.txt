SET( EXE_NAME dgemm )

add_executable( ${EXE_NAME}
    dgemm_avx256.cpp
    dgemm_avx512.cpp
    dgemm_blocked.cpp
    dgemm_unrolled.cpp
    dgemm_basic.cpp
    dgemm_basic_blocked.cpp
    dgemm_openmp.cpp
    get_timestamp.cpp
    main.cpp
    mtx.cpp
)

