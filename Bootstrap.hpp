#pragma once
#include <vector>
#include <string>
#include <map>
#include "Stock.hpp"
#include "Vector.hpp"

using namespace std;

class Bootstrap {
private:
    int N_;
    int number_of_samples_;
    int number_of_dates_;
    int resample_times_;

public:
    Bootstrap() : N_(0), number_of_samples_(80), resample_times_(40), number_of_dates_(0) {};

    int GetN() const;
    int GetDates() const;
    int GetSamples() const;
    int GetResamples() const;

    void SetN(int N);
    void SetDates(int number_of_dates);
    void SetSamples(int number_of_samples);
    void SetResamples(int resample_times);

    void populateTickerVector(vector<string>& tickers);
    void populateIWVVector(map<string, Stock>& stock_map);
    void SplitToGroups(vector<string>& title, vector<string>& miss, vector<string>& meet, vector<string>& beat);
    vector<string> Resample(vector<string> vec);
    void ResampleVector(vector<vector<string>>& vec, vector<string>& vec2);

    Vector CalculateReturn(Vector V);
    Vector CalculateCumReturn(Vector V);
    void GetHistoricalPrices(map<string, string> ticker_date_map, map<string, Vector>& price_map, map<string, Vector>& benchmark_map, map<string, map<string, double>>& date_price_map, map<string, double>& iwv_date_map);
    vector<Vector> GetAR(int n, vector<vector<string>> ar, map<string, Vector> ar_table);
    Vector GetAAR(vector<Vector> vec);
    Vector GetCAAR(Vector vec);
    Vector CalculateAvg(vector<Vector> vec);
    Vector CalculateStd(vector<Vector> vec, Vector avg);
    vector<Vector> CalculateAll(vector<vector<string>> vec, map<string, Vector> ar_table);

    ~Bootstrap() {};
};