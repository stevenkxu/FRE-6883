#ifndef Selectdata_h
#define Selectdata_h

#include <string>
#include <iostream>
#include <fstream>
#include "ExtractData.h"
#include <vector>
#include "tools.h"
#include "EquityDivide.h"
#include <map>

using namespace std;

typedef map<string,vector<string>> Map;

// number = 0 means miss, 1 is meet, 2is
Map SelectData(Group group, int number)
{
    ifstream fin;
    ofstream fout;
    
    
    vector<string> Tradedate;
    fin.open("tradedate.txt");
    string tem;
    while(fin >> tem)
    {
        Tradedate.push_back(tem);
    }
    fin.close();
    
    remove("Results.csv");
    vector<string> Tickers;
    vector<string> AnnounceDate;
    vector<int> PreStartIndex;
    
    // download stock information including benchmark
    // Tickers.push_back("^GSPC");
    
    string date;
    int dateindex;
    for(int i = 0; i < group[number].size(); i++)
    {
        cout <<group[number][i].first << "   " << group[number][i].second << endl;
        date = group[number][i].second;
        Tickers.push_back(group[number][i].first);
        for(int j = 30; j <=100 ; j++)
        {
            cout << Tradedate[j] << endl;
            if(Tradedate[j] == date)
            {
                dateindex = j-32;
                cout << "==="<<date << endl;
                j = 120;
            }
        }
        PreStartIndex.push_back(dateindex);
    }
    
    Extract(Tickers);
    
    
    string Date, Open, High, Low, Close, Volume;
    fin.open("Results.csv");
    string AdjClose;
    
    Map Price;
    
    int i = 0;
    int countindex = 0;
    while (getline(fin, Date, ','), getline(fin, Open, ','), getline(fin, High, ','), getline(fin, Low, ','), getline(fin, Close, ','), getline(fin, AdjClose, ','), getline(fin, Volume))
    {
        countindex++;
        if (countindex == PreStartIndex[i])
        {
            vector<string> temvector;
            AdjClose = "";
            countindex = 0;
            for(int j = 0; j < 61; j++)
            {
                getline(fin, Date, ','), getline(fin, Open, ','), getline(fin, High, ','), getline(fin, Low, ','), getline(fin, Close, ','), getline(fin, AdjClose, ','), getline(fin, Volume);
                temvector.push_back(AdjClose);
            }
            Price.insert(make_pair(Tickers[i],temvector));
            i++;
        }
    }
    fin.close();
    
    /*
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
    
    return Price;
}


#endif /* Selectdata_h */
