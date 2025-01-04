#include <iostream>
#include <limits>

#include "include/menu.hpp"
#include "include/csvReader.hpp"
#include "include/orderBookEntry.hpp"
#include "include/wallet.hpp"

mainMenu::mainMenu(){

}

void mainMenu::init(){
    int input;
    currentTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10);
    while(true){
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void mainMenu::printMenu(){
    // 1. Print Help
    std::cout << "1. Help" << std::endl;
    // 2. Show exchange data
    std::cout << "2. Show Exchange Data" << std::endl;
    // 3. Make ask
    std::cout << "3. Make an ask" << std::endl;
    // 4. Make bid
    std::cout << "4. Make a bid" << std::endl;
    // 5. Show wallet
    std::cout << "5. Show wallet" << std::endl;
    // 6. Continue
    std::cout << "6. Continue" << std::endl;
    // 7. Exit
    std::cout << "7. Exit" << std::endl;

    std::cout << "***********************" << std::endl;
    std::cout << "Current Time: " << currentTime << std::endl;
    std::cout << "***********************" << std::endl;

}

int mainMenu::getUserOption(){
    int userOption;
    std::cout << "Select an option (1-7)..." << std::endl;
    // Input validation
    while(!(std::cin >> userOption) || userOption < 1 || userOption > 7){
        std::cout << "Invalid option... Select an option (1-7)..." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return userOption;
}

void mainMenu::processUserOption(int userOption){
    // Checking user input
    if(userOption == 1){
        printHelp();
    } else if(userOption == 2){
        showMarketData();
    } else if(userOption == 3){
        enterAsk();
    } else if(userOption == 4){
        enterBid();
    } else if(userOption == 5){
        showWallet();
    } else if(userOption == 6){
        goToNextFrame();
    } else if(userOption == 7){
        std::cout << "Exiting..." << std::endl;
        exit(EXIT_SUCCESS);
    }
    std::cout << "***********************" << std::endl;
}

void mainMenu::printHelp(){
    std::cout << "The objective is to make money trading cyrptocurrency." << std::endl;
}

void mainMenu::showMarketData(){
    /*
    std::cout << orders.size() << std::endl;
    unsigned int bids = 0;
    unsigned int asks = 0;

    for(OrderBookEntry& e: orders){
        if(e.orderType == orderBookType::ask){
            asks ++;
        } else if(e.orderType == orderBookType::bid){
            bids ++;
        }
    }
    std::cout << "Order Book asks:" << asks << std::endl;
    std::cout << "Order Book bids:" << bids << std::endl;
    */
    for(std::string const p: orderBook.getProducts()){
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType::ask,
                                                                  p,
                                                                  currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;

    }
}

void mainMenu::enterAsk(){
    std::cout << "Make an ask: [Product, Price, Amount]" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if(tokens.size()!=3){
        std::cout << "[*]Error: Bad Input..." << std::endl;
    } else{
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                         tokens[2],
                                                         currentTime,
                                                         tokens[0],
                                                         orderBookType::ask,
                                                         "admin");
            // obe.username = "admin";
            if(wallet.fulfillOrder(obe)){
                std::cout << "Order Fulfilled..." << std::endl;
                orderBook.insertOrder(obe);
            } else{
                std::cout << "Insufficient Funds..." << std::endl;
            }
        } catch(const std::exception& e){
            std::cout << "[*]Error: Bad Input..." << std::endl;
            throw;
        }
    }
}

void mainMenu::enterBid(){
    std::cout << "Make a bid: [Product, Price, Amount]" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if(tokens.size()!=3){
        std::cout << "[*]Error: Bad Input..." << std::endl;
    } else{
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                         tokens[2],
                                                         currentTime,
                                                         tokens[0],
                                                         orderBookType::bid,
                                                         "admin");
            // obe.username = "admin";
            if(wallet.fulfillOrder(obe)){
                std::cout << "Order Fulfilled..." << std::endl;
                orderBook.insertOrder(obe);
            } else{
                std::cout << "Insufficient Funds..." << std::endl;
            }
        } catch(const std::exception& e){
            std::cout << "[*]Error: Bad Input..." << std::endl;
            throw;
        }
    }
}

void mainMenu::showWallet(){
    std::cout << wallet.toString() << std::endl;
}

void mainMenu::goToNextFrame(){
    std::cout << "Move to the next timeframe..." << std::endl;
    for(std::string p: orderBook.getProducts()){
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for(OrderBookEntry& sale: sales){
            std::cout << "Sales Price: " << sale.price << std::endl;
            std::cout << "Sales Amount: " << sale.amount << std::endl;
            if(sale.username == "admin"){
                // Update the Wallet
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}
