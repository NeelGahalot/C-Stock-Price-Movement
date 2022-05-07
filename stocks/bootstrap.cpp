#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "stocks.hpp"
#include "bootstrap.hpp"

using namespace std;

/*
class attribute
    int stocks_in_group_ = 80;
    int samples_ = 40;
    int N_;
*/

vector<vector<double>> Bootstrap::CalculateAR(vector<vector<double>>& price, vector<double>& IWVreturn) {
	// price: price vecter around annoucement date with 80 stocks
	// length of vector: 2N+1 or less if not enough date
	// stocks_in_group_: 80

	//replce price matrix with daily return matrix
	//calculate AR inplace
	for (int i = 0; i < stocks_in_group_; i++)
	{
		int T = price[i].size();  //T shoulds be 2N+1 or the number of all available dates
		for (int t=0; t < T-1; t++)
		{
			price[i][t] = price[i][t + 1] / price[i][t] - 1;
			price[i][t] = price[i][t] - IWVreturn[t];
			//if the length of two vector differ, how to match return with regards to date
		}
	}
	//or create a new abnormal return matrix instead of replace

	return price;
}

vector<double> Bootstrap::CalculateAAR(vector<vector<double>>& ar) {

	double sum;
    int T = ar[1].size();	
    vector<double> AAR;
	AAR.resize(stocks_in_group_);

    for (int t=0; t < T - 1; t++)
	{
		sum = 0;
		for (int i = 0; i < stocks_in_group_; i++)
		{
			sum += ar[i][t];
		}
		AAR[t] = sum / stocks_in_group_;
	}
    return AAR;
}

vector<double> Bootstrap::CalculateCAAR(vector<double>& AAR) {

    vector<double> CAAR;
    CAAR.resize(AAR.size());
    CAAR[0] = AAR[0];
    for (int i = 1; i < AAR.size(); i++)
    {
        CAAR[i] = CAAR[i-1] + AAR[i];
    }

	return CAAR;
}

vector<double> Bootstrap::finalmean(vector<vector<double>>& bootres){
    vector<double> avg;
    double mu = 0;

    int T = bootres[0].size();
    for (int t = 0; t < T; t++) {
        for (int i = 0; i < samples_; i++) 
        {
            mu += bootres[i][t];
        }
        mu = mu / samples_;
        avg.push_back(mu);
    }
    return avg;
}

vector<double> Bootstrap::finalsd(vector<vector<double>>& bootres, vector<double>& avg){
    vector<double> sd;
    double sigma = 0, mu = 0;

    int T = bootres[0].size();
    for (int t = 0; t < T; t++) {
        mu = avg[t];
        for (int i = 0; i < samples_; i++) 
        {
            sigma += pow((bootres[i][t] - mu), 2);
        }
        sigma = sqrt(sigma / samples_);
        sd.push_back(sigma);
    }
    return sd;
}

vector<vector<double>> Bootstrap::finalCalculation(vector<vector<double>>& calAAR, vector<vector<double>>& calCAAR){
    vector<vector<double>> result;
    vector<double> avg_AAR, avg_CAAR, sd_AAR, sd_CAAR;
    //double mu_AAR, mu_AAR, 

    avg_AAR = finalmean(calAAR);
    avg_CAAR = finalmean(calCAAR);
    sd_AAR = finalsd(calAAR, avg_AAR);
    sd_CAAR = finalsd(calCAAR, avg_CAAR);

    result.push_back(avg_AAR);
    result.push_back(avg_CAAR);
    result.push_back(sd_AAR);
    result.push_back(sd_CAAR);

    return result;
}

/*
void Bootstrap::CheckSize(StockMap& stock_list) {

}

int Bootstrap::GetN() {
	return N_;
}
*/