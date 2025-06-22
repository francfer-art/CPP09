#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        if (argc < 2) {
            std::cerr << "Error: could not open file." << std::endl;
        } else {
            std::cerr << "Error: too many arguments." << std::endl;
        }
        return 1;
    }

    BitcoinExchange exchange;

    if (!exchange.loadExchangeRates("data.csv")) {
        return 1;
    }

    if (!exchange.loadData(argv[1])) {
        return 1;
    }

    exchange.printResult();
    return 0;
}
