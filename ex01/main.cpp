#include "RPN.hpp"

int main(int argc, char **argv) {
   
    RPN rpn;

    try {
        if (argc != 2) {
            throw std::runtime_error("Error: Invalid number of arguments.");
        }
        rpn.evaluate(argv[1]);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
