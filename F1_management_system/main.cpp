// main.cpp
// Compilation command  g++ *.cpp  -o f1_manager
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>

// .h files
#include "date.h"
#include "person.h"
#include "driver.h"
#include "engineer.h"
#include "team.h"
#include "vehicle.h"
#include "car.h"
#include "raceEvent.h"
#include "raceResult.h"
#include "raceQueue.h"
#include "raceManager.h"
#include "driver_queue.h"
#include "engineer_queue.h"
#include "person_queue.h"
#include "engine.h"

using namespace std;

// ************ Global Structures & Objects ************
DriverQueue driverQueue;
EngineerQueue engineerQueue;
unordered_map<string, Team*> teams;  // For qualified association
vector<Driver*> allDrivers;
vector<Engineer*> allEngineers;
vector<Vehicle*> allVehicles;
RaceManager raceManager;
RaceQueue raceQueue;


// Forward declarations
// Menu screens
void personnelManagement();
void raceManagement();
void searchByTeamAndRole();
void vehicleManagement();
void performanceStats();
void mainMenu();

// Supporting functions
void addVehicle();
void viewAllVehicles();
void assignVehicleToDriver();
void registerDriver();
void registerEngineer();
void searchDriverByTeamAndRole();
void searchEngineerByTeamAndRole();



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

// ******** Supporting functions **********************
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
    string driverID;
    getline(cin, driverID);

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
    teams[teamName]->assignRoleToDriver(role, d);

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
