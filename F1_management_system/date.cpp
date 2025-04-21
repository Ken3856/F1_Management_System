#include "date.h"

Date::Date() : day(0), month(0), year(0) {}
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

string Date::getDateString() const {
    return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
}

ostream& operator<<(ostream& os, const Date& d){
    os << d.getDateString();
    return os;
}

istream& operator>>(istream& is, Date& d){
    int dd, mm, yy;
    char dash1, dash2;
    if (is >> dd >> dash1 >> mm >> dash2 >> yy){
        d = Date(dd, mm, yy);
    }
    return is;
}
