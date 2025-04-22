//Task by Adam Bance
// raceEvent.cpp
#include "raceEvent.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Default constructor which is used to create empty raceevent first
RaceEvent::RaceEvent() : eventName(""), eventDate(), eventTime(""), eventLocation("") {}

// this Parameterized constructor sets up the race event with all its main info
RaceEvent::RaceEvent(const string& name, const Date& date, const string& time, const string& location)
    : eventName(name), eventDate(date), eventTime(time), eventLocation(location) {}
// we copy in the date object here which is why this is composition as RaceEvent owns a Date
// Destructor: cleans up allocated RaceResult pointers stored in vectors
RaceEvent::~RaceEvent(){
    for (RaceResult* rr : raceResults){
        delete rr;// free all the memory for each result
    }
}
// This function adds a race result for a specific driver
void RaceEvent::addRaceResult(Driver* d, int position, float lapTime){
    raceResults.push_back(new RaceResult(d, this, position, lapTime));// We create a new RaceResult object dynamically Then we add it to the raceResults list 
}
// this Prints all race event details and every driver's result
void RaceEvent::displayRaceDetails() const{
    cout << "\n=== RACE EVENT: " << eventName << " ===\n"
         << "Date: "             << eventDate << "\n"// Date is an object; << is overloaded to print it
         << "Time: "             << eventTime << "\n"
         << "Location: "         << eventLocation << "\n\n"
         << "-- All Results --" << endl;
    for (RaceResult* r : raceResults) {//loop through every result and display it
        r->displayRaceResult();// this prints the drivers position,name and lap time
    }
}

void RaceEvent::displayPodium() const{// This shows only the top 3 finishers
    vector<RaceResult*> sorted = raceResults;// make a copy so we can sort safely
    sort(sorted.begin(), sorted.end(),//this will Sort results by position 1st, 2nd, 3rd
         [](RaceResult* a, RaceResult* b) {
             return a->getPosition() < b->getPosition();// here we say the smallest position = best
         });
    cout << "\nPodium:\n"; // Print the top 3 only, or less if there aren't enough drivers
    for (int i = 0; i < min(3, (int)sorted.size()); ++i) {
        sorted[i]->displayRaceResult();
    }
}

const string& RaceEvent::getName() const{// Simple getter for the event name
    return eventName;//give back the event name 
}

const string& RaceEvent::getLocation() const{// Getter for the event location
    return eventLocation;//give back the events location
}

string RaceEvent::getDate() const{// Returns the event date as a string
    return eventDate.getDateString();// this calls the Date class method
}

const string& RaceEvent::getTime() const{// Returns the time of the event
    return eventTime;
}

const vector<RaceResult*>& RaceEvent::getRaceResults() const{// Returns all the race results stored in the event
    return raceResults;
}
