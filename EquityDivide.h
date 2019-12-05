//
//  EquitDivide.h
//  Finanal Project
//
//  Created by IanCheng on 12/4/19.
//  Copyright © 2019 NYU FRE 6883. All rights reserved.
//

#ifndef EquityDivide_h
#define EquityDivide_h

#include <string>
#include <vector>
using namespace std;

typedef string Ticker;
typedef string Date;
typedef pair<Ticker, Date> TickerInfo;
typedef vector<vector<TickerInfo> > Group;

class EquityDivide{
protected:
    vector<pair<double, TickerInfo> > surprise_vec;
public:
    EquityDivide(const string& path);
    Group divide_group() const;
};


#endif /* EquitDivide_h */
