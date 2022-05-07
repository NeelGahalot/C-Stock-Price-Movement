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
    int samples_ = 40;
    int N_;

    //int N = 80; //total day = 2N+1
    //int random = 80; //number of stocks selected in each group
    //int repeat = 40; //repeat calculation # times
public:
    Bootstrap() {
        while (true) {
            cout << "Enter value of N (30 - 60): " << endl;
            cin >> N_;
        
            if ((N_ >= 30) && (N_ <= 60)) {
                break;
            }
            else if (N_ < 30 || N_ > 60) {
                cout << "Invalid value entered for N (30 - 60). Please retry..." << endl;
            }

        }
    }

    vector<vector<double>> Bootstrap::CalculateAR(vector<vector<double>>& price, vector<vector<double>>& IWVreturn);
    vector<double> Bootstrap::CalculateAAR(vector<vector<double>>& ar);
    vector<double> Bootstrap::CalculateCAAR(vector<double>& AAR);
    vector<double> Bootstrap::finalmean(vector<vector<double>>& bootres);
    vector<double> Bootstrap::finalsd(vector<vector<double>>& bootres, vector<double>& avg);
    vector<vector<double>> Bootstrap::finalCalculation(vector<vector<double>>& calAAR, vector<vector<double>>& calCAAR);
    // void CheckSize(StockMap& stock_list);
    //int GetN();
};