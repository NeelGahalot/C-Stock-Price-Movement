#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Data {
private:
	const char* cStocksFile = "Russell_3000_component_stocks.csv";
	const char* cEarningsFile = "Russell_3000_Earnings_Announcements.csv";

	struct MemoryStruct {
		char* memory;
		size_t size;
		size_t total_size;
	};

public:
	void populateEarningVector(vector<string>& symbols, vector<string>& anndate, vector<string>& prdend, vector<string>& est, vector<string>& rpt, vector<string>& sur_prise, vector<string>& sur_pct);
	void populateSymbolVector(vector<string>& symbols);
	int write_data(void* ptr, int size, int nmemb, FILE* stream);
	void* myrealloc(void* ptr, size_t size);
	int write_data2(void* ptr, size_t size, size_t nmemb, void* data);
	int downloadData();
};