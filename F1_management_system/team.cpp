#include "team.h"
#include "driver.h"
#include "engineer.h"

Team::Team(const string& name) : name(name){}

Team::~Team(){
    // We do not own the Driver/Engineer pointers, so don't delete them here.
}

void Team::assignRoleToDriver(const string& role, Driver* d){
    roleToDriverMap[role] = d;
}

Driver* Team::getDriverByRole(const string& role) const{
    unordered_map<string, Driver*>::const_iterator it = roleToDriverMap.find(role);
    return it != roleToDriverMap.end() ? it->second : nullptr;
}

void Team::assignEngineer(const string& role, Engineer* e){
    roleToEngineerMap[role] = e;
}

Engineer* Team::getEngineerByRole(const string& role) const{
    unordered_map<string, Engineer*>::const_iterator it = roleToEngineerMap.find(role);
    return it != roleToEngineerMap.end() ? it->second : nullptr;
}

const string& Team::getName() const{
    return name;
}
