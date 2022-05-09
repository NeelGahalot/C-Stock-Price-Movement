#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include "stocks.hpp"

using namespace std;

class Bootstrap {
private:
    int stocks_in_group_ = 80;
    int N_;

    //int N = 80; //total day = 2N+1
    //int random = 80; //number of stocks selected in each group
    //int repeat = 40; //repeat calculation # times
public:
	Bootstrap(int N) : N_(N) {
        
    }

    vector<vector<double>> CalculateAR(vector<vector<double>> price, vector<double> IWVreturn);
    vector<double> CalculateAAR(vector<vector<double>>& ar);
    vector<double> CalculateCAAR(vector<double>& AAR);
    vector<double> finalmean(vector<vector<double>>& bootres, int samples);
    vector<double> finalsd(vector<vector<double>>& bootres, vector<double>& avg, int samples);
    vector<vector<double>> finalCalculation(vector<vector<double>>& calAAR, vector<vector<double>>& calCAAR, int samples);
    // void CheckSize(StockMap& stock_list);
    //int GetN();
};