#include <iostream>
#include <string>

using namespace std;

// ******* Date class for composition ****************************
class Date{

    private:




    public:



};

// Abstract Base class Person
class Person {
protected:
    string name;
    int age;
    string dateOfBirth;

public:
    Person(const string& name, int age, const string& dob) : name(name), age(age), dateOfBirth(dob) {}
    virtual ~Person() {
        cout << "Destroying person object" << endl;
    }

    virtual string getName() const = 0; // Pure virtual function
    virtual int getAge() const = 0; // Pure virtual function
    virtual string getDateOfBirth() const = 0; // Pure virtual function
};

// Driver class inheriting from Person (Inheritance)
class Driver : public Person {
private:
    string team;
    int driver_num;

public:
    Driver(const string& name, int age, const string& dob, const string& team, int driver_num)
        : Person(name, age, dob), team(team), driver_num(driver_num) {}
    ~Driver() {
        cout << "Destroying Driver object" << endl;
    }

    string getName() const override {
        return name;
    }

    int getAge() const override {
        return age;
    }

    string getDateOfBirth() const override {
        return dateOfBirth;
    }

    string getTeam() const {
        return team;
    }

    int getDriverNum() const {
        return driver_num;
    }
};

// Engineer class inheriting from Person (Example of Inheritance)
class Engineer : public Person {
private:
    string team;
    int id;
    string Qualification;

public:
    Engineer(const string& name, int age, const string& dob, const string& team, int id, const string& Qualification)
        : Person(name, age, dob), team(team), id(id), Qualification(Qualification) {}
    ~Engineer() {
        cout << "Destroying the Engineer object" << endl;
    }

    string getName() const override {
        return name;
    }

    int getAge() const override {
        return age;
    }

    string getDateOfBirth() const override {
        return dateOfBirth;
    }

    string getTeam() const {
        return team;
    }

    int getId() const {
        return id;
    }

    string getQualification() const {
        return Qualification;
    }
};

int main() {
    Driver driver("Michael Schumacher", 30, "1995-05-15", "Ferrari", 7);
    Engineer engineer("Fernando Alonso", 40, "1985-08-25", "McLaren", 14, "Mechanical Engineering");

    cout << "Driver: " << driver.getName() << ", Age: " << driver.getAge() << ", DOB: " << driver.getDateOfBirth()
         << ", Team: " << driver.getTeam() << ", Driver Number: " << driver.getDriverNum() << endl;
    cout << "Engineer: " << engineer.getName() << ", Age: " << engineer.getAge() << ", DOB: " << engineer.getDateOfBirth()
         << ", Team: " << engineer.getTeam() << ", ID: " << engineer.getId() << ", Qualification: " << engineer.getQualification() << endl;

    return 0;
}