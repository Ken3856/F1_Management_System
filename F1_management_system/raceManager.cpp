// RaceManager.cpp
#include "raceManager.h"
#include <iostream>
#include <iomanip>
#include "Engine.h"  // for Fractional time parsing, if needed
#include "utils.h"

using namespace std;

RaceManager::~RaceManager(){
    for (RaceEvent* r : races){
        delete r;
    }
}

RaceEvent* RaceManager::getLastRace() const{
    if (races.empty()){
        return nullptr;
    }
    return races.back();
}

void RaceManager::scheduleRace(RaceQueue &rq){
    string name, time, loc;
    Date raceDate;

    cout << "Enter event name: ";
    getline(cin, name);

    cout << "Enter race date (DD-MM-YY): ";
    cin >> raceDate;
    if (cin.fail()){
        handleInvalidInputChar();
        return;
    }
    cin.ignore();

    cout << "Enter race time (e.g. 14:00): ";
    getline(cin, time);

    cout << "Enter race location: ";
    getline(cin, loc);

    RaceEvent* r = new RaceEvent(name, raceDate, time, loc);
    races.push_back(r);
    rq.addRaceToQueue(*r);

    cout << "Race successfully scheduled.\n";
}

void RaceManager::enterRaceResults(const vector<Driver*>& allDrivers){
    if (races.empty() || allDrivers.empty()){
        cout << "Make sure at least one race and one driver are registered.\n";
        return;
    }
    RaceEvent* r = races.back();
    cout << "Entering results for: " << r->getLocation()
         << " on " << r->getDate() << "\n";

    for (Driver* d : allDrivers){
        int pos, mins, secs;
        char c1, c2;
        string frac;

        cout << "\nDriver: " << d->getName() << "\n";
        cout << "Enter position: ";
        cin >> pos;
        if (cin.fail()){
            handleInvalidInputChar();
            return;
        }
        cin.ignore();

        cout << "Enter best lap time (MM:SS:FFF): ";
        cin >> mins >> c1 >> secs >> c2 >> frac;
        if (cin.fail() || c1 != ':' || c2 != ':'){
            handleInvalidInputChar();
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

double RaceManager::getAverageLapTime() const{
    double total = 0.0;
    int count = 0;
    for (RaceEvent* r : races) {
        for (RaceResult* res : r->getRaceResults()){
            total += res->getRaceTime();
            ++count;
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