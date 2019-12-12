#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Stock.h"
#include "Selectdata.h"
#include "SelectRandomStocks.h"
#include "Calculation.h"

using namespace std;

int main()
{
    

    

    // read EPS file
    string path = "EPS.csv";
    EquityDivide test1(path);
    Group group1 = test1.divide_group();
    //randomly chosse 30 stocks of 3 groups, so group[0] means miss.
    StockShuffler shuffle = StockShuffler(group1);

    Group group2(3);
    shuffle.ShuffleStocks();

    shuffle.Get30StocksPerGroup(group2);
    cout << 1 << endl;
    // get sp500
    vector<string> SPY = getSPY();
    cout << SPY.size();
    cout << 2 << endl;
    StockMap StockList;
    Stock tempstock(0);
    StockList["SPY"] = tempstock;
    StockList["SPY"].AdjClose = SPY;
    cout << 3 << endl; //so we get here.


    // StockList is a map <string Tickers, Stock>, Stock is a class, has Adj class and dateindex.
    // dateindex means its 61days mean using SP500's price from dateindex to dateindex+61 to get AR
    // Map is <string Tickers, vector<string> 61days prices>
    Map Price = SelectData(group2, 0, StockList);
    Map Price2 = SelectData(group2, 1, StockList);
    Map Price3 = SelectData(group2, 2, StockList);
    cout << 3.1 << endl;
    // show Map
    for(Map::const_iterator it = Price.begin(); it != Price.end(); ++it)
    {
        cout << it->first << endl;
        for(auto iter = it->second.begin(); iter != it->second.end() ; ++iter)
        {
            cout << *iter << " ";

        }
        cout << endl;
    }
    cout << 4 << endl;
    cout << StockList["SPY"].AdjClose[0] << StockList["SPY"].AdjClose [1] << endl;
    
    //cout << StockList["ABT"].StartDateIndex << endl;

    //Why on God's green Earth would you ever ame a data structure 'return'???
   /* Return abnormalReturn;
    Return abnormalReturn2;
    Return abnormalReturn3;
    abnormalReturn=calculationOfReturn(abnormalReturn, StockList, Price, SPY);
    abnormalReturn2=calculationOfReturn(abnormalReturn2, StockList, Price2, SPY);
    abnormalReturn3=calculationOfReturn(abnormalReturn, StockList, Price3, SPY);
    
    AAR averageAbnormalReturn;
    AAR averageAbnormalReturn2;
    AAR averageAbnormalReturn3;
    
    averageAbnormalReturn = calculationOfAAR(abnormalReturn);
    averageAbnormalReturn2 = calculationOfAAR(abnormalReturn2);
    averageAbnormalReturn3 = calculationOfAAR(abnormalReturn3);
    
    CAAR culmulativeAbnormalReturn;
    CAAR culmulativeAbnormalReturn2;
    CAAR culmulativeAbnormalReturn3;
    
    culmulativeAbnormalReturn = calculationOfCAAR(averageAbnormalReturn);
    culmulativeAbnormalReturn2 = calculationOfCAAR(averageAbnormalReturn2);
    culmulativeAbnormalReturn3 = calculationOfCAAR(averageAbnormalReturn3);
    
    cout << averageAbnormalReturn[4] << endl;*/
    
    int opt;
    bool cont = TRUE;
    while (cont == TRUE) {
        cout << "1: Get historical price data of all stocks" << endl;
        cout << "2: Price data for 1 specific stock" << endl;
        cout << "3: AAR, AAR-SD, CAAR, CAAR-SD for one group" << endl;
        cout << "4: Plot CAAR for all three groups" << endl;
        cout << "5: Exit" << endl;
        cin >> opt;
        string userticker;
        string choice;
        switch (opt) {
        case 1:
            cout << 1 << endl;
            cout << cont << endl;
            break;
        case 2:
            cout << "Input ticker:";
            cin >> userticker;
            cout << 2 << endl;
            cout << cont << endl;
            break;
        case 3:
            cout << 3 << endl;
            cout << cont << endl;
            break;
        case 4:
            //call gnuplot and plot.
            cout << 4 << endl;
            break;
        case 5:
            cout << "Are you sure you want to exit (Y to confirm (case sensitive))" << endl;
            cin >> choice;
            if (choice == "Y") {
                return 0;
            }
            else {
                cout << "Exit Unconfirmed. Not exiting." << endl;
                break;
            }
            break;
        default:
            cont = FALSE;
            cout << cont;
            break;
        };
    };
}
