// RaceManager.h
#ifndef RACEMANAGER_H
#define RACEMANAGER_H

#include <vector>
#include <string>
#include "RaceEvent.h"
#include "Driver.h"
#include "RaceQueue.h"

using namespace std;

class RaceManager{
private:
    vector<RaceEvent*> races;

public:
    // Destructor to clean up allocated race objects 
    ~RaceManager();

    // Get pointer to the most recently scheduled race (or nullptr if none)
    RaceEvent* getLastRace() const;

    // Schedule a new race and enqueue it
    void scheduleRace(RaceQueue &rq);

    // Enter results for the last scheduled race using all registered drivers
    void enterRaceResults(const vector<Driver*>& allDrivers);

    // Display podiums for all races
    void viewRaceResults() const;

    // Compute and return the average lap time across all races
    double getAverageLapTime() const;

    // Display the average lap time
    void displayAverageLapTime() const;
};

#endif // RACEMANAGER_H