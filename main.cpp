#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Stock.h"
#include "Selectdata.h"
#include "SelectRandomStocks.h"

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
    
    // get sp500
    vector<string> SPY = getSPY();
    cout << SPY.size();
    StockMap StockList;
    Stock tempstock(0);
    StockList["SPY"] = tempstock;
    StockList["SPY"].AdjClose = SPY;
    
    // StockList is a map <string Tickers, Stock>, Stock is a class, has Adj class and dateindex.
    // dateindex means its 61days mean using SP500's price from dateindex to dateindex+61 to get AR
    // Map is <string Tickers, vector<string> 61days prices>
    Map Price = SelectData(group2, 1, StockList);
    
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
    
    cout << StockList["SPY"].AdjClose[0] << StockList["SPY"].AdjClose [1] << endl;
    
}
