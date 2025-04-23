// Responsible: Yifan Xiang (creating the abstract base class)
// vehicle.cpp
#include "vehicle.h"
#include "driver.h"    // for Driver::setAssignedVehicle()

// Responsible: Adam Bance
// Initialize static count
int Vehicle::vehicleCount = 0;

Vehicle::Vehicle(const string& mk, const string& mdl, const string& col, int ms)
  : make(mk), model(mdl), color(col), maxSpeed(ms), assignedDriver(nullptr){
    ++vehicleCount;                                 // Responsible: Adam Bance
                                                    
}

Vehicle::~Vehicle(){
    --vehicleCount;
}

// Assign a Vehicle to a Driver
// Responsible: Adam Bance
void Vehicle::assignDriver(Driver* d){
    assignedDriver = d;
    if (d){
        d->setAssignedVehicle(this);
    }
}
// Get the Driver that was assigned the Vehicle
// Responsible: Adam Bance
Driver* Vehicle::getAssignedDriver() const{
    return assignedDriver;
}

string Vehicle::getColor() const{
    return color;
}

int Vehicle::getMaxSpeed() const{
    return maxSpeed;
}

// Responsible: Adam Bance
int Vehicle::displayVehicleCount(){
    return vehicleCount;
}
