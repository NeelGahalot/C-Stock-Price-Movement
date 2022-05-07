#pragma once
#include <vector>
#include <string>
#include <map>
#include "Stock.hpp"
#include "Vector.hpp"

using namespace std;

class Bootstrap {
private:
    const char* cStockSymbolsFile = "Russell_1000_component_stocks.csv";
    const char* cIWVFile = "Russell_3000_Earnings_Announcements.csv";

    int number_of_samples_;
    int number_of_dates_;
    int resample_times_;
    
    //typedef map<string, Vector> ARTable;
    //typedef vector<vector<string>> GroupMap;
    typedef map<string, Stock> StockMap;

public:
    Bootstrap() : number_of_samples_(80), resample_times_(40), number_of_dates_(0) {};
    int GetN() const;
    void populateIWVVector(StockMap& stock_map);
    void populateSymbolVector(vector<string>& symbols);
    void SplitToGroups(vector<string>& title, vector<string>& miss, vector<string>& meet, vector<string>& beat);
    vector<string> Resample(vector<string> vec);
    void ResampleVector(vector<vector<string>>& vec, vector<string>vec2, int resample_times);
    void GetHistoricalPrices(int N, map<string, string> symbol_date_map, map<string, Vector>& price_map, map<string, Vector>& benchmark_map, map<string, map<string, double>>& date_price_map, map<string, double>& iwv_date_map);
    vector<Vector> GetAR(int N, vector<vector<string>> ar, int number_of_samples, map<string, Vector> ar_table);
    Vector GetAAR(vector<Vector> vec, int number_of_dates, int number_of_samples);
    Vector GetCAAR(Vector vec, int number_of_dates);
    Vector CalculateAvg(vector<Vector> vec, int number_of_dates_, int resample_times);
    Vector CalculateStd(vector<Vector> vec, Vector avg, int number_of_dates, int resample_times);
    vector<Vector> Calculate(vector<vector<string>> vec, int number_of_samples, int number_of_dates, int resample_times, map<string, Vector> ar_table);
    ~Bootstrap() {}
};