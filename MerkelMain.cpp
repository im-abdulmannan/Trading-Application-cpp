#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "MerkelMain.h"
#include <limits>

using namespace std;

MerkelMain::MerkelMain()
{
}

void MerkelMain::goToNextTimeFrame()
{
    cout << "Going to the next frame" << endl;
    vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    cout << "Sales: " << sales.size() << endl;
    for (OrderBookEntry &sale : sales)
    {
        cout << "Sale Price: " << sale.price << " amount " << sale.amount << endl;
        if (sale.username == "simuser")
        {
            // update the user wallet
            wallet.processSale(sale);
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

/* Initialization of the main function where we take input from the user */
void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10.0);
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    cout << "0. Exit the program" << endl;
    cout << "1: Print help" << endl;
    cout << "2: Print market stats" << endl;
    cout << "3: Make an offer" << endl;
    cout << "4: Make a bid" << endl;
    cout << "5: Print wallet" << endl;
    cout << "6: Continue to the next time frame" << endl;
    cout << "=====================" << endl;

    cout << "Current time: " << currentTime << endl;
}

void MerkelMain::printHelp()
{
    cout << "Currency help" << endl;
}

void MerkelMain::printMarketStats()
{

    for (string const&p : orderBook.getKnownProducts())
    {
        cout << "Product: " << p << endl;
        vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        cout << "Asks seen: " << entries.size() << endl;
        cout << "Max ask: " << OrderBook::getHighPrice(entries) << endl;
        cout << "Min ask: " << OrderBook::getLowPrice(entries) << endl;
    }
}

void MerkelMain::enterOffer()
{
    cout << "Let's make an offer --  Enter product, price, and amount\nExample:- ETH/BTC,200,0.5" << endl;
    string input;
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    cout << "You typed: " << input << endl;

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        cout << "MerkelMain::enterOffer Bad input!!! " << input << endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToObj(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                cout << "Wallet looks good!" << endl;
                orderBook.insertNewOrder(obe);
            }
            else
            {
                cout << "Wallet doesn't have enough money!" << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "MerkelMain::enterOffer Bad Input!" << endl;
        }
    }
}

void MerkelMain::enterBid()
{
    cout << "Let's make a bid -- Enter product, price, and amount\nExample:- ETH/BTC,200,0.5" << endl;
    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        cout << "MerkelMain::enterBid Bad input!!! " << input << endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToObj(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                cout << "Wallet looks good!" << endl;
                orderBook.insertNewOrder(obe);
            }
            else
            {
                cout << "Wallet doesn't have enough money!" << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "MerkelMain::enterBid Bad Input!" << endl;
        }
    }
}

void MerkelMain::printWallet()
{
    cout << wallet.toString() << endl;
}

int MerkelMain::getUserOption()
{
    int choice = -1;
    string line;
    cout << "Select between 0-6" << endl;
    getline(cin, line);
    try
    {
        choice = stoi(line);
    }
    catch (const exception &e)
    {
        cout << "Enter a number to pursue" << endl;
    }

    cout << "You choose: " << choice << endl;
    return choice;
}

void MerkelMain::exitProgram()
{
    cout << "Exiting the program" << endl;
    exit(0);
}

void MerkelMain::invalidStatement()
{
    cout << "Please enter valid number!!!" << endl;
}

void MerkelMain::processUserOption(int choice)
{
    if (choice == 0)
    {
        exitProgram();
    }
    else if (choice == 1)
    {
        printHelp();
    }
    else if (choice == 2)
    {
        printMarketStats();
    }
    else if (choice == 3)
    {
        enterOffer();
    }
    else if (choice == 4)
    {
        enterBid();
    }
    else if (choice == 5)
    {
        printWallet();
    }
    else if (choice == 6)
    {
        goToNextTimeFrame();
    }
    else
    {
        invalidStatement();
    }
}