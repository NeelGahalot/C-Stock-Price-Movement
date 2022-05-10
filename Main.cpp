#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include <map>
#include <algorithm>
#include <thread>
#include "Bootstrap.hpp"
#include "Download.hpp"
#include "Plot.hpp"
#include "Stock.hpp"
#include "Vector.hpp"

using namespace std;

void DisplayMenu() {
    cout << "------------------------- Menu -------------------------" << endl;
    cout << "1. Enter N." << endl
         << "2. Pull information for one stock." << endl
         << "3. Show AAR, AAR-STD, CAAR and CAAR-STD for one group." << endl
         << "4. Show the CAAR graph for all groups." << endl
         << "5. Exit menu." << endl;
}

int main() {
    srand(time(NULL));
    int N = 0;
    string start_date = "2021-04-01";
    string end_date = "2022-03-31";

    Bootstrap bs;
    map<string, Stock> stock_map;
    vector<string> ticker_list;
    vector<string> beat, meet, miss;

    cout << "----------------------- Populating tickers & IWV ----------------------" << endl;

    // Read all the symbols from the file
    bs.populateTickers(ticker_list);
    bs.populateEarnings(stock_map);

    map<string, string> ticker_date_map; // a map that contains tickers and corresponding day zeros
 
    for (auto itr = stock_map.begin(); itr != stock_map.end(); itr++) {
        //use intersection of ticker_list and ticker
        string ticker = itr->first;
        string announce_date = itr->second.GetAnnounceDate();

        if (find(ticker_list.begin(), ticker_list.end(), ticker) != ticker_list.end() && ticker != "") {
            ticker_date_map[ticker] = announce_date;
        }
    }

    //price_map: ticker and vector of price pair
    //benchmark_map: ticker and vector of benchmark price pair
    map<string, Vector> price_map, benchmark_map;
    map<string, double> iwv_date_map;
    map<string, map<string, double>> date_price_map;

    ExtractIWVData(iwv_date_map, start_date, end_date);
    ExtractStockData(stock_map, date_price_map, start_date, end_date);

    vector<string> current_tickers;
    vector<string> valid_tickers;
    map<string, Vector> ar_table;
    string ticker;
    Vector stock_return;
    Vector benchmark_return;
    vector<string> sort_vec;
    vector<Stock> sorted_stocks;

    vector<vector<string>> beat_estimated;
    vector<vector<string>> meet_estimated;
    vector<vector<string>> miss_estimated;

    vector<Vector> beat_calculation;
    vector<Vector> meet_calculation;
    vector<Vector> miss_calculation;

    //calculate average average AAR,CAAR,AAR_STD,CAAR_STD
    vector<vector<Vector>> calcualtion_results;

    //get operator
    int choice = 0;
    //string stock_ticker;
    string group;
    int ticker_index = 0;
    Vector daily_return;
    Vector cum_daily_return;
    int group_selection;
    int group_name;

    while (choice != 5) {
        DisplayMenu();
        cout << "Please select an option: ";
        cin >> choice;
        cout << endl;

        if (N == 0 && choice != 1 && choice != 5) {
            cout << "Cannot proceed without retrieving historical prices. Proceeding with option 1." << endl;
            choice = 1;
        }

        switch (choice) {
            default: {
                cout << "Invalid option. Please enter correct options from the menu." << endl;
                break;
            }
            
            case 1: {
                cout << "Please enter N (N>=60):" << endl;
                cin >> N;

                if (N < 60) {
                    cout << "Invalid value for N, setting N to 60." << endl;
                    N = 60;
                }
                bs.SetN(N);

                current_tickers.clear();
                valid_tickers.clear();
                ar_table.clear();
                stock_return.clear();
                benchmark_return.clear();
                beat_estimated.clear();
                meet_estimated.clear();
                miss_estimated.clear();
                beat_calculation.clear();
                meet_calculation.clear();
                miss_calculation.clear();
                calcualtion_results.clear();
                beat_estimated.clear();
                meet_estimated.clear();
                miss_estimated.clear();
                sort_vec.clear();
                sorted_stocks.clear();

                bs.GetHistoricalPrices(ticker_date_map, price_map, benchmark_map, date_price_map, iwv_date_map);

                for (auto itr = price_map.begin(); itr != price_map.end(); itr++)
                    current_tickers.push_back(itr->first);

                //Check and erase stocks with less than 2N+1 days of data
                //If valid, put symbol into valid_symbol and caluclate returns & AR
                for (int i = 0; i < current_tickers.size(); i++) {
                    ticker = current_tickers[i];

                    if ((int)price_map[ticker].size() < (2 * N + 1)) {
                        cout << ticker + " less than (2N + 1) days! Actual days: " + to_string(price_map[ticker].size()) << endl;
                        //price_map.erase(ticker);
                        //benchmark_map.erase(ticker);
                    }
                    else {
                        valid_tickers.push_back(ticker);
                        stock_map[ticker].SetDailyPrices(price_map[ticker]);
                        stock_return = bs.CalculateReturn(price_map[ticker]);
                        benchmark_return = bs.CalculateReturn(benchmark_map[ticker]);
                        ar_table[ticker] = stock_return - benchmark_return;
                    }
                }

                for (auto itr = stock_map.begin(); itr != stock_map.end(); itr++) {
                    string ticker = itr->first;

                    for (int i = 0; i < valid_tickers.size(); i++) {
                        if (ticker == valid_tickers[i]) {
                            // sort_vec.push_back(ticker);
                            sorted_stocks.push_back(itr->second);
                        }
                    }
                }
                sort( sorted_stocks.begin(), sorted_stocks.end(), Stock::before );
                for(int i = 0; i < sorted_stocks.size(); i++) {
                    sort_vec.push_back(sorted_stocks[i].GetTicker());
                }

                //Split Valid Symbols into three groups
                bs.SplitToGroups(sort_vec, beat, miss, meet);

                //resample data of three groups
                bs.ResampleVector(beat_estimated, beat);
                bs.ResampleVector(meet_estimated, meet);
                bs.ResampleVector(miss_estimated, miss);
                cout << "Resampled groups successfully." << endl << endl;

                bs.SetDates(2 * N);

                beat_calculation = bs.CalculateAll(beat_estimated, ar_table);
                meet_calculation = bs.CalculateAll(meet_estimated, ar_table);
                miss_calculation = bs.CalculateAll(miss_estimated, ar_table);

                calcualtion_results.push_back(beat_calculation);
                calcualtion_results.push_back(meet_calculation);
                calcualtion_results.push_back(miss_calculation);

                break;
            }

            case 2: {
                cout << "Please enter stock ticker:" << endl;
                cin >> ticker;
                
                for (int i = 0; i < valid_tickers.size(); i++) {
                    if (ticker == valid_tickers[i]) {
                        daily_return = bs.CalculateReturn(price_map[ticker]);
                        stock_map[ticker].SetDailyReturns(daily_return);
                        cum_daily_return = bs.CalculateCumReturn(daily_return);
                        stock_map[ticker].SetCumDailyReturns(cum_daily_return);

                        cout << stock_map[ticker] << endl;
                        break;
                    }
                    else if (i == valid_tickers.size() - 1) {
                        cout << "Ticker not found. Please enter a valid ticker. " << endl;
                        break;
                    }
                }

                break;
            }
            
            case 3: {
                cout << "Please enter the group selection: " << endl
                     << "1. Beat Estimate Group" << endl
                     << "2. Miss Estimate Group" << endl
                     << "3. Meet Estimate Group" << endl
                     << "4. Go back to the previous menu" << endl;

                cin >> group_selection;

                if (group_selection == 1) group_name = 0;
                else if (group_selection == 2) group_name = 1;
                else if (group_selection == 3) group_name = 2;
                else if (group_selection == 4) break;
                else {
                    cout << "Incorrect selection. Please enter a valid choice." << endl << endl;
                    break;
                }

                cout << "AAR: " << calcualtion_results[group_name][0] << endl
                     << "CAAR: " << calcualtion_results[group_name][1] << endl
                     << "AAR_STD: " << calcualtion_results[group_name][2] << endl
                     << "CAAR_STD: " << calcualtion_results[group_name][3] << endl << endl;

                break;
            }

            case 4: {
                cout << "Plotting CAAR with Gnuplot..." << endl;
                Plot(calcualtion_results);
                break;
            }

            case 5: {
                break;
            }
        }
    }
    return 0;
}