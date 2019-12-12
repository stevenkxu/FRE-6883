#ifndef Stock_hpp
#define Stock_hpp

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;


class Stock
{
public:
    int StartDateIndex;
    string Ticker;
    vector<string> AdjClose;
    string StartDate;
    string EndDate;
    string AnnounceDate;
    double EstEPS;
    double ActEPS;
    double Surprise;
    /*
    vector<double> AdjClose;
    vector<double> Ret;
    vector<double> AR;
    vector<double> CAR;
    string getStartDate() { return StartDate; }
    string getEndDate() { return EndDate; }
    vector<double> getRet() { return Ret; }
    vector<double> getAR() { return AR; }
    vector<double> getCAR() { return CAR; }
*/
    Stock() { StartDateIndex = 0; }
    Stock(int StartDateIndex_) { StartDateIndex = StartDateIndex_; }

};



#endif /* Stock_hpp */

