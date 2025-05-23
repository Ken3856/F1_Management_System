// Eamon Mahrooq
// I implemented inheritance, polymorphism, and composition
// I added static variables to keep count of the number of objects

#include <iostream>
#include <string>
using namespace std;

// Abstract Base Class for inheritance and polymorphism
class Vehicle {
protected:
    string make;
    string model;
    string color;
    int maxSpeed;
    static int vehicleCount;

public:
    Vehicle(string make, string model, string color, int maxSpeed)
        : make(make), model(model), color(color), maxSpeed(maxSpeed) { vehicleCount++; } // Increment the count whenever a Vehicle object is created

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

    virtual void showCarInfo() const = 0;

    static int displayVehicleCount() {
        return vehicleCount;
    }
};

int Vehicle::vehicleCount = 0;

// Engine class
class Engine {
private:
    string type;
    int horsepower;

public:
    Engine(string type, int horsepower) : type(type), horsepower(horsepower) {}

    // Getters
    string getType() const {
        return type;
    }

    int getHorsepower() const {
        return horsepower;
    }
    
    void showEngineInfo() const {
        cout << "Engine Type: " << type << ", Horsepower: " << horsepower << endl;
    }
};

// Car inherits from Vehicle
// Car has an Engine (composition)
class Car : public Vehicle {
private:
    Engine engine;
    int horsepower;
    static int carCount; // Static member carCount

public:
    Car(string make, string model, string color, int maxSpeed, string engineType, int horsepower)
        : Vehicle(make, model, color, maxSpeed), engine(engineType, horsepower) { carCount++; }

    string getMake() const override {
        return make;
    }

    string getModel() const override {
        return model;
    }

    string getEngine() const override {
        return engine.getType() + " with " + to_string(engine.getHorsepower()) + " HP"; // Convert horsepower to string to concatenate with the strings
    }

    string getType() const override {
        return "Hatchback";
    }

    void showCarInfo() const override {
        cout << "Car Model: " << model << endl;
        cout << "Engine Type: " << engine.getType() 
        << ", Horsepower: " << engine.getHorsepower() << endl;
        cout << "Color: " << color << endl;
    }

    /*
    void showCarInfo() const {
        cout << "Car Model: " << model << endl;
        engine.showEngineInfo();  // Display engine details
    }
    */

    // Get the car count
    static int getCarCount() {
        return carCount;
    }
};

int Car::carCount = 0;

// Base class for inheritance
class Person {
protected: // The attributes are only accessible by abstract class Person and derived classes (like Driver)
	string name;
	int age;

public:
    // Constructor
	Person(string name, int age) : name(name), age(age) {}
	virtual void displayInfo() const = 0; // Pure virtual function to be overriden in derived classes

    // Getters
	string getName() const { // Const ensures that the function won't modify the object, in this case it's just collecting information from the object
		return name;
	}
	int getAge() const {
		return age;
	}

    // Destructor
	virtual ~Person() {}
};

// Driver class inherits from Person
class Driver : public Person { 
private:
	int driverId;
	string team;
	int driverNumber;
	static int driverCount;

public:
	Driver(string name, int age, int driverId, string team, int driverNumber)
		: Person(name, age), driverId(driverId), team(team), driverNumber(driverNumber) {driverCount++;}
         // Inherited from person
         
	int getDriverId() const {
		return driverId;
	}

	void displayInfo() const override { // Override pure virtual
		cout << "Driver: " << name << ", Age: " << age
		     << ", ID: " << driverId << ", Team: " << team
		     << ", Number: " << driverNumber << endl;
	}
	
	// Static method to get the number of drivers
    static int getDriverCount() {
        return driverCount++;
    }
    
    ~Driver() {
    }
};

int Driver::driverCount = 0;

// Main for testing purposes
int main() {
// Registerd Cars
    int numCars;
    cout << "Enter number of cars: ";
    cin >> numCars;

    Car* cars[numCars];

    for (int i = 0; i < numCars; i++) { // Prompt to enter details based on the number of cars
        // Initialize variables to allow dynamic creation of objects based on user input
        string make, model, color, engineType;
        int maxSpeed, horsepower;

        cout << "Enter make, model, color, max speed, engine type, and horsepower: ";
        cin >> make >> model >> color >> maxSpeed >> engineType >> horsepower;

        cars[i] = new Car(make, model, color, maxSpeed, engineType, horsepower);
    }

    cout << "\nCar Details:\n";
    for (int i = 0; i < numCars; i++) {
        Vehicle* v = cars[i];
        v->showCarInfo(); // Show info
        cout << "Make: " << v->getMake() << ", Model: " << v->getModel()
             << ", Engine: " << v->getEngine() << ", Type: " << v->getType() << endl;
        delete cars[i];
    }

    cout << "\nTotal Registered Cars: " << Car::getCarCount() << endl; // Print car count
    cout << "Vehicle object count: " << Vehicle::displayVehicleCount() << endl; // Print vehicle count
//------------------------------------------------------------------------------------------------
// Registered Drivers
    int numDrivers;
	cout << "\nEnter number of drivers: ";
	cin >> numDrivers;

	Driver* drivers[numDrivers];

	for (int i = 0; i < numDrivers; i++) {
		string name, team;
		int age, driverId, driverNumber;

		cout << "Enter name, age, ID, team, and number: ";
		cin >> name >> age >> driverId >> team >> driverNumber;

		drivers[i] = new Driver(name, age, driverId, team, driverNumber);
	}

	cout << "\nRegistered Drivers:\n";
	for (int i = 0; i < numDrivers; i++) {
		drivers[i]->displayInfo();
		delete drivers[i];
	}
	
	cout << "\nTotal Drivers Registered: " << Driver::getDriverCount() << endl; // Print number of registered racers
//-------------------------------------------------------------------------------------------------
    return 0;
}
