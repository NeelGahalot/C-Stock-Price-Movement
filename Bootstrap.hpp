#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include "Stock.hpp"

using namespace std;

class Bootstrap {
private:
    int stocks_in_group_ = 80;
    int samples_ = 40;
    int N_;

    typedef vector<vector<string>> GroupMap;
    typedef map<string, vector<double>> AbnormalReturnsMap;
    typedef map<string, Stock> StockMap;
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

    void CalculateStockReturn(AbnormalReturnsMap& abnormal_return, StockMap& stock_list, const vector<double>& rmt);
    vector<double> CalculateAAR(AbnormalReturnsMap& abnormal_return);
    vector<double> CalculateCAAR(vector<double>& calculation);
    vector<vector<vector<double>>> finalCalculation(GroupMap& group_list, vector<double>& rmt, AbnormalReturnsMap& abnormal_return);
    void PopulateStockMap(const string& file_path, StockMap& stock_list, vector<string>& ticker_list, vector<string>& trade_date);
    void CheckSize(StockMap& stock_list);
    int GetN();
};