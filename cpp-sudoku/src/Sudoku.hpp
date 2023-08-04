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
    static int parse_value(char c);
    static Cell of(int value);

    int get_value();
    Cell eliminate_possibility(int value);
    char to_char();

    static constexpr int NO_VALUE = 0;
private:
    // bit n indicates that this cell can (possibly) be in
    // this implies that bits 1..9 are used and the rest are not
    uint16_t possibilities;

};

class Board {
public:
    explicit Board();
    explicit Board(std::string &&input);

    std::string dump_to_string();
    void set_cell(int x, int y, uint16_t value);
    Cell& cell_at(int , int y);

private:
    std::array<Cell, 81> cells;
};

#endif //CPP_SUDOKU_SUDOKU_HPP
