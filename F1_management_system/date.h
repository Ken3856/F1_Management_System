// Responsible: Eamon Mahrooq
// date.h
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

using namespace std;

// ************ Date Class (Composition (Person has a date of birth) ************
class Date{
    private:
        int day, month, year;
    
    public:
        Date();
        Date(int d, int m, int y);

        string getDateString() const;
    };

    // Responsible: Eamon Mahrooq
    // Stream operators
    ostream& operator<<(ostream& os, const Date& d);
    istream& operator>>(istream& is, Date& d);

#endif // DATE_H
