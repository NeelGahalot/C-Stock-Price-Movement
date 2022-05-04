#include <vector>
#include <iostream>
#include "Stock.hpp"

using namespace std;

void Stock::SetAdjustedClose(vector<double> adjusted_close) {
    adjusted_close_ = adjusted_close;
}

void Stock::SetReturn(double return_val) {
    return_.push_back(return_val);
}

void Stock::SetAbnormalReturn(double abnormal_return) {
    abnormal_return_.push_back(abnormal_return);
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

void Stock::SetActualEPS(double actual_eps) {
    actual_eps_ = actual_eps;
}

void Stock::SetSurprise(double surprise) {
    surprise_ = surprise;
}

void Stock::SetStartDateIndex(int start_date_index) {
    start_date_index_ = start_date_index;
}

void Stock::SetStartDate(string start_date) {
    start_date_ = start_date;
}

void Stock::SetEndDate(string end_date) {
    end_date_ = end_date;
}

vector<double> Stock::GetAdjustedClose() const {
    return adjusted_close_;
}

vector<double> Stock::GetReturn() const {
    return return_;
}

vector<double> Stock::GetAbnormalReturn() const {
    return abnormal_return_;
}

string Stock::GetTicker() const {
    return ticker_;
}

string Stock::GetGroup() const {
    return group_;
}

string Stock::GetAnnounceDate() const {
    return announce_date_;
}

double Stock::GetEstimatedEPS() const {
    return estimated_eps_;
}

double Stock::GetActualEPS() const {
    return actual_eps_;
}

double Stock::GetSurprise() const {
    return surprise_;
}

int Stock::GetStartDateIndex() const {
    return start_date_index_;
}

string Stock::GetStartDate() const {
    return start_date_;
}

string Stock::GetEndDate() const {
    return end_date_;
}

void print(std::vector<double> const& item) {
    for (int i = 0; i < item.size(); i++)
    {
        std::cout << item.at(i) << ' ';
    }
    cout << " \n" << endl;
}

ostream& operator<<(ostream& os, Stock& stock) {
    os << "Start Date Index: " << stock.GetStartDateIndex() << endl;
    os << "Ticker: " << stock.GetTicker() << endl;
    os << "Group: " << stock.GetGroup() << endl;
    os << "Start Date: " << stock.GetStartDate() << endl;
    os << "End Date: " << stock.GetEndDate() << endl;
    os << "Announcement Date: " << stock.GetAnnounceDate() << endl;
    os << "Estimated Earning Per Share: " << stock.GetEstimatedEPS() << endl;
    os << "Actual Earning Per Share: " << stock.GetActualEPS() << endl;
    os << "Surprise: " << stock.GetSurprise() << endl;
    cout << " \n" << endl;
    os << "Adjusted Close Price: " << endl;
    print(stock.GetAdjustedClose());
    os << "Return: " << endl;
    print(stock.GetReturn());
    os << "Abnormal Return: " << endl;
    print(stock.GetAbnormalReturn());

    return os;
}
