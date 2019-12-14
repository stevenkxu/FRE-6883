#ifndef Calculation_h
#define Calculation_h

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "tools.h"
#include "Stock.h"
#include "EquityDivide.h"
#include <map>

typedef map<string,vector<double>> Return;

//typedef vector <double> AAR;
//typedef vector <double> CAAR;
//typedef vector <double> averageAAR;
//typedef vector <double> averageCAAR;
typedef vector <double> Vector;
typedef vector<vector<vector<double>>> Matrix;
typedef vector<vector<double>> Container;




//Return divideGroup ( StockMap stockList, Group g){
    //for (int i = 0; i <3; i ++){
       // for ( auto it = g[i].begin(); it != g[i].end(); it ++){
            
        //}
   // }
    
//}
vector<double> findSPYReturn(vector<string> spy){
    vector<double> SPYRETURN;

    for ( int i = 0; i < spy.size()-1; i ++){
        double SPY1 = stod(spy[i ]);
        double SPY2 = stod(spy[i + 1]);
        double SPY3 = (SPY2 - SPY1)/SPY1;
        SPYRETURN.push_back(SPY3);
    }
    return SPYRETURN;
}

Return calculationOfReturn (Return abnormalReturn, StockMap stocklist,StockMap stocklist2,vector<double>spy ){
    
    
    for (StockMap:: iterator it = stocklist2.begin(); it != stocklist2.end();it ++){
        vector<double> abnormal;
        vector<string> stockPrice = it -> second.AdjClose;
        string stockName = it->first;
        
        int startDate = it -> second.StartDateIndex;
        for (int i = 0; i < 60 ; i ++){
            string one  = stockPrice[i];
            string two = stockPrice[i+1];
            double first = stod(one);
            double second = stod(two);
            
            
            double result = (second - first)/first;
            it -> second.Return = result;
            //double SPY1 = stod(spy[startDate + i ]);
            //double SPY2 = stod(spy[startDate + i + 1]);
            //double SPY3 = (SPY2 - SPY1)/SPY1;
            double SPY = spy[startDate + i + 1];
            result = result - SPY;
            it -> second.AbnormalReturn = result;
            abnormal.push_back(result);
        }
        abnormalReturn.insert({stockName,abnormal});
        
    }

    return abnormalReturn;
    
}

Vector calculationOfAAR(Return abnormalReturn){
    Vector calculation(60,0);
    for (Return:: iterator it = abnormalReturn.begin(); it != abnormalReturn.end();it ++){
        for ( int i = 0; i < 60 ; i ++){
            calculation[i] += it->second[i]/30;
        }
        
    }
    return calculation;
    
}

Vector calculationOfCAAR(Vector calculation){
    Vector calculationCAAR(60,0);
    calculationCAAR[0] = calculation [0];
    for(int i = 0; i < 59; i ++){
        calculationCAAR[i + 1] = calculationCAAR[i] + calculation[i + 1];
    }
    return calculationCAAR;
}

Vector operator +(Vector &V1, const Vector &V2){
    for (int i  = 0; i <60; i++){
        V1[i] = V1[i] + V2[i]/30;
    }
    return V1;
}

Vector operator+( Container &V1, Vector &V2){
    for (int i = 0; i < 60; i++){
        for (int j = 0; j< 30; j++){
            V2[i] = V2[i]+V1[j][i]/30;
        }
    }
    return V2;
}
 
Container operator -(Container &V1, const Vector &V2){
    for (int i  = 0; i <60; i++){
        for (int j = 0; j < 30; j++){
            V1[j][i] = V1[j][i] - V2[i];
        }
    }
    return V1;
}

Container operator ^(Container &V1, Container &V2){
    for (int i  = 0; i <60; i++){
        for (int j = 0; j <30; j++){
            V1[j][i] = V2[j][i] * V2[j][i];
        }
    }
    return V1;
}

Vector squareRootOperator(Vector &V1){
    for (int i  = 0; i <60; i++){
        V1[i] = sqrt(V1[i]);
    }
    return V1;
    
}

Matrix finalCalculation(Group group1,vector<double>spy, StockMap StockList){
    vector<double> original(60,0.0);
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
    StockShuffler shuffle = StockShuffler(group1);

    for (int j = 0; j < 30 ;j++){
        cout << 41 << j << " ";
        
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
    return Result;
    
}

#endif /* Calculation_h */
