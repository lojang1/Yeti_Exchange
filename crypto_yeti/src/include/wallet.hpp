#pragma once

#include <string>
#include <map>

#include "orderBookEntry.hpp"


class Wallet{
private:
    std::map<std::string, double> coins;

public:
    Wallet();

    void insertCurrency(std::string type, double balance);
    bool removeCurrency(std::string type, double balance);
    bool checkCurrency(std::string type, double balance);
    bool fulfillOrder(OrderBookEntry order);
    void processSale(OrderBookEntry& sale);
    std::string toString();
};
