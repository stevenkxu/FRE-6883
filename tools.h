//
//  tools.h
//  Finanal Project
//
//  Created by IanCheng on 12/4/19.
//  Copyright © 2019 NYU FRE 6883. All rights reserved.
//

#ifndef tools_h
#define tools_h

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

template <typename T1, typename T2>
T1 read_col(ifstream& file, int data_col){
    file.clear();
    // point read pointer at beginning of file
    file.seekg(0, ios::beg);
    
    string line;
    char *ptr;
    T2 item;
    T1 ans(0);
    //define row and column in every line
    int row = 0;
    int col;
    
    while(getline(file, line)){
        col = 0;
        ptr = strtok((char *)line.c_str(), ",");
        while(ptr){
            if (strcmp(ptr, "")){
                if (col == data_col && row >= 1)
                {
                    std::stringstream ss;
                    ss << std::string(ptr);
                    ss >> item;
                    ans.push_back(item);
                }
                ++col;
            }
            ptr = strtok(NULL, ",");
        }
        ++row;
        
    }
    return ans;
    
}


#endif /* tools_h */
