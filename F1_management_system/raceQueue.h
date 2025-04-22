#ifndef RACEQUEUE_H    // by Yifan Xiang
#define RACEQUEUE_H

#include <string>
#include "RaceEvent.h"

class RaceNode{
    public:
        // explicit RaceNode(const RaceEvent& e);
        RaceEvent data; // RaceEvent type of data
        RaceNode* next;// a pointer point to the next node

        RaceNode(RaceEvent e);
        RaceNode();
};

class RaceQueue {
    private:
        RaceNode* listhead;
        RaceNode* listtail;
    
    public:
        RaceQueue();//
        RaceQueue(const RaceQueue& q);
        ~RaceQueue();//destruct function

        void addRaceToQueue(const RaceEvent& e);//add function
        RaceEvent pop();//pop function
        void showQueue();// show nodes in queue
        void deleteRaceNode();// delete function


};

#endif // RACEQUEUE_H
