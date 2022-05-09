#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Vector.hpp"
#include "Bootstrap.hpp"
#include "Stock.hpp"

using namespace std;

void Plot(vector<vector<Vector>> calculation_results) {
    int dataSize = calculation_results[0][1].size();
    int N = (dataSize >> 1) + 1;
    FILE* gnuplotPipe, * tempDataFile;
    const char* tempDataFileName1 = "Miss";
    const char* tempDataFileName2 = "Meet";
    const char* tempDataFileName3 = "Beat";
    double x, y, x2, y2, x3, y3;
    int i;

    gnuplotPipe = _popen("C:\\PROGRA~1\\gnuplot\\bin\\gnuplot.exe", "w");

    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n", tempDataFileName1, tempDataFileName2, tempDataFileName3);
        fflush(gnuplotPipe);
        tempDataFile = fopen(tempDataFileName1, "w");
        for (i = 0; i < dataSize; i++) {
            x = i - N;
            y = calculation_results[0][1][i];
            fprintf(tempDataFile, "%lf %lf\n", x, y);
        }
        fclose(tempDataFile);

        tempDataFile = fopen(tempDataFileName2, "w");
        for (i = 0; i < dataSize; i++) {
            x2 = i - N;
            y2 = calculation_results[1][1][i];
            fprintf(tempDataFile, "%lf %lf\n", x2, y2);
        }
        fclose(tempDataFile);

        tempDataFile = fopen(tempDataFileName3, "w");
        for (i = 0; i < dataSize; i++) {
            x3 = i - N;
            y3 = calculation_results[2][1][i];
            fprintf(tempDataFile, "%lf %lf\n", x3, y3);
        }
        fclose(tempDataFile);

        fprintf(gnuplotPipe, "set terminal qt\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set xlabel 'N - Number of days'\n");
        fprintf(gnuplotPipe, "set ylabel 'CAAR'\n");
        fprintf(gnuplotPipe, "set title 'CAAR of all groups'\n");
        fprintf(gnuplotPipe, "set key left top\n");
        fprintf(gnuplotPipe, "set key width '10'\n");


        printf("press enter to continue...");
        system("pause");
        remove(tempDataFileName1);
        remove(tempDataFileName2);
        remove(tempDataFileName3);
        fprintf(gnuplotPipe, "exit\n");
    }
    else {
        printf("gnuplot not found...");
    }
}