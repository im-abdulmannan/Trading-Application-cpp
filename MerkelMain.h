#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain
{
public:
    MerkelMain();
    void init();

private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterOffer();
    void enterBid();
    void printWallet();
    void goToNextTimeFrame();
    int getUserOption();
    void exitProgram();
    void invalidStatement();
    void processUserOption(int choice);

    std::string currentTime;

    OrderBook orderBook{"./20200317.csv"};

    Wallet wallet;
};