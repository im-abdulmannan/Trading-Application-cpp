#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet
{
public:
    Wallet();

    /** Insert Currency to the wallet
     * @param type type of the currency
     * @param amount amount of the currency
     */
    void insertCurrency(std::string type, double amount);
    bool removeCurrency(std::string type, double amount);

    /** Checking if the wallet this currency
     * @param type type of the currency
     * @param amount amount of the currency
     */
    bool containsCurrency(std::string type, double amount);

    /** Check if the wallet can cope the required bid or ask
     * @param order Order from OrderBookEntry to check
     */
    bool canFulfillOrder(OrderBookEntry order);

    /* Generate a string representation of the wallet */
    std::string toString();

private:
    std::map<std::string, double> currencies;
};