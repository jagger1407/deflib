cmake_minimum_required(VERSION 3.0)

project(deflib)

set(deflib_SRC
    types.h
    string.h
    string.cpp

    main.cpp
)

add_executable(deflib ${deflib_SRC})

install(TARGETS deflib RUNTIME DESTINATION bin)
