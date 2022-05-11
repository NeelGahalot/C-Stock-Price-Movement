#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include <map>
#include "curl/curl.h"
#include "Stock.hpp"

using namespace std;

struct MemoryStruct {
	char* memory;
	size_t size;
	size_t total_size;
};

// Return if year is leap year or not.
bool CheckLeap(int y) {
	if (y % 100 != 0 && y % 4 == 0 || y % 400 == 0)
		return true;

	return false;
}

// Given a date, returns number of days elapsed
// from the  beginning of the current year (1st
// jan).
int OffsetDays(int d, int m, int y) {
	int offset = d;

	switch (m - 1) {
	case 11:
		offset += 30;
	case 10:
		offset += 31;
	case 9:
		offset += 30;
	case 8:
		offset += 31;
	case 7:
		offset += 31;
	case 6:
		offset += 30;
	case 5:
		offset += 31;
	case 4:
		offset += 30;
	case 3:
		offset += 31;
	case 2:
		offset += 28;
	case 1:
		offset += 31;
	}

	if (CheckLeap(y) && m > 2)
		offset += 1;

	return offset;
}

// Given a year and days elapsed in it, finds
// date by storing results in d and m.
void ReverseOffsetDays(int offset, int y, int* d, int* m) {
	int month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (CheckLeap(y))
		month[2] = 29;

	int i;
	for (i = 1; i <= 12; i++)
	{
		if (offset <= month[i])
			break;
		offset = offset - month[i];
	}

	*d = offset;
	*m = i;
}

// Add x days to the given date.
string AddDays(string date, int days) {
	string end_date;

	int y1 = stoi(date.substr(0, 4));
	int m1 = stoi(date.substr(6, 2));
	int d1 = stoi(date.substr(8));

	int offset1 = OffsetDays(d1, m1, y1);
	int remDays = CheckLeap(y1) ? (366 - offset1) : (365 - offset1);

	// y2 is going to store result year and
	// offset2 is going to store offset days
	// in result year.
	int y2, offset2;
	if (days <= remDays)
	{
		y2 = y1;
		offset2 = offset1 + days;
	}

	else
	{
		// x may store thousands of days.
		// We find correct year and offset
		// in the year.
		days -= remDays;
		y2 = y1 + 1;
		int y2days = CheckLeap(y2) ? 366 : 365;
		while (days >= y2days)
		{
			days -= y2days;
			y2++;
			y2days = CheckLeap(y2) ? 366 : 365;
		}
		offset2 = days;
	}

	// Find values of day and month from
	// offset of result year.
	int m2, d2;
	ReverseOffsetDays(offset2, y2, &d2, &m2);

	end_date = to_string(y2) + "-" + to_string(m2) + "-" + to_string(d2);
	return end_date;
}

void* myrealloc(void* ptr, size_t size) {
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

int write_data2(void* ptr, size_t size, size_t nmemb, void* data) {
	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)data;

	if ((mem->size + realsize) >= mem->total_size)
		mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);

	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
		if (mem->size > mem->total_size)
			mem->total_size = mem->size;
	}
	return realsize;
}

int ExtractIWVData(map<string, double>& iwv_date_map, string& start_date, string& end_date) {
	// declaration of an object CURL
	CURL* handle;

	// result of the whole process
	CURLcode result;

	// set up the program environment that libcurl needs
	curl_global_init(CURL_GLOBAL_ALL);

	// curl_easy_init() returns a CURL easy handle
	handle = curl_easy_init();

	// if everything's all right with the easy handle...
	if (handle)
	{
		string url_common = "https://eodhistoricaldata.com/api/eod/";
		string api_token = "62686d23ea5b52.97340064";  // You must replace this API token with yours

		struct MemoryStruct data;
		data.memory = NULL;
		data.size = 0;
		data.total_size = 0;

		cout << "----------------------- IWV data extraction -----------------------------" << endl;

		string url_request = url_common + "IWV" + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
		curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

		//adding a user agent
		curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
		curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);

		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2); 
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);

		// perform, then store the expected code in result
		result = curl_easy_perform(handle);

		if (result != CURLE_OK)
		{
			// if errors have occured, tell us what is wrong with result
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			return 1;
		}

		stringstream sData;
		sData.str(data.memory);
		string sValue, sDate;
		double dValue = 0;
		string line;
		
		while (getline(sData, line)) {
			size_t found = line.find('-');

			if (found != std::string::npos) {
				sDate = line.substr(0, line.find_first_of(','));
				line.erase(line.find_last_of(','));
				sValue = line.substr(line.find_last_of(',') + 1);
				dValue = strtod(sValue.c_str(), NULL);
				iwv_date_map[sDate] = dValue;
			}
		}

		free(data.memory);
		data.size = 0;
	}
	else {
		fprintf(stderr, "Curl init failed!\n");
		return -1;
	}

	// cleanup since you've used curl_easy_init
	curl_easy_cleanup(handle);

	// release resources acquired by curl_global_init()
	curl_global_cleanup();

	cout << "IWV data extraction completed successfully." << endl << endl;

	return 0;
}

int ExtractStockData(map<string, Stock> stock_map, map<string, map<string, double>>& date_price_map, string& start_date, string& end_date) {
	int count = 0;
	int length = stock_map.size();

	// declaration of an object CURL
	CURL* handle;

	// result of the whole process
	CURLcode result;

	// set up the program environment that libcurl needs
	curl_global_init(CURL_GLOBAL_ALL);

	// curl_easy_init() returns a CURL easy handle
	handle = curl_easy_init();

	// if everything's all right with the easy handle...
	if (handle)
	{
		string url_common = "https://eodhistoricaldata.com/api/eod/";
		string api_token = "62686d23ea5b52.97340064";  // You must replace this API token with your

		struct MemoryStruct data;
		data.memory = NULL;
		data.size = 0;
		data.total_size = 0;

		cout << "------------------------- Stock data extraction -------------------------" << endl;

		//for (auto itr = ticker_date_map.begin(); itr != ticker_date_map.end(); itr++) {
		for (auto itr = stock_map.begin(); itr != stock_map.end(); itr++) {
			data.size = 0;
			memset(data.memory, '\0', data.total_size);

			string symbol = itr->first;
			string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
			curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

			//adding a user agent
			curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);

			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);

			// perform, then store the expected code in result
			result = curl_easy_perform(handle);

			if (result != CURLE_OK) {
				// if errors have occured, tell us what is wrong with result
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}

			stringstream sData;
			sData.str(data.memory);
			string sValue, sDate;
			double dValue = 0;
			string line;

			while (getline(sData, line)) {
				size_t found = line.find('-');

				if (found != std::string::npos) {
					sDate = line.substr(0, line.find_first_of(','));
					line.erase(line.find_last_of(','));
					sValue = line.substr(line.find_last_of(',') + 1);
					dValue = strtod(sValue.c_str(), NULL);
					date_price_map[symbol][sDate] = dValue;
				}
			}

			count += 1;

			if (count % 1 == 0)
				cout << "- - - - - - - - - - - - - - Downloading " << ceil((count * 1.0 / length) * 100) << "% - - - - - - - - - - - - - - \r";
		}

		free(data.memory);
		data.size = 0;

	}
	else {
		fprintf(stderr, "Curl init failed!\n");
		return -1;
	}

	// cleanup since you've used curl_easy_init
	curl_easy_cleanup(handle);

	// release resources acquired by curl_global_init()
	curl_global_cleanup();

	cout << endl << "Stock data extraction complete." << endl << endl;

	return 0;
}
