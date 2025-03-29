cmake_minimum_required(VERSION 3.0)

project(deflib)

set(deflib_INC
    deflib/types.h
    deflib/deflib.h

    deflib/data/string.h
    deflib/data/string.cpp
    deflib/data/time.h
    deflib/data/time.cpp

    deflib/collections/array.h

    deflib/io/defcon.h
    deflib/io/defcon.cpp
    deflib/io/file.h
    deflib/io/file.cpp

    deflib/cvt.h
    deflib/cvt.cpp
)

set(deflib_SRC
    main.cpp
    main.h
    boot.cpp
)

add_executable(deflib ${deflib_SRC} ${deflib_INC})

install(TARGETS deflib RUNTIME DESTINATION bin)
