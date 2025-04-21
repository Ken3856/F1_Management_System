// Responsible: Eamon Mahrooq
// driver.h
#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "person.h"
#include "vehicle.h"

using namespace std;

//Driver class inherits from Person
class Driver : public Person {

    private:
        string driverId;
        string team;
        int driverNumber;
        Vehicle* assignedVehicle = nullptr; // Responsible: Adam Bance

        static int driverCount;
    
    public:
        Driver(const string& name, int age, const Date& dob, string driverId, const string& team, int driverNumber);
                    // Inherited from person
        ~Driver();

        void setAssignedVehicle(Vehicle* v); // Responsible: Adam Bance

        // Getters
        string getDriverId() const;
        int getDriverNumber() const;
        string getTeam() const;
        static int getDriverCount();

        Vehicle* getAssignedVehicle() const; // Responsible: Adam Bance

        void displayInfo() const override;

};

#endif // DRIVER_H
