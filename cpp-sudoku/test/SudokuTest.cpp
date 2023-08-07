#include <iostream>
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

TEST_CASE("Can infer value of the only cell in a row that could hold a particular value") {
    Board board{"1________\n"
                "______1__\n"
                "___1_____\n"
                "_1_______\n"
                "____1____\n"
                "_______1_\n"
                "__1______\n"
                "_____1___\n"
                "_________"};
    board.solve_one_iteration();
    CHECK(board.dump_to_string() == "1________\n"
                                    "______1__\n"
                                    "___1_____\n"
                                    "_1_______\n"
                                    "____1____\n"
                                    "_______1_\n"
                                    "__1______\n"
                                    "_____1___\n"
                                    "________1"
    );
}

TEST_CASE("Can infer value of the only cell in a column that could hold that value") {
    Board board{"________2\n"
                "________3\n"
                "________4\n"
                "________5\n"
                "________6\n"
                "________7\n"
                "___1_____\n"
                "1________\n"
                "_________"};
    board.solve_one_iteration();
    CHECK(board.dump_to_string() == "________2\n"
                                    "________3\n"
                                    "________4\n"
                                    "________5\n"
                                    "________6\n"
                                    "________7\n"
                                    "___1_____\n"
                                    "1________\n"
                                    "________1"
    );
}

TEST_CASE("Can infer value of the only cell in a square that could hold that value") {
    Board board{"________1\n"
                "_____1___\n"
                "_________\n"
                "_1_______\n"
                "_________\n"
                "_________\n"
                "__1______\n"
                "_________\n"
                "_________"};
    board.solve_one_iteration();
    CHECK(board.dump_to_string() == "________1\n"
                                    "_____1___\n"
                                    "1________\n"
                                    "_1_______\n"
                                    "_________\n"
                                    "_________\n"
                                    "__1______\n"
                                    "_________\n"
                                    "_________"
    );
    CHECK(board.is_solved() == false);
}

TEST_CASE("Can solve easy board in one teration") {
    Board board{"53__7____\n"
                "6__195___\n"
                "_98____6_\n"
                "8___6___3\n"
                "4__8_3__1\n"
                "7___2___6\n"
                "_6____28_\n"
                "___419__5\n"
                "____8__79"};

    board.solve_one_iteration();

    CHECK(board.dump_to_string() == "534678912\n"
                                    "672195348\n"
                                    "198342567\n"
                                    "859761423\n"
                                    "426853791\n"
                                    "713924856\n"
                                    "961537284\n"
                                    "287419635\n"
                                    "345286179"
    );
    CHECK(board.is_solved() == true);
}

TEST_CASE("Can only partially solve a hard board with repeated calls to solve_one_iteration") {
    Board board{"_____8__6\n"
                "9_17_53_4\n"
                "_____4_1_\n"
                "1__94__5_\n"
                "49__5__67\n"
                "_2__71__3\n"
                "_3_4_____\n"
                "2_53_97_1\n"
                "7__5_____"};

    board.solve_multiple_iterations();

    CHECK(board.dump_to_string() == "3__198_76\n"
                                    "9_17_53_4\n"
                                    "____34_1_\n"
                                    "1__94__5_\n"
                                    "49__5_167\n"
                                    "52__71__3\n"
                                    "_3_417___\n"
                                    "2_53_97_1\n"
                                    "71_5___3_"
    );
    CHECK(board.is_solved() == false);
}

TEST_CASE("Can fully solve a hard board with depth first search") {
    Board board{"_____8__6\n"
                "9_17_53_4\n"
                "_____4_1_\n"
                "1__94__5_\n"
                "49__5__67\n"
                "_2__71__3\n"
                "_3_4_____\n"
                "2_53_97_1\n"
                "7__5_____"};

    Board solved_board{board.solve()};

    CHECK(solved_board.dump_to_string() == "342198576\n"
                                           "961725384\n"
                                           "857634912\n"
                                           "173946258\n"
                                           "498253167\n"
                                           "526871493\n"
                                           "639417825\n"
                                           "285369741\n"
                                           "714582639"
    );
    CHECK(solved_board.is_solved() == true);
}

TEST_CASE("Can NOT solve a board that has no solution") {
    // I'm not actually convinced that this board does not have a solution but several sites on the interwebs think that
    // it can't be solved
    Board board{"_98__425_\n"
                "___2____3\n"
                "__5_____8\n"
                "__34__17_\n"
                "6____9___\n"
                "________2\n"
                "_2__7____\n"
                "_______8_\n"
                "__71__54_"};

    Board solved_board{board.solve()};

    CHECK(solved_board.is_solved() == false);
}
