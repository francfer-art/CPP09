// BitcoinExchange.hpp

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cctype>

class BitcoinExchange {
public:
    BitcoinExchange();
    ~BitcoinExchange();

    bool loadExchangeRates(const std::string &filename);
    bool loadData(const std::string &filename);
    void printResult() const;

private:
    std::map<std::string, double> exchangeRates; // date -> rate
    std::map<std::string, std::string> result;   // original line -> output string

    void parseLine(const std::string &line);
    static std::string trim(const std::string &str);
    bool isValidDate(const std::string &date) const;
    bool isValidValue(const std::string &value) const;
};

#endif
