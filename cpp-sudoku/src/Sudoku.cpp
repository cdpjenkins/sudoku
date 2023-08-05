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

bool Cell::has_possible(int value) {
    return possibilities & (1 << value);
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

    cell_at(x, y) = Cell::of(value);
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
    // rows
    for (int row_y = 0; row_y < 9; row_y++) {
        for (int value = 1; value < 9; value++) {
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
        for (int value = 1; value < 9; value++) {
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
            for (int value = 1; value < 9; value++) {
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
