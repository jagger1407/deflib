cmake_minimum_required(VERSION 3.0)

project(deflib)

add_executable(deflib main.cpp)

install(TARGETS deflib RUNTIME DESTINATION bin)
