// Version 4.1 - Fixed Compilation Issues and Closer to UML Diagram

// Comments:
// pop() function of RaceQueue and its copy constructor not used. We need to fugure out where
// we are going to use this.


#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Forward declarations (if needed)
class Driver;
class Engineer;
class Race;

// ************ Display Banner & Utility ************
void displayBanner(){
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

void clearScreenDisplayBanner(){
    system("CLS"); // Clear screen (Windows)
    displayBanner();
}

void pauseScreen(){
    cout << "\nPress Enter to continue...";
    // cin.ignore();
    cin.get();
}

// void handleInvalidInputChar() {
//     // Handle invalid input using a character
//         cin.clear();               // Clear the error state
//         cin.ignore(100, '\n');     // Discard invalid input up to the next newline
//         cout << "\nInvalid input. Please enter a number." << endl;
//         cout << "Press Enter to continue...";
//         cin.get();                 // Wait for user to press Enter
// }

// ************ Date Class (Composition) ************
class Date {
private:
    int day, month, year;

public:
    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    // Helper to convert internal data to string
    string getDateString() const {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }
};

// Helper function to read a Date from user input
Date readDateFromUser(const string &prompt) {
    cout << prompt << " (Day Month Year): ";
    int d, m, y;
    char dash1, dash2;
    cin >> d >> dash1 >> m >> dash2 >> y;
    cin.ignore(); // Just ignore one character after reading input
    return Date(d, m, y);
}


// ************ Abstract Base Class: Person ************
class Person {
protected:
    string name;
    int age;
    Date dateOfBirth;  // Composition: a Person "has-a" Date

public:
    Person(const string& nm, int a, const Date& dob)
        : name(nm), age(a), dateOfBirth(dob) {}

    virtual ~Person(){
        cout << "Destroying person object" << endl;
    }
    virtual string getName() const = 0;
    virtual int getAge() const = 0;
    virtual string getDateOfBirth() const = 0;
    virtual void display() const = 0;
};

// ************ Driver (Inherits from Person) ************
class Driver : public Person {
private:
    int driver_num;

public:
    Driver(const string& nm, int a, const Date& dob, int dnum)
        : Person(nm, a, dob), driver_num(dnum) {}

    ~Driver() {
        cout << "Destroying Driver object" << endl;
    }
    string getName() const override { return name; }
    int getAge() const override { return age; }
    string getDateOfBirth() const override {
        return dateOfBirth.getDateString(); 
    }
    int getDriverNum() const { return driver_num; }

    void display() const override {
        cout << "Name: " << name << "\n"
             << "Age: " << age << "\n"
             << "Date of Birth: " << dateOfBirth.getDateString() << "\n"
             << "Driver Number: " << driver_num << "\n";
    }
};

// ************ Engineer (Inherits from Person) ************
class Engineer : public Person {
private:
    string id;
    string qualification;

public:
    Engineer(const string& nm, int a, const Date& dob, const string& engID, const string& qual) : Person(nm, a, dob), id(engID), qualification(qual) {}

    ~Engineer() {
        cout << "Destroying the Engineer object" << endl;
    }
    string getName() const override { return name; }
    int getAge() const override { return age; }
    string getDateOfBirth() const override {
        return dateOfBirth.getDateString();
    }
    string getId() const { return id; }
    string getQualification() const { return qualification; }

    void display() const override {
        cout << "Name: " << name << "\n"
             << "Age: " << age << "\n"
             << "Date of Birth: " << dateOfBirth.getDateString() << "\n"
             << "Engineer ID: " << id << "\n"
             << "Qualification: " << qualification << "\n";
    }
};

// ************ Abstract Base Class for Person Queues + Derived Queues ************
class PersonQueue {
    protected:
        struct Node {
            Person* person;
            Node* next;
            Node(Person* p) : person(p), next(nullptr) {}
        };
    
        Node* front;
        Node* rear;
    
    public:
        PersonQueue() : front(nullptr), rear(nullptr) {}
        virtual ~PersonQueue() {}  // Let derived classes clean up
        virtual void push(Person* p) = 0;
        virtual void pop() = 0;
        virtual void display() const = 0;
        bool isEmpty() const { return front == nullptr; }
    };
    
    class DriverQueue : public PersonQueue {
    public:
        ~DriverQueue() {
            while(!isEmpty()){ pop(); }
        }
        void push(Person* p) override {
            Node* newNode = new Node(p);
            if(!rear) { front = rear = newNode; }
            else { rear->next = newNode; rear = newNode; }
        }
        void pop() override {
            if(isEmpty()) return;
            Node* temp = front;
            front = front->next;
            delete temp->person;
            delete temp;
            if(!front) rear = nullptr;
        }
        void display() const override {
            Node* curr = front;
            while(curr) {
                curr->person->display();
                cout << endl;
                curr = curr->next;
            }
        }
    };
    
    class EngineerQueue : public PersonQueue {
    public:
        ~EngineerQueue() {
            while(!isEmpty()){ pop(); }
        }
        void push(Person* p) override {
            Node* newNode = new Node(p);
            if(!rear) { front = rear = newNode; }
            else { rear->next = newNode; rear = newNode; }
        }
        void pop() override {
            if(isEmpty()) return;
            Node* temp = front;
            front = front->next;
            delete temp->person;
            delete temp;
            if(!front) rear = nullptr;
        }
        void display() const override {
            Node* curr = front;
            while(curr) {
                curr->person->display();
                cout << endl;
                curr = curr->next;
            }
        }
    };

// ************ RaceResult (Association Class) ************
class RaceResult {
private:
    Driver* driver;    // Points to the associated Driver
    const Race* race;  // Points back to the associated Race
    int position;
    int points;
    float bestLapTime;

public:
    RaceResult(Driver* d, const Race* r, int pos, int pts, float lapTime)
        : driver(d), race(r), position(pos), points(pts), bestLapTime(lapTime) {}

    void display() const;
};

// ************ Race Class ************
class Race {
private:
    string location;
    Date date;         // Composition: Race "has-a" Date
    int courseID;
    vector<RaceResult*> results;

public:
    Race(){}

    Race(const string& loc, const Date& d, int cid)
        : location(loc), date(d), courseID(cid) {}

    ~Race() {
        // Clean up RaceResult pointers
        for (auto* rr : results) {
            delete rr;
        }
    }

    string getLocation() const { return location; }
    string getDate() const { return date.getDateString(); }
    int getCourseID() const { return courseID; }

    void addRaceResultForDriver(Driver* d, int pos, int pts, float lapTime) {
        results.push_back(new RaceResult(d, this, pos, pts, lapTime));
    }

    void displayResults() const {
        cout << "\n=== Results for Race at " << location
             << " on " << date.getDateString() << " ===\n";
        if (results.empty()) {
            cout << "No results recorded yet.\n";
            return;
        }
        for (auto& r : results) {
            r->display();
        }
    }

    friend class RaceResult; // Allow RaceResult to access private members if needed.
};

// Implementation of RaceResult::display() (after Race is fully defined)
void RaceResult::display() const {
    cout << "Driver: " << driver->getName()
         << ", Race: " << race->getLocation()
         << ", Date: " << race->getDate()
         << ", Position: " << position
         << ", Points: " << points
         << ", Best Lap Time: " << bestLapTime << "s\n";
}


// ************ RaceQueue Class for Race Management ************
class RaceNode {
    public:
        Race data;
        RaceNode* next;

        RaceNode(Race r) : data(r), next(NULL) {}
        RaceNode() :data(Race()), next(NULL) {}
    };
    
    class RaceQueue {
    private:
    private:
        RaceNode* listhead;
        RaceNode* listtail;
    public:
        RaceQueue(){
            listhead = NULL;
            listtail = NULL;
        }
        ~RaceQueue() {
            RaceNode* temp;
            while(listhead != NULL) //as long as the queue is not empty
            {
                temp = listhead;//put listhead to dynamic temp
                listhead = listhead->next;//get a new listhead
                delete temp;//delete dynamic temp
            }
        }
        RaceQueue(const RaceQueue& q);
        void addRaceToQueue(const Race& r);
        void showQueue();
        Race pop();
        void deleteRaceNode();
    };


    void RaceQueue::addRaceToQueue(const Race& r)
    {
        RaceNode* temp = new RaceNode(r);
    
        if (temp == NULL)//check the overflow
        {
            cout << "overflow error" << endl;
        }
        else
        {
            if (listhead == NULL)
            {   // if the queue is empry
                listhead = temp;
                listtail = temp;// new node would be the list head and tail
    
            }
            else
            {
                listtail->next = temp;// put new node at the end of queue
                listtail = temp;     // update new listtail
            }
        }
    }
    
    Race RaceQueue::pop(){
        if (listhead == NULL)//if it's an empty queue ,then return a default value Class Student
        {
            cout << "underflow error" << endl;
            return Race();
        }
        else
        {
            RaceNode* temp = listhead;//push listhead to temp (dynamic memory)
            Race poppedRace = listhead->data;//put the data of listhead to an new object 
            listhead = listhead->next;//let the next of original listhead be the new listhead
            delete temp;//delete the dynamic
            return poppedRace;//return the value 
         
        }
    }
    
    RaceQueue::RaceQueue(const RaceQueue& q){
        RaceNode* hold = q.listhead;//let hold be as the The head pointer of the source queue
        RaceNode* temp;
        RaceNode* oldtemp;
    
        if (hold == NULL)//if the source queue is empty,then the cory queue be empty too
        {
            listhead = NULL;
            listtail = NULL;
        }
        else
        {
            temp = new RaceNode;//create a new nede, give it to temp
            listhead = temp;//let the new node be the new listhead of copy queue
    
            while (hold != NULL)//if the hold has something, starts to traverse the source queue
            {
                temp->data = hold->data;//as we set the hold is head of source queue before, now put it to the head of copy queue 
                oldtemp = temp;//now temp is oldtemp, 
                hold = hold->next;//make the next of hold before be the new hold, continue to traverse
                if (hold != NULL)//check if the hold gets the end of source queue
                {
                    temp = new RaceNode;//there is still has somthing to copy, create a new node 
                    oldtemp->next = temp;//connect temp and oldtemp
                }
            }
            listtail = temp;//after finishing the traverse, we make the last one temp as listtail
            listtail->next = NULL;//Make sure the next pointer of the tail node is NULL
        }
    }
    
    void RaceQueue:: showQueue(){
        if (listhead == NULL)
        {
            cout << "The Queue of Race is empty." << endl;
        }
        else
        {
            cout << "=== Race Queue ===" << endl;
            RaceNode* temp = new RaceNode;
            temp = listhead;
            int count = 1;
            while (temp != NULL)
            {
                cout << "Race # " << count << " :" << endl;
                cout << "Location: " << temp->data.getLocation() << endl; // Use getters instead of temp->data.showRaces();
                cout << "Date: " << temp->data.getDate() << endl;
                cout << "Course ID: " << temp->data.getCourseID() << endl;
                temp = temp->next;
                count++;
            }
        }
    }
    
    void RaceQueue:: deleteRaceNode()
    {
        if (listhead == NULL)
        {
            cout << "The Queue is empty. Nothing to delete." << endl;
            return;
        }
        int total=0;
        RaceNode* temp = listhead;
        while (temp != NULL)
        {
            total++;
            temp = temp->next;
        }
        int num;
        showQueue();
        cout << "Which Race would you like to delete ? " << endl;
        cin >> num;
        if (num<1 || num>total)
        {
            cout << "error input,please choose a number between 1 and " << total << endl;
            return;
        }
    
        string confirm;
        cout << "Are you sure you want to delete Race # " << num << " ？ (yes/no)" << endl;
        cin >> confirm;
        if (confirm != "Yes" && confirm != "yes" && confirm != "YES")
        {
            cout << "deletion cancled " << endl;
            return;
        }
        RaceNode* current = listhead;
        RaceNode* prev = NULL;
    
        if (num == 1)
        {
            listhead = current->next;
            delete current;
            if (listhead == NULL)
            {
                listtail = NULL;
            }
            cout << "Race # 1 has been deleted" << endl;
            return;
        }
        for (int i=1;i < num;i++)
        {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        if (current == listtail)
        {
            listtail = prev;
        }
        delete current;
    
        cout << "Race # " << num << " has been deleted !" << endl;
    }


// ************ Team (Qualified Association) ************
class Team {
public:
    string name;
    // Qualified association: role -> Driver
    unordered_map<string, Driver*> roleToDriverMap;


    // Qualified associaltion: role -> Engineer
    unordered_map<string, Engineer*> roleToEngineerMap;

    Team(const string &n) : name(n) {}

    // Qualified association for Drivers.
    void AssignRoleToDriver(const string &role, Driver* d) {
        roleToDriverMap[role] = d;
    }

    Driver* getDriverByRole(const string &role) const {
        auto it = roleToDriverMap.find(role);
        return (it != roleToDriverMap.end()) ? it->second : nullptr;
    }

    // Qualified association for Engineers.

    void assignEngineer(const string &role, Engineer* e){ // role is the key
        roleToEngineerMap[role] = e;
    }

    Engineer* getEngineerByKey(const string &role) const{
        auto it = roleToEngineerMap.find(role);
        return(it != roleToEngineerMap.end()) ? it->second : nullptr;
    }
};

// ************ RaceManager (Dependency) ************
class RaceManager {
private:
    vector<Race*> races;

public:
    ~RaceManager() {
        // Clean up allocated Race objects
        for (auto* r : races) {
            delete r;
        }
    }

    // Create & store new race
    void scheduleRace(class RaceQueue &rq) {
        cin.ignore(); // Clear buffer
        string loc;
        cout << "Enter race location: ";
        getline(cin, loc);

        Date d = readDateFromUser("Enter race date");
        cout << "Enter course ID: ";
        int cid;
        cin >> cid;
        cin.ignore();

        Race* r = new Race(loc, d, cid);
        races.push_back(r);

        rq.addRaceToQueue(*r); // Adds a race to the race queue.
        cout << "Race successfully scheduled.\n";
    }

    // Use the global allDrivers to enter race results (for the last race)
    void enterRaceResults(const vector<Driver*>& allDrivers) {
        if (races.empty() || allDrivers.empty()) {
            cout << "Make sure at least one race and one driver are registered.\n";
            return;
        }
        Race* r = races.back();
        cout << "Entering results for: " << r->getLocation()
             << " on " << r->getDate() << "\n";

        for (Driver* d : allDrivers) {
            int pos, pts;
            float lap;
            cout << "Driver: " << d->getName() << "\n";
            cout << "Enter position: ";
            cin >> pos;
            cout << "Enter points: ";
            cin >> pts;
            cout << "Enter best lap time: ";
            cin >> lap;
            r->addRaceResultForDriver(d, pos, pts, lap);
        }
        cout << "Results recorded.\n";
    }

    // Show results for all races
    void viewRaceResults() const {
        if (races.empty()) {
            cout << "No races scheduled.\n";
            return;
        }
        for (auto* r : races) {
            r->displayResults();
        }
    }
};

// ************ Global Structures & Objects ************
DriverQueue driverQueue;
EngineerQueue engineerQueue;
unordered_map<string, Team*> teams;  // For qualified association
vector<Driver*> allDrivers;
vector<Engineer*> allEngineers;
RaceManager raceManager;
RaceQueue raceQueue;

// ************ Registration Functions ************
void registerDriver(){
    // cin.ignore(); get rid!!!
    cout << "Enter Driver name: ";
    string dname;
    getline(cin, dname);

    cout << "Enter Driver age: ";
    int age;
    cin >> age;
    cin.ignore();

    Date dob = readDateFromUser("Enter driver date of birth");

    cout << "Enter driver number: ";
    int dnum;
    cin >> dnum;
    cin.ignore();

    // Construct a new Driver
    Driver* d = new Driver(dname, age, dob, dnum);
    driverQueue.push(d);
    allDrivers.push_back(d);

    cout << "Enter team name (e.g., Red, Green, Blue): ";
    string teamName;
    getline(cin, teamName);

    cout << "Enter role (e.g., Main Driver, Reserve Driver): ";
    string role;
    getline(cin, role);

    if (teams.find(teamName) == teams.end()) {
        teams[teamName] = new Team(teamName);
    }
    teams[teamName]->AssignRoleToDriver(role, d);

    cout << "Driver registered successfully and assigned role.\n";
}

void registerEngineer() {
    cout << "Enter Engineer name: ";
    string ename;
    getline(cin, ename);

    cout << "Enter age: ";
    int age;
    cin >> age;
    cin.ignore();

    Date dob = readDateFromUser("Enter engineer date of birth");

    cout << "Enter Engineer ID: ";
    string engID;
    cin >> engID;
    cin.ignore();

    cout << "Enter qualification: ";
    string qual;
    getline(cin, qual);

    Engineer* e = new Engineer(ename, age, dob, engID, qual);
    engineerQueue.push(e);
    allEngineers.push_back(e);

    cout << "Enter team name (e.g., Red, Green, Blue): ";
    string teamName;
    getline(cin, teamName);

    if (teams.find(teamName) == teams.end()) {
        teams[teamName] = new Team(teamName);
    }
    cout << "Enter the Engineer role (e.g Senior Engineer, Junior Engineer, Technician)" << endl;
    string role;
    getline(cin, role);
    teams[teamName]->assignEngineer(role,e);

    cout << "Engineer registered and added to team successfully!\n";
}

// ************ Searching ************
void searchDriverByTeamAndRole() {
    cin.ignore();
    cout << "Enter team name (e.g., Red, Green, Blue): ";
    string teamName;
    getline(cin, teamName);

    cout << "Enter driver role (e.g., Main Driver, Reserve Driver): ";
    string role;
    getline(cin, role);

    if (teams.find(teamName) != teams.end()) {
        Driver* found = teams[teamName]->getDriverByRole(role);
        if (found) {
            cout << "Driver found: " << found->getName()
                 << ", Number: " << found->getDriverNum() << endl;
        } else {
            cout << "No driver found for role '" << role
                 << "' in team " << teamName << ".\n";
        }
    } else {
        cout << "Team not found.\n";
    }
    pauseScreen();
}

// ************ Example Menus ************
void personnelManagement(){
    int choice;
    do {
        clearScreenDisplayBanner();
        cout << "===== Personnel Management Menu =====\n\n";
        cout << " 1. Register New Driver\n";
        cout << " 2. View All Drivers\n";
        cout << " 3. Register New Engineer\n";
        cout << " 4. View All Engineers\n";
        cout << " 5. Return to Main Menu\n";
        cout << " Enter an option: ";
        cin >> choice;
        cin.ignore();

        switch(choice){
            case 1:
                clearScreenDisplayBanner();
                cout << "==== Registering new driver ====\n";
                registerDriver();
                pauseScreen();
                break;
            case 2:
                clearScreenDisplayBanner();
                cout << "==== View All Drivers ====\n";
                driverQueue.display();
                pauseScreen();
                break;
            case 3:
                clearScreenDisplayBanner();
                cout << "==== Registering new engineer ====\n";
                registerEngineer();
                pauseScreen();
                break;
            case 4:
                clearScreenDisplayBanner();
                cout << "==== View All Engineers ====\n";
                engineerQueue.display();
                pauseScreen();
                break;
            case 5:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    } while(choice != 5);
}

// ******** Race Management Menu *****************
void raceManagement(){
    int choice;
    do {
        displayBanner();
        cout << "==== Race Management Menu ====\n\n";
        cout << " 1. Schedule New Race\n";
        cout << " 2. View Scheduled Races (Queue placeholder)\n";
        cout << " 3. Enter Race Results\n";
        cout << " 4. View Race Results\n";
        cout << " 5. Delete Past Race (Placeholder)\n";
        cout << " 6. Return to Main Menu\n";
        cout << " Enter an option: ";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "==== Schedule New Race ====\n";
                raceManager.scheduleRace(raceQueue);
                break;
            case 2:
                cout << "==== View Scheduled Races (Placeholder) ====\n";
                raceQueue.showQueue();
                break;
            case 3:
                cout << "==== Enter Race Results ====\n";
                raceManager.enterRaceResults(allDrivers);
                break;
            case 4:
                cout << "==== View Race Results ====\n";
                raceManager.viewRaceResults();
                break;
            case 5:
                cout << "==== Delete Past Race (Placeholder) ====\n";
                raceQueue.deleteRaceNode();
                break;
            case 6:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while(choice != 6);
}

// ******** Team Management Menu *****************
void teamManagement(){
    int choice;
    do {
        displayBanner();
        cout << "==== Team Management Menu ====\n\n";
        cout << " 1. Create New Team (Placeholder)\n";
        cout << " 2. View All Teams (Placeholder)\n";
        cout << " 3. Search Driver by Team and Role\n";
        cout << " 4. Search Engineer by Team and Role (Placeholder)\n";
        cout << " 5. Return to Main Menu\n";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "==== Create New Team (Placeholder) ====\n";
                break;
            case 2:
                cout << "==== View All Teams (Placeholder) ====\n";
                break;
            case 3:
                cout << "==== Search Driver by Team and Role ====\n";
                searchDriverByTeamAndRole();
                break;
            case 4:
                cout << "==== Search Engineer by Team and Role (Placeholder) ====\n";
                break;
            case 5:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while(choice != 5);
}

// ******** Vehicle Management Menu ******************
void vehicleManagement(){
    int choice;
    do {
        displayBanner();
        cout << "==== Vehicle Management Menu ====\n\n";
        cout << " 1. Add New Vehicle (Placeholder)\n";
        cout << " 2. View All Vehicles (Placeholder)\n";
        cout << " 3. Assign Vehicle to Driver (Placeholder)\n";
        cout << " 4. Search Vehicle by Make or Driver (Placeholder)\n";
        cout << " 5. Return to Main Menu\n";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "==== Add New Vehicle (Placeholder) ====\n";
                break;
            case 2:
                cout << "==== View All Vehicles (Placeholder) ====\n";
                break;
            case 3:
                cout << "==== Assign Vehicle to Driver (Placeholder) ====\n";
                break;
            case 4:
                cout << "==== Search Vehicle by Make or Driver (Placeholder) ====\n";
                break;
            case 5:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while(choice != 5);
}

// ******** Performance & Stats menu *********************
void performanceStats(){
    int choice;
    do {
        displayBanner();
        cout << "==== Performance Statistics Menu ====\n\n";
        cout << " 1. View Lap Times (Reverse Order) (Placeholder)\n";
        cout << " 2. View Leaderboard (Placeholder)\n";
        cout << " 3. View Driver Performance Stats (Placeholder)\n";
        cout << " 4. Compare Driver Stats (Placeholder)\n";
        cout << " 5. Return to Main Menu\n";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "==== View Lap Times (Reverse Order) (Placeholder) ====\n";
                break;
            case 2:
                cout << "==== View Leaderboard (Placeholder) ====\n";
                break;
            case 3:
                cout << "==== View Driver Performance Stats (Placeholder) ====\n";
                break;
            case 4:
                cout << "==== Compare Driver Stats (Placeholder) ====\n";
                break;
            case 5:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while(choice != 5);
}

// ******** Main menu ****************************
void mainMenu(){
    int choice;
    do {
        clearScreenDisplayBanner();
        cout << "====== Main Menu ========\n\n";
        cout << " 1. Personnel Management\n";
        cout << " 2. Race Management\n";
        cout << " 3. Team Management\n";
        cout << " 4. Vehicle Management\n";
        cout << " 5. Performance & Stats\n";
        cout << " 6. Exit\n";
        cout << " Enter an option: ";
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
                cout << "Exiting program\n";
                break;
            default:
                cout << "Invalid choice. Please select an option between 1 and 6\n";
                break;
        }
    } while(choice != 6);
}

int main(){
    mainMenu();
    return 0;
}
