#include <iostream>
#include <string>
#include <vector>
#include "MerkelMain.h"
#include "Wallet.h"

int main()
{
    MerkelMain app{};
    app.init();
    // Wallet wallet;
    // wallet.insertCurrency("BTC", 20);
    // wallet.insertCurrency("USDT", 10000);
    // cout << wallet.toString() << endl;
    // wallet.removeCurrency("USDT", 1000);
    // cout << wallet.toString() << endl;

    // cout << "Your wallet contain BTC: " << wallet.containsCurrency("USDT", 10) << endl;


    // CSVReader::readCSV("./20200317.csv");

    return 0;
}
