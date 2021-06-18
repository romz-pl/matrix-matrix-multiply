SET( EXE_NAME dgemm )

add_executable( ${EXE_NAME}
    avx256.cpp
    avx512.cpp
    basic.cpp
    get_timestamp.cpp
    main.cpp
    mtx.cpp
)

