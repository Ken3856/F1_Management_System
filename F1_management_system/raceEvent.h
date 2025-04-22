//Task by Adam Bance
// raceevent.h
#ifndef RACEEVENT_H
#define RACEEVENT_H
//include core data type 
#include <string>
#include <vector>
#include "date.h"        // Date class
#include "raceResult.h"  // RaceResult forward declaration

using namespace std;

class Driver;//forward declare of the driver class to avoid full include

class RaceEvent {// this class here will store details about a single race event
private:
    string eventName;// this the name of the event 
    Date eventDate;   // "has-a" Date meaning its composition with class with Data
    string eventTime;//time of the event
    string eventLocation;//this is for its location
    vector<RaceResult*> raceResults;//list of results for the race using vectors(linked to the driver)

public:
    // Constructors & Destructor
    RaceEvent();// the default constructor in case if needed
    RaceEvent(const string& name, const Date& date, const string& time, const string& location);//the constructor with values to set up event with all key details
    ~RaceEvent();// Destructor here is needed to manage cleanup of dynamic RaceResult pointers

    // Record a result
    void addRaceResult(Driver* d, int position, float lapTime);// Adds a RaceResult entry linked to a Driver, with their position and lap time

    // Display methods
    void displayRaceDetails() const;//this function Shows all race event info: name, date, time, location, and results
    void displayPodium() const; // Shows just the top 3 drivers in the race

    // Getters
    const string& getName() const;// Getter function for the name of the event
    const string& getLocation() const; // Getter for the event's location
    string getDate() const;// Getter for the date as a formatted string 
    const string& getTime() const;// Getter for the time of the event
    const vector<RaceResult*>& getRaceResults() const;// Getter for all race results used by other classes or printing
};

#endif // RACEEVENT_H

