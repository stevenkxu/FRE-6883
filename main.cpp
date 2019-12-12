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
        //for(auto iter = it->second.begin(); iter != it->second.end() ; ++iter)
        //{
        //    cout << *iter << " ";

        //}
        cout << endl;
    }
    cout << 4 << endl;
    cout << StockList["SPY"].AdjClose[0] << StockList["SPY"].AdjClose [1] << endl;
    
    //cout << StockList["ABT"].StartDateIndex << endl;

    //Why on God's green Earth would you ever ame a data structure 'return'???

    Matrix Result;
    
    for (int i = 0; i < 3 ; i ++){
        Vector AAR;
        Vector AARSD;
        Container temp1;
        Container temp2;
        Vector CAAR;
        Vector CAARSD;
        
        
        for (int j = 0; j < 30 ;j++){
            StockShuffler shuffle = StockShuffler(group1);
            Group group2(3);
            shuffle.ShuffleStocks();
            shuffle.Get30StocksPerGroup(group2);
            
            vector<string> SPY = getSPY();
            cout << SPY.size();
            StockMap StockList;
            Stock tempstock(0);
            StockList["SPY"] = tempstock;
            StockList["SPY"].AdjClose = SPY;
            
            Map Price = SelectData(group2, j, StockList);
            //for (int k = 0; k < 4;k++){
            Return abnormalReturn;
            abnormalReturn=calculationOfReturn(abnormalReturn, StockList, Price, SPY);
            Vector averageAbnormalReturn;
            averageAbnormalReturn = calculationOfAAR(abnormalReturn);
            temp1[j] =averageAbnormalReturn;
            AAR = operator+ (AAR ,averageAbnormalReturn);
            
            Vector culmulativeAbnormalReturn;
            culmulativeAbnormalReturn = calculationOfCAAR(averageAbnormalReturn);
            temp2 [j] =culmulativeAbnormalReturn;
            CAAR = operator+(CAAR, culmulativeAbnormalReturn);
            
           
                
                
            //}
        }
        
        temp1 = operator-( temp1, AAR);
        temp1 = operator ^(temp1,temp1);
        AARSD = operator+(temp1, AARSD);
        AARSD = squareRootOperator(AARSD);
        
        temp2 = operator-( temp2, CAAR);
        temp2 = operator ^(temp2,temp2);
        CAARSD = operator+(temp2,CAARSD);
        CAARSD = squareRootOperator(CAARSD);
        Result[i][0] = AAR;
        Result[i][1] = AARSD;
        Result[i][2] = CAAR;
        Result[i][3] = CAARSD;
                   
        
    }
    
    for (int i = 0; i <60;i++){
        cout<< Result[0][0][i]<<endl;
    }
    /*

    Return abnormalReturn;
    Return abnormalReturn2;
    Return abnormalReturn3;
    abnormalReturn=calculationOfReturn(abnormalReturn, StockList, Price, SPY);
    abnormalReturn2=calculationOfReturn(abnormalReturn2, StockList, Price2, SPY);
    abnormalReturn3=calculationOfReturn(abnormalReturn, StockList, Price3, SPY);
    
    Vector averageAbnormalReturn;
    Vector averageAbnormalReturn2;
    Vector averageAbnormalReturn3;
    
    averageAbnormalReturn = calculationOfAAR(abnormalReturn);
    averageAbnormalReturn2 = calculationOfAAR(abnormalReturn2);
    averageAbnormalReturn3 = calculationOfAAR(abnormalReturn3);
    
    Vector culmulativeAbnormalReturn;
    Vector culmulativeAbnormalReturn2;
    Vector culmulativeAbnormalReturn3;
    
    culmulativeAbnormalReturn = calculationOfCAAR(averageAbnormalReturn);
    culmulativeAbnormalReturn2 = calculationOfCAAR(averageAbnormalReturn2);
    culmulativeAbnormalReturn3 = calculationOfCAAR(averageAbnormalReturn3);
    
    cout << averageAbnormalReturn[4] << endl;
    */
    
}
