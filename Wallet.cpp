#include "Wallet.h"
#include "CSVReader.h"

Wallet::Wallet()
{
}

void Wallet::insertCurrency(std::string type, double amount)
{
    double balance;
    if (amount < 0)
    {
        throw std::exception{};
    }
    if (currencies.count(type) == 0)
        balance = 0.0;
    else
        balance = currencies[type];

    balance += amount;
    currencies[type] = balance;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0)
    {
        return false;
    }
    if (currencies.count(type) == 0)
    {
        return false;
    }
    else
    {
        if (containsCurrency(type, amount))
        {
            currencies[type] -= amount;
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    if (currencies.count(type) == 0)
        return false;
    else
        return currencies[type] >= amount;
}

bool Wallet::canFulfillOrder(OrderBookEntry order)
{
    std::vector<std::string> curr = CSVReader::tokenise(order.productType, '/');
    if (order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        std::string currency = curr[0];
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }

    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount * order.price;
        std::string currency = curr[1];
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }
    return false;
}

void Wallet::processSale(OrderBookEntry &sale)
{
    std::vector<std::string> curr = CSVReader::tokenise(sale.productType, '/');
    if (sale.orderType == OrderBookType::askSale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = curr[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = curr[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }

    if (sale.orderType == OrderBookType::bidSale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = curr[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = curr[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}

std::string Wallet::toString()
{
    std::string s;
    for (std::pair<std::string, double> pair : currencies)
    {
        s += pair.first + ": " + std::to_string(pair.second) + "\n";
    }
    return s;
}
