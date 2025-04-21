// Version 4.1 - Fixed Compilation Issues and Closer to UML Diagram

// Comments:
// pop() function of RaceQueue and its copy constructor not used. We need to fugure out where
// we are going to use this.


#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;


// Forward declarations
class Driver;
class Engineer;
class RaceEvent;
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

void handleInvalidInputChar() {
    // Handle invalid input using a character
        cin.clear();               // Clear the error state
        cin.ignore(100, '\n');     // Discard invalid input up to the next newline
        cout << "\nInvalid input. Please enter a number." << endl;
        cout << "Press Enter to continue...";
        cin.get();                 // Wait for user to press Enter
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
// To be inherited from by other derived classes
// Responsible: Eamon
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
// To be inherited from by other derived classes
// Responsible: Eamon
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
    // Responsible: Eamon
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
    // Responsible: Eamon
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
class PersonQueue{
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
    
class DriverQueue : public PersonQueue{
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
    
class EngineerQueue : public PersonQueue{
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
            unordered_map<string, Driver*>::const_iterator it = roleToDriverMap.find(role);
            return (it != roleToDriverMap.end()) ? it->second : nullptr;
        }
    
        // Qualified association for Engineers.
    
        void assignEngineer(const string &role, Engineer* e){ // role is the key
            roleToEngineerMap[role] = e;
        }
    
        Engineer* getEngineerByRole(const string &role) const{
            unordered_map<string, Engineer*>::const_iterator it = roleToEngineerMap.find(role);
            return(it != roleToEngineerMap.end()) ? it->second : nullptr;
        }
    };
    
// ******************** Race & Results *********************************
class RaceResult;
//Responsible:Adam
// ************ RaceResult (Association Class) ************
class RaceResult {
    private:
        Driver* driver;    // Points to the associated Driver
        const RaceEvent* event;  // Points back to the associated Race
        int position;
        float lapTime;
    
    public:
        RaceResult(Driver* d, const RaceEvent* e, int pos, float time)
            : driver(d), event(e), position(pos), lapTime(time) {}
    
        void displayRaceResult() const;

        // combine two results 
        RaceResult operator+(const RaceResult& o) const {
            float total = lapTime + o.lapTime;
            int   avg   = (position + o.position)/2;
            return { nullptr, nullptr, avg, total };
        }

        int getPosition() const {return position;}
        float getRaceTime() const {return lapTime;}

        Driver* getDriver() const {return driver;}
};


// ************ Race Event Class ************
//Responsible:Adam
class RaceEvent {
    private:
        string eventName;
        Date   eventDate;  // Composition: Race "has-a" Date
        string eventTime;
        string eventLocation;
        vector<RaceResult*> raceResults;
    
    public:
        RaceEvent(){}
        RaceEvent(const string& name, const Date& d, string time, string loc) 
        : eventName(name), eventDate(d), eventTime(time), eventLocation(loc) {}
    
        ~RaceEvent() {
            // Clean up RaceResult pointers
            for (RaceResult* rr : raceResults) { delete rr;}
        }
    
        // factory style: create & store a new RaceResult
        void addRaceResult(Driver* d, int pos, float lap) {
            raceResults.push_back(new RaceResult(d, this, pos, lap));
        }
    
        void displayRaceDetails() const {
            cout << "\n=== RACE EVENT: " << eventName << " ===\n"
                 << "Date:     "         << eventDate     << "\n"
                 << "Time:     "         << eventTime     << "\n"
                 << "Location: "         << eventLocation << "\n\n"
                 << "-- All Results --\n";
            for (RaceResult* r : raceResults)
              r->displayRaceResult();
          }
    
    
        void displayPodium() const {
            vector<RaceResult*> sorted = raceResults;
            sort(sorted.begin(), sorted.end(),
                [](RaceResult* a, RaceResult* b){ return a->getPosition() < b->getPosition(); });
            cout << "\n Podium:\n";
            for (int i = 0; i < min(3, (int)sorted.size()); ++i){
                sorted[i]->displayRaceResult();
            }
        }
    
        // Getters
        const string& getName()     const { return eventName; }
        const string& getLocation() const { return eventLocation; }
        const string  getDate()     const { return eventDate.getDateString(); }
        const string& getTime()     const { return eventTime; }

        
        const vector<RaceResult*>& getRaceResults() const {
            return raceResults;
        }

        
        friend class RaceResult; // Allow RaceResult to access private members if needed.
    };
    


// ************ RaceQueue Class for Race Management ************
class RaceNode {
    public:
        RaceEvent data;
        RaceNode* next;

        RaceNode(RaceEvent e) : data(e), next(NULL) {}
        RaceNode() :data(RaceEvent()), next(NULL) {}
};
    
class RaceQueue {
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
            while(listhead != NULL){ //as long as the queue is not empty
                temp = listhead;   //put listhead to dynamic temp
                listhead = listhead->next;  //get a new listhead
                delete temp;   //delete dynamic temp
            }
        }
        RaceQueue(const RaceQueue& q);
        void addRaceToQueue(const RaceEvent& e);
        void showQueue();
        RaceEvent pop();
        void deleteRaceNode();
};


void RaceQueue::addRaceToQueue(const RaceEvent& e){
    RaceNode* temp = new RaceNode(e);

    if (temp == NULL){ //check the overflow
        cout << "overflow error" << endl;
    }
    else{
        if (listhead == NULL){   // if the queue is empry
            listhead = temp;
            listtail = temp;// new node would be the list head and tail
        }
        else{
            listtail->next = temp;// put new node at the end of queue
            listtail = temp;     // update new listtail
        }
    }
}
    
RaceEvent RaceQueue::pop(){
    if (listhead == NULL){   //if it's an empty queue ,then return a default value Class Student
        cout << "underflow error" << endl;
        return RaceEvent();
    }
    else
    {
        RaceNode* temp = listhead;//push listhead to temp (dynamic memory)
        RaceEvent poppedRace = listhead->data;//put the data of listhead to an new object 
        listhead = listhead->next;//let the next of original listhead be the new listhead
        delete temp;//delete the dynamic
        return poppedRace;//return the value 
        
    }
}
        
RaceQueue::RaceQueue(const RaceQueue& q){
    RaceNode* hold = q.listhead;//let hold be as the The head pointer of the source queue
    RaceNode* temp;
    RaceNode* oldtemp;

    if (hold == NULL){    //if the source queue is empty,then the cory queue be empty too
        listhead = NULL;
        listtail = NULL;
    }
    else{

        // (!!!**** This creates a memory leak! :) fixed it ***)
        // temp = new RaceNode;   //create a new nede, give it to temp 
        // listhead = temp;    //let the new node be the new listhead of copy queue

        RaceNode* temp = listhead;

        while (hold != NULL)  //if the hold has something, starts to traverse the source queue
        {
            temp->data = hold->data;   //as we set the hold is head of source queue before, now put it to the head of copy queue 
            oldtemp = temp;  //now temp is oldtemp, 
            hold = hold->next;   //make the next of hold before be the new hold, continue to traverse
            if (hold != NULL){     //check if the hold gets the end of source queue
                temp = new RaceNode;//there is still has somthing to copy, create a new node 
                oldtemp->next = temp;//connect temp and oldtemp
            }
        }
        listtail = temp;//after finishing the traverse, we make the last one temp as listtail
        listtail->next = NULL;//Make sure the next pointer of the tail node is NULL
    }
}

void RaceQueue:: showQueue(){
    if (listhead == NULL){
        cout << "The Queue of Race is empty." << endl;
        return;
    }
    else{
        cout << "=== Race Queue ===" << endl;
        RaceNode* temp = listhead;
        int count = 1;
        while (temp != NULL){
            cout << "Race # " << count << " :" << endl;
            cout << "Event Name: " << temp->data.getName() << endl;
            cout << "Event Date: " << temp->data.getDate() << endl;
            cout << "Event Time: " << temp->data.getTime() << endl;
            cout << "Location: " << temp->data.getLocation() << endl; // Use getters instead of temp->data.showRaces();
            temp = temp->next;
            count++;
        }
    }
}

void RaceQueue:: deleteRaceNode(){
    if (listhead == NULL){
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
    if (cin.fail()) {
        handleInvalidInputChar();
        return;
    }
    cin.ignore();


    if (num<1 || num>total){
        cout << "error input,please choose a number between 1 and " << total << endl;
        return;
    }

    string confirm;
    cout << "Are you sure you want to delete Race # " << num << " (yes/no)" << endl;
    cin >> confirm;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;
    }
    cin.ignore();

    if (confirm != "Yes" && confirm != "yes" && confirm != "YES"){
        cout << "deletion cancled " << endl;
        return;
    }
    RaceNode* current = listhead;
    RaceNode* prev = NULL;

    if (num == 1){
        listhead = current->next;
        delete current;
        if (listhead == NULL){
            listtail = NULL;
        }
        cout << "Race # 1 has been deleted" << endl;
        return;
    }
    for (int i=1;i < num;i++){
        prev = current;
        current = current->next;
    }
    prev->next = current->next;
    if (current == listtail){
        listtail = prev;
    }
    delete current;

    cout << "Race # " << num << " has been deleted !" << endl;
}

    
// ************ RaceManager ************

//Responsible:Adam
class RaceManager{
    private:
        vector<RaceEvent*> races;
    
    public:
        ~RaceManager() {
            // Clean up allocated Race objects
            for (RaceEvent* r : races) {
                delete r;
            }
        }

        RaceEvent* getLastRace() const {
            if (races.empty()) return nullptr;
            return races.back();
          }
    
        // Create & store new race
        void scheduleRace(class RaceQueue &rq) {
            string name;
            cout << "Enter event name: ";
            getline(cin, name);

            cout << "Enter race date (DD-MM-YY): ";
            Date d;
            cin >> d; // Uses operator oveloading.
            if (cin.fail()) {
                handleInvalidInputChar();
                return;
            }
            cin.ignore();

            string time;
            cout << "Enter race time (e.g. 14:00): ";
            getline(cin, time);

            string loc;
            cout << "Enter race location: ";
            getline(cin, loc);
    
            RaceEvent* r = new RaceEvent(name, d, time, loc);
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
            RaceEvent* r = races.back();
            cout << "Entering results for: " << r->getLocation()
                 << " on " << r->getDate() << "\n";
    
            for (Driver* d : allDrivers) {
                int pos, mins, secs;
                char c1, c2;
                string frac;

                cout << "\nDriver: " << d->getName() << "\n";
                cout << "Enter position: ";
                cin >> pos;
                if (cin.fail()) {
                    handleInvalidInputChar();
                    return;
                }
                cin.ignore();

                // Enter Lap time
                cout << "Enter best lap time (MM:SS:FFF): ";            
                // read something like “05:12:08” or “5:12:8” or “05:12:008”
                cin >> mins >> c1 >> secs >> c2 >> frac;
                if (cin.fail() || c1 != ':' || c2 != ':') {
                    handleInvalidInputChar();
                    return;
                }
                cin.ignore();
                // normalize fractional part to exactly 3 digits
                while (frac.length() < 3) frac.push_back('0');
                if (frac.length() > 3)  frac = frac.substr(0,3);
            
                int ms = stoi(frac);
                float lap = mins*60 + secs + ms/1000.0f;

                r->addRaceResult(d, pos, lap);
            
            }
            cout << "Results recorded.\n";
        }
    
        // Show results for all races
        void viewRaceResults() const{
            if (races.empty()) {
                cout << "No races scheduled.\n";
                return;
            }
            for (RaceEvent* r : races){
                r->displayPodium();
            }
        }

        double getAverageLapTime() const{
            double total = 0.0;
            int count = 0;
            for (size_t i = 0; i < races.size(); ++i) {
                const vector<RaceResult*>& results = races[i]->getRaceResults();  // make raceResults public or add a getter
                for (size_t j = 0; j < results.size(); ++j) {
                    total += results[j]->getRaceTime();
                    ++count;
                }
            }
            if (count == 0) return 0.0;
            return total / count;
        }

        void displayAverageLapTime() const {
            if (races.empty()){
                cout << "No races have been run yet." << endl;
                return;
            }

            double avg = getAverageLapTime();
            cout << "Average lap time across all races: " << fixed << setprecision(3) << avg << " seconds\n"; // Rounds to 3 digits after decimal.
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


// ****************** Free funcitons & Menus **************************** */

// Added this ***** Vehicle Management functions ********************** */
void addVehicle(){
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
    if (cin.fail()) {
        handleInvalidInputChar();
        return;
    }
    cin.ignore();
    cout << "Enter Engine Type: ";
    getline(cin, engineType);
    cout << "Enter Horsepower: ";
    cin >> horsepower;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;
    }
    cin.ignore();

    Vehicle* newVehicle = new Car(make, model, color, maxSpeed, engineType, horsepower);
    allVehicles.push_back(newVehicle);

    cout << "Vehicle added successfully!\n";
}

void viewAllVehicles(){
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
    cout << "Choose a vehicle: " << endl;
    for(int i = 0 ; i < allVehicles.size() ; i++){ // List all vehicles
        cout << i+1 << ". " << allVehicles[i]->getMake() << " " << allVehicles[i]->getModel() << endl;
    }

    int vehicleChoice;
    cin >> vehicleChoice;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;  // Loop back
    }
    cin.ignore();

    cout << "Choose a Driver: " << endl;
    for(int i = 0 ; i < allDrivers.size() ; i++){
        cout << i+1 << ". " << allDrivers[i]->getName() << endl;
    }
    int driverChoice;
    cin >> driverChoice;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;  // Loop back
    }
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
    if (cin.fail()) {
        handleInvalidInputChar();
        return;  // Loop back
    }
    cin.ignore();

    // Uses operator overloading
    cout << "Enter Driver date of birth (DD-MM-YY): ";
    Date dob;
    cin >> dob; // Uses istream& operator >>(istream&, Date&)
    if (cin.fail()) {
        handleInvalidInputChar();
        return;  // Loop back
    }
    cin.ignore();

    cout << "Enter Driver ID: ";
    int driverID;
    cin >> driverID;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;  // Loop back
    }
    cin.ignore();

    cout << "Enter Team Name (e.g. Red, Green, Blue): ";
    string teamName;
    getline(cin,teamName);
   
    cout << "Enter driver number: ";
    int driverNumber;
    cin >> driverNumber;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;  // Loop back function
    }
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

void registerEngineer(){
    cout << "Enter Engineer name: ";
    string ename;
    getline(cin, ename);

    cout << "Enter age: ";
    int age;
    cin >> age;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;
    }
    cin.ignore();

    // Read date using overloaded operator
    cout << "Enter enngineer date of birth (DD-MM-YY): ";
    Date dob;
    cin >> dob;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;
    }
    cin.ignore();


    cout << "Enter Engineer ID: ";
    string engID;
    cin >> engID;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;
    }
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
    cout << "Enter the Engineer role (e.g Senior Engineer, Junior Engineer, Technician): ";
    string role;
    getline(cin, role);
    teams[teamName]->assignEngineer(role,e);

    cout << "Engineer registered and added to team successfully!\n";
}

// ************ Searching - Qualified Assoiciation************
void searchDriverByTeamAndRole(){
    cout << "Enter team name (e.g., Red, Green, Blue): ";
    string teamName;
    getline(cin, teamName);

    cout << "Enter driver role (e.g., Main Driver, Reserve Driver): ";
    string role;
    getline(cin, role);

    if (teams.find(teamName) != teams.end()){
        Driver* found = teams[teamName]->getDriverByRole(role);
        if (found) {
            cout << "\nDriver found!!! " << endl;
            found->displayInfo();
        }else{
            cout << "No Driver found for role '" << role
            << "' in team " << teamName << ".\n";
        }
    } else{
        cout << "Team not found.\n";
    }
}

void searchEngineerByTeamAndRole() {
    cout << "Enter team name (e.g., Red, Green, Blue): ";
    string teamName;
    getline(cin, teamName);

    cout << "Enter engineer role (e.g., Senior Engineer, Junior Engineer, Technician): ";
    string role;
    getline(cin, role);

        if (teams.find(teamName) != teams.end()){
        Engineer* found = teams[teamName]->getEngineerByRole(role);
        if (found) {
            cout << "\nEngineer found!!! " << endl;
            found->displayInfo();
        } else {
            cout << "No engineer found for role '" << role
                 << "' in team " << teamName << ".\n";
        }
    } else {
        cout << "Team not found.\n";
    }
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

void RaceResult::displayRaceResult() const {
    int mm = int(lapTime) / 60;
    int ss = int(lapTime) % 60;
    int ms = int((lapTime - mm*60 - ss)*1000 + .5f);
    cout << "\n[RACE RESULT]\n"
         << "Event:    " << event->getName()   << "\n"
         << "Driver:   " << driver->getName()  << "\n"
         << "Time:     "
        << setw(2) << setfill('0') << mm << ':'
        << setw(2) << setfill('0') << ss << '.'
        << setw(3) << setfill('0') << ms << "\n";
    cout << "Position: " << position     << endl;

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
        if (cin.fail()) {
            handleInvalidInputChar();
            continue;  // re‑draw the same menu
        }
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
        cout << " 2. View Scheduled Races \n";
        cout << " 3. Enter Race Results\n";
        cout << " 4. View Race Results\n";
        cout << " 5. Delete Past Race \n";
        cout << " 6. Return to Main Menu\n";
        cout << " Enter an option: ";
        cin >> choice;
        if (cin.fail()) {
            handleInvalidInputChar();
            continue;  // re‑draw the same menu
        }
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
                cout << "==== View Scheduled Races ====\n";
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
                cout << "==== Delete Past Race ====\n";
                raceQueue.deleteRaceNode();
                pauseScreen(); // Waits for the user to hit Enter
                break;
            case 6:
                clearScreenDisplayBanner(); // redraw banner 
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while(choice != 6);
}

// ******** Team Management Menu *****************
void searchByTeamAndRole(){
    int choice;
    do {
        clearScreenDisplayBanner();
        cout << "==== Search By Team & Role Menu ====\n\n";
        cout << " 1. Search Driver by Team and Role\n";
        cout << " 2. Search Engineer by Team and Role \n";
        cout << " 3. Return to Main Menu\n";
        cin >> choice;
        if (cin.fail()) {
            handleInvalidInputChar();
            continue;  // re‑draw the same menu
        }
        cin.ignore();

        switch(choice){
            case 1:
                clearScreenDisplayBanner();
                cout << "==== Search Driver by Team and Role ====\n";
                searchDriverByTeamAndRole();
                pauseScreen();
                break;
            case 2:
                clearScreenDisplayBanner();
                cout << "==== Search Engineer by Team and Role ====\n";
                searchEngineerByTeamAndRole();
                pauseScreen();
                break;
            case 3:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while(choice != 3);
}

// ******** Vehicle Management Menu ******************
void vehicleManagement(){
    int choice;
    do {
        clearScreenDisplayBanner();
        cout << "==== Vehicle Management Menu ====\n\n";
        cout << " 1. Add New Vehicle \n";
        cout << " 2. View All Vehicles \n";
        cout << " 3. Assign Vehicle to Driver \n";
        cout << " 4. Return to Main Menu\n";
        cin >> choice;
        if (cin.fail()) {
            handleInvalidInputChar();
            continue;  // re‑draw the same menu
        }
        cin.ignore();

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
        clearScreenDisplayBanner();
        cout << "==== Performance Statistics Menu ====\n\n";
        cout << " 1. Average Lap Time\n";
        cout << " 2. Combine Two Drives Times \n";
        cout << " 3. View Registration counts\n";
        cout << " 4. Return to Main Menu\n";
        cin >> choice;
        if (cin.fail()) {
            handleInvalidInputChar();
            continue;  // re‑draw the same menu
        }
        cin.ignore();

        switch(choice){
            case 1:
                clearScreenDisplayBanner();
                cout << "==== Average Lap Time ====\n";
                raceManager.displayAverageLapTime();
                pauseScreen();
                break;
            case 2:{
                clearScreenDisplayBanner();
                cout << "==== Combine Two Drives Times ====\n";
                RaceEvent* last = raceManager.getLastRace();
                if (! last) {
                    cout << "No race has been run yet.\n";
                    pauseScreen();
                    break;
                }
    
                // Ask for Drivers Name input
                string DriverName1, DriverName2;
                cout << "Enter first Drivers name: ";  
                getline(cin, DriverName1);
                cout << "Enter second Drivers name: "; 
                getline(cin, DriverName2);
            
                // Find each driver's RaceResult
                RaceResult* rr1 = nullptr;
                RaceResult* rr2 = nullptr;
                const vector<RaceResult*>& results = last->getRaceResults();
                for (size_t i = 0; i < results.size(); ++i) {
                    if (results[i]->getDriver()->getName() == DriverName1) rr1 = results[i];
                    if (results[i]->getDriver()->getName() == DriverName2) rr2 = results[i];
                }
            
                if (! rr1 || ! rr2) {
                    cout << "Couldn't find results for one or both drivers in that race.\n";
                    pauseScreen();
                    break;
                }
            
                // use your operator+ to combine
                RaceResult combined = *rr1 + *rr2;
            
                // display combined
                int mm = int(combined.getRaceTime()) / 60;
                int ss = int(combined.getRaceTime()) % 60;
                int ms = int((combined.getRaceTime() - mm*60 - ss)*1000 + .5f);
            
                cout << "\n[COMBINED RESULT]\n"
                     << "Drivers: " << DriverName1 << " + " << DriverName2 << "\n"
                     << "Combined Position (avg): " << combined.getPosition() << "\n"
                     << "Combined Time: "
                     << setw(2) << setfill('0') << mm << ':'
                     << setw(2) << setfill('0') << ss << '.'
                     << setw(3) << setfill('0') << ms << "\n";
                pauseScreen();
                break;
            }
            case 3:
                clearScreenDisplayBanner();
                cout << "==== View Registration counts ====\n";
                cout << "Drivers registered:  " << Driver::getDriverCount()   << "\n"
                     << "Engineers registered: " << Engineer::getEngineerCount()   << "\n"
                     << "Vehicles in fleet:    " << Vehicle::displayVehicleCount() << "\n"
                     << "Cars built:           " << Car::getCarCount() << "\n";
                pauseScreen();
                break;
            case 4:
                clearScreenDisplayBanner();
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while(choice != 4);
}

// ******** Main menu ****************************
void mainMenu(){
    int choice;
    do {
        clearScreenDisplayBanner();
        cout << "====== Main Menu ========\n\n";
        cout << " 1. Personnel Management\n";
        cout << " 2. Race Management\n";
        cout << " 3. Search By Team & Role\n";
        cout << " 4. Vehicle Management\n";
        cout << " 5. Performance & Stats\n";
        cout << " 6. Exit\n";
        cout << " Enter an option: ";
        cin >> choice;
        if (cin.fail()) {
            handleInvalidInputChar();
            continue;  // re‑draw the same menu
        }
        cin.ignore();

        switch(choice){
            case 1:
                personnelManagement();
                break;
            case 2:
                raceManagement();
                break;
            case 3:
                searchByTeamAndRole();
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

    // Memory cleanup of heap memory allocated in heap for containers.
    // delete all Vehicles
    for (Vehicle* v : allVehicles) {
        delete v;
    }
    allVehicles.clear();

    // delete all Teams
    for (const pair<const string, Team*>& kv : teams) {
        delete kv.second;
    }
    teams.clear();
    
    return 0;
}
