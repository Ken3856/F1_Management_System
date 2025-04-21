// raceResult.h
#ifndef RACERESULT_H
#define RACERESULT_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Forward declarations
class Driver;
class RaceEvent;

class RaceResult {
    private:
        Driver* driver;
        const RaceEvent* event;
        int position;
        float lapTime;

    public:
        RaceResult(Driver* d, const RaceEvent* e, int pos, float time);

        // Combine two results
        RaceResult operator+(const RaceResult& o) const;

        // Display this result
        void displayRaceResult() const;

        // Getters
        int getPosition() const;
        float getRaceTime() const;
        Driver* getDriver() const;


};

#endif // RACERESULT_H