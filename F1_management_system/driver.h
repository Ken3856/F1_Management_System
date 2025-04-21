// driver.h
#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "person.h"
#include "vehicle.h"

using namespace std;

class Driver : public Person {

    private:
        string driverId;
        string team;
        int driverNumber;
        Vehicle* assignedVehicle = nullptr;

        static int driverCount;
    
    public:
        Driver(const string& name, int age, const Date& dob, string driverId, const string& team, int driverNumber);
        ~Driver();

        void setAssignedVehicle(Vehicle* v);

        string getDriverId() const;
        int getDriverNumber() const;
        string getTeam() const;
        Vehicle* getAssignedVehicle() const;
        static int getDriverCount();

        void displayInfo() const override;

};

#endif // DRIVER_H
