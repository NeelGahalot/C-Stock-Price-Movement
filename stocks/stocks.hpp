#pragma once

#include <string>
#include <vector>
#include "date.hpp"

using namespace std;

namespace fre {
  class StockDayData {
    public:
      Date date;
      double open;
      double high;
      double low;
      double close;
      double adj_close;
      long volume;
    
    StockDayData();
    StockDayData(Date date_, double open_, double high_, double low_, double close_, double adj_close_, long volume_) : date(date_), open(open_), high(high_), low(low_), close(close_), adj_close(adj_close_), volume(volume_) {};

    void reset(Date date_, double open_, double high_, double low_, double close_, double adj_close_, long volume_);
  };

  class Stock {
    public:
      string ticker;
      string name;
      Date date;
      Date period_ending;
      double estimate;
      double reported;
      double surprise;
      double surprise_percent;

      vector<StockDayData> day_data_list;
      vector<double> r;
      vector<double> ar;

    public:
      Stock();
      Stock(string ticker_, string name_, Date date_, Date period_ending_, double estimate_, double reported_, double surprise_, double surprise_percent_) : ticker(ticker_), name(name_), date(date_), period_ending(period_ending_), estimate(estimate_), reported(reported_), surprise(surprise_), surprise_percent(surprise_percent_) {};
    
      void reset(string ticker_, string name_, Date date_, Date period_ending_, double estimate_, double reported_, double surprise_, double surprise_percent_);
  };
}