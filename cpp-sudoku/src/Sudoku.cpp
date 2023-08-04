#include "Sudoku.hpp"

int Cell::get_value() {
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
        int value = c - '0';

        return Cell::of(value);
    } else {
        return Cell();
    }
}

Cell Cell::of(int value) {
    if (value >= 1 && value <= 9) {
        return Cell(1 << value);
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

Board::Board() {
    
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

}
