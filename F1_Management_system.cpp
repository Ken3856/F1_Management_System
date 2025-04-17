// Version 4.1 - Fixed Compilation Issues and Closer to UML Diagram

// Comments:
// pop() function of RaceQueue and its copy constructor not used. We need to fugure out where
// we are going to use this.


#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


// Forward declarations
class Driver;
class Engineer;
class Race;
class Vehicle;
class Team;
class DriverQueue;
class EngineerQueue;
class RaceManager;
class RaceQueue;


void displayBanner();
void clearScreenDisplayBanner();
void pauseScreen();


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


// ************ Date Class (Composition) ************
class Date {
private:
    int day, month, year;

public:
    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    // Helper to convert internal data to string
    string getDateString() const {
        return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
    }
};

// non-member stream-operators for Date
ostream& operator << (ostream& os, const Date& d){ // Output:  cout << date;   prints “DD-MM-YYYY”
    os << d.getDateString();
    return os;
}

// Input:  cin >> date; reads three ints separated by ‘-’
istream& operator>>(istream& is, Date& d) {
    int dd, mm, yy;
    char dash1, dash2;
    if (is >> dd >> dash1 >> mm >> dash2 >> yy) {
        d = Date(dd, mm, yy);
    }
    return is;
}


// ************ Abstract Base Class: Person ************
class Person {
protected:
    string name;
    int age;
    Date dateOfBirth;  // Composition: a Person "has-a" Date

public:
    // Constructor
    Person(const string& n, int a, const Date& dob) : name(n), age(a), dateOfBirth(dob) {}

    // Destructor
    virtual ~Person(){
        cout << "Destroying person object" << endl; // Test destructor
    }

    // Getters
    string getName() const {
        return name;
    }
    int getAge() const {
        return age;
    }
    string getDateOfBirth() const {
        return dateOfBirth.getDateString();
    }
    virtual void displayInfo() const = 0; // Pure virtual function to be overriden in derived classes
};




// ************ Driver & Engineer (Inherits from Person) ************
class Driver;
class Engineer;

class Driver : public Person {
private:
    int driverId;
    string team;
    int driverNumber;
    static int driverCount;
    Vehicle* assignedVehicle = nullptr;

public:
    Driver(const string& n, int a, const Date& dob, int dID, const string& t, int dnum) // Inherited from person
        : Person(n, a, dob), driverId(dID), team(t), driverNumber(dnum){
            driverCount++;
    } 

    ~Driver() {
        cout << "Destroying Driver object" << endl; // Test destructor
    }

    int getDriverId() const {return driverId;}
    int getDriverNumber() const {return driverNumber;}
    const string& getTeam() const {return team;}

    void setAssignedVehicle(Vehicle* v){
        assignedVehicle = v;
    }
    Vehicle* getAssignedVehicle()const{
        return assignedVehicle;
    }

    // void displayInfo() const override {
    //     cout << "Driver Name: "   << getName() << "\n"
    //          << "Age: "           << getAge() << "\n"
    //          << "Date of Birth: " << getDateOfBirth() << "\n"
    //          << "DriverID: "      << getDriverId() << "\n"
    //          << "Team: "          << getTeam() << "\n"
    //          << "Driver Number: " << getDriverNumber() << endl;
    //     if(assignedVehicle){ // Added for binary association to display relationship
    //         cout << "Assigned Vehicle: " << assignedVehicle->getMake() << " " << assignedVehicle->getModel() << endl;
    //     }else{
    //         cout << "Assigned Vehicle: None" << endl;
    //     }
    // }

    void displayInfo() const override;

    static int getDriverCount(){return driverCount;}
};
int Driver::driverCount = 0;

// ************ Engineer (Inherits from Person) ************
class Engineer : public Person {
private:
    string engID;
    string qualification;
    static int engineerCount; // To track how many were created.

public:
    Engineer(const string& n, int a, const Date& dob, const string& ID, const string& qual) : Person(n, a, dob), engID(ID), qualification(qual){
        ++engineerCount;
    }
    ~Engineer() {
        cout << "Destroying the Engineer object" << endl; // Test Destructor.
    }

    // Get methods
    const string& getId() const { return engID;}
    const string& getQualification() const { return qualification; }

    // Display method
    void displayInfo() const override {
        cout << "Name: "          << getName() << "\n"
             << "Age: "           << getAge() << "\n"
             << "Date of Birth: " << getDateOfBirth() << "\n"
             << "Engineer ID: "   << getId() << "\n"
             << "Qualification: " << getQualification() << "\n";
    }
    static int getEngineerCount(){return engineerCount;}
};
int Engineer::engineerCount = 0;


// Abstract Base Class for inheritance and polymorphism
class Vehicle {
    protected:
        string make;
        string model;
        string color;
        int maxSpeed;
        static int vehicleCount;
        Driver* assignedDriver = nullptr; // Binary Association
    
    public:
        Vehicle(string make, string model, string color, int maxSpeed)
            : make(make), model(model), color(color), maxSpeed(maxSpeed) { vehicleCount++; } // Increment the count whenever a Vehicle object is created
        
        virtual ~Vehicle() {}

        virtual string getMake() const = 0;
        virtual string getModel() const = 0;
        virtual string getEngine() const = 0; // Polymorphic behaviour: pure virtual functions where the implementation will be in the derived class(es)
        virtual string getType() const = 0;

        // void assignDriver(Driver* d){
        //     assignedDriver = d;
        //     if(d){
        //         d->setAssignedVehicle(this);
        //     }
        // }
        void assignDriver(Driver* d);

        Driver* getAssignedDriver()const{
            return assignedDriver;
        }
    
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
        Engine(const string& t, int hp) : type(t), horsepower(hp) {}
    
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
        Car(const string& mk, const string& mdl, const string& col, int maxSp, const string& engTyp, int hp)
            : Vehicle(mk, mdl, col, maxSp), engine(engTyp, hp){ 
                carCount++; 
            }
    
        string getMake() const override {return make;}
    
        string getModel() const override {return model;}
    
        string getEngine() const override {
            return engine.getType() + " with " + to_string(engine.getHorsepower()) + " HP"; // Convert horsepower to string to concatenate with the strings
        }
    
        string getType() const override {
            return "Hatchback";
        }
    
        void showCarInfo() const override {
            cout << "Car: "         << getMake()  << "\n"
                 << "Car Model: "   << getModel() << "\n"
                 << "Engine Type: " << engine.getType()  << "\n"
                 << "Horsepower: "  << engine.getHorsepower() << "\n"
                 << "Color: "       << color << endl;

            // Added this for driver association
            if(assignedDriver){
                cout << "Assigned to Driver: " << assignedDriver->getName() << endl;
            } else{
                cout << "No Driver assigned." << endl;
            }
        }

        // Get the car count
        static int getCarCount() {return carCount;}
    };

    int Car::carCount = 0;



// ******************** Queues & Team *********************
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
                curr->person->displayInfo();
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
                curr->person->displayInfo();
                cout << endl;
                curr = curr->next;
            }
        }
    };


// ************ Team (Qualified Association) - Kenneth ************
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
    
// ******************** Race & Results *********************************
class Race;
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
        string courseID;
        vector<RaceResult*> results;
    
    public:
        Race(){}
    
        Race(const string& loc, const Date& d, string cid)
            : location(loc), date(d), courseID(cid) {}
    
        ~Race() {
            // Clean up RaceResult pointers
            for (auto* rr : results) {
                delete rr;
            }
        }
    
        string getLocation() const { return location; }
        string getDate() const { return date.getDateString(); }
        string getCourseID() const { return courseID; }
    
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
            cout << "Which Race would you like to delete ? (choose number) " << endl;
            cin >> num;
            if (num<1 || num>total)
            {
                cout << "error input,please choose a number between 1 and " << total << endl;
                return;
            }
        
            string confirm;
            cout << "Are you sure you want to delete Race # " << num << " (yes/no)" << endl;
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
    
    
    // ************ RaceManager (Dependency) - Kenneth ************
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
            string loc;
            cout << "Enter race location: ";
            getline(cin, loc);
    
            cout << "Enter race date (DD-MM-YY): ";
            Date d;
            cin >> d; // Uses operator oveloading.
            cin.ignore();
    
            cout << "Enter course ID: ";
            string cid;
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
vector<Vehicle*> allVehicles;
RaceManager raceManager;
RaceQueue raceQueue;


//****************** Free funcitons & Menus **************************** */

// Added this ***** Vehicle Management functions ********************** */
void addVehicle() {
    string make, model, color, engineType;
    int maxSpeed, horsepower;

    cout << "Enter Make: ";
    getline(cin, make);
    cout << "Enter Model: ";
    getline(cin, model);
    cout << "Enter Color: ";
    getline(cin, color);
    cout << "Enter Max Speed: ";
    cin >> maxSpeed;
    cin.ignore();
    cout << "Enter Engine Type: ";
    getline(cin, engineType);
    cout << "Enter Horsepower: ";
    cin >> horsepower;
    cin.ignore();

    Vehicle* newVehicle = new Car(make, model, color, maxSpeed, engineType, horsepower);
    allVehicles.push_back(newVehicle);

    cout << "Vehicle added successfully!\n";
}

void viewAllVehicles() {
    if (allVehicles.empty()) {
        cout << "No vehicles registered yet.\n";
    } else {
        for (size_t i = 0; i < allVehicles.size(); ++i) {
            cout << "\nVehicle #" << i + 1 << ":\n";
            allVehicles[i]->showCarInfo();
        }
    }
}

void assignVehicleToDriver(){
    if(allVehicles.empty() || allDrivers.empty()){
        cout << "No vehiles or drivers are available." << endl;
    }
    cout << "Choose a vehicle: ";
    for(int i = 0 ; i < allVehicles.size() ; i++){
        cout << i+1 << ". " << allVehicles[i]->getModel() << endl;
    }

    int vehicleChoice;
    cin >> vehicleChoice;
    cin.ignore();

    cout << "Choose a Driver: ";
    for(int i = 0 ; i < allDrivers.size() ; i++){
        cout << i+1 << ". " << allDrivers[i]->getName() << endl;
    }
    int driverChoice;
    cin >> driverChoice;
    cin.ignore();

    if (vehicleChoice > 0 && vehicleChoice <= allVehicles.size() && driverChoice > 0 && driverChoice <= allDrivers.size()){
        allVehicles[vehicleChoice - 1]->assignDriver(allDrivers[driverChoice - 1]);
        cout << "Vehicle assigned to driver successfully.\n";
    } else{
        cout << "Invalid selection.\n";
    }
}

// ************ Registration Functions ************
void registerDriver(){
    cout << "Enter Driver name: ";
    string driverName;
    getline(cin, driverName);

    cout << "Enter Driver age: ";
    int age;
    cin >> age;
    cin.ignore();

    // Uses operator overloading
    cout << "Enter Driver date of birth (DD-MM-YY): ";
    Date dob;
    cin >> dob; // Uses istream& operator >>(istream&, Date&)
    cin.ignore();

    cout << "Enter Driver ID: ";
    int driverID;
    cin >> driverID;
    cin.ignore();

    cout << "Enter Team Name (e.g. Red, Green, Blue): ";
    string teamName;
    getline(cin,teamName);
   
    cout << "Enter driver number: ";
    int driverNumber;
    cin >> driverNumber;
    cin.ignore();

    // Construct a new Driver
    Driver* d = new Driver(driverName, age, dob, driverID, teamName, driverNumber);
    driverQueue.push(d);
    allDrivers.push_back(d);

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

    // Read date using overloaded operator
    cout << "Enter enngineer date of birth (DD-MM-YY): ";
    Date dob;
    cin >> dob;
    cin.ignore();


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
                 << ", Number: " << found->getDriverNumber() << endl;
        } else {
            cout << "No driver found for role '" << role
                 << "' in team " << teamName << ".\n";
        }
    } else {
        cout << "Team not found.\n";
    }
    pauseScreen();
}

void Vehicle::assignDriver(Driver* d){
    assignedDriver = d;
    if(d){
        d->setAssignedVehicle(this);
    }
}

void Driver::displayInfo() const {
    cout << "Driver Name: "   << getName() << "\n"
         << "Age: "           << getAge() << "\n"
         << "Date of Birth: " << getDateOfBirth() << "\n"
         << "DriverID: "      << getDriverId() << "\n"
         << "Team: "          << getTeam() << "\n"
         << "Driver Number: " << getDriverNumber() << endl;
    if(assignedVehicle){ // Added for binary association to display relationship
        cout << "Assigned Vehicle: " << assignedVehicle->getMake() << " " << assignedVehicle->getModel() << endl;
    }else{
        cout << "Assigned Vehicle: None" << endl;
    }
}

// ************ Personnel Management Menu ************
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
        clearScreenDisplayBanner();
        cout << "==== Race Management Menu ====\n\n";
        cout << " 1. Schedule New Race\n";
        cout << " 2. View Scheduled Races (Queue placeholder)\n";
        cout << " 3. Enter Race Results\n";
        cout << " 4. View Race Results\n";
        cout << " 5. Delete Past Race (Placeholder)\n";
        cout << " 6. Return to Main Menu\n";
        cout << " Enter an option: ";
        cin >> choice;
        cin.ignore();

        switch(choice){
            case 1:
                clearScreenDisplayBanner(); // redraw banner 
                cout << "==== Schedule New Race ====\n";
                raceManager.scheduleRace(raceQueue);
                pauseScreen(); // Waits for the user to hit Enter
                break;
            case 2:
                clearScreenDisplayBanner(); // redraw banner 
                cout << "==== View Scheduled Races (Placeholder) ====\n";
                raceQueue.showQueue();
                pauseScreen(); // Waits for the user to hit Enter
                break;
            case 3:
                clearScreenDisplayBanner(); // redraw banner 
                cout << "==== Enter Race Results ====\n";
                raceManager.enterRaceResults(allDrivers);
                pauseScreen(); // Waits for the user to hit Enter
                break;
            case 4:
                clearScreenDisplayBanner(); // redraw banner 
                cout << "==== View Race Results ====\n";
                raceManager.viewRaceResults();
                pauseScreen(); // Waits for the user to hit Enter
                break;
            case 5:
                clearScreenDisplayBanner(); // redraw banner 
                cout << "==== Delete Past Race (Placeholder) ====\n";
                raceQueue.deleteRaceNode();
                pauseScreen(); // Waits for the user to hit Enter
                break;
            case 6:
                clearScreenDisplayBanner(); // redraw banner 
                cout << "Returning to Main Menu...\n";
                pauseScreen(); // Waits for the user to hit Enter
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
        clearScreenDisplayBanner();
        cout << "==== Vehicle Management Menu ====\n\n";
        cout << " 1. Add New Vehicle (Placeholder)\n";
        cout << " 2. View All Vehicles (Placeholder)\n";
        cout << " 3. Assign Vehicle to Driver (Placeholder)\n";
        cout << " 4. Search Vehicle by Make or Driver (Placeholder)\n";
        cout << " 5. Return to Main Menu\n";
        cin >> choice;

        switch(choice){
            case 1:
                clearScreenDisplayBanner();
                cout << "==== Add New Vehicle (Placeholder) ====\n";
                addVehicle();
                pauseScreen();
                break;
            case 2:
                clearScreenDisplayBanner();
                cout << "==== View All Vehicles (Placeholder) ====\n";
                viewAllVehicles();
                pauseScreen();
                break;
            case 3:
                clearScreenDisplayBanner();
                cout << "==== Assign Vehicle to Driver (Placeholder) ====\n";
                assignVehicleToDriver();
                pauseScreen();
                break;
            case 4:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while(choice != 4);
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
