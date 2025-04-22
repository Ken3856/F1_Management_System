// Responsible: Eamon Mahrooq
#include "person.h"
#include <iostream>

using namespace std;

// Person has a date of birth (Date) (composition)
Person::Person(const string& n, int a, const Date& dob) : name(n), age(a), dateOfBirth(dob) {}

Person::~Person(){
    cout << "Destroying person object" << endl;
}

string Person::getName() const{
    return name;
}

int Person::getAge() const{
    return age;
}

string Person::getDateOfBirth() const{
    return dateOfBirth.getDateString(); // Return date of birth as a string
}
