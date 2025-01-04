#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

#include "include/wallet.hpp"
#include "include/csvReader.hpp"

Wallet::Wallet(){
}

void Wallet::insertCurrency(std::string type, double balance){
    double localBal;
    if(balance < 0){
        std::cout << "[*]Error: No coins available" << std::endl;
    }
    if(coins.count(type) == 0){
        localBal = 0;
    } else{
        balance = coins[type];
    }
    localBal += balance;
    coins[type] = localBal;

}

bool Wallet::removeCurrency(std::string type, double balance){
    double localBal;
    if(balance < 0){
        std::cout << "[*]Error: No coins available" << std::endl;
        return false;
    }
    if(coins.count(type) == 0){
        return false;
    } else{
        if(checkCurrency(type, balance)){
            coins[type] += balance;
            return true;
        } else{
            return false;
        }
    }
}

bool Wallet::checkCurrency(std::string type, double balance){
    if(coins.count(type) == 0)
        return false;
    else
        return coins[type] >= balance;
}

std::string Wallet::toString(){

    std::string c;

    for(std::pair<std::string, double> pair: coins){
        std::string coin = pair.first;
        double balance = pair.second;
        c += coin + ": " + std::to_string(balance) + "\n";
    }
    return c;
}

bool Wallet::fulfillOrder(OrderBookEntry order){
    std::vector<std::string> coins = CSVReader::tokenise(order.product, '/');

    if(order.orderType == orderBookType::ask){
        double amount = order.amount;
        std::string currency = coins[0];
        return checkCurrency(currency, amount);
    }
    if(order.orderType == orderBookType::bid){
        double amount = order.amount * order.price;
        std::string currency = coins[1];
        return checkCurrency(currency, amount);
    }
    return false;
}

void Wallet::processSale(OrderBookEntry& sale){
    std::vector<std::string> c = CSVReader::tokenise(sale.product, '/');

    if(sale.orderType == orderBookType::asksale){
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = c[0];

        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = c[1];

        coins[incomingCurrency] += incomingAmount;
        coins[outgoingCurrency] -= outgoingAmount;

    }
    if(sale.orderType == orderBookType::bidsale){
        double incomingAmount = sale.amount;
        std::string incomingCurrency = c[0];

        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = c[1];

        coins[incomingCurrency] += incomingAmount;
        coins[outgoingCurrency] -= outgoingAmount;
    }
}
