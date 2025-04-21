#include "person.h"
#include <iostream>

using namespace std;

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
    return dateOfBirth.getDateString();
}