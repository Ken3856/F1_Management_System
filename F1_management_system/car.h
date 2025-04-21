// car.h
#ifndef CAR_H
#define CAR_H

#include <string>
#include "vehicle.h"
#include "engine.h"

using namespace std;

class Driver;

// Car inherits from Vehicle
// Car has an Engine (composition)
class Car : public Vehicle{
    private:
        Engine engine;
        int horsepower;
        static int carCount; // Static member carCount
    
    public:
        Car(const string& mk, const string& mdl, const string& col, int maxSp, const string& engTyp,  int hp);
    
        // Vehicle overides
        string getMake() const override;
        string getModel() const override;
        string getEngine() const override;
        string getType() const override;
        void showCarInfo() const override;

        // Get the car count
        static int getCarCount();
};

#endif // CAR_H
