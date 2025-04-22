#ifndef RACEQUEUE_H    // by Yifan Xiang
#define RACEQUEUE_H

#include <string>
#include "RaceEvent.h"

class RaceNode{
    public:
        // explicit RaceNode(const RaceEvent& e);
        RaceEvent data; // RaceEvent type of data
        RaceNode* next;// a pointer point to the next node

        RaceNode(RaceEvent e);//when input the data, constructor
        RaceNode();//default value.
};

class RaceQueue {
    private:
        RaceNode* listhead;
        RaceNode* listtail;
    
    public:
        RaceQueue();//default value
        RaceQueue(const RaceQueue& q);//copy function
        ~RaceQueue();//destruct function，It is automatically called when an object ends its life cycle
                     //(for example, it is deleted) to release resources and clear memory.

        void addRaceToQueue(const RaceEvent& e);//add function
        RaceEvent pop();//pop function
        void showQueue();// show nodes in queue
        void deleteRaceNode();// delete function


};

#endif // RACEQUEUE_H
