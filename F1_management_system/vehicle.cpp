// vehicle.cpp
#include "vehicle.h"
#include "driver.h"    // for Driver::setAssignedVehicle()

int Vehicle::vehicleCount = 0;

Vehicle::Vehicle(const string& mk, const string& mdl, const string& col, int ms)
  : make(mk), model(mdl), color(col), maxSpeed(ms), assignedDriver(nullptr){
    ++vehicleCount;
}

Vehicle::~Vehicle(){
    --vehicleCount;
}

void Vehicle::assignDriver(Driver* d){
    assignedDriver = d;
    if (d){
        d->setAssignedVehicle(this);
    }
}

Driver* Vehicle::getAssignedDriver() const{
    return assignedDriver;
}

string Vehicle::getColor() const{
    return color;
}

int Vehicle::getMaxSpeed() const{
    return maxSpeed;
}

int Vehicle::displayVehicleCount(){
    return vehicleCount;
}
