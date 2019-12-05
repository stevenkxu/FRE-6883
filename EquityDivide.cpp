//
//  EquityDivide.cpp
//  Finanal Project
//
//  Created by IanCheng on 12/4/19.
//  Copyright © 2019 NYU FRE 6883. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include "tools.h"
#include "EquityDivide.h"
using namespace std;

EquityDivide::EquityDivide(const string& path){
    ifstream file;
    file.open(path);
    
    vector<Ticker> id = read_col<vector<Ticker>, Ticker>(file, 0);
    vector<Date> date = read_col<vector<Date>, Date>(file, 1);
    vector<double> actual = read_col<vector<double>, double>(file, 2);
    vector<double> est = read_col<vector<double>, double>(file, 3);
    
    file.close();
    
    size_t n = id.size();
    for(int i=0;i<n;++i){
        double surprise = (actual[i] - est[i]) / abs(est[i]);
        TickerInfo TI = {id[i], date[i]};
        surprise_vec.push_back({surprise, TI});
    }
    sort(surprise_vec.begin(), surprise_vec.end());
}

Group EquityDivide::divide_group() const{
    Group ans(3);
    size_t n = surprise_vec.size();
    int group_size = static_cast<int>(n) / 3;
    for(int i=0;i<n;++i){
        //Miss group
        if(i < group_size){
            ans[0].push_back(surprise_vec[i].second);
        }
        //Meet group
        else if(i >= group_size && i < 2 * group_size){
            ans[1].push_back(surprise_vec[i].second);
        }
        //Beat group
        else{
            ans[2].push_back(surprise_vec[i].second);
        }
    }
    return ans;
}

