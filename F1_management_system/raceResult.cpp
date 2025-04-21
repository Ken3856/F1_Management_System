// raceResult.cpp
#include "raceResult.h"
#include "driver.h"
#include "raceEvent.h"

RaceResult::RaceResult(Driver* d, const RaceEvent* e, int pos, float time)
    : driver(d), event(e), position(pos), lapTime(time) {}

RaceResult RaceResult::operator+(const RaceResult& o) const{
    float total = lapTime + o.lapTime;
    int avg = (position + o.position) / 2;
    return RaceResult(nullptr, nullptr, avg, total);
}

void RaceResult::displayRaceResult() const{
    int mm = static_cast<int>(lapTime) / 60;
    int ss = static_cast<int>(lapTime) % 60;
    int ms = static_cast<int>((lapTime - mm*60 - ss) * 1000 + 0.5f);

    cout << "\n[RACE RESULT]" << endl;
    cout << "Event: "  << event->getName() << endl;
    cout << "Driver: " << driver->getName() << endl;
    cout << "Time: "
         << setw(2) << setfill('0') << mm << ':'
         << setw(2) << setfill('0') << ss << '.'
         << setw(3) << setfill('0') << ms << endl;
    cout << "Position: " << position << endl;
}

int RaceResult::getPosition() const{
    return position;
}

float RaceResult::getRaceTime() const{
    return lapTime;
}

Driver* RaceResult::getDriver() const{
    return driver;
}