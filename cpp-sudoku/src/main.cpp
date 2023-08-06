#include <iostream>
#include <fstream>
#include <vector>

#include "Sudoku.hpp"

void read_input_file(char *const *argv, std::vector<std::string> lines) {
    std::ifstream input_stream{argv[1]};
    if (!input_stream) {
        std::cerr << "Failed to open " << argv[1] << std::endl;
        throw std::runtime_error("Failed to open " + std::string(argv[1]));
    }

    std::string str;
    while (std::getline(input_stream, str)) {
        lines.push_back(str);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: cpp_sudoku board-file" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    read_input_file(argv, lines);

    Board board{lines};
//    Board solved_board{board.solve()};
//    std::cout << solved_board.dump_to_string() << std::endl;
//
//#ifdef WAIT_FOR_KEYPRESS_BEFORE_QUIT
//    std::cin.get();
//#endif
}

