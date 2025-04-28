// raceResult.cpp
//resposible:Adam Bance
#include "raceResult.h"
#include "driver.h"
#include "raceEvent.h"
// Constructor for RaceResult
RaceResult::RaceResult(Driver* d, const RaceEvent* e, int pos, float time)
    : driver(d), event(e), position(pos), lapTime(time) {} // Initialize member variables with the given parameters
// Overloaded + operator for RaceResult objects
RaceResult RaceResult::operator+(const RaceResult& o) const{
    //this Adds the lap times of the two RaceResult objects
    float total = lapTime + o.lapTime;
    int avg = (position + o.position) / 2;// Then Calculate the average position between the two RaceResults
    return RaceResult(nullptr, nullptr, avg, total); // Return a new RaceResult object with nullptr driver/event, avg position, total time
}

void RaceResult::displayRaceResult() const{//Display the RaceResult Details
    int mm = static_cast<int>(lapTime) / 60;//Calculate the minuites from the lap times
    int ss = static_cast<int>(lapTime) % 60;// Calculate the remaining seconds after minutes are taken out
    int ms = static_cast<int>((lapTime - mm*60 - ss) * 1000 + 0.5f);// Calculate the remaining milliseconds (with rounding)

    cout << "\n[RACE RESULT]" << endl; //print out header
    cout << "Event: "  << event->getName() << endl;// Print the name of the event by useing event pointer to call getName()
    cout << "Driver: " << driver->getName() << endl;// Print the name of the Driver uses driver pointer to call getName()
    cout << "Time: " // Print the formatted lap time in mm:ss.mmm 
         << setw(2) << setfill('0') << mm << ':'// make sure minutues are 2 digits
         << setw(2) << setfill('0') << ss << '.'//make sure secounds are 2 digits
         << setw(3) << setfill('0') << ms << endl;// making sure millisecounds are 3 digits
    cout << "Position: " << position << endl; //print out race positions
}
//Getter for race position
int RaceResult::getPosition() const{
    return position; //return position value
}
//getter for Racetime 
float RaceResult::getRaceTime() const{
    return lapTime; // Return laptime value
}
//getter for RaceResult
Driver* RaceResult::getDriver() const{
    return driver;//Returns the pointer to the Driver object
}
