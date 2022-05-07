#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <thread>
#include "stocks.hpp"
#include "bootstrap.hpp"

using namespace std;

void execute_sampling_iteration(int thread_id, vector<vector<double>>& price, vector<double>& iwv, map<int, vector<vector<double>>>& thread_res) {
    Bootstrap trial;

    vector<vector<double>> res_ar = trial.CalculateAR(price, iwv);
	cout << "D1" << endl;

    vector<double> res_aar = trial.CalculateAAR(res_ar);
	cout << "D2" << endl;

    vector<double> res_caar = trial.CalculateCAAR(res_aar);
	cout << "D3" << endl;

    vector<vector<double>> res;
    res.push_back(res_aar);
    res.push_back(res_caar);
    thread_res[thread_id] = res;
	cout << "D4: " << thread_res.size() << endl;
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
    vector<vector<double>> price;

	for (int i = 0; i < 80; i++) {
		price.push_back(generate_stock_data());
	}

    vector<double> iwv;
    iwv.push_back(1);
    iwv.push_back(1);
    iwv.push_back(1);
    iwv.push_back(1);
    iwv.push_back(1);

    map<int, vector<vector<double>>> thread_res;

	execute_sampling_iteration(1, price, iwv, thread_res);

    //thread t1(execute_sampling_iteration, 1, price, iwv, thread_res);
    //t1.join();

    cout << "result count: " << thread_res.size() << '\n';

    return 0;
}