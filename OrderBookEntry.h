#pragma once

#include <iostream>
using namespace std;

enum class OrderBookType
{
    bid,
    ask,
    unknown,
    sale
};

class OrderBookEntry
{
public:
    OrderBookEntry(double _price,
                   double _amount,
                   string _timeStamp,
                   string _productType,
                   OrderBookType _orderType);

    static OrderBookType stringToOrderBookType(string s);

    static bool compareByTimeStamp(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.timeStamp < e2.timeStamp;
    }

    static bool compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.price < e2.price;
    }

    static bool compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.price > e2.price;
    }

    double price;
    double amount;
    string timeStamp;
    string productType;
    OrderBookType orderType;
};