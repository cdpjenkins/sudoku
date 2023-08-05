#include <iostream>
#include <sstream>
#include <vector>

#include "Sudoku.hpp"

int Cell::get_value() const {
    switch (possibilities) {
        case (1 << 1):
            return 1;
        case (1 << 2):
            return 2;
        case (1 << 3):
            return 3;
        case (1 << 4):
            return 4;
        case (1 << 5):
            return 5;
        case (1 << 6):
            return 6;
        case (1 << 7):
            return 7;
        case (1 << 8):
            return 8;
        case (1 << 9):
            return 9;
        default:
            return 0;
    }
}

Cell Cell::parse(char c) {
    if (isdigit(c)) {
        int value = parse_value(c);

        return Cell::of(value);
    } else {
        return Cell();
    }
}

int Cell::parse_value(char c) {
    if (isdigit(c)) {
        int value = c - '0';

        return value;
    } else {
        return NO_VALUE;
    }
}

Cell Cell::of(int value) {
    if (value >= 1 && value <= 9) {
        return Cell(1 << value);
    } else if (value == 0) {
        return Cell();
    } else {
        throw std::runtime_error("bad value: " + std::to_string(value));
    }
}

char Cell::to_char() {
    int value = get_value();

    if (value == NO_VALUE) {
        return '_';
    } else {
        return static_cast<char>(value) + '0';
    }
}

Cell Cell::eliminate_possibility(int value) {
    return Cell{static_cast<uint16_t>(possibilities & ~(1 << value))};
}

bool Cell::is_solved() const {
    return get_value() != 0;
}

bool Cell::is_impossible() const {
    return num_possibles() == 0;
}

bool Cell::has_possible(int value) const {
    return possibilities & (1 << value);
}

int Cell::num_possibles() const {
    int result = 0;
    
    for (int value = 1; value <= 9; value++) {
        if (has_possible(value)) {
            result += 1;
        }
    }
    
    return result;
}

Board::Board() {
    
}

Board::Board(std::string &&input) {
    // this is probably a terrible way to parse the input

    std::istringstream ss{input};

    auto cells_it = cells.begin();

    for (int y = 0; y < 9; y++) {
        std::string line;
        std::getline(ss, line);
        auto ch_it = line.begin();
        for (int x = 0; x < 9; x++) {
            char ch = *ch_it++;
            int value = Cell::parse_value(ch);
            if (value != Cell::NO_VALUE) {
                set_cell(x, y, value);
            }
        }
    }
}

std::string Board::dump_to_string() {
    auto it = cells.begin();

    std::string result;

    // This is a horrible way to do it... must learn how to do this a bit better

    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            result += (it++)->to_char();
        }
        if (y != 8) {
            result += '\n';
        }
    }

    return result;
}

void Board::set_cell(int x, int y, uint16_t value) {
    for (int x1 = 0; x1 < 9; x1++) {
        if (x1 != x) {
            eliminate_possibility_at(x1, y, value);
        }
    }

    for (int y1 = 0; y1 < 9; y1++) {
        if (y1 != y) {
            eliminate_possibility_at(x, y1, value);
        }
    }

    int xo = x - (x % 3);
    int yo = y - (y % 3);
    for (int y1 = yo; y1 < yo + 3; y1++) {
        for (int x1 = xo; x1 < xo + 3; x1++) {
            if (x1 != x && y1 != y) {
                eliminate_possibility_at(x1, y1, value);
            }
        }
    }

    if (!cell_at(x, y).is_solved()) {
        modified_this_time = true;
        cell_at(x, y) = Cell::of(value);
    }
}

void Board::eliminate_possibility_at(int x, int y, uint16_t value) {
    Cell &cell = cell_at(x, y);

    if (!cell.is_solved()) {
        const Cell new_cell = cell.eliminate_possibility(value);

        if (new_cell.is_solved()) {
            cell_at(x, y) = new_cell;
            set_cell(x, y, new_cell.get_value());
        }

        cell_at(x, y) = new_cell;
    }
}

Cell& Board::cell_at(int x, int y) {
    return cells[y * 9 + x];
}

void Board::solve_one_iteration() {
    modified_this_time = false;

    // rows
    for (int row_y = 0; row_y < 9; row_y++) {
        for (int value = 1; value <= 9; value++) {
            std::vector<int> possible_xs;

            for (int x = 0; x < 9; x++) {
                if (cell_at(x, row_y).has_possible(value)) {
                    possible_xs.push_back(x);
                }
            }

            if (possible_xs.size() == 1) {
                set_cell(possible_xs[0], row_y, value);
            }
        }
    }

    // columns
    for (int col_x = 0; col_x < 9; col_x++) {
        for (int value = 1; value <= 9; value++) {
            std::vector<int> possible_ys;

            for (int y = 0; y < 9; y++) {
                if (cell_at(col_x, y).has_possible(value)) {
                    possible_ys.push_back(y);
                }
            }

            if (possible_ys.size() == 1) {
                set_cell(col_x, possible_ys[0], value);
            }
        }
    }

    // squares
    for (int yo = 0; yo < 9; yo += 3) {
        for (int xo = 0; xo < 9; xo += 3) {
            for (int value = 1; value <= 9; value++) {
                std::vector<int> possible_cells;
                for (int y = xo; y < yo + 3; y++) {
                    for (int x = xo; x < xo + 3; x++) {
                        if (cell_at(x, y).has_possible(value)) {
                            possible_cells.push_back(y * 16 + x);
                        }
                    }
                }

                if (possible_cells.size() == 1) {
                    int& cell = possible_cells.front();
                    set_cell(cell % 16, cell / 16, value);
                }
            }
        }
    }
}

void Board::solve_multiple_iterations() {
    do {
        solve_one_iteration();
    } while (is_modified_this_time());
}

Board Board::depth_first_search() {
    Cell cell_to_search = Cell{};
    Position pos_to_search = Position{-1, -1};
    int current_min_num_possibles = 10;

    // find cell with smallest number of possibles
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            Cell &cell = cell_at(x, y);
            int num_possibles = cell.num_possibles();

            if (num_possibles != 1 && num_possibles < current_min_num_possibles) {
                cell_to_search = cell;
                pos_to_search = Position(x, y);
                current_min_num_possibles = num_possibles;
            }
        }
    }

    for (int guess = 1; guess < 9; guess++) {
        if (cell_to_search.has_possible(guess)) {
            Board new_board {*this};
            new_board.set_cell(pos_to_search.x, pos_to_search.y, guess);

            new_board.solve_multiple_iterations();

            if (new_board.is_impossible()) {
                continue;
            }

            Board new_new_board = new_board.solve();
            if (new_new_board.is_impossible()) {
                continue;
            }

            if (new_new_board.is_solved()) {
                return new_new_board;
            }
        }
    }

    throw std::runtime_error("Couldn't find one... aiaiaiaiaiaai");
}

bool Board::is_solved() const {
    for (auto cell : cells) {
        if (!cell.is_solved()) {
            return false;
        }
    }

    return true;
}

bool Board::is_impossible() const {
    for (auto cell : cells) {
        if (cell.is_impossible()) {
            return true;
        }
    }

    return false;
}

Board Board::solve() {
    solve_multiple_iterations();
    if (is_solved()) {
        return *this;
    } else if (is_impossible()) {
        throw std::runtime_error(dump_to_string());
    } else {
        return depth_first_search();
    }
}
