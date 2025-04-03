#include <iostream>
#include <string>
using namespace std;

class Person {
protected: // Attributes only accessible by abstract class Person and derived classes (like Driver)
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

class Driver : public Person { //Driver class inherits from Person
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

	void displayInfo() const override { //Override pure virtual
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
	int numDrivers;
	cout << "Enter number of drivers: ";
	cin >> numDrivers;

	Driver* drivers[numDrivers];

	for (int i = 0; i < numDrivers; ++i) {
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

	return 0;
}