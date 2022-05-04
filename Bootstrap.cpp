#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Stock.hpp"
#include "Bootstrap.hpp"

using namespace std;

void Bootstrap::CalculateStockReturn(AbnormalReturnsMap& abnormal_return, StockMap& stock_list, const vector<double>& rmt) {

}

vector<double> Bootstrap::CalculateAAR(AbnormalReturnsMap& abnormal_return) {

}

vector<double> Bootstrap::CalculateCAAR(vector<double>& calculation) {

}

vector<vector<vector<double>>> Bootstrap::finalCalculation(GroupMap& group_list, vector<double>& rmt, AbnormalReturnsMap& abnormal_return) {

}

void Bootstrap::PopulateStockMap(const string& file_path, StockMap& stock_list, vector<string>& ticker_list, vector<string>& trade_date) {
	ifstream file;
	file.open(file_path);


}

void Bootstrap::CheckSize(StockMap& stock_list) {

}

int Bootstrap::GetN() {
	return N_;
}