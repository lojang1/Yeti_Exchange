#pragma once

#include <string>
#include <vector>

// #include "csvReader.hpp"
#include "orderBookEntry.hpp"

class OrderBook{
private:
    std::vector<OrderBookEntry> orders;
public:
    OrderBook(std::string filename);
    std::vector<std::string> getProducts();
    std::vector<OrderBookEntry> getOrders(orderBookType type,
                                          std::string product,
                                          std::string timestamp);

    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getLowPrice(std::vector<OrderBookEntry>& orders);

    void insertOrder(OrderBookEntry& order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product,
                                                std::string timestamp);

    std::string getEarliestTime();
    std::string getNextTime(std::string timestamp);
};
