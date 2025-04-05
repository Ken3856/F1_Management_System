// Eamon
/*
Inheritance between Vehicle and Car (Car inherits from Vehicle)
I only implemented Runtime Polymorphism because:
    For Compile Time Polymorphism you need to implement (whoever has the task to do so):
		- Operator Overloading on the derived classes of Vehicle
*/

#include<iostream>
#include<string>
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    string color;
    int maxSpeed;
    static int vehicleCount;

public:
    Vehicle(string make, string model, string color, int maxSpeed)
        : make(make), model(model), color(color), maxSpeed(maxSpeed) { vehicleCount++; }

    virtual string getMake() const = 0;
    virtual string getModel() const = 0;
    virtual string getEngine() const = 0; // Polymorphic behaviour: pure virtual functions where the implementation will be in the derived class(es)
    virtual string getType() const = 0;

    virtual ~Vehicle() {}

    
    string getColor() const {
        return color;
    }

    int getMaxSpeed() const {
        return maxSpeed;
    }

    static int displayVehicleCount() {
        return vehicleCount;
    }
};

int Vehicle::vehicleCount = 0;

class Car : public Vehicle {
public:
    Car(string make, string model, string color, int maxSpeed)
        : Vehicle(make, model, color, maxSpeed) {}

    string getMake() const override {
        return make;
    }

    string getModel() const override {
        return model;
    }

    string getEngine() const override {
        return "1.5-liter three-cylinder petrol";
    }

    string getType() const override {
        return "Hatchback";
    }
};

int main() {
    Car Vehicle1("Toyota", "Yaris", "Red", 109);  // Create a Car object on the stack
    
    // Runtime polymorphism where a pointer of type abstract base class is pointing to the concrete derived class(es)
    Vehicle* v = &Vehicle1;  // Pointer to point to the address of the new object
    cout << "Vehicle details: " 
    << v->getMake() << " " 
    << v->getModel() << ". "    // Polymorphic behaviour: change the address of the function that the pointer is pointing to
    << v->getEngine() << endl;
    
    cout << "Type: " << v->getType() << endl;
    
    cout << "Vehicle object count: " << Vehicle::displayVehicleCount() << endl; // Print the vehicle count

    return 0;
}
