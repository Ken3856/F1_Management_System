// RaceManager.cpp
#include "raceManager.h"
#include <iostream>// For user input/output
#include <iomanip>//for when printing lap times
#include "Engine.h"  // for Fractional time parsing, if needed
#include "utils.h"// Contains input handling functions 

using namespace std;

RaceManager::~RaceManager(){ // Destructor is used to delete all RaceEvent pointers to avoid memory leaks
    for (RaceEvent* r : races){
        delete r;// Each RaceEvent was created with new, so we must delete them
    }
}

RaceEvent* RaceManager::getLastRace() const{// Returns the most recent RaceEvent or nullptr if none of them exist
    if (races.empty()){
        return nullptr;//this means  No races exist yet after checking
    }
    return races.back();// Return the most recently added race
}

void RaceManager::scheduleRace(RaceQueue &rq){// This function allows the user to input and schedule a new race event
    string name, time, loc;
    Date raceDate;

    cout << "Enter event name: ";// Ask for event name
    getline(cin, name);

    cout << "Enter race date (DD-MM-YY): "; // Ask for date in specific format and read as a Date object
    cin >> raceDate;
    if (cin.fail()){
        handleInvalidInputChar();// Handle if the input was not a valid date
        return;
    }
    cin.ignore();// Clear leftover newline

    cout << "Enter race time (e.g. 14:00): ";//this will Ask for time
    getline(cin, time);

    cout << "Enter race location: ";// Ask for location
    getline(cin, loc);

    RaceEvent* r = new RaceEvent(name, raceDate, time, loc);// Create a new RaceEvent with all inputted data
    races.push_back(r);// Add the race to our internal list of races
    rq.addRaceToQueue(*r);// this also adds it to the race queue another structure that manages races

    cout << "Race successfully scheduled.\n";
}

void RaceManager::enterRaceResults(const vector<Driver*>& allDrivers){// This function lets the user enter results for each driver in the most recent race
    if (races.empty() || allDrivers.empty()){//checking statement to see if the user entered nothing
        cout << "Make sure at least one race and one driver are registered.\n";
        return;
    }
    RaceEvent* r = races.back();// We’re adding results to the last race that was scheduled
    cout << "Entering results for: " << r->getLocation()
         << " on " << r->getDate() << "\n";

    for (Driver* d : allDrivers){// For each driver, ask for position and best lap time
        int pos, mins, secs;
        char c1, c2;// To hold : characters
        string frac;// For fractional milliseconds


        cout << "\nDriver: " << d->getName() << "\n";
        cout << "Enter position: ";
        cin >> pos;
        if (cin.fail()){
            handleInvalidInputChar();// Input error
            return;
        }
        cin.ignore();

        cout << "Enter best lap time (MM:SS:FFF): ";
        cin >> mins >> c1 >> secs >> c2 >> frac;
        if (cin.fail() || c1 != ':' || c2 != ':'){
            handleInvalidInputChar();// Wrong format or bad input
            return;
        }
        cin.ignore();

        // Normalise fractional to 3 digits
        while (frac.length() < 3){
            frac.push_back('0');
        }
        if (frac.length() > 3){
            frac = frac.substr(0,3);
        }

        int ms = stoi(frac);
        float lap = mins * 60 + secs + ms / 1000.0f;

        r->addRaceResult(d, pos, lap);
    }
    cout << "Results recorded.\n";
}

void RaceManager::viewRaceResults() const{
    if (races.empty()){
        cout << "No races scheduled.\n";
        return;
    }
    for (RaceEvent* r : races){
        r->displayPodium();
    }
}

double RaceManager::getAverageLapTime() const{// Calculates average lap time across all races and all results
    double total = 0.0;
    int count = 0;
    for (RaceEvent* r : races) {// Loop through all races and all results
        for (RaceResult* res : r->getRaceResults()){
            total += res->getRaceTime();// Add each lap time
            ++count;// Keep count of how many
        }
    }
    if (count == 0){ 
        return 0.0;
    }
    return total / count;
}

void RaceManager::displayAverageLapTime() const{
    if (races.empty()){
        cout << "No races have been run yet." << endl;
        return;
    }
    double avg = getAverageLapTime();
    cout << "Average lap time across all races: " << fixed << setprecision(3) << avg << " seconds" << endl; // Rounds to 3 digits after decimal.
}
