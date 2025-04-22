// car.cpp
// Responsible: Eamon Mahrooq
#include "car.h"
#include "driver.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Initialize static member
// Responsible: Adam Bance
int Car::carCount = 0;

// Constructor
Car::Car(const string& make, const string& model,const string& color, int maxSpeed, const string& engineType, int hp) 
        : Vehicle(make, model, color, maxSpeed), engine(engineType, hp), horsepower(hp){
        // Car inherits from Vehicle
            ++carCount;
        }

// Getters
string Car::getMake() const{
    return make;
}

string Car::getModel() const{
    return model;
}

string Car::getEngine() const{
    return engine.getType() + " with " + to_string(engine.getHorsepower()) + " HP"; // Convert horsepower to string to concatenate with the other strings
}

string Car::getType() const{
    return "Hatchback";
}

void Car::showCarInfo() const{
    cout << "Car: "         << getMake()  << "\n"
         << "Car Model: "   << getModel() << "\n"
         << "Engine Type: " << engine.getType()
         << "Horsepower: "  << engine.getHorsepower() << " HP) \n"
         << "Color: "       << color << "\n"
         << "Max Speed: "   << maxSpeed << " km/h" << endl;;

    // For driver association
    // Responsible: Adam Bance
    if (assignedDriver){
        cout << "Assigned to Driver:  " << assignedDriver->getName() << endl;;
    } else{
        cout << "No Driver assigned." << endl;
    }
}

// Responsible: Adam Bance
int Car::getCarCount(){
    return carCount;
}
