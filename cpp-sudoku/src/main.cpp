#include <iostream>
#include "hello.hpp"
#include "Sudoku.hpp"

int main() {
    for (auto i = 0; i < 1000; i++) {
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

        std::cout << solved_board.dump_to_string() << std::endl;
    }
}
