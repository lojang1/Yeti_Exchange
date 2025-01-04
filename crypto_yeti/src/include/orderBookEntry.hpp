#pragma once

#include <string>

enum class orderBookType{bid, ask, unknown, asksale, bidsale};

class OrderBookEntry{
public:
    // Constructor
    OrderBookEntry(double _price,
                   double _amount,
                   std::string _timestamp,
                   std::string _product,
                   orderBookType _orderType,
                   std::string username = "dataset");

    static orderBookType stringToOBT(std::string s);
    // Data members of the class
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    orderBookType orderType;
    std::string username;

    static bool compareByTime(OrderBookEntry& e1, OrderBookEntry& e2){
        return e1.timestamp < e2.timestamp;
    }
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2){
        return e1.price < e2.price;
    }
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2){
        return e1.price > e2.price;
    }
};
