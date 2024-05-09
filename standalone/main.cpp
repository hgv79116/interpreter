#include <fstream>
#include <iostream>

#include "interpreter.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        throw std::runtime_error{"Wrong number of command line arguments"};
    }

    std::string path{argv[1]};

    std::ifstream ins{path};
    if (ins.fail()) {
        // If this exception is not caught,
        // the fail will go unnoticed
        throw std::runtime_error{"Failed to open file"};
    }

    Interpreter intr;

    std::string line;
    while (std::getline(ins, line)) {
        try {
            intr.processLine(line);
        } catch (std::exception e) {
            std::cout << "Exception encountered: " << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}