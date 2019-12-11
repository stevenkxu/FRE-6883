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
    Map Price = SelectData(group2, 0, StockList);
    Map Price2 = SelectData(group2, 1, StockList);
    Map Price3 = SelectData(group2, 2, StockList);
    
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
    
    //cout << StockList["SPY"].AdjClose[0] << StockList["SPY"].AdjClose [1] << endl;
    
    //cout << StockList["ABT"].StartDateIndex << endl;
    Return abnormalReturn;
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
    
    cout << averageAbnormalReturn[4] << endl;
    
    
}
