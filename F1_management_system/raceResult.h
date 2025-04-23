// Responsible - Kenneth Johnson (Association class)
// raceResult.h
#ifndef RACERESULT_H // If the RACERESULT_H is not defined, then define it so header content are only included once.
#define RACERESULT_H 

#include <iostream> // Include  input/output stream funcitons.
#include <string> // Include string library.
#include <iomanip> // Included for formatting the output.

using namespace std; // Uses namespace std librart names without std prefix.

// Forward declarations.
class Driver;
class RaceEvent;

// Declaration of association class linking the Driver RaceEvent to RaceResult.
class RaceResult {
    // Private access specifier.
    private:
        Driver* driver; // Holds a pointer to a specific driver for the result. (Not const, incase we need to modidy driver, e.g. increment a race).
        const RaceEvent* event; // Holds a pointer to a specific event for the result. (Const, as we only need to read and not modify RaceEvent. Result never modifies a race). 
        int position; // Has its own attribute position of type int.
        float lapTime; // Has its own attribute lapTime  of type float.
   
    // Public access specifier.
    public:
        // Constructor to initialise all member variables.
        // Contains pointer to a Driver object, pointer to RaceEvent object, int and float. 
        RaceResult(Driver* d, const RaceEvent* e, int pos, float time);

        // Overloaded operator to combine two results into one
        RaceResult operator+(const RaceResult& o) const;

        // Display this result on the screen
        void displayRaceResult() const; // Const after the declaration, since we dont need to modify just display.

        // Getters
        int getPosition() const; // Returns the finishing position.
        float getRaceTime() const; // Returns the lap time.
        Driver* getDriver() const; // returns the Associated Driver pointer.


};

// End of RACERESULT_H include guard, prevent multiple inclusions of this header.
#endif // RACERESULT_H
