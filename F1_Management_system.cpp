// Version 3.0

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include <unordered_map>
#include <vector> // Used for mapping in qualified association.
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

// ********* Function to clear and refresh screen ********************* 
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
    Date() : day(0), month(0), year(0){}
    Date(int d, int m, int y) : day(d), month(m), year(y){}
    string getDateString() const {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }
};

// ****************** Abstract Base class Person *****************************************
class Person{
protected:
    string name;
    int age;
    string dateOfBirth;

public:
    Person(const string& name, int age, const string& dob) : name(name), age(age), dateOfBirth(dob){}
    virtual ~Person(){
        cout << "Destroying person object" << endl;
    }
    virtual string getName() const = 0;
    virtual int getAge() const = 0;
    virtual string getDateOfBirth() const = 0;
};

// ******************** Driver class (Inheritance from Person) *****************************
class Driver : public Person {
private:
    // string team; // Remove this for qualified asssociation
    int driver_num;

public:
    Driver(const string& name, int age, const string& dob, int driver_num)
        : Person(name, age, dob), driver_num(driver_num) {}
    ~Driver() {
        cout << "Destroying Driver object" << endl;
    }
    string getName() const override { return name; }
    int getAge() const override { return age; }
    string getDateOfBirth() const override { return dateOfBirth; }
    // string getTeam() const { return team; }
    int getDriverNum() const { return driver_num; }
};



// *********** Association class - Kenneth Johnson *******************************

class raceResult{
    private:



    public:
};



// *************** Engineer class (Inheritance from Person) ************************
class Engineer : public Person {
private:
    // string team; // Remove this for quaified association
    int id;
    string qualification;

public:
    Engineer(const string& name, int age, const string& dob, const string& team, int id, const string& qualification)
        : Person(name, age, dob), id(id), qualification(qualification) {}
    ~Engineer() {
        cout << "Destroying the Engineer object" << endl;
    }
    string getName() const override { return name; }
    int getAge() const override { return age; }
    string getDateOfBirth() const override { return dateOfBirth; }
    // string getTeam() const { return team; }
    int getId() const { return id; }
    string getQualification() const { return qualification; }
};

// ************* Team class (Qualified association)- Kenneth Johnson *********************************
class Team {
    public:
        string name;
        unordered_map<string, Driver*> roleToDriverMap; // Quaified association
        vector<Engineer*> engineers;

        Team(string name) : name(name){}
    
        void AssignRoleToDriver(const string& role, Driver* d){
            roleToDriverMap[role] = d;
        }

        Driver* getDriverByRole(const string& role) const{
            auto it = roleToDriverMap.find(role);
            return (it != roleToDriverMap.end()) ? it->second : nullptr;
        }
    
        void addEngineer(Engineer* e) {
            engineers.push_back(e);
        }
    
        void listMembers() const {
            cout << "Drivers in team " << name << ":\n";
            for ( const auto& pair : roleToDriverMap)
                cout << "- " << pair.first << ": " << pair.second->getName() << endl;
    
            cout << "Engineers in team " << name << ":\n";
            for (Engineer* e : engineers)
                cout << "- " << e->getName() << " (" << e->getQualification() << ")\n";
        }
};




unordered_map<string, Team*> teams; // Qualified association map
vector<Driver*> allDrivers;
vector<Engineer*> allEngineers;

//*********** Qualified association ******************** */

void registerDriver(){
    string name, dob, team, role;
    int age, driverNumber;
    cin.ignore();
    cout << "Enter driver name: ";
    getline(cin, name);
    cout << "Enter age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter date of birth: ";
    getline(cin, dob);
    cout << "Enter team (Red, Green, Blue): ";
    getline(cin, team);
    cout << "Enter driver number: ";
    cin >> driverNumber;
    cin.ignore();
    cout << "Enter role (e.g., Main Driver, Reserve Driver): ";
    getline(cin, role);

    Driver* d = new Driver(name, age, dob, driverNumber);
    allDrivers.push_back(d);

    if (teams.find(team) == teams.end()){
        teams[team] = new Team(team);
    }
    teams[team]->AssignRoleToDriver(role, d);

    cout << "Driver registered successfully and assigned role." << endl;
}

void registerEngineer(){
    string name, dob, team, qualification;
    int age, id;
    cin.ignore();
    cout << "Enter Engineer name: ";
    getline(cin, name);
    cout << "Enter age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter date of birth: ";
    getline(cin, dob);
    cout << "Enter team (Red, Green, Blue): ";
    getline(cin, team);
    cout << "Enter ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter qualification: ";
    getline(cin, qualification);

    Engineer* e = new Engineer(name, age, dob, team, id, qualification);
    allEngineers.push_back(e);

    if (teams.find(team) == teams.end()){
        teams[team] = new Team(team);
    }
    teams[team]->addEngineer(e);

    cout << "Engineer registered and added to team successfully!" << endl;
}

void searchDriverByTeamAndRole() {
    string teamName, role;
    cin.ignore();
    cout << "Enter team name (e.g., Red, Green, Blue): ";
    getline(cin, teamName);
    cout << "Enter driver role (e.g., Main Driver, Reserve Driver): ";
    getline(cin, role);

    if (teams.find(teamName) != teams.end()) {
        Driver* found = teams[teamName]->getDriverByRole(role);
        if (found) {
            cout << "Driver found: " << found->getName() << ", Number: " << found->getDriverNum() << endl;
        } else {
            cout << "No driver found for role '" << role << "' in team " << teamName << "." << endl;
        }
    } else {
        cout << "Team not found." << endl;
    }

    pauseAndClear();
}



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



void personnelManagement(){
    int choice;
    do{
        displayBanner();
        cout << "===== Personnel Management Menu =====\n" << endl;
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
                registerDriver();
                pauseAndClear();
                break;
            case 2:
                cout << "View All Drivers...." << endl; 
                break;
            case 3:
                cout << "Searching Drivers by Name...." << endl;
                searchDriverByTeamAndRole();
                pauseAndClear(); 
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
    int choice;
    do{
        displayBanner();
        cout << "==== Race Management Menu ==== \n" << endl;
        cout << " 1. Schedule New Race " << endl;
        cout << " 2. View Schdule Races (Queue) " << endl;
        cout << " 3. Enter race results " << endl;
        cout << " 4. View Race Results " << endl;
        cout << " 5. Delete Past Race From Queue " << endl;
        cout << " 6. Return to Main Menu " << endl;
        cin >> choice;

        switch(choice){
            case 1:
                cout << "==== Schedule New Race ====" << endl;
                break;
            case 2:
                cout << "==== View Race Results ====" << endl;
                break;
            case 3:
                cout << "==== Enter Race Results ====" << endl;
                break;
            case 4:
                cout << "==== View Race Results ====" << endl;
                break;
            case 5:
                cout << "==== Delete Past Race From Queue ====" << endl;
                break;
            case 6:
                cout << "Returning to Main Menu...." << endl;
                break;
            default:
                cout << "Invalid option selected. Please choose an option between 1 and 6." << endl;
        }
    } while(choice != 6);
}

void teamManagement(){
    int choice;
    do{
        displayBanner();
        cout << "==== Team Management Menu ==== \n" << endl;
        cout << " 1. Create New Team " << endl;
        cout << " 2. View All Teams " << endl;
        cout << " 3. Assign Driver to Team " << endl;
        cout << " 4. Search Team by Name " << endl;
        cout << " 5. Return to Main Menu " << endl;
        cin >> choice;

        switch(choice){
            case 1:
                cout << "==== Create New Team ====" << endl;
                break;
            case 2:
                cout << "==== View All Teams ====" << endl;
                break;
            case 3:
                cout << "==== Assign Driver to Team ====" << endl;
                break;
            case 4:
                cout << "==== Search Team by Name ====" << endl;
                break;
            case 5:
                cout << "Returning to Main Menu...." << endl;
                break;
            default:
                cout << "Invalid option selected. Please choose an option between 1 and 5." << endl;
        }
    } while(choice != 5);
}

void vehicleManagement(){
    int choice;
    do{
        displayBanner();
        cout << "==== Vehicle Management Menu ==== \n" << endl;
        cout << " 1. Add New Vehicle " << endl;
        cout << " 2. View All Vehicles " << endl;
        cout << " 3. Assign Vehicle to Driver " << endl;
        cout << " 4. Search Vehichle by Make or Driver " << endl;
        cout << " 5. Return to Main Menu " << endl;
        cin >> choice;

        switch(choice){
            case 1:
                cout << "==== Add New Vehicle ====" << endl;
                break;
            case 2:
                cout << "==== View All Vehicles ====" << endl;
                break;
            case 3:
                cout << "==== Assign Vehicle to Driver ====" << endl;
                break;
            case 4:
                cout << "==== Search Vehichle by Make or Driver ====" << endl;
                break;
            case 5:
                cout << "Returning to Main Menu...." << endl;
                break;
            default:
                cout << "Invalid option selected. Please choose an option between 1 and 5." << endl;
        }
    } while(choice != 5);
}

void performanceStats(){
    int choice;
    do{
        displayBanner();
        cout << "==== Performance Statistics Menu ==== \n" << endl;
        cout << " 1. View Lap Times (Reverse Order) " << endl;
        cout << " 2. View Leaderboard " << endl;
        cout << " 3. View Driver Performance Stats " << endl;
        cout << " 4. Compare Driver Stats " << endl;
        cout << " 5. Return to Main Menu " << endl;
        cin >> choice;

        switch(choice){
            case 1:
                cout << "==== View Lap Times (Reverse Order)e ====" << endl;
                break;
            case 2:
                cout << "==== View Leaderboard ====" << endl;
                break;
            case 3:
                cout << "==== View Driver Performance Stats ====" << endl;
                break;
            case 4:
                cout << "==== Compare Driver Stats ====" << endl;
                break;
            case 5:
                cout << "Returning to Main Menu...." << endl;
                break;
            default:
                cout << "Invalid option selected. Please choose an option between 1 and 5." << endl;
        }
    } while(choice != 5);
}



void mainMenu(){
    int choice;
    do{
        displayBanner();
        cout << "====== Main Menu ========\n" << endl;
        cout << " 1. Personnel Management" << endl; 
        cout << " 2. Race Management" << endl;                       
        cout << " 3. Team Management" << endl;                       
        cout << " 4. Vehicle Management" << endl;                     
        cout << " 5. Performance & Stats" << endl;                                
        cout << " 6. Exit" << endl;
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