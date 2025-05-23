// Responsible: Eamon Mahrooq
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
        static int carCount; // Static member carCount, responsible: Adam Bance
    
    public:
        Car(const string& mk, const string& mdl, const string& col, int maxSp, const string& engTyp,  int hp);
                                                                                 // Constructor has parameters of Engine
        // Vehicle overrides
        string getMake() const override;
        string getModel() const override;
        string getEngine() const override;
        string getType() const override;
        void showCarInfo() const override;

        // Get the car count
        // Responsible: Adam Bance
        static int getCarCount();
};

#endif // CAR_H
