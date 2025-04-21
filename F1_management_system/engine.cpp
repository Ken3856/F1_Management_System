#include "engine.h"

Engine::Engine(const string& t, int hp): type(t), horsepower(hp){}

Engine::~Engine(){}

string Engine::getType() const{
    return type;
}

int Engine::getHorsepower() const{
    return horsepower;
}

void Engine::showEngineInfo() const{
    cout << "Engine Type: " << type
         << ", Horsepower: " << horsepower << endl;
}
