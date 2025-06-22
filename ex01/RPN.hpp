#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <stack>

class RPN {
    public:
        RPN();
        ~RPN();
        void evaluate(const std::string &expression);
};

#endif
