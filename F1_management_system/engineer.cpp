// engineer.cpp
// Responsible: Eamon Mahrooq (inheritance from Person)
#include "engineer.h"
#include <iostream>

int Engineer::engineerCount = 0; // Responsible: Adam Bance

// Inherits from Person
Engineer::Engineer(const string& name, int age, const Date& dob, const string& ID, const string& qual)
    : Person(name, age, dob), engID(ID), qualification(qual){
    ++engineerCount;
}

Engineer::~Engineer(){
    --engineerCount;
    cout << "Destroying Engineer object" << endl;
}

const string& Engineer::getId() const{
    return engID;
}

const string& Engineer::getQualification() const{
    return qualification;
}

// Responsible: Adam Bance
int Engineer::getEngineerCount(){
    return engineerCount;
}

void Engineer::displayInfo() const{
    cout << "Name: "          << getName() << "\n"
         << "Age: "           << getAge() << "\n"
         << "Date of Birth: " << getDateOfBirth() << "\n"
         << "Engineer ID: "   << getId() << "\n"
         << "Qualification: " << getQualification() << endl;
}
