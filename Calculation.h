//
//  Calculation.h
//  ExtractData
//
//  Created by 蔡宁 on 2019/12/9.
//  Copyright © 2019 Song Tang. All rights reserved.
//

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
typedef vector <double> AAR;
typedef vector <double> CAAR;

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

AAR calculationOfAAR(Return abnormalReturn){
    AAR calculation(61,0);
    for (Return:: iterator it = abnormalReturn.begin(); it != abnormalReturn.end();it ++){
        for ( int i = 0; i < 61 ; i ++){
            calculation[i] += it->second[i]/30;
        }
        
    }
    return calculation;
    
}

CAAR calculationOfCAAR(AAR calculation){
    CAAR calculationCAAR(61,0);
    calculationCAAR[0] = calculation [0];
    for(int i = 0; i < 60; i ++){
        calculationCAAR[i + 1] = calculationCAAR[i] + calculation[i + 1];
    }
    return calculationCAAR;
}
 
#endif /* Calculation_h */

