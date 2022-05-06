#include "stocks.hpp"

using namespace fre;


void Stock::reset(string ticker_, string name_, Date date_, Date period_ending_, double estimate_, double reported_, double surprise_, double surprise_percent_) {
        ticker = ticker_;
        name = name_;
        date = date_;
        period_ending = period_ending_;
        estimate = estimate_;
        reported = reported_;
        surprise = surprise_;
        surprise_percent = surprise_percent_;
        day_data_list.clear();
      };