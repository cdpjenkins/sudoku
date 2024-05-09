cmake_minimum_required(VERSION 3.18)
project(cpp_sudoku)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_sudoku
        src/main.cpp
        src/hello.cpp
        src/Sudoku.cpp)

add_executable(cpp_sudoku_doctest
        test/test.cpp
        test/SudokuTest.cpp
        src/hello.cpp
        src/Sudoku.cpp)


