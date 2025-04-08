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
        virtual void display() const = 0;
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
    void display() const override {
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Date of Birth: " << dateOfBirth << "\n";
        cout << "Driver Number: " << driver_num << "\n";
    }

};
    
// *************** Engineer class (Inheritance from Person) ************************
class Engineer : public Person{
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
        void display() const override {
            cout << "Name: " << name << "\n";
            cout << "Age: " << age << "\n";
            cout << "Date of Birth: " << dateOfBirth << "\n";
            cout << "Engineer ID: " << id << "\n";
            cout << "Qualification: " << qualification << "\n";
        }        
};

// **** Need to find out how we are using this??
// class RaceNode{


// };



// ******* Abstract Queue base class with deried wueue class for driver and engineer ***********************
class Queue{
    protected:
        struct Node {
            Person* person;
            Node* next;
            Node(Person* p) : person(p), next(nullptr) {}
        };
    
        Node* front;
        Node* rear;
    
    public:
        Queue() : front(nullptr), rear(nullptr) {}
        virtual ~Queue() {
            // while (!isEmpty()) pop(); // Let derived classes handle pop cleanup as getting linker error.
        }
    
        virtual void push(Person* p) = 0;
        virtual void pop() = 0;
        virtual void display() const = 0;
    
        bool isEmpty() const {
            return front == nullptr;
        }
};
    
// Derived DriverQueue from Queue
class DriverQueue : public Queue{
    public:
        ~DriverQueue(){
            while(!isEmpty()){
                pop();
            }
        }

        void push(Person* p) override {
            Node* newNode = new Node(p);
            if (!rear) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }

        void pop() override{
            if (isEmpty()) return;
            Node* temp = front;
            front = front->next;
            delete temp->person;
            delete temp;
            if (!front) rear = nullptr;
        }

        void display() const override{
            Node* curr = front;
            while (curr) {
                curr->person->display(); // Polymorphism call
                cout << endl;
                curr = curr->next;
            }
        }
};
    
// Derived EngineerQueue from Queue
class EngineerQueue : public Queue{
    public:

        ~EngineerQueue(){
            while(!isEmpty()){
                pop();
            }
        }

        void push(Person* p) override {
            Node* newNode = new Node(p);
            if (!rear) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }

        void pop() override {
            if (isEmpty()) return;
            Node* temp = front;
            front = front->next;
            delete temp->person;
            delete temp;
            if (!front) rear = nullptr;
        }

        void display() const override {
            Node* curr = front;
            while (curr) {
                curr->person->display(); // Polymorphisim call.
                cout << endl;
                curr = curr->next;
            }
        }
};



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


// *********** Association class - Kenneth Johnson ******************************* (NEED TO FINISH!!!!)
// One driver can participate in many races, and one race can have many drivers.
// The display funciton only handles one race result using the display function, a vector is needed to display all results.
class RaceResult{
    private:
        Driver* driver;
        const Race* race;
        int position;
        int points;
        float bestLapTime;

    public:
    RaceResult(Driver* d, const Race* r, int pos, int pts, float lapTime) : driver(d), race(r), position(pos), points(pts), bestLapTime(lapTime){}
    
    void display() const{
        cout << "Driver: " << driver->getName() << ", Race: " << race->getLocation()
        << ", Date: " << race->getDate() << ", Position: " << position
        << ", Points: " << points << ", Best Lap Time: " << bestLapTime << "s" << endl;
    }

};


// ************* Team class (Qualified association)- Kenneth Johnson *********************************
class Team{
    public:
        string name; // Name of Team 
        unordered_map<string, Driver*> roleToDriverMap; // This is quaified association, string is the qualifier ("Main Driver", "Reserve Driver", etc.), Driver* is the object associated with the qualifier.
        vector<Engineer*> engineers; // Stores pointers to Engineer objets associated with this team.

        Team(string name) : name(name){} // Constructor that initialises the team with the given name.
    
        void AssignRoleToDriver(const string& role, Driver* d){ // Function that assigns a driver to a spcific role in the team. THe Role is the qualifier.
            roleToDriverMap[role] = d; // This adds or updates the map for role to driver.
        }

        Driver* getDriverByRole(const string& role) const{ // This function retrieve a driver by their role, this is qualified lookup.
            auto it = roleToDriverMap.find(role); // This looks for a role in the map.
            return (it != roleToDriverMap.end()) ? it->second : nullptr; // This returns the Driver* if found, else returns a nullptr. 
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

class RaceManager{ // ****** This can be used as a dependancy *********
    private:
        vector<Race*> races;
        vector<Driver*> drivers;
    public:
        void scheduleRace(){ // Create and store a new race
        string loc, date;
        int courseID;

        cout << "Enter race location: ";
        getline(cin, loc);
        cout << "Enter race date: ";
        getline(cin, date);
        cout << "Enter course ID: ";
        cin >> courseID;
        
        Race* r = new Race(loc, date, courseID);
        races.push_back(r);
        // allRaces.push_back(r);

        cout << "Race sucessfully scheduled" << endl;
        }

        void enterRaceResults(){ // Selects race and driver, create raceResults
            if (races.empty() || allDrivers.empty()) {
                cout << "Make sure at least one race and one driver are registered.\n";
                return;
            }

            Race* r = races.back();

            cout << "Entering results for: " << r->getLocation() << " on " << r->getDate() << endl;
            for (Driver* d : allDrivers) {
                int pos, pts;
                float lap;
                cout << "Driver: " << d->getName() << "\n";
                cout << "Enter position: "; cin >> pos;
                cout << "Enter points: "; cin >> pts;
                cout << "Enter best lap time: "; cin >> lap;

                r->addRaceResultForDriver(d, pos, pts, lap);
            }
            cout << "Results recorded.\n";

        }

    void viewRaceResults(){ // Display results for a selected race
        if (races.empty()) {
            cout << "No races scheduled.\n";
            return;
        }

        for (Race* r : races) {
            r->displayResults();
        }
    }
};


DriverQueue driverQueue;
EngineerQueue engineerQueue;

unordered_map<string, Team*> teams; // Qualified association map, Teams is an unordered map.
vector<Driver*> allDrivers;
vector<Engineer*> allEngineers;
vector<Race*> allRaces;
RaceManager raceManager;

//*********** Qualified association ******************** */

void registerDriver(){
    string name, dob, team, role; // Local variables to hold user input
    int age, driverNumber; // Local variables to hold user input
    cin.ignore(); // Clear input buffer.
    cout << "Enter driver name: "; // Enter Driver Name
    getline(cin, name); // Reads the full name including the spaces.
    cout << "Enter age: "; 
    cin >> age; // Enter Driver Age
    cin.ignore();
    cout << "Enter date of birth: ";
    getline(cin, dob); // Enter Driver DOB string.
    cout << "Enter team (Red, Green, Blue): ";
    getline(cin, team);
    cout << "Enter driver number: ";
    cin >> driverNumber; // Enter Driver Number
    cin.ignore();
    cout << "Enter role (e.g., Main Driver, Reserve Driver): ";
    getline(cin, role); // Enter Driver Role

    // Dynamically create a new driver object with the data that was entered
    Driver* d = new Driver(name, age, dob, driverNumber);
    
    driverQueue.push(d); // Adds a driver to the queue.

    // Stores the driver pointer in the global allDrivers vector.
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

    engineerQueue.push(e); // Adds an engineer to the queue.


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



// Statistics class (operator overloading)
class Statistics{
    private:


    public:

};



// RaceNode class for queue
class RaceNode {
public:
    Race data;
    RaceNode* next;
    RaceNode(Race r) : data(r), next(nullptr){}
};



void personnelManagement(){
    int choice;
    do{
        displayBanner();
        cout << "===== Personnel Management Menu =====\n" << endl;
        cout << " 1. Register New Driver " << endl;
        cout << " 2. View All Drivers  " << endl;
        cout << " 3. Register New Engineer " << endl;
        cout << " 4. View All Engineers " << endl;
        cout << " 5. Return to Main Menu " << endl;
        cin >> choice;

        switch(choice){
            case 1:
                pauseAndClear();
                displayBanner();
                cout << "==== Registering new drivers ====" << endl;
                registerDriver();
                pauseAndClear();
                break;
            case 2:
                pauseAndClear();
                 displayBanner();
                cout << "==== View All Drivers ====" << endl; 
                driverQueue.display();
                pauseAndClear();
                break;
            case 3:
                cout << "Registering new Engineers....." << endl; 
                registerEngineer();
                pauseAndClear();
                break;
            case 4:
                cout << "View All Engineers....." << endl; 
                engineerQueue.display();
                pauseAndClear();
                break;
            case 5:
                cout << "Returning to Main Menu....." << endl; 
                break;
            default:
                cout << "Invalid choice. Please select an option between 1 and 7" << endl;
                break;
        }
    } while(choice != 5);
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
                raceManager.scheduleRace();
                break;
            case 2:
                cout << "==== View Race Results ====" << endl;
                break;
            case 3:
                cout << "==== Enter Race Results ====" << endl;
                raceManager.enterRaceResults();
                break;
            case 4:
                cout << "==== View Race Results ====" << endl;
                raceManager.viewRaceResults();
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
        cout << " 1. Create New Team " << endl; // Assigns Driver, Engineer, and car
        cout << " 2. View All Teams " << endl;
        cout << " 3. Search Driver by Team and Role " << endl;
        cout << " 4. Search Engineer by Team and Role " << endl;
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
                cout << "==== Search Driver by Team and Role ====" << endl;
                searchDriverByTeamAndRole();
                break;
            case 4:
                cout << "==== Search Engineer by Team and Role ====" << endl;
                // Add qualified association to this here!!!
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


// Need to figure this out last
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
                cout << "==== View Lap Times (Reverse Order) ====" << endl;
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


int main(){
    mainMenu();
   
    return 0;
}