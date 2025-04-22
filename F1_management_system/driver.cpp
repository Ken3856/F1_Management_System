// driver.cpp
// Responsible: Eamon Mahrooq
#include "driver.h"
#include <iostream>

// Static Driver object count
int Driver::driverCount = 0; // Responsible: Adam Bance

// Constructor
Driver::Driver(const string& name, int age, const Date& dob, string dID, const string& t, int dnum)
                : Person(name, age, dob), driverId(dID), team(t), driverNumber(dnum), assignedVehicle(nullptr){
                    ++driverCount;                                                    // Responsible: Adam Bance
                  // Driver inherits from Person
                }

Driver::~Driver(){
    --driverCount;
    cout << "Destroying Driver object\n";
}

// Getters
string Driver::getDriverId() const{
    return driverId;
}

int Driver::getDriverNumber() const{
    return driverNumber;
}

string Driver::getTeam() const{
    return team;
}

void Driver::setAssignedVehicle(Vehicle* v){
    assignedVehicle = v;
}

Vehicle* Driver::getAssignedVehicle() const{
    return assignedVehicle;
}

void Driver::displayInfo() const{
    cout << "Driver Name: "   << getName() << "\n"
         << "Age: "           << getAge()  << "\n"
         << "Date of Birth: " << getDateOfBirth() << "\n"
         << "Driver ID: "     << getDriverId() << "\n"
         << "Team: "          << team << "\n"
         << "Driver Number: " << driverNumber << endl;

    // // Responsible: Adam Bance
    if (assignedVehicle){
        cout << "Assigned Vehicle: " << assignedVehicle->getMake() << " " << assignedVehicle->getModel() << endl;
    } else{
        cout << "Assigned Vehicle: None" << endl;
    }
}

// Responsible: Adam Bance
int Driver::getDriverCount(){
    return driverCount;
}
