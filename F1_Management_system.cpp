// Fully working refactored program with all logic implemented using classes and inheritance

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

// ******* Date class for composition (To be expanded if needed) ****************************
class Date {
private:
    int day, month, year;

public:
    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    string getDateString() const {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }
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
    virtual string getName() const = 0;
    virtual int getAge() const = 0;
    virtual string getDateOfBirth() const = 0;
};

// Driver class (Inheritance from Person)
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
    string getName() const override { return name; }
    int getAge() const override { return age; }
    string getDateOfBirth() const override { return dateOfBirth; }
    string getTeam() const { return team; }
    int getDriverNum() const { return driver_num; }
};

// Engineer class (Inheritance from Person)
class Engineer : public Person {
private:
    string team;
    int id;
    string qualification;

public:
    Engineer(const string& name, int age, const string& dob, const string& team, int id, const string& qualification)
        : Person(name, age, dob), team(team), id(id), qualification(qualification) {}
    ~Engineer() {
        cout << "Destroying the Engineer object" << endl;
    }
    string getName() const override { return name; }
    int getAge() const override { return age; }
    string getDateOfBirth() const override { return dateOfBirth; }
    string getTeam() const { return team; }
    int getId() const { return id; }
    string getQualification() const { return qualification; }
};

// Race class
class Race {
private:
    string location;
    string date;
    int courseID;

public:
    Race() {}
    Race(string loc, string d, int cid) : location(loc), date(d), courseID(cid) {}

    string getLocation() const { return location; }
    string getDate() const { return date; }
    int getCourseID() const { return courseID; }

    void setLocation(string loc) { location = loc; }
    void setDate(string d) { date = d; }
    void setCourseID(int id) { courseID = id; }
};

// Leaderboard class
class Leaderboard {
private:
    string firstName;
    int points;
    int wins;
    int podium;

public:
    Leaderboard() {}
    Leaderboard(string name, int pts, int w, int p) : firstName(name), points(pts), wins(w), podium(p) {}

    string getName() const { return firstName; }
    int getPoints() const { return points; }
    int getWins() const { return wins; }
    int getPodium() const { return podium; }

    void setName(string name) { firstName = name; }
    void setPoints(int pts) { points = pts; }
    void setWins(int w) { wins = w; }
    void setPodium(int p) { podium = p; }
};

// Statistics class
class Statistics {
private:
    string driverName;
    string team;
    float bestTime;
    int ranking;

public:
    Statistics() {}
    Statistics(string name, string t, float bt, int r) : driverName(name), team(t), bestTime(bt), ranking(r) {}

    string getDriverName() const { return driverName; }
    string getTeam() const { return team; }
    float getBestTime() const { return bestTime; }
    int getRanking() const { return ranking; }

    void setDriverName(string name) { driverName = name; }
    void setTeam(string t) { team = t; }
    void setBestTime(float time) { bestTime = time; }
    void setRanking(int r) { ranking = r; }
};

// LapTime class
class LapTime {
private:
    string name;
    string make;
    float timeLaps;

public:
    LapTime() {}
    LapTime(string n, string m, float t) : name(n), make(m), timeLaps(t) {}

    string getName() const { return name; }
    string getMake() const { return make; }
    float getTimeLaps() const { return timeLaps; }

    void setName(string n) { name = n; }
    void setMake(string m) { make = m; }
    void setTimeLaps(float t) { timeLaps = t; }

    void display() const {
        cout << name << " " << make << " - " << timeLaps << " laps" << endl;
    }
};

// RaceNode class for queue
class RaceNode {
public:
    Race data;
    RaceNode* next;

    RaceNode(Race r) : data(r), next(nullptr) {}
};

// Display menu
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add Race\n";
    cout << "2. Register Driver\n";
    cout << "3. Display Lap Times\n";
    cout << "4. Show Leaderboard\n";
    cout << "5. Show Sample Driver and Engineer\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

// Add race to queue
void addRaceToQueue(RaceNode*& head, Race r) {
    RaceNode* newNode = new RaceNode(r);
    if (!head) head = newNode;
    else {
        RaceNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

// Recursive lap display
void displayLapsRecursive(LapTime* laps, int index) {
    if (index < 0) return;
    laps[index].display();
    displayLapsRecursive(laps, index - 1);
}

int main() {
    int choice;
    RaceNode* raceHead = nullptr;
    static int nextID = 1;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string loc, date;
            int cid;
            cout << "Enter location: "; getline(cin, loc);
            cout << "Enter date: "; getline(cin, date);
            cout << "Enter course ID: "; cin >> cid;
            Race r(loc, date, cid);
            addRaceToQueue(raceHead, r);
            cout << "Race added.\n";
        }
        else if (choice == 2) {
            string name, team;
            cout << "Enter driver's name: "; getline(cin, name);
            cout << "Enter team: "; getline(cin, team);
            Driver d(name, 30, "1995-05-15", team, nextID++);
            cout << "Driver registered: " << d.getName() << ", Team: " << d.getTeam() << ", Number: " << d.getDriverNum() << endl;
        }
        else if (choice == 3) {
            ifstream in("lapResultsIn.txt");
            if (!in) { cout << "Lap file not found.\n"; continue; }
            int lapSize;
            in >> lapSize;
            LapTime* laps = new LapTime[lapSize];
            for (int i = 0; i < lapSize; ++i) {
                string name, make;
                float t;
                in >> name >> make >> t;
                laps[i] = LapTime(name, make, t);
            }
            cout << "\nLap times in reverse:\n";
            displayLapsRecursive(laps, lapSize - 1);
            delete[] laps;
        }
        else if (choice == 4) {
            ifstream in("leaderIn.txt");
            int size;
            in >> size;
            Leaderboard* lb = new Leaderboard[size];
            for (int i = 0; i < size; ++i) {
                string name; int pts, w, p;
                in >> name >> pts >> w >> p;
                lb[i] = Leaderboard(name, pts, w, p);
            }
            cout << "Leaderboard:\n";
            for (int i = 0; i < size; ++i)
                cout << lb[i].getName() << " - " << lb[i].getPoints() << " points\n";
            delete[] lb;
        }
        else if (choice == 5) {
            Driver sampleDriver("Michael Schumacher", 30, "1995-05-15", "Ferrari", 7);
            Engineer sampleEngineer("Fernando Alonso", 40, "1985-08-25", "McLaren", 14, "Mechanical Engineering");

            cout << "Driver: " << sampleDriver.getName() << ", Age: " << sampleDriver.getAge()
                 << ", DOB: " << sampleDriver.getDateOfBirth() << ", Team: " << sampleDriver.getTeam()
                 << ", Number: " << sampleDriver.getDriverNum() << endl;

            cout << "Engineer: " << sampleEngineer.getName() << ", Age: " << sampleEngineer.getAge()
                 << ", DOB: " << sampleEngineer.getDateOfBirth() << ", Team: " << sampleEngineer.getTeam()
                 << ", ID: " << sampleEngineer.getId() << ", Qualification: " << sampleEngineer.getQualification() << endl;
        }

    } while (choice != 6);

    while (raceHead) {
        RaceNode* temp = raceHead;
        raceHead = raceHead->next;
        delete temp;
    }
    return 0;
}
