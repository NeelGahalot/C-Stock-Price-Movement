#include <iostream>
#include <string>
#include <vector>
#include "Stock.hpp"
#include "Vector.hpp"

using namespace std;

void Stock::SetDailyPrices(Vector daily_prices) {
    daily_prices_= daily_prices;
}

void Stock::SetDailyReturns(Vector daily_returns) {
    daily_returns_ = daily_returns;
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

Vector Stock::GetDailyPrices() {
    return daily_prices_;
}

Vector Stock::GetDailyReturns() {
    return daily_returns_;
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

bool Stock::before(Stock& lhs, Stock& rhs) {
    return lhs.GetSurprisePercent() > rhs.GetSurprisePercent();
}

void print(Vector const& item) {
    for (int i = 0; i < item.size(); i++)
        std::cout << item.at(i) << ' ';
    cout << endl;
}

ostream& operator<<(ostream& os, Stock& stock) {
    os << "Ticker: " << stock.GetTicker() << endl;
    os << "Group: " << stock.GetGroup() << endl;
    os << "Announcement Date: " << stock.GetAnnounceDate() << endl;
    os << "Period Ending: " << stock.GetEndDate() << endl;
    os << "Estimated Earning Per Share: " << stock.GetEstimatedEPS() << endl;
    os << "Actual Earning Per Share: " << stock.GetEstimatedEPS() << endl;
    os << "Surprise: " << stock.GetSurprise() << endl;
    os << "Surprise %: " << stock.GetSurprisePercent() << endl;
    os << "Daily Prices: " << endl;
    print(stock.GetDailyPrices());
    /*os << "Daily Returns: " << endl;
    print(stock.GetDailyReturns());*/
    os << "Cumulative Daily Returns: " << endl;
    print(stock.GetCumDailyReturns());

    return os;
}