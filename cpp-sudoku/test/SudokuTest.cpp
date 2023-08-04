#include "doctest.h"

#include "../src/Sudoku.hpp"

TEST_CASE("Can parse numbers to Cells") {
    CHECK(Cell::parse('1').get_value() == 1);
    CHECK(Cell::parse('2').get_value() == 2);
    CHECK(Cell::parse('3').get_value() == 3);
    CHECK(Cell::parse('4').get_value() == 4);
    CHECK(Cell::parse('5').get_value() == 5);
    CHECK(Cell::parse('6').get_value() == 6);
    CHECK(Cell::parse('7').get_value() == 7);
    CHECK(Cell::parse('8').get_value() == 8);
    CHECK(Cell::parse('9').get_value() == 9);
}

TEST_CASE("Any non-numeric value results in a cell with no value") {
    CHECK(Cell::parse('_').get_value() == 0);
}

TEST_CASE("Newly initialised board is empty") {
    CHECK(Board().dump_to_string() == "_________\n"
                                      "_________\n"
                                      "_________\n"
                                      "_________\n"
                                      "_________\n"
                                      "_________\n"
                                      "_________\n"
                                      "_________\n"
                                      "_________"
    );
}

TEST_CASE("Can set a single value") {
    Board board{};
    board.set_cell(0, 0, 1);
    CHECK(board.dump_to_string() == "1________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________"
    );
}

TEST_CASE("Can set a single value") {
    Board board{};
    board.set_cell(0, 0, 1);
    CHECK(board.dump_to_string() == "1________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________"
    );
}

TEST_CASE("Can initialise board with multiple cells") {
    // notice how no constrain propagation is happening yet
    Board board{"12345678_\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "98765____\n"
                "_________"};
    CHECK(board.dump_to_string() == "12345678_\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "98765____\n"
                                    "_________"
    );
}