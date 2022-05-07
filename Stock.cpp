#include <iostream>
#include <string>
#include <vector>
#include "Stock.hpp"
#include "Vector.hpp"

using namespace std;

void Stock::SetAdjustedClose(Vector adjusted_close) {
    adjusted_close_ = adjusted_close;
}

void Stock::SetDailyPrices(Vector daily_prices) {
    daily_prices_= daily_prices;
}

void Stock::SetCumDailyReturns(Vector cum_daily_returns) {
    cum_daily_returns_ = cum_daily_returns;
}

void Stock::SetTicker(string ticker) {
    ticker_ = ticker;
}

void Stock::SetGroup(string group) {
    group_ = group;
}

void Stock::SetAnnounceDate(string announce_date) {
    announce_date_ = announce_date;
}

void Stock::SetEstimatedEPS(double estimated_eps) {
    estimated_eps_ = estimated_eps;
}

void Stock::SetReportedEPS(double actual_eps) {
    actual_eps_ = actual_eps;
}

void Stock::SetSurprise(double surprise) {
    surprise_ = surprise;
}

void Stock::SetSurprisePercent(double surprise_pct) {
    surprise_pct_ = surprise_pct;
}

void Stock::SetEndDate(string end_date) {
    end_date_ = end_date;
}

Vector Stock::GetAdjustedClose() {
    return adjusted_close_;
}

Vector Stock::GetDailyPrices() {
    return daily_prices_;
}

Vector Stock::GetCumDailyReturns() {
    return cum_daily_returns_;
}

string Stock::GetTicker() {
    return ticker_;
}

string Stock::GetGroup() {
    return group_;
}

string Stock::GetAnnounceDate() {
    return announce_date_;
}

string Stock::GetEndDate() {
    return end_date_;
}

double Stock::GetEstimatedEPS() {
    return estimated_eps_;
}

double Stock::GetReportedEPS() {
    return actual_eps_;
}

double Stock::GetSurprise() {
    return surprise_;
}

double Stock::GetSurprisePercent() {
    return surprise_pct_;
}

void print(Vector const& item) {
    for (int i = 0; i < item.size(); i++)
    {
        std::cout << item.at(i) << ' ';
    }
    cout << " \n" << endl;
}

ostream& operator<<(ostream& os, Stock& stock) {
    os << "Ticker: " << stock.GetTicker() << endl;
    os << "Group: " << stock.GetGroup() << endl;
    os << "Announcement Date: " << stock.GetAnnounceDate() << endl;
    os << "End Date: " << stock.GetEndDate() << endl;
    os << "Estimated Earning Per Share: " << stock.GetEstimatedEPS() << endl;
    os << "Actual Earning Per Share: " << stock.GetEstimatedEPS() << endl;
    os << "Earning Per Share Surprise: " << stock.GetSurprise() << endl;
    os << "Earning Per Share Surprise %: " << stock.GetSurprisePercent() << endl;
    os << "Adjusted Close Price: " << endl;
    print(stock.GetAdjustedClose());
    os << "Daily Prices: " << endl;
    print(stock.GetDailyPrices());
    os << "Cumulative Daily Returns: " << endl;
    print(stock.GetCumDailyReturns());

    return os;
}