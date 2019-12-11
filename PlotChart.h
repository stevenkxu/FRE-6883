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
using namespace std;

void plotChat(vector<double> beat, vector<double> meet, vector<double> miss){
    FILE *gnuplotPipe, *tempDataFile;
    size_t dataSize = beat.size();
    const char *tempDataFileBeat = "beatData";
    const char *tempDataFileMeet = "meetData";
    const char *tempDataFileMiss = "missData";
    
    double x1, y1, x2, y2, x3, y3;
    
    //set gnuplot enviorment
    gnuplotPipe = popen("/opt/local/bin/gnuplot", "w");
    if(gnuplotPipe){
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n",tempDataFileBeat, tempDataFileMeet, tempDataFileMiss);
        fflush(gnuplotPipe);
        
        //open beatData file
        tempDataFile = fopen(tempDataFileBeat,"w");
        for (int i=0; i<= dataSize; i++) {
            x1 = i-30;
            y1 = beat[i];
            fprintf(tempDataFile,"%lf %lf\n",x1,y1);
        }
        fclose(tempDataFile);
        
        //open meetData file
        tempDataFile = fopen(tempDataFileMeet,"w");
        for (int i=0; i <= dataSize; i++) {
            x2 = i-30;
            y2 = meet[i];
            fprintf(tempDataFile,"%lf %lf\n",x2,y2);
        }
        fclose(tempDataFile);
        
        //open missData file
        tempDataFile = fopen(tempDataFileMiss,"w");
        for (int i=0; i <= dataSize; i++) {
            x3 = i-30;
            y3 = miss[i];
            fprintf(tempDataFile,"%lf %lf\n",x3,y3);
        }
        fclose(tempDataFile);
        
        printf("press enter to continue...");
        getchar();
        
        //delete 3 temporary files
        remove(tempDataFileBeat);
        remove(tempDataFileMeet);
        remove(tempDataFileMiss);
        
        fprintf(gnuplotPipe,"exit \n");
        }
    else {
            printf("gnuplot not found...");
        }
}

#endif
