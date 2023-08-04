cmake_minimum_required(VERSION 3.25)
project(cpp_sudoku)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_sudoku
        src/main.cpp
        src/hello.cpp)

add_executable(cpp_sudoku_doctest
        test/test.cpp
        src/hello.cpp)


