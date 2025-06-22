// BitcoinExchange.cpp

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::loadExchangeRates(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open exchange rate file: " << filename << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos)
            continue;

        std::string date = trim(line.substr(0, commaPos));
        std::string rateStr = trim(line.substr(commaPos + 1));

        std::istringstream iss(rateStr);
        double rate;
        if (!(iss >> rate)) {
            std::cerr << "Invalid exchange rate in: " << line << std::endl;
            continue;
        }
        exchangeRates[date] = rate;
    }

    file.close();
    return true;
}

bool BitcoinExchange::loadData(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open input file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            parseLine(line);
        }
    }
    file.close();
    return true;
}

void BitcoinExchange::parseLine(const std::string &line) {
    size_t delimiterPos = line.find('|');
    if (delimiterPos == std::string::npos) {
        result[line] = "Error: bad input => " + line;
        return;
    }

    std::string date = trim(line.substr(0, delimiterPos));
    std::string valueStr = trim(line.substr(delimiterPos + 1));

    if (!isValidDate(date)) {
        result[line] = "Error: bad input => " + line;
        return;
    }

    if (!isValidValue(valueStr)) {
        double val = 0.0;
        try {
            val = std::stod(valueStr);
        } catch (...) {}
        if (val < 0)
            result[line] = "Error: not a positive number.";
        else
            result[line] = "Error: too large a number.";
        return;
    }

    double value = std::stod(valueStr);

    // Buscar tasa de cambio: fecha exacta o anterior
    std::map<std::string, double>::const_iterator it = exchangeRates.lower_bound(date);

    if (it != exchangeRates.end() && it->first == date) {
        // exact match
    } else {
        if (it == exchangeRates.begin()) {
            result[line] = "Error: no exchange rate available.";
            return;
        }
        --it; // fecha anterior más cercana
    }

    double rate = it->second;

    std::ostringstream oss;
    oss.precision(6);
    oss << std::fixed;
    oss << date << " => " << value << " = " << value * rate;

    result[line] = oss.str();
}

void BitcoinExchange::printResult() const {
    for (std::map<std::string, std::string>::const_iterator it = result.begin(); it != result.end(); ++it) {
        std::cout << it->second << std::endl;
    }
}

std::string BitcoinExchange::trim(const std::string &str) {
    size_t start = 0;
    while (start < str.length() && std::isspace(str[start])) ++start;
    size_t end = str.length();
    while (end > start && std::isspace(str[end - 1])) --end;
    return str.substr(start, end - start);
}

bool BitcoinExchange::isValidDate(const std::string &date) const {
    // Check format YYYY-MM-DD
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.size(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) return false;
    }
    // Podrías agregar validación adicional (mes <= 12, día <= 31) si quieres.
    return true;
}

bool BitcoinExchange::isValidValue(const std::string &value) const {
    try {
        double val = std::stod(value);
        return val >= 0 && val <= 1000;
    } catch (...) {
        return false;
    }
}
