SET( EXE_NAME dgemm )

add_executable( ${EXE_NAME}
    avx256.cpp
    avx512.cpp
    avx512_subword_parallel.cpp
    basic.cpp
    basic_blocked.cpp
    get_timestamp.cpp
    main.cpp
    mtx.cpp
)

