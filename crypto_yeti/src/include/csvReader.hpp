#pragma once

#include <vector>
#include <string>

#include "orderBookEntry.hpp"

class CSVReader{
public:
    CSVReader();

    static std::vector<OrderBookEntry> readCSV(std::string csvFileName);
    static std::vector<std::string> tokenise(std::string csvLine, char separator);
    static OrderBookEntry stringsToOBE(std::string priceString,std::string amountString,
                                      std::string timestampe,
                                      std::string product,
                                      orderBookType orderType,std::string username);

private:
    static OrderBookEntry stringToOBE(std::vector<std::string> tokens);
};
