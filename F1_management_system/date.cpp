// Responsible: Eamon Mahrooq (inheritance)
#include "date.h"

// Default constructor with member initialiser list.
Date::Date() : day(0), month(0), year(0) {}

// Parameterised constructor. 
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

// Returns a string representation in dd-mm-yy format. 
string Date::getDateString() const { // Const as it doesnt modify any member variables.
    return to_string(day) + "-" + to_string(month) + "-" + to_string(year); // to_string converts integer to string form "-" to seperate day and month. '+' combines each into a larger string.
}

// Responsible: Yifan Xiang (Input/output operator overloading
// Non-member overload of output stream operator, to easly print Date objects.
ostream& operator<<(ostream& os, const Date& d){ // ostream& os, so the original stream state is not modified. const Date& d, to only read a reference to the Date object being printed. 
    os << d.getDateString(); // Insert the date string into output stream.
    return os; // Returns the ouput stream.
}

// Input stream overload to read Date in dd-mm-yy format
istream& operator>>(istream& is, Date& d){ // istream& is, is a reference to input stream. Date& d, is a non-const reference to a Date object. 
    int dd, mm, yy; // Initailise day month and year.
    char dash1, dash2; // Itialise dash characters.
    if (is >> dd >> dash1 >> mm >> dash2 >> yy){ // Read attempt for day dash, month dash, year,
        d = Date(dd, mm, yy); // Only assign to 'd' if all parts were successfully read.
    }
    return is; // Return the stream.
}
