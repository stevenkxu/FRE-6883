//
//  PlotChart.cpp
//  Finanal Project
//
//  Created by IanCheng on 12/11/19.
//  Copyright © 2019 NYU FRE 6883. All rights reserved.
//
#ifndef PlotChart_h
#define PlotChart_h

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "Calculation.h"
using namespace std;

inline void plotChart(vector<double> beat, vector<double> meet, vector<double> miss){
    FILE *gnuplotPipe, *tempDataFile;
    size_t dataSize = beat.size() - 1;
    const char *tempDataFileBeat = "Beat";
    const char *tempDataFileMeet = "Meet";
    const char *tempDataFileMiss = "Miss";
    
    double x1, y1, x2, y2, x3, y3;
    
    //set gnuplot enviorment
    #ifdef _WIN32
        gnuplotPipe = _popen("/opt/local/bin/gnuplot", "w");
    #else
        gnuplotPipe = popen("/opt/local/bin/gnuplot", "w");
    #endif;
        cout << 510 << endl;;
    //gnuplotPipe = popen("/opt/local/bin/gnuplot", "w");
    if(gnuplotPipe){
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n",tempDataFileBeat, tempDataFileMeet, tempDataFileMiss);
        fflush(gnuplotPipe);
       // cout << 520 << endl;
        //open beatData file
        tempDataFile = fopen(tempDataFileBeat,"w");
        for (int i=0; i<= dataSize; i++) {
            x1 = i-30;
            y1 = beat[i];
            fprintf(tempDataFile,"%lf %lf\n",x1,y1);
        }
        fclose(tempDataFile);
        //cout << 530 << endl;
        //open meetData file
        tempDataFile = fopen(tempDataFileMeet,"w");
        for (int i=0; i <= dataSize; i++) {
            x2 = i-30;
            y2 = meet[i];
            fprintf(tempDataFile,"%lf %lf\n",x2,y2);
        }
        fclose(tempDataFile);
        cout << 540 << endl;
        //open missData file
        tempDataFile = fopen(tempDataFileMiss,"w");
        for (int i=0; i <= dataSize; i++) {
            x3 = i-30;
            y3 = miss[i];
            fprintf(tempDataFile,"%lf %lf\n",x3,y3);
        }
        cout << 550 << endl;
        fclose(tempDataFile);
        
        printf("press enter to continue...");
        //getchar();
        cout << 555 << endl;
        //delete 3 temporary files
        remove(tempDataFileBeat);
        remove(tempDataFileMeet);
        remove(tempDataFileMiss);
        cout << 560 << endl;
        fprintf(gnuplotPipe,"exit \n");
        cout << 570 << endl;
        }
    else {
            printf("gnuplot not found...");
        }
}



#endif
