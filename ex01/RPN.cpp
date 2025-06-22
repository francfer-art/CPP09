#include "RPN.hpp"

RPN::RPN() {

}

RPN::~RPN() {

}

void RPN::evaluate(const std::string &expression) {
    std::stack<int> stack;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else {
            if (stack.size() < 2) {
                std::cerr << "Error: not enough operands for operation '" << token << "'" << std::endl;
                return;
            }
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();

            switch (token[0]) {
                case '+':
                    stack.push(a + b);
                    break;
                case '-':
                    stack.push(a - b);
                    break;
                case '*':
                    stack.push(a * b);
                    break;
                case '/':
                    if (b == 0) {
                        std::cerr << "Error: division by zero" << std::endl;
                        return;
                    }
                    stack.push(a / b);
                    break;
                default:
                    std::cerr << "Error: unknown operator '" << token << "'" << std::endl;
                    return;
            }
        }
    }

    if (stack.size() != 1) {
        std::cerr << "Error: invalid expression" << std::endl;
        return;
    }

    std::cout << "Result: " << stack.top() << std::endl;
}