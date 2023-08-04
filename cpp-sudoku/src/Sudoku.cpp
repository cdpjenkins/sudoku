//
// Created by Chris Jenkins on 04/08/2023.
//

#include "Sudoku.hpp"

uint_fast16_t Cell::get_value() {
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

        if (value >= 1 && value <= 9) {
            return Cell(1 << value);
        } else {
            throw std::runtime_error("bad value: " + std::to_string(value));
        }
    }
}

Board::Board() {

}

std::string Board::dump_to_string() {
    return  "_________\n"
            "_________\n"
            "_________\n"
            "_________\n"
            "_________\n"
            "_________\n"
            "_________\n"
            "_________\n"
            "_________";
}
