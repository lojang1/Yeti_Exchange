#pragma once

// #include <vector>

// #include "orderBookEntry.hpp"
#include "orderBook.hpp"
#include "wallet.hpp"

class mainMenu{
public:
    mainMenu();
    void init();
private:
    void printMenu();
    void printHelp();
    void showMarketData();
    void enterAsk();
    void enterBid();
    void showWallet();
    void goToNextFrame();
    int getUserOption();
    void processUserOption(int userOption);

    std::string currentTime;

    OrderBook orderBook{"data/orderbook_data.csv"};

    Wallet wallet{};
};
