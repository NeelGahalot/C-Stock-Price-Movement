#pragma once
#include <iostream>
#include <string>
#include "Vector.hpp"

class Stock
{
private:
    string ticker_;
    string group_;
    string end_date_;
    string announce_date_;
    double estimated_eps_;
    double actual_eps_;
    double surprise_;
    double surprise_pct_;
    Vector daily_prices_;
    Vector daily_returns_;
    Vector cum_daily_returns_;

public:
    Stock() { 
        ticker_ = "";
        group_ = "";
        end_date_ = "";
        announce_date_ = "";
        estimated_eps_ = 0;
        actual_eps_ = 0;
        surprise_ = 0;
        surprise_pct_ = 0;
    }

    void SetDailyPrices(Vector daily_prices_);
    void SetDailyReturns(Vector daily_returns_);
    void SetCumDailyReturns(Vector cum_daily_returns_);
    void SetEstimatedEPS(double estimated_eps);
    void SetReportedEPS(double actual_eps);
    void SetSurprise(double surprise);
    void SetSurprisePercent(double surprise_pct);
    void SetTicker(string ticker);
    void SetGroup(string group);
    void SetAnnounceDate(string announce_date);
    void SetEndDate(string end_date);
    
    Vector GetDailyPrices();
    Vector GetDailyReturns();
    Vector GetCumDailyReturns();
    double GetEstimatedEPS();
    double GetReportedEPS();
    double GetSurprise();
    double GetSurprisePercent();
    string GetTicker();
    string GetGroup();
    string GetAnnounceDate();
    string GetEndDate();
    
    friend ostream& operator<<(ostream& os, Stock& stock);
};