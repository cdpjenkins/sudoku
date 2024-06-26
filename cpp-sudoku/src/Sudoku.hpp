#ifndef CPP_SUDOKU_SUDOKU_HPP
#define CPP_SUDOKU_SUDOKU_HPP

#include <cstdint>
#include <cctype>

#include <array>
#include <stdexcept>
#include <string>
#include <vector>

class Cell {
public:
    explicit Cell() : possibilities(0b1111111110) {};
    explicit Cell(uint16_t possibilities) : possibilities(possibilities) {}

    static Cell parse(char c);
    static int parse_value(char c);
    static Cell of(int value);

    int get_value() const;
    Cell eliminate_possibility(int value) const {
        return Cell{static_cast<uint16_t>(possibilities & ~(1 << value))};
    }
    char to_char();
    bool is_solved() const {
        return get_value() != 0;
    }

    bool is_impossible() const;

    bool has_possible(int value) const;
    int num_possibles() const;

    static constexpr int NO_VALUE = 0;

private:
    // bit n indicates that this cell can (possibly) be in
    // this implies that bits 1..9 are used and the rest are not
    uint16_t possibilities;
};

class Position {
public:
    explicit Position(int x, int y) : x(x), y(y) {}

    int x;
    int y;
};

class Board {
public:
    explicit Board();
    explicit Board(std::string&& input);
    explicit Board(std::vector<std::string>& lines);

    Board solve();
    void solve_one_iteration();
    void solve_multiple_iterations();

    std::string dump_to_string();
    std::string dump_to_string_with_guides();
    void set_cell(int x, int y, uint16_t value);
    Cell& cell_at(int , int y);

    Board depth_first_search();

    bool is_modified_this_time() { return modified_this_time; }

    bool is_solved() const;
    bool is_impossible() const;

private:
    bool modified_this_time = false;
    std::array<Cell, 81> cells;

    void eliminate_possibility_at(int x, int y, uint16_t value);
};

#endif //CPP_SUDOKU_SUDOKU_HPP
