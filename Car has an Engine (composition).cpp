#include <iostream>
#include <string>
using namespace std;

class Engine {
private:
    string type;
    int horsepower;

public:
    Engine(string type, int horsepower) : type(type), horsepower(horsepower) {}

    void showEngineInfo() const {
        cout << "Engine Type: " << type << ", Horsepower: " << horsepower << endl;
    }
};

class Car {
private:
    string model;
    Engine engine; // Car has an Engine
    static int carCount; // Static member carCount

public:
    Car(string model, string engineType, int horsepower)
        : model(model), engine(engineType, horsepower) {carCount++;} // Increment carCount whenever an object is created
                        // Constructor has parameters of Engine

    void showCarInfo() const {
        cout << "Car Model: " << model << endl;
        engine.showEngineInfo(); // Use engine object to access the showEngineInfo function
    }
    
    // Get the car count
    static int getCarCount() {
        return carCount;
    }
};

// Initialize static member
int Car:: carCount = 0;

// For testing purposes
int main() {
    int numCars;
    cout << "Enter number of cars: ";
    cin >> numCars;

    Car* cars[numCars];

    for (int i = 0; i < numCars; i++) { // Prompt to enter details based on the number of cars
        string model, engineType;
        int horsepower;

        cout << "Enter car model, engine type, and horsepower: ";
        cin >> model >> engineType >> horsepower;

        cars[i] = new Car(model, engineType, horsepower);
    }

    cout << "\nCar Details:\n";
    for (int i = 0; i < numCars; i++) { 
        cars[i]->showCarInfo();
        delete cars[i];
    }
    
    cout << "\nTotal Registered Cars: " << Car::getCarCount() << endl; // Print car count

    return 0;
}
