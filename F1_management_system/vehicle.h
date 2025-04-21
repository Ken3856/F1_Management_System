// vehicle.h
#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

class Driver;  // forward

// Abstract Base Class for inheritance and polymorphism
class Vehicle {
protected:
    string make;
    string model;
    string color;
    int maxSpeed;
    static int vehicleCount;
    Driver* assignedDriver = nullptr; // Binary Association

public:
    Vehicle(const string& make, const string& model, const string& color, int maxSpeed);
    virtual ~Vehicle();

    // pure‐virtual interface
    virtual string getMake()  const = 0;
    virtual string getModel() const = 0;
    virtual string getEngine() const = 0; // Polymorphic behaviour: pure virtual functions where the implementation will be in the derived class(es)
    virtual string getType()   const = 0;
    virtual void showCarInfo() const = 0;

    void assignDriver(Driver* d);
    Driver* getAssignedDriver() const;

    string getColor() const;
    int getMaxSpeed() const;

    static int displayVehicleCount();
};

#endif // VEHICLE_H
