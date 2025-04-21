// raceevent.h
#ifndef RACEEVENT_H
#define RACEEVENT_H

#include <string>
#include <vector>
#include "date.h"        // Date class
#include "raceResult.h"  // RaceResult forward declaration

using namespace std;

class Driver;

class RaceEvent {
private:
    string eventName;
    Date eventDate;   // "has-a" Date
    string eventTime;
    string eventLocation;
    vector<RaceResult*> raceResults;

public:
    // Constructors & Destructor
    RaceEvent();
    RaceEvent(const string& name, const Date& date, const string& time, const string& location);
    ~RaceEvent();

    // Record a result
    void addRaceResult(Driver* d, int position, float lapTime);

    // Display methods
    void displayRaceDetails() const;
    void displayPodium() const;

    // Getters
    const string& getName() const;
    const string& getLocation() const;
    string getDate() const;
    const string& getTime() const;
    const vector<RaceResult*>& getRaceResults() const;
};

#endif // RACEEVENT_H

