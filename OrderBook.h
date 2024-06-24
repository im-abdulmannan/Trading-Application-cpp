#pragma once

#include <iostream>
#include <string>
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <vector>

class OrderBook
{
public:
    /* Constructor to read csv data file */
    OrderBook(std::string filename);

    /* return all products in dataset */
    std::vector<std::string> getKnownProducts();

    /** return order according to the sent filter */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

    /** @return the earliest time in the orderbook */
    std::string getEarliestTime();

    /** @return the next time after the sent time in the orderbook
     */
    std::string getNextTime(std::string timestamp);

    void insertNewOrder(OrderBookEntry &order);

    vector<OrderBookEntry> matchAsksToBids(string product, string timestamp);

    static double getHighPrice(std::vector<OrderBookEntry> &orders);
    static double getLowPrice(std::vector<OrderBookEntry> &orders);

private:
    std::vector<OrderBookEntry> orders;
};