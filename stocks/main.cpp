#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "stocks.hpp"
#include "bootstrap.hpp"

using namespace std;

int main()
{

    Bootstrap trial;

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

    vector<vector<double>> res_ar = trial.CalculateAR(price, iwv);

    vector<double> res_aar = trial.CalculateAAR(res_ar);

    vector<double> res_caar = trial.CalculateCAAR(res_aar);

}