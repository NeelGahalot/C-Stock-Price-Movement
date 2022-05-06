class Date {
  public:
    int date;
    int month;
    int year;

  public:
    Date();
    Date(int date_, int month_, int year_) : date(date_), month(month_), year(year_) {};
    Date(const Date &date_);
};