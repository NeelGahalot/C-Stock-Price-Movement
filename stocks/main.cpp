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

    vector<double> res_aar = trial.CalculateAAR(res_ar);

    vector<double> res_caar = trial.CalculateCAAR(res_aar);

    vector<vector<double>> res;
    res.push_back(res_aar);
    res.push_back(res_caar);
    thread_res[thread_id] = res;
}

int main()
{
    vector<vector<double>> price;

    vector<double> demo_stock;
    demo_stock.push_back(127.3431);
    demo_stock.push_back(143.3431);
    demo_stock.push_back(134.3431);
    demo_stock.push_back(153.3431);
    demo_stock.push_back(169.3431);

    vector<double> demo_stock2;
    demo_stock2.push_back(127.3431);
    demo_stock2.push_back(143.3431);
    demo_stock2.push_back(134.3431);
    demo_stock2.push_back(153.3431);
    demo_stock2.push_back(169.3431);

    price.push_back(demo_stock);
    price.push_back(demo_stock2);

    vector<double> iwv;
    iwv.push_back(1);
    iwv.push_back(1);
    iwv.push_back(1);
    iwv.push_back(1);
    iwv.push_back(1);

    map<int, vector<vector<double>>> thread_res;

    thread t1(execute_sampling_iteration, 1, price, iwv, thread_res);

    t1.join();

    cout << "result count: ", thread_res.size() << '\n';

    return 0;
}