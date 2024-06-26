#include "OrderBookEntry.h"
OrderBookEntry::OrderBookEntry(double _price,
                               double _amount,
                               string _timeStamp,
                               string _productType,
                               OrderBookType _orderType,
                               string _username) : price(_price), amount(_amount), timeStamp(_timeStamp), productType(_productType), orderType(_orderType), username(_username) {}

OrderBookType OrderBookEntry::stringToOrderBookType(string s)
{
    if (s == "ask")
        return OrderBookType::ask;
    if (s == "bid")
        return OrderBookType::bid;
    return OrderBookType::unknown;
}