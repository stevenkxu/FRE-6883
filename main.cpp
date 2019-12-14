#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Stock.h"
#include "SelectRandomStocks.h"
#include <algorithm>
#include <iomanip> 
#include "Calculation.h"
#include "PlotChart.h"
#include "ExtractData.h"

using namespace std;

int main()
{
    
    vector<string> TickerList;
    
    cout<<12<<endl;
    // get sp500
    vector<string> SPY;
    vector<string> DATE;
    ExtractSPY(SPY, DATE, "2019-01-10", "2019-08-20");
    //cout <<SPY[1]<<endl;
    vector<double> spy = findSPYReturn(SPY);
    
    StockMap StockList;
    
    
    cout << 100 << endl;
    
    // read EPS file
    string path = "EPS.csv";
    EquityDivide test1(path, StockList,TickerList,DATE);
    Group group1 = test1.divide_group();
    
    cout << 200 << endl;
    
    //randomly chosse 30 stocks of 3 groups, so group[0] means miss.
    //StockShuffler shuffle = StockShuffler(group1);
    //Group group2(3);
    //shuffle.ShuffleStocks();
    //shuffle.Get30StocksPerGroup(group2);
    //Extract(StockList, "2019-01-10", "2019-08-20");
    Extract(StockList);
    cout << 300 << endl;
    //for(int i =0 ; i<=60;i++)
    //    cout << "++///++"<<StockList["A"].AdjClose[i] << endl;
    
    int i = 0;
    //for(auto it = StockList.begin(); i < 3; ++it)
    //{
    //    cout << it->first << "  "  << it->second.StartDate << "  " << it->second.AdjClose.size()<< endl;
    //    ++i;
    //}
    //
    //for(auto it = SPY.begin(); it != SPY.end(); ++it)
    //    cout << *it << endl;
    cout << 400 << endl;
    
    Matrix Result(3,vector<vector<double>>(4)) ;

    Result = finalCalculation( group1,spy, StockList);
    cout << 500 << endl;
  
    int opt;
    bool cont = TRUE;
    while (cont == TRUE) {
        cout << "1: Get historical price data of all stocks" << endl;
        cout << "2: Information for 1 specific stock" << endl;
        cout << "3: AAR, AAR-SD, CAAR, CAAR-SD for one group" << endl;
        cout << "4: Plot CAAR for all three groups" << endl;
        cout << "5: Exit" << endl;
        cin >> opt;
        string userticker;
        string choice;
        switch (opt) {
        case 1:
            cout << "Input ticker:";
            cin >> userticker;
            cout << endl;
            if (StockList.count(userticker)) {
                int sdate = StockList[userticker].StartDateIndex;
                int kount = 0;
                for (auto itr = StockList[userticker].AdjClose.begin(); itr != StockList[userticker].AdjClose.end(); itr++) {
                    cout << *itr << endl;
                    kount++;
                }
                
            }
            break;
        case 2:
            cout << "Input ticker:";
            cin >> userticker;
            cout << endl;
            if (StockList.count(userticker)) {
            cout << "Ticker:             " << StockList[userticker].Ticker << endl;
            cout << "Earnings Call Date: " << StockList[userticker].AnnounceDate << endl;
            cout << "Actual EPS:         " << StockList[userticker].ActEPS << endl;
            cout << "Estimated EPS:      " << StockList[userticker].EstEPS << endl;
            cout << endl;
        }
            else {
                cout << "No Data for Ticker!" << endl;
            }
            break;
        case 3:
            cout << "Choose group: " << endl;
            cout << " 0 for miss, 1 for beat, 2 for meet" << endl;
            int groupselect;
            cin >> groupselect;
            //printstats(groupselect);
            if (groupselect != 1 && groupselect != 2 && groupselect != 0) {
                cout << "Invalid choice!" << endl;
                break;
            }
            cout << "Day == AAR == AAR-SD == CAAR == CAAR-SD " << endl;

            for (int i = 0; i < 60; i++) {
                cout << setprecision(0) << i - 30 << " ";
                cout << setprecision(7) << Result[groupselect][0][i] << " " << Result[groupselect][1][i] << " " << Result[groupselect][2][i] << " " << Result[groupselect][3][i] << endl;
            }

            
            break;
        case 4:
            //call gnuplot and plot.
            plotChart(Result[2][2], Result[1][2], Result[0][2]);
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
            break;
        };
    };
    /*
    //randomly chosse 30 stocks of 3 groups, so group[0] means miss.
    StockShuffler shuffle = StockShuffler(group1);
    Group group2(3);
    shuffle.ShuffleStocks();
    shuffle.Get30StocksPerGroup(group2);
    
    // get sp500
    vector<string> SPY = getSPY();
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
    
    cout << StockList["EW"].StartDateIndex << " " << StockList["SPY"].AdjClose [1] << endl;
    */
    
    
       
    //for (int i = 0; i < 3 ; i ++){
    /*vector<double> original(60,0.0);
    Vector AAR1 (60,0.0);
    Vector AARSD1(60,0.0);
    Vector AAR2 (60,0.0);
    Vector AARSD2(60,0.0);
    Vector AAR3 (60,0.0);
    Vector AARSD3(60,0.0);
    Container temp11(30,original);
    Container temp21 (30,original);
    Container temp12(30,original);
    Container temp22 (30,original);
    Container temp31(30,original);
    Container temp32 (30,original);
    Vector CAAR1(60,0.0);
    Vector CAARSD1(60,0.0);
    Vector CAAR2(60,0.0);
    Vector CAARSD2(60,0.0);
    Vector CAAR3(60,0.0);
    Vector CAARSD3(60,0.0);
    Matrix Result(3,vector<vector<double>>(4));
    
        for (int j = 0; j < 30 ;j++){
            StockShuffler shuffle = StockShuffler(group1);
            Group group2(3);
            shuffle.ShuffleStocks();
            shuffle.Get30StocksPerGroup(group2);
            StockMap map1;
            StockMap map2;
            StockMap map3;
            
            for (int i = 0; i<3; i++){
                for (auto it = group2[i].begin(); it != group2[i].end(); it++){
                    //string original = "map";
                    //string add = to_string(i);
                    //original = original + add;
                    if (StockList.find(it->first) != StockList.end()){
                        if (i ==0){
                            map1.insert({it->first,StockList[it->first]});
                        } else if (i ==1){
                            map2.insert({it->first,StockList[it->first]});
                        } else{
                            map3.insert({it->first,StockList[it->first]});
                        }
                    }
                }
            }
               
            //vector<string> SPY = getSPY();
            //cout << SPY.size();
            //StockMap StockList;
            //Stock tempstock(0);
            //StockList["SPY"] = tempstock;
            //StockList["SPY"].AdjClose = SPY;
               
            //Map Price = SelectData(group2, i, StockList);
            //for (int k = 0; k < 4;k++){
            Return abnormalReturn1;
            Return abnormalReturn2;
            Return abnormalReturn3;
            abnormalReturn1=calculationOfReturn(abnormalReturn1, StockList,map1, spy);
            abnormalReturn2=calculationOfReturn(abnormalReturn2, StockList,map2, spy);
            abnormalReturn3=calculationOfReturn(abnormalReturn3, StockList,map3, spy);
            Vector averageAbnormalReturn1;
            averageAbnormalReturn1 = calculationOfAAR(abnormalReturn1);
            Vector averageAbnormalReturn2;
            averageAbnormalReturn2 = calculationOfAAR(abnormalReturn2);
            Vector averageAbnormalReturn3;
            averageAbnormalReturn3 = calculationOfAAR(abnormalReturn3);
            temp11[j] =averageAbnormalReturn1;
            AAR1 = operator+ (AAR1 ,averageAbnormalReturn1);
            temp21[j] =averageAbnormalReturn2;
            AAR2 = operator+ (AAR2 ,averageAbnormalReturn2);
            temp31[j] =averageAbnormalReturn3;
            AAR3 = operator+ (AAR3 ,averageAbnormalReturn3);
               
            Vector culmulativeAbnormalReturn1;
            Vector culmulativeAbnormalReturn2;
            Vector culmulativeAbnormalReturn3;
            culmulativeAbnormalReturn1 = calculationOfCAAR(averageAbnormalReturn1);
            culmulativeAbnormalReturn2 = calculationOfCAAR(averageAbnormalReturn2);
            culmulativeAbnormalReturn3 = calculationOfCAAR(averageAbnormalReturn3);
            temp12 [j] =culmulativeAbnormalReturn1;
            CAAR1 = operator+(CAAR1, culmulativeAbnormalReturn1);
            temp22 [j] =culmulativeAbnormalReturn2;
            CAAR2 = operator+(CAAR2, culmulativeAbnormalReturn2);
            temp32 [j] =culmulativeAbnormalReturn3;
            CAAR3 = operator+(CAAR3, culmulativeAbnormalReturn3);
           
               //}
           }
           
    temp11 = operator-( temp11, AAR1);
    temp11 = operator ^(temp11,temp11);
    temp21 = operator-( temp21, AAR2);
    temp21 = operator ^(temp21,temp21);
    temp31 = operator-( temp31, AAR3);
    temp31 = operator ^(temp31,temp31);
    AARSD1 = operator+(temp11, AARSD1);
    AARSD1 = squareRootOperator(AARSD1);
    AARSD2 = operator+(temp21, AARSD2);
    AARSD2 = squareRootOperator(AARSD2);
    AARSD3 = operator+(temp31, AARSD3);
    AARSD3 = squareRootOperator(AARSD3);
           
    temp12 = operator-( temp12, CAAR1);
    temp12 = operator ^(temp12,temp21);
    temp22 = operator-( temp22, CAAR2);
    temp22 = operator ^(temp22,temp22);
    temp32 = operator-( temp32, CAAR3);
    temp32 = operator ^(temp32,temp32);
    CAARSD1 = operator+(temp12,CAARSD1);
    CAARSD1 = squareRootOperator(CAARSD1);
    CAARSD2 = operator+(temp22,CAARSD2);
    CAARSD2 = squareRootOperator(CAARSD2);
    CAARSD3 = operator+(temp32,CAARSD3);
    CAARSD3 = squareRootOperator(CAARSD3);
    Result[0][0]= AAR1;
    Result[0][1] = AARSD1;
    Result[0][2] = CAAR1;
    Result[0][3] = CAARSD1;
    
    Result[1][0] = AAR2;
    Result[1][1] = AARSD2;
    Result[1][2] = CAAR2;
    Result[1][3] = CAARSD2;
    
    Result[2][0] = AAR3;
    Result[2][1] = AARSD3;
    Result[2][2] = CAAR3;
    Result[2][3] = CAARSD3;
                      
           
       //}
       
    //for (int i = 0; i <60;i++){
        //cout<< Result[0][0][1]<<endl;
      // }*/
     
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
    /*
    //randomly chosse 30 stocks of 3 groups, so group[0] means miss.
    StockShuffler shuffle = StockShuffler(group1);
    Group group2(3);
    shuffle.ShuffleStocks();
    shuffle.Get30StocksPerGroup(group2);
    
    // get sp500
    vector<string> SPY = getSPY();
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
    
    cout << StockList["EW"].StartDateIndex << " " << StockList["SPY"].AdjClose [1] << endl;
    */
    
  /*
    vector<string> TickerList;
    
    // get sp500
    vector<string> SPY;
    vector<string> DATE;
    //get SPY data
    ExtractSPY(SPY, DATE, "2019-01-10", "2019-08-20");
    StockMap StockList;
    
    
    // read EPS file
    string path = "EPS.csv";
    EquityDivide test1(path, StockList,TickerList,DATE);
    Group group1 = test1.divide_group();
    
    // add group feature into Stocklist
    string temgroup[3];
    temgroup[0] = "Miss", temgroup[1] = "Meet", temgroup[2] = "Beat";
    cout << "size: "<<temgroup[0].size() <<endl;
    for(int i = 0; i < 3; i++)
    {
        for(auto it = group1[i].begin(); it != group1[i].end(); ++it)
            StockList[it->first].group = temgroup[i];
    }
    
    for(int i = 0; i < 3; i++)
    {
        for(auto it = group1[i].begin(); it != group1[i].end(); ++it)
            cout<< StockList[it->first].group << endl;
    }
    

    Extract(StockList);
   */
}
