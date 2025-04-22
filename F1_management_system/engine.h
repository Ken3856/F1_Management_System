// Responsible: Eamon Mahrooq
// Car has an Engine (composition)
#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <iostream>

using namespace std;

// Engine class
class Engine{
    private:
        string type;
        int horsepower;
    
    public:
// Constructor and destructor prototype
        Engine(const string& t, int hp);
        ~Engine();
    
        // Getters
        string getType() const;
        int getHorsepower() const;
        void showEngineInfo() const;
};

#endif // ENGINE_H
