# C++ Sudoku Solver
This is a work-in-progress Sudoku solver written as I attempt to re-learn C++ after many years. 

I'm still fairly early in my Modern C++ journey so this code is likely pretty terrible but I'm hoping to learn a lot
along the way.

Given that this is C++, I'm hoping to ultimately wring every last drop of performance out of the machine and solve
really hard Sudokus with extremely low latency. I'm hopeful that this will present an opportunity to play with
templates, constexpr and other extremely hairy language features.

Right now, it uses a 16 bit integer to represent the state of a cell, with one bit encoding whether a particular
value is possible. This is already proving to be faster than the use of a set of integers in a JVM language.
