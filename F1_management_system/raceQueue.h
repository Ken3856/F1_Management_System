#ifndef RACEQUEUE_H
#define RACEQUEUE_H

#include <string>
#include "RaceEvent.h"

class RaceNode{
    public:
        // explicit RaceNode(const RaceEvent& e);
        RaceEvent data;
        RaceNode* next;

        RaceNode(RaceEvent e);
        RaceNode();
};

class RaceQueue {
    private:
        RaceNode* listhead;
        RaceNode* listtail;
    
    public:
        RaceQueue();
        RaceQueue(const RaceQueue& q);
        ~RaceQueue();

        void addRaceToQueue(const RaceEvent& e);
        RaceEvent pop();
        void showQueue();
        void deleteRaceNode();


};

#endif // RACEQUEUE_H
