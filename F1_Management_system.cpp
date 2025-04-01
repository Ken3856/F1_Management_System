// Fully working refactored program with all logic implemented using classes and inheritance
// Version 2.0

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

void displayBanner(){
    system("CLS");
    cout << R"(
        _________   __  ___                                             __ 
       / ____<  /  /  |/  /___ _____  ____ _____ _____ ___  ___  ____  / /_
      / /_   / /  / /|_/ / __ `/ __ \/ __ `/ __ `/ __ `__ \/ _ \/ __ \/ __/
     / __/  / /  / /  / / /_/ / / / / /_/ / /_/ / / / / / /  __/ / / / /_  
    /_/____/_/  /_/  /_/\__,_/_/ /_/\__,_/\__, /_/ /_/ /_/\___/_/ /_/\__/  
      / ___/__  _______/ /____  ____ ___ /____/                            
      \__ \/ / / / ___/ __/ _ \/ __ `__ \                                  
     ___/ / /_/ (__  ) /_/  __/ / / / / /                                  
    /____/\__, /____/\__/\___/_/ /_/ /_/                                   
         /____/                                                             
        )" << '\n';
}

void pauseAndClear(){
    cout << "\nPress Enter to return to the menu...";
    cin.ignore();
    cin.get();
    system("CLS");

}

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


// --- ADMIN MAIN MENU ---
// 1. Personnel Management                   // Inheritance and polymorphism, Abstract base classes, Basic class design, Basic association
// 2. Race Management                        // Queue (linked list), Composition, Dependency
// 3. Team Management                        // Basic association, Qualified association, Association class
// 4. Vehicle Management                     // Basic class design, Composition, Association class, Qualified association
// 5. Performance & Stats                    // Operator overloading (member and non-member), Polymorphism, Basic class
// 6. System Info & Sample Data              // Abstract base/concrete classes, Integration testing, Best code/novel solution
// 7. Exit                                   



// // --- PERSONNEL MANAGEMENT ---
// 1. Register New Driver                    // Basic class with constructors and accessors, Inheritance from abstract base class
// 2. View All Drivers                       // Polymorphism (viewing drivers through base class pointer/reference)
// 3. Search Driver by Name                  // Accessor methods, Basic string comparison
// 4. Register New Engineer                  // Basic class, Abstract base + inheritance (Engineer derived from Person)
// 5. View All Engineers                     // Polymorphism example (viewing multiple concrete derived types)
// 6. Search Engineer by Team                // Basic association (Engineer → Team)
// 7. Return to Main Menu                    // 


// // --- RACE MANAGEMENT ---
// 1. Schedule New Race                      // Composition (using a Date object), Basic class with constructors
// 2. View Scheduled Races (Queue)           // Queue implemented via linked list
// 3. Enter Race Results                     // Composition (LapTime inside Race), Dependency (Race → Results)
// 4. View Race Results                      // Shows dependent relationship (Race object affects Leaderboard/Stats)
// 5. Delete Past Race from Queue            // Linked list manipulation (Queue)
// 6. Return to Main Menu                    // 


// // --- TEAM MANAGEMENT ---
// 1. Create New Team                        // Basic class, Association with Drivers and Engineers
// 2. View All Teams                         // Association relationships displayed
// 3. Assign Driver to Team                  // Basic association (Team ↔ Driver)
// 4. Assign Engineer to Team                // Basic association (Team ↔ Engineer)
// 5. Search Team by Name                    // Qualified association (using team name as qualifier)
// 6. Return to Main Menu                    // 


// // --- VEHICLE MANAGEMENT --- (maybe add a base class here for a F1 car and a test car for inheritance)
// 1. Add New Vehicle                        // Basic class with accessors and constructors, Composition (engine specs)
// 2. View All Vehicles                      // Association class if vehicle is linked to driver
// 3. Assign Vehicle to Driver               // Association class (Vehicle ↔ Driver), Composition
// 4. Search Vehicle by Make or Driver       // Qualified association (search by attribute like make or driver name)
// 5. Return to Main Menu                    // 


// // --- PERFORMANCE & STATS ---
// 1. View Lap Times (Reverse Order)         // Composition (LapTime), Recursive display, Optional sorting logic
// 2. View Leaderboard                       // Basic class, Operator overloading (non-member, for comparisons or sorting)
// 3. View Driver Performance Stats          // Operator overloading (as member function, e.g., compare two stats)
// 4. Compare Driver Stats                   // Polymorphism (different behavior for different driver objects), Overloading
// 5. Return to Main Menu                    // 


// // --- SYSTEM INFO & SAMPLE DATA ---       // **Might not use this**
// 1. View Sample Driver & Engineer  
// 2. Load Sample Data  
// 3. Export Current Data to File  
// 4. View Application Info / Credits  
// 5. Return to Main Menu




// Display menu ********** Delete
// void displayMenu() {

//     cout << R"(
//         _________   __  ___                                             __ 
//        / ____<  /  /  |/  /___ _____  ____ _____ _____ ___  ___  ____  / /_
//       / /_   / /  / /|_/ / __ `/ __ \/ __ `/ __ `/ __ `__ \/ _ \/ __ \/ __/
//      / __/  / /  / /  / / /_/ / / / / /_/ / /_/ / / / / / /  __/ / / / /_  
//     /_/____/_/  /_/  /_/\__,_/_/ /_/\__,_/\__, /_/ /_/ /_/\___/_/ /_/\__/  
//       / ___/__  _______/ /____  ____ ___ /____/                            
//       \__ \/ / / / ___/ __/ _ \/ __ `__ \                                  
//      ___/ / /_/ (__  ) /_/  __/ / / / / /                                  
//     /____/\__, /____/\__/\___/_/ /_/ /_/                                   
//          /____/                                                             
//         )" << '\n';

//     cout << "\nMenu:\n";
//     cout << "1. Add Race\n";
//     cout << "2. Register Driver\n";
//     cout << "3. Display Lap Times\n";
//     cout << "4. Show Leaderboard\n";
//     cout << "5. Show Sample Driver and Engineer\n";
//     cout << "6. Exit\n";
//     cout << "Enter your choice: ";
// }



void personnelManagement(){
    cout << "Personnel Management selected" << endl;

    int choice;
    do{
        displayBanner();
        cout << " 1. Register New Driver " << endl;
        cout << " 2. View All Drivers  " << endl;
        cout << " 3. Search Driver by Name " << endl;
        cout << " 4. Register New Engineer " << endl;
        cout << " 5. View All Engineers " << endl;
        cout << " 6. Search Engineer by Team " << endl;
        cout << " 7. Return to Main Menu " << endl;
        cin >> choice;

        switch(choice){
            case 1:
                cout << "Registering new drivers...." << endl;
                pauseAndClear();
                break;
            case 2:
                cout << "View All Drivers...." << endl; 
                break;
            case 3:
                cout << "Searching Drivers by Name...." << endl; 
                break;
            case 4:
                cout << "Registering new Engineers....." << endl; 
                break;
            case 5:
                cout << "View All Engineers....." << endl; 
                break;
            case 6:
                cout << "Search Engineers by Team....." << endl; 
                break;
            case 7:
                cout << "Returning to Main Menu....." << endl; 
                break;
            default:
                cout << "Invalid choice. Please select an option between 1 and 7" << endl;
                break;
        }
    } while(choice != 7);
}

void raceManagement(){
    displayBanner();
    cout << "Race Management selected" << endl;
}

void teamManagement(){
    displayBanner();
    cout << "Team Management selected" << endl;
}

void vehicleManagement(){
    displayBanner();
    cout << "Vehicle Management selected" << endl;
}

void performanceStats(){
    displayBanner();
    cout << "Performance Management selected" << endl;
}





void mainMenu(){
    displayBanner();
    int choice;
    do{
        cout << "Main Menu" << endl;
        cout << "1. Personnel Management" << endl; 
        cout << "2. Race Management" << endl;                       
        cout << "3. Team Management" << endl;                       
        cout << "4. Vehicle Management" << endl;                     
        cout << "5. Performance & Stats" << endl;                                
        cout << "6. Exit" << endl;
        cout << "Enter an option: ";
        cin >> choice;

        switch(choice){
            case 1:
                personnelManagement();
                break;
            case 2:
                raceManagement();
                break;
            case 3:
                teamManagement();
                break;
            case 4:
                vehicleManagement();
                break;
            case 5:
                performanceStats();
                break;
            case 6:
                cout << "Exiting program" << endl;
                break;
            default:
                cout << "Invalid choice. Please select an option between 1 and 6" << endl;
                break;
        }
    } while(choice != 6);
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

int main(){
    mainMenu();
   
    return 0;
}