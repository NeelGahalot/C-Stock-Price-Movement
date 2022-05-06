#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
#include "Stock.hpp"
#include "Bootstrap.hpp"
#include "Vector.hpp"

using namespace std;

void Bootstrap::populateIWVVector(StockMap& stock_map) {
    ifstream fstream;
    fstream.open(cIWVFile, ios::in);

    string line, ticker, announce_date, end_date, estimated_eps, reported_eps, surprise, surprise_pct;

    while (!fstream.eof()) {
        getline(fstream, line);
        stringstream sin(line);

        getline(sin, ticker, ',');
        getline(sin, announce_date, ',');
        getline(sin, end_date, ',');
        getline(sin, estimated_eps, ',');
        getline(sin, reported_eps, ',');
        getline(sin, surprise, ',');
        getline(sin, surprise_pct);

        stock_map[ticker].SetTicker(ticker);
        stock_map[ticker].SetAnnounceDate(announce_date);
        stock_map[ticker].SetEndDate(end_date);
        stock_map[ticker].SetEstimatedEPS(stod(estimated_eps));
        stock_map[ticker].SetReportedEPS(stod(reported_eps));
        stock_map[ticker].SetSurprise(stod(surprise));
        stock_map[ticker].SetSurprisePercent(stod(surprise_pct));
    }

    cout << "IWV data populated successfully." << endl << endl;
}

void Bootstrap::populateSymbolVector(vector<string>& symbols) {
    ifstream fstream;
    fstream.open(cStockSymbolsFile, ios::in);

    string line, name, symbol;
    int count = 0;

    while (!fstream.eof()) {
        getline(fstream, line);
        stringstream sin(line);

        getline(sin, symbol, ',');
        getline(sin, name);
        symbols.push_back(symbol);

        count++;
    }

    cout << "Number of stocks successfully populated: " << count << endl << endl;
}

void Bootstrap::SplitToGroups(vector<string>& title, vector<string>& miss, vector<string>& meet, vector<string>& beat) {
    int msize = title.size() / 3;

    copy(title.begin(), title.begin() + msize, back_inserter(miss));
    copy(title.begin() + msize, title.begin() + 2 * msize, back_inserter(meet));
    copy(title.begin() + 2 * msize, title.begin() + title.size(), back_inserter(beat));

    cout << "Stocks have been seperated to different groups" << endl << endl;
}

vector<Vector> GetAR(int N, vector<vector<string>> vec, int number_of_samples, map<string, Vector> ar_table) {
    map<string, Vector>::iterator itr;
    vector<vector<double>> AR;

    for (int i = 0; i < number_of_samples; i++) {
        itr = ar_table.find(vec[N][i]);

        if (itr != ar_table.end())
            AR.push_back(itr->second);
        else
            cout << vec[N][i] << "could not be found." << endl << endl;
    }

    return AR;
}

Vector GetAAR(vector<Vector> vec, int number_of_dates, int number_of_samples) {
    vector<double> AAR;

    for (int i = 0; i < number_of_dates; i++) {
        double sum = 0;

        for (int n = 0; n < number_of_samples; n++)
            sum += vec[n][i];

        double avg = sum / number_of_samples;
        AAR.push_back(avg);
    }

    return AAR;
}

Vector GetCAAR(Vector vec, int number_of_dates) {
    Vector CAAR;
    double caar = 0.0;

    for (int i = 0; i < number_of_dates; i++) {
        caar += vec[i];
        CAAR.push_back(caar);
    }

    return CAAR;
}

Vector CalculateAvg(vector<Vector> vec, int number_of_dates, int resample_times) {
    Vector AVG;
    double res = 0.0;

    for (int i = 0; i < number_of_dates; i++) {
        for (int j = 0; j < resample_times; j++) {
            res += vec[j][i];
        }
        res = res / resample_times;
        AVG.push_back(res);
    }

    return AVG;
}

Vector CalculateStd(vector<Vector> vec, Vector avg, int number_of_dates, int resample_times) {
    Vector STD;
    double res = 0.0;
    double mean = 0.0;

    for (int i = 0; i < number_of_dates; i++) {
        mean = avg[i];

        for (int j = 0; j < resample_times; j++) {
            res += pow((vec[j][i] - mean), 2);
        }

        res = sqrt(res / resample_times);
        STD.push_back(res);
    }

    return STD;
}

vector<Vector> Calculate(vector<vector<string>> vec, int number_of_samples, int number_of_dates, int resample_times, map<string, Vector> ar_table) {
    vector<Vector> result;
    vector<Vector> AAR_pop;
    vector<Vector>CAAR_pop;
    Vector AVG_AAR;
    Vector AVG_CAAR;
    Vector STD_AAR;
    Vector STD_CAAR;

    for (int n = 0; n < resample_times; n++) {
        vector<Vector> AR = GetAR(n, vec, number_of_samples, ar_table);
        Vector AAR = GetAAR(AR, number_of_dates, number_of_samples);
        Vector CAAR = GetCAAR(AAR, number_of_dates);

        AAR_pop.push_back(AAR);
        CAAR_pop.push_back(CAAR);
    }

    AVG_AAR = CalculateAvg(AAR_pop, number_of_dates, resample_times);
    AVG_CAAR = CalculateAvg(CAAR_pop, number_of_dates, resample_times);
    STD_AAR = CalculateStd(AAR_pop, AVG_AAR, number_of_dates, resample_times);
    STD_CAAR = CalculateStd(CAAR_pop, AVG_CAAR, number_of_dates, resample_times);

    result.push_back(AVG_AAR);
    result.push_back(AVG_CAAR);
    result.push_back(STD_AAR);
    result.push_back(STD_CAAR);

    return result;
}

vector<string> Bootstrap::Resample(vector<string> vec) {
    int len = vec.size();
    int index = 0;

    vector<string> result;
    int count = 0;

    while (count < number_of_samples_) {

        count += 1;
        index = rand() % len;

        result.push_back(vec[index]);
    }

    return result;
}

void Bootstrap::ResampleVector(vector<vector<string>>& vec, vector<string>vec2, int resample_times) {
    for (int i = 0; i < resample_times; i++) {
        vector<string> sample = Resample(vec2);
        vec.push_back(sample);
    }

    cout << "Resampling group successfull." << endl << endl;
}

void Bootstrap::GetHistoricalPrices(int N, map<string, string> symbol_date_map, map<string, Vector>& price_map, map<string, Vector>& benchmark_map, map<string, map<string, double>>& date_price_map, map<string, double>& iwv_date_map) {
    map<string, string>::iterator symbol_itr = symbol_date_map.begin();

    for (; symbol_itr != symbol_date_map.end(); symbol_itr++)
    {
        string symbol = symbol_itr->first;
        string date = symbol_itr->second;

        map<string, double>::iterator itr = date_price_map[symbol].find(date);
        // if the date zero is not found, return empty
        if (itr == date_price_map[symbol].end()) {
            cout << symbol + " day zero is not found!" << endl;
            continue;
        }

        for (int i = 0; i < N; i++) {
            //if the symbol doesn't have +N days, return end
            if (itr == date_price_map[symbol].end()) {
                break;
            }
            itr++;
        }

        map<string, double>::iterator end_itr = itr;
        if (itr != date_price_map[symbol].end()) {
            end_itr++;
        }

        //reset itr
        itr = date_price_map[symbol].find(date);
        for (int i = 0; i < N; i++) {
            //if the symbol doesn't have -N days, return begin
            if (itr == date_price_map[symbol].begin()) {
                break;
            }
            itr--;
        }

        Vector adjClose;
        Vector benchmark;
        while (itr != end_itr) {
            adjClose.push_back(itr->second);
            benchmark.push_back(iwv_date_map[itr->first]);
            itr++;
        }

        price_map[symbol] = adjClose;
        benchmark_map[symbol] = benchmark;
    }
}

int Bootstrap::GetN() const {
    return number_of_samples_;
}
