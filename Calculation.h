
//HAHAHAHAHAHA!! We made it !!!!    LisaChen

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
#include "Selectdata.h"

typedef map<string,vector<double>> Return;
//typedef vector <double> AAR;
//typedef vector <double> CAAR;
//typedef vector <double> averageAAR;
//typedef vector <double> averageCAAR;
typedef vector <double> Vector;
typedef vector<vector<vector<double>>> Matrix;
typedef vector<vector<double>> Container;



Return calculationOfReturn (Return abnormalReturn, StockMap &StockList, Map &StockList2, vector <string> spy ){
    
    
    
    for (Map:: iterator it = StockList2.begin(); it != StockList2.end();it ++){
        vector<double> abnormal;
        vector<string> stockPrice = it -> second;
        string stockName = it->first;
        
        int startDate = StockList[stockName].StartDateIndex;
        for (int i = 0; i < 60 ; i ++){
            string one  = stockPrice[i];
            string two = stockPrice[i+1];
            double first = stod(one);
            double second = stod(two);
            
            
            double result = (second - first)/first;
            double SPY1 = stod(spy[startDate + i ]);
            double SPY2 = stod(spy[startDate + i + 1]);
            double SPY3 = (SPY2 - SPY1)/SPY1;
            result = result - SPY3;
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
    for(int i = 0; i < 60; i ++){
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
            V2[j] = V2[j]+V1[j][i];
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

#endif /* Calculation_h */

