// engineer.h
// Responsible: Eamon Mahrooq (inheritance from Person)
#ifndef ENGINEER_H
#define ENGINEER_H

#include <string>
#include "person.h"

using namespace std;

// Engineer inherits from Person
class Engineer : public Person {
private:
    string engID;
    string qualification;
    static int engineerCount;

public:
    // Constructor & Destructor
    Engineer(const string& name, int age, const Date& dob, const string& ID, const string& qual);
    ~Engineer();

    // Getters
    const string& getId() const;
    const string& getQualification() const;
    
    static int getEngineerCount();

    // Override display function
    void displayInfo() const override;
};

#endif // ENGINEER_H

