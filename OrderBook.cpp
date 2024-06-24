#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <limits>
#include <algorithm>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string, bool> productMap;

    for (OrderBookEntry &order : orders)
    {
        productMap[order.productType] = true;
    }

    for (auto const &pm : productMap)
    {
        products.push_back(pm.first);
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> sub_order;

    for (OrderBookEntry entry : orders)
    {
        if (entry.orderType == type && entry.productType == product && entry.timeStamp == timestamp)
        {
            sub_order.push_back(entry);
        }
    }

    return sub_order;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timeStamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = "";
    for (OrderBookEntry &e : orders)
    {
        if (e.timeStamp > timestamp)
        {
            next_timestamp = e.timeStamp;
            break;
        }
    }
    if (next_timestamp == "")
    {
        next_timestamp = orders[0].timeStamp;
    }

    return next_timestamp;
}

void OrderBook::insertNewOrder(OrderBookEntry &order)
{
    orders.push_back(order);
    sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimeStamp);
}

vector<OrderBookEntry> OrderBook::matchAsksToBids(string product, string timestamp)
{
    vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);

    vector<OrderBookEntry> sales;
    sort(asks.begin(), asks.begin(), OrderBookEntry::compareByPriceAsc);
    sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for (OrderBookEntry &ask : asks)
    {
        for (OrderBookEntry &bid : bids)
        {
            if (bid.price >= ask.price)
            {
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::sale};

                if (bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }
                else if (bid.amount > ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount -= ask.amount;
                    break;
                }
                else if (bid.amount < ask.amount)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount -= bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }

    return sales;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double highPrice = 0.0;

    for (OrderBookEntry order : orders)
    {
        if (order.price > highPrice)
        {
            highPrice = order.price;
        }
    }

    return highPrice;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    double lowPrice = __INT_MAX__;

    for (OrderBookEntry order : orders)
    {
        if (order.price < lowPrice)
        {
            lowPrice = order.price;
        }
    }

    return lowPrice;
}
