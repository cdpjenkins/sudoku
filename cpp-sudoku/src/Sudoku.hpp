#ifndef CPP_SUDOKU_SUDOKU_HPP
#define CPP_SUDOKU_SUDOKU_HPP

#include <cstdint>
#include <cctype>

#include <array>
#include <stdexcept>
#include <string>

class Cell {
public:
    explicit Cell() : possibilities(0b1111111110) {};
    explicit Cell(uint16_t possibilities) : possibilities(possibilities) {}

    static Cell parse(char c);
    uint_fast16_t get_value();

private:
    // bit n indicates that this cell can (possibly) be in
    // this implies that bits 1..9 are used and the rest are not
    uint16_t possibilities;
};

class Board {
public:
    Board();

    std::string dump_to_string();

private:
    std::array<Cell, 81> cells;
};

#endif //CPP_SUDOKU_SUDOKU_HPP
