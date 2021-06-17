SET( EXE_NAME dgemm )

add_executable( ${EXE_NAME}
    avx256.cpp
    basic.cpp
    main.cpp
    mtx.cpp
)

