// Responsible: Eamon Mahrooq
#include "engine.h"

// Constructor
Engine::Engine(const string& t, int hp): type(t), horsepower(hp){}

// Destructor
Engine::~Engine(){}

// Getters
string Engine::getType() const{
    return type;
}

int Engine::getHorsepower() const{
    return horsepower;
}

void Engine::showEngineInfo() const{
    cout << "Engine Type: " << type << endl;
    cout << "Horsepower: " << horsepower << endl;
}
