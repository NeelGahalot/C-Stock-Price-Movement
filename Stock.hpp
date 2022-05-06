#pragma once
#include <iostream>
#include <string>
#include <vector>

class Stock
{
private:
    int start_date_index_;
    string ticker_;
    string group_;
    vector<double> adjusted_close_;
    vector<double> return_;
    vector<double> abnormal_return_;
    //string day_zero_;
    string end_date_;
    string announce_date_;
    double estimated_eps_;
    double actual_eps_;
    double surprise_;
    double surprise_pct_;

public:
    Stock() { 
        //start_date_index_ = 0;
        ticker_ = "";
        group_ = "";
        //day_zero_ = "";
        end_date_ = "";
        announce_date_ = "";
        estimated_eps_ = 0;
        actual_eps_ = 0;
        surprise_ = 0;
        surprise_pct_ = 0;
    }

    void SetAdjustedClose(vector<double> adjusted_close);
    void SetReturn(double return_val);
    void SetAbnormalReturn(double abnormal_return);
    void SetTicker(string ticker);
    void SetGroup(string group);
    void SetAnnounceDate(string announce_date);
    void SetEstimatedEPS(double estimated_eps);
    void SetReportedEPS(double actual_eps);
    void SetSurprise(double surprise);
    void SetSurprisePercent(double surprise_pct);
    //void SetStartDateIndex(int start_date_index);
    void SetDayZero(string start_date);
    void SetEndDate(string end_date);

    vector<double> GetAdjustedClose() const;
    vector<double> GetReturn() const;
    vector<double> GetAbnormalReturn() const;
    string GetTicker() const;
    string GetGroup() const;
    string GetAnnounceDate() const;
    double GetEstimatedEPS() const;
    double GetReportedEPS() const;
    double GetSurprise() const;
    double GetSurprisePercent() const;
    //int GetStartDateIndex() const;
    string GetDayZero() const;
    string GetEndDate() const;
    
    friend ostream& operator<<(ostream& os, Stock& stock);
};