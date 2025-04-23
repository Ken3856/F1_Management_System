// Responsible - Kenneth Johnson (Qualified Association)

// Prevents multiple inclusions of this header file.
#ifndef TEAM_H
#define TEAM_H

#include <string> // Include string library.
#include <unordered_map> // Include unorderd map for mapping roles to pointers.

using namespace std; // Use namespace std to avoid std prefix.

// Forward declaration of classes.
class Driver;
class Engineer;

// Class definition for Team class, which manages the qualified association.
class Team{

    // Private access specifier.
    private:
        string name;
        unordered_map<string, Driver*>   roleToDriverMap; // Map from role (the qualifier) to Driver*
        unordered_map<string, Engineer*> roleToEngineerMap; // Map from role (the qualifier) to Engineer*
   
    // Public access specifier.
    public:
        // Constructor to take a reference to a string 'n' to initialse the teams name.
        Team(const string& n);
        // Destrutor that is called when a Team object is destroyed.
        ~Team();
    
        // Qualified association for Drivers. Qualify a Driver by a role.
    
        void assignRoleToDriver(const string& role, Driver* d); // Maps the Driver pointer 'd' into the teams driver role (key).
        Driver* getDriverByRole(const string& role) const; // Looks up and returns the Driver* stored under the key (role) in the teams driver role map.
    
        // Qualified association for Engineers. Qualify an Engineer by a role.
        void assignEngineer(const string& role, Engineer* e); // Maps the Engineer pointer 'e' into the teams engineer role map under the role (key).
        Engineer* getEngineerByRole(const string& role) const; // Looks up and returns the Engineer* stored under the key (role) in the teams engineer role map.
    
        // Getter
        const string& getName() const; // Returns a const reference to the stored string without copying it. Gets the Teams name. Called on a Team object.

};

#endif // TEAM_H
