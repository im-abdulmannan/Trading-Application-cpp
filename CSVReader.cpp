#include "CSVReader.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

CSVReader::CSVReader()
{
}

vector<OrderBookEntry> CSVReader::readCSV(string csvFilename)
{
    vector<OrderBookEntry> entries;

    ifstream csvFile{csvFilename};
    string line;

    if (csvFile.is_open())
    {
        while (getline(csvFile, line))
        {
            try
            {
                OrderBookEntry obj = stringsToObj(tokenise(line, ','));
                entries.push_back(obj);
            }
            catch (const exception &e)
            {
                cout << "CSVReader::readCSV read bad data!!!" << endl;
            }
        }
    }

    cout << "CSVReader::readCSV read " << entries.size() << " entries" << endl;

    return entries;
}

vector<string> CSVReader::tokenise(string csvLine, char separator)
{
    vector<string> tokens;
    signed int start, end;
    string token = "";

    start = csvLine.find_first_not_of(separator, 0);

    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
        {
            break;
        }
        else if (end >= 0)
        {
            token = csvLine.substr(start, end - start);
        }
        else
        {
            token = csvLine.substr(start, csvLine.length() - start);
        }
        tokens.push_back(token);
        start = end + 1;
    } while (end > 0);

    return tokens;
}

OrderBookEntry CSVReader::stringsToObj(string priceString,
                                       string amountString,
                                       string timestamp,
                                       string product,
                                       OrderBookType orderType)
{
    double price, amount;
    try
    {
        price = stod(priceString);
        amount = stod(amountString);
    }
    catch (const std::exception &e)
    {
        cout << "Bad Float! " << priceString << endl;
        cout << "Bad Float! " << amountString << endl;
    }

    OrderBookEntry obe{price,
                       amount,
                       timestamp,
                       product,
                       orderType};

    return obe;
}

OrderBookEntry CSVReader::stringsToObj(vector<string> tokens)
{
    double price, amount;
    if (tokens.size() != 5)
    {
        cout << "Bad Line" << endl;
        throw exception{};
    }

    try
    {
        price = stod(tokens[3]);
        amount = stod(tokens[4]);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
        cout << "Bad Line" << endl;
        throw;
    }

    OrderBookEntry obj{
        price, amount, tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obj;
}