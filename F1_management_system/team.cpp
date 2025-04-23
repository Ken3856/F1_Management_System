// Responsible - Kenneth Johsnon (Qualified Association)

#include "team.h" // Include the header file for Team class.
#include "driver.h" // Include the driver file for Driver class. 
#include "engineer.h" // Inlclude the header file for Engineer class.

// Constructor for team with initialisation list for team name.
Team::Team(const string& name) : name(name){}

// Destructor for Team
Team::~Team(){
    // We do not own the Driver/Engineer pointers, so don't delete them here.
}

// Assigns a drive to a role within a Team. Take a key (role) and a pointer to the driver (d).
void Team::assignRoleToDriver(const string& role, Driver* d){
    roleToDriverMap[role] = d; // Updates the role to driver map enabling qualified association.
}

// Retrieves the Driver associated with the role within the team. string represents the role to be search for
// A pointer to the assigned driver to the role or nullptrif the role is not found.
Driver* Team::getDriverByRole(const string& role) const{
    unordered_map<string, Driver*>::const_iterator it = roleToDriverMap.find(role);
    return it != roleToDriverMap.end() ? it->second : nullptr; // If found, return the associated Driver pointer.    
}                                                              // Else, if not found returns nullptr.

// Assigns an engineer to a specific role within the team. String represents the engineer role.
// "e" is a pointer to the engineer object to be assigned. 
void Team::assignEngineer(const string& role, Engineer* e){
    roleToEngineerMap[role] = e; // Inserts the role to engineer map enabling qualified association.
}

// Retrieves the Engineer associated with the specific role in the team.
// String is the role to search for, returns a pointer to Engineer assigned that role or nullptr if not found.
Engineer* Team::getEngineerByRole(const string& role) const{
    unordered_map<string, Engineer*>::const_iterator it = roleToEngineerMap.find(role); // Searches engineer-role map.
    return it != roleToEngineerMap.end() ? it->second : nullptr; // Returns the pointer for Engineer if found, otherise returns a nullptr.
}

// Returns the name of the team.
// Returns a const reference t the string that represents a team.
const string& Team::getName() const{
    return name; // Returns the name member of the Team object.
}
