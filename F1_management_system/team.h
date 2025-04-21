#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <unordered_map>

using namespace std;

class Driver;
class Engineer;

class Team{

    private:
    string name;
        unordered_map<string, Driver*>   roleToDriverMap;
        unordered_map<string, Engineer*> roleToEngineerMap;
    
        public:
        Team(const string& n);
        ~Team();

        // Qualified association for Drivers
        void assignRoleToDriver(const string& role, Driver* d);
        Driver* getDriverByRole(const string& role) const;

        // Qualified association for Engineers
        void assignEngineer(const string& role, Engineer* e);
        Engineer* getEngineerByRole(const string& role) const;

        // Getter
        const string& getName() const;

};

#endif // TEAM_H
