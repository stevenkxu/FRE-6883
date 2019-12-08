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
    string path = "EPS.csv";
    EquityDivide test1(path);
    Group group1 = test1.divide_group();
    
    StockShuffler shuffle = StockShuffler(group1);
    Group group2(3);
    shuffle.ShuffleStocks();
    shuffle.Get30StocksPerGroup(group2);
    
    vector<string> SPY = getSPY();
    cout << SPY.size();
    
    /*
    Map Price = SelectData(group2,1);
    
    
    for(Map::const_iterator it = Price.begin(); it != Price.end(); ++it)
    {
        cout << it->first << endl;
        for(auto iter = it->second.begin(); iter != it->second.end() ; ++iter)
        {
            cout << *iter << " ";
        }
        cout << endl;
    }
    */
}
