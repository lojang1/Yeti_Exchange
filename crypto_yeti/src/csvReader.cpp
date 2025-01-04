#include <iostream>
#include <fstream>

#include "include/csvReader.hpp"
#include "include/orderBookEntry.hpp"

CSVReader::CSVReader(){

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName){
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFileName};
    std::string line;

    if(csvFile.is_open()){
        while(std::getline(csvFile, line)){
            try{
                OrderBookEntry obe = stringToOBE(tokenise(line, ','));
                entries.push_back(obe);
            } catch(const std::exception& e){
                std::cout << "[*]Error: Bad data..." << std::endl;
                // throw;
            }
        } // End of while
    }
    std::cout << "[*]CSVReader::readCSV has read: " << entries.size() << " entries..." << std::endl;
    std::cout << "\n\n";

    csvFile.close();

    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator){
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;

    start = csvLine.find_first_not_of(separator, 0);
    do{
        end = csvLine.find_first_of(separator,start);
        if(start==csvLine.length() || start==end)
            break;
        // Separator found
        if(end >= 0){
            token = csvLine.substr(start, end - start);
        } else{
            token = csvLine.substr(start, csvLine.length() - start);
        }
        tokens.push_back(token);
        start = end + 1;
    }while(end != std::string::npos);

    return tokens;
}

OrderBookEntry CSVReader::stringToOBE(std::vector<std::string> tokens){
    // OrderBookEntry obe{};
    double price, amount;

    if(tokens.size() != 5){
        std::cout << "[*]Error: Bad Line..." << std::endl;
        throw std::exception{};
    }
    try{
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }catch(const std::exception& e){
        std::cout << "[*]Error: Bad float..." << std::endl;
        throw;
    }

    OrderBookEntry obe{price,amount,tokens[0],tokens[1],
        OrderBookEntry::stringToOBT(tokens[2]),"dataset"};

    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
                                       std::string amountString,
                                       std::string timestampe,
                                       std::string product,
                                       orderBookType orderType,
                                       std::string username){
    double price, amount;
    try{
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }catch(const std::exception& e){
        std::cout << "[*]Error: Bad float..." << std::endl;
        throw;
    }
    OrderBookEntry obe{price,amount,timestampe,product,orderType,username};
    return obe;
}
