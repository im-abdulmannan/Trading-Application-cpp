#pragma once

#include "OrderBookEntry.h"
#include <string>
#include <vector>

using namespace std;

class CSVReader
{
public:
    CSVReader();

    static vector<OrderBookEntry> readCSV(string csvFile);
    static vector<string> tokenise(string csvLine, char separator);
    static OrderBookEntry stringsToObj(string price,
                                       string amount,
                                       string timestamp,
                                       string product,
                                       OrderBookType OrderBookType);

private:
    static OrderBookEntry stringsToObj(vector<string> strings);
};