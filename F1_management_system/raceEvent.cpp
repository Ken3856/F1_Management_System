// raceEvent.cpp
#include "raceEvent.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Default constructor
RaceEvent::RaceEvent() : eventName(""), eventDate(), eventTime(""), eventLocation("") {}

// Parameterized constructor
RaceEvent::RaceEvent(const string& name, const Date& date, const string& time, const string& location)
    : eventName(name), eventDate(date), eventTime(time), eventLocation(location) {}

// Destructor: cleans up allocated RaceResult pointers
RaceEvent::~RaceEvent(){
    for (RaceResult* rr : raceResults){
        delete rr;
    }
}

void RaceEvent::addRaceResult(Driver* d, int position, float lapTime){
    raceResults.push_back(new RaceResult(d, this, position, lapTime));
}

void RaceEvent::displayRaceDetails() const{
    cout << "\n=== RACE EVENT: " << eventName << " ===\n"
         << "Date: "             << eventDate << "\n"
         << "Time: "             << eventTime << "\n"
         << "Location: "         << eventLocation << "\n\n"
         << "-- All Results --" << endl;
    for (RaceResult* r : raceResults) {
        r->displayRaceResult();
    }
}

void RaceEvent::displayPodium() const{
    vector<RaceResult*> sorted = raceResults;
    sort(sorted.begin(), sorted.end(),
         [](RaceResult* a, RaceResult* b) {
             return a->getPosition() < b->getPosition();
         });
    cout << "\nPodium:\n";
    for (int i = 0; i < min(3, (int)sorted.size()); ++i) {
        sorted[i]->displayRaceResult();
    }
}

const string& RaceEvent::getName() const{
    return eventName;
}

const string& RaceEvent::getLocation() const{
    return eventLocation;
}

string RaceEvent::getDate() const{
    return eventDate.getDateString();
}

const string& RaceEvent::getTime() const{
    return eventTime;
}

const vector<RaceResult*>& RaceEvent::getRaceResults() const{
    return raceResults;
}
