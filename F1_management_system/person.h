#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "date.h"

using namespace std;

// ************ Abstract Base Class: Person ************
class Person{
    protected:
        string name;
        int age;
        Date dateOfBirth;  // Composition: a Person "has-a" Date of birth
    
    public:
        // Constructor
        Person(const string& n, int a, const Date& dob);
    
        // Destructor
        virtual ~Person();
    
        // Getters
        string getName() const;
        int getAge() const;
        string getDateOfBirth() const;

        virtual void displayInfo() const = 0; // Pure virtual function to be overriden in derived classes
    };

    #endif // PERSON_H