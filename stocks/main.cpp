#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <thread>
#include "stocks.hpp"
#include "bootstrap.hpp"

using namespace std;
using namespace fre;

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void execute_sampling_iteration(int thread_id, vector<vector<double>>& price, vector<double>& iwv, map<int, vector<vector<double>>>& thread_res) {
    Bootstrap trial;
	//cout << "D0" << endl;

    vector<vector<double>> res_ar = trial.CalculateAR(price, iwv);
	//cout << "D1" << endl;

    vector<double> res_aar = trial.CalculateAAR(res_ar);
	//cout << "D2" << endl;

    vector<double> res_caar = trial.CalculateCAAR(res_aar);
	//cout << "D3" << endl;

    vector<vector<double>> res;
    res.push_back(res_aar);
    res.push_back(res_caar);
    thread_res[thread_id] = res;
	//cout << "D4: " << thread_res.size() << endl;
}

StockDayData generate_random_stock_day_data() {
	Date date;
	double open = fRand(100, 200);
	double high = fRand(100, 200);
	double low = fRand(100, 200);
	double close = fRand(100, 200);
	double adj_close = fRand(100, 200);
	long volume = rand() % 10 + 1;

	StockDayData sd = StockDayData(date, open, high, low, close, adj_close, volume);
	return sd;
}

Stock generate_random_stock(const int stockDayDataCount) {
	string ticker = "AAPL";
	string name = "Apple";
	Date date;
	Date period_ending;
	double estimate = fRand(100, 200);
	double reported = fRand(100, 200);
	double surprise = fRand(100, 200);
	double surprise_per = fRand(0, 1);

	Stock s(ticker, name, date, period_ending, estimate, reported, surprise, surprise_per);
	for (int i = 0; i < stockDayDataCount; i++) {
		s.day_data_list.push_back(generate_random_stock_day_data());
	}

	return s;	
}

vector<double> generate_stock_data() {
	vector<double> demo_stock;
	demo_stock.push_back(127.3431);
	demo_stock.push_back(143.3431);
	demo_stock.push_back(134.3431);
	demo_stock.push_back(153.3431);
	demo_stock.push_back(169.3431);
	
	return demo_stock;
}

int main()
{
	vector<Stock> stockList;
	for (int i = 0; i < 80; i++) {
		stockList.push_back(generate_random_stock(5));
	}

  vector<vector<double>> price;
	int stockCount = stockList.size();
	for (int i = 0; i < stockCount; i++) {
		vector<double> priceList;
		int dayDataCount = stockList[i].day_data_list.size();
		for (int j = 0; j < dayDataCount; j++)
			priceList.push_back(stockList[i].day_data_list[j].adj_close);
		price.push_back(priceList);
	}

    vector<double> iwv;
    iwv.push_back(1);
    iwv.push_back(1);
    iwv.push_back(1);
    iwv.push_back(1);
    iwv.push_back(1);

    map<int, vector<vector<double>>> thread_res;

    thread t1(execute_sampling_iteration, 1, ref(price), ref(iwv), ref(thread_res));
    thread t2(execute_sampling_iteration, 1, ref(price), ref(iwv), ref(thread_res));
    t1.join();

		// vector<vector<double>> res1 = thread_res[1];
		// vector<vector<double>> res2 = thread_res[2];
		// res1[0]; // sampling 1 res_aar
		// res1[1]; // sampling 1 res_caar

		// res2[0]; // sampling 2 res_aar
		// res2[1]; // sampling 2 res_caar
   
	  cout << "result count: " << thread_res.size() << '\n';

    return 0;
}

