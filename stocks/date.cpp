#include "date.hpp"

Date::Date() {
  date = 1;
  month = 1;
  year = 1970;
}

Date::Date(const Date& date_) {
  date = date_.date;
  month = date_.month;
  year = date_.year;
}