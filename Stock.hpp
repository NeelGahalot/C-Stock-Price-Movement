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
    string start_date_;
    double estimated_eps_;
    double actual_eps_;
    double surprise_;
    double surprise_pct_;
    Vector adjusted_close_;
    Vector daily_prices_;
    Vector cum_daily_returns_;

public:
    Stock() { 
        ticker_ = "";
        group_ = "";
        end_date_ = "";
        announce_date_ = "";
        start_date_ = "";
        estimated_eps_ = 0;
        actual_eps_ = 0;
        surprise_ = 0;
        surprise_pct_ = 0;
    }

    void SetAdjustedClose(Vector adjusted_close);
    void SetDailyPrices(Vector daily_prices_);
    void SetCumDailyReturns(Vector cum_daily_returns_);
    void SetEstimatedEPS(double estimated_eps);
    void SetReportedEPS(double actual_eps);
    void SetSurprise(double surprise);
    void SetSurprisePercent(double surprise_pct);
    void SetTicker(string ticker);
    void SetGroup(string group);
    void SetAnnounceDate(string announce_date);
    void SetEndDate(string end_date);
    
    Vector GetAdjustedClose();
    Vector GetDailyPrices();
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