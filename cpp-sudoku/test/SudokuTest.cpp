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
    Board board{"1234567__\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "9876_____\n"
                "_________"};
    CHECK(board.dump_to_string() == "1234567__\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "9876_____\n"
                                    "_________"
    );
}

TEST_CASE("Can eliminate values along rows") {
    Board board{"12345678_\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________"};
    CHECK(board.dump_to_string() == "123456789\n"
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

TEST_CASE("Can eliminate values along columns") {
    Board board{"________1\n"
                "________2\n"
                "________3\n"
                "________4\n"
                "________5\n"
                "________6\n"
                "________7\n"
                "________8\n"
                "_________"};
    CHECK(board.dump_to_string() == "________1\n"
                                    "________2\n"
                                    "________3\n"
                                    "________4\n"
                                    "________5\n"
                                    "________6\n"
                                    "________7\n"
                                    "________8\n"
                                    "________9"
    );
}

TEST_CASE("Can eliminate values in squares") {
    Board board{"123______\n"
                "456______\n"
                "78______\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________\n"
                "_________"};
    CHECK(board.dump_to_string() == "123______\n"
                                    "456______\n"
                                    "789______\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________\n"
                                    "_________"
    );
}

TEST_CASE("Constraint propagation happens") {
    Board board{"12345678_\n"
                "________1\n"
                "________2\n"
                "________3\n"
                "________4\n"
                "________5\n"
                "________6\n"
                "________7\n"
                "_________"};
    CHECK(board.dump_to_string() == "123456789\n"
                                    "________1\n"
                                    "________2\n"
                                    "________3\n"
                                    "________4\n"
                                    "________5\n"
                                    "________6\n"
                                    "________7\n"
                                    "________8"
    );
}


