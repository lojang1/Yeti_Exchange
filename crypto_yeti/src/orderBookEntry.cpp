#include "include/orderBookEntry.hpp"

OrderBookEntry::OrderBookEntry(double _price,
                               double _amount,
                               std::string _timestamp,
                               std::string _product,
                               orderBookType _orderType,
                               std::string _username)
    :price(_price),amount(_amount),timestamp(_timestamp),
    product(_product),orderType(_orderType),username(_username)
{
}

orderBookType OrderBookEntry::stringToOBT(std::string s){
    if(s == "ask"){
        return orderBookType::ask;
    } else if(s == "bid"){
        return orderBookType::bid;
    } else{
        return orderBookType::unknown;
    }
}
