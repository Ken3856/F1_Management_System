#include "RaceQueue.h"
#include <iostream>
#include "utils.h"
// RaceNode constructor
RaceNode::RaceNode(RaceEvent e) : data(e), next(nullptr) {}
RaceNode::RaceNode():data(RaceEvent()), next(NULL) {}


// RaceQueue methods
RaceQueue::RaceQueue(){ 
    listhead = NULL;
    listtail = NULL;
}

RaceQueue::~RaceQueue(){
    while (listhead != NULL) { //as long as the queue is not empty
        RaceNode* tmp = listhead; //put listhead to dynamic temp
        listhead = listhead->next; //get a new listhead
        delete tmp; //delete dynamic temp
    }
}

void RaceQueue::addRaceToQueue(const RaceEvent& e){// Dependency by Adam//
    RaceNode* temp = new RaceNode(e);

    if (temp == NULL){ //check the overflow
        cout << "overflow error" << endl;
    }
    else{
        if (listhead == NULL){   // if the queue is empry
            listhead = temp;
            listtail = temp;// new node would be the list head and tail
        }
        else{
            listtail->next = temp;// put new node at the end of queue
            listtail = temp;     // update new listtail
        }
    }
}


RaceEvent RaceQueue::pop(){
    if (listhead == NULL){   //if it's an empty queue ,then return a default value Class Student
        cout << "underflow error" << endl;
        return RaceEvent();
    }
    else{
        RaceNode* temp = listhead;//push listhead to temp (dynamic memory)
        RaceEvent poppedRace = listhead->data;//put the data of listhead to an new object 
        listhead = listhead->next;//let the next of original listhead be the new listhead
        delete temp;//delete the dynamic
        if (!listhead){
            listtail = nullptr;   // reset the tail
        }
        return poppedRace;//return the value 
    }
}



RaceQueue::RaceQueue(const RaceQueue& q){
    RaceNode* hold = q.listhead;//let hold be as the The head pointer of the source queue
    RaceNode* temp;
    RaceNode* oldtemp;

    if (hold == NULL){    //if the source queue is empty,then the cory queue be empty too
        listhead = NULL;
        listtail = NULL;
    }
    else{

        // (!!!**** This creates a memory leak! :) fixed it ***)
        // temp = new RaceNode;   //create a new nede, give it to temp 
        // listhead = temp;    //let the new node be the new listhead of copy queue

        RaceNode* temp = listhead;

        while (hold != NULL)  //if the hold has something, starts to traverse the source queue
        {
            temp->data = hold->data;   //as we set the hold is head of source queue before, now put it to the head of copy queue 
            oldtemp = temp;  //now temp is oldtemp, 
            hold = hold->next;   //make the next of hold before be the new hold, continue to traverse
            if (hold != NULL){     //check if the hold gets the end of source queue
                temp = new RaceNode;//there is still has somthing to copy, create a new node 
                oldtemp->next = temp;//connect temp and oldtemp
            }
        }
        listtail = temp;//after finishing the traverse, we make the last one temp as listtail
        listtail->next = NULL;//Make sure the next pointer of the tail node is NULL
    }
}


void RaceQueue:: showQueue(){
    if (listhead == NULL){
        cout << "The Queue of Race is empty." << endl;
        return;
    }
    else{
        cout << "=== Race Queue ===" << endl;
        RaceNode* temp = listhead;
        int count = 1;
        while (temp != NULL){
            cout << "\nRace # " << count << " :" << endl;
            cout << "Event Name: " << temp->data.getName() << endl;
            cout << "Event Date: " << temp->data.getDate() << endl;
            cout << "Event Time: " << temp->data.getTime() << endl;
            cout << "Location: " << temp->data.getLocation() << endl; // Use getters instead of temp->data.showRaces();
            temp = temp->next;
            count++;
        }
    }
}

void RaceQueue:: deleteRaceNode(){
    if (listhead == NULL){
        cout << "The Queue is empty. Nothing to delete." << endl;
        return;
    }
    int total=0;
    RaceNode* temp = listhead;
    while (temp != NULL)
    {
        total++;
        temp = temp->next;
    }
    int num;
    showQueue();

    cout << "Which Race would you like to delete ? (choose number) " << endl;
    cin >> num;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;
    }
    cin.ignore();


    if (num<1 || num>total){
        cout << "error input,please choose a number between 1 and " << total << endl;
        return;
    }

    string confirm;
    cout << "Are you sure you want to delete Race # " << num << " (yes/no)" << endl;
    cin >> confirm;
    if (cin.fail()) {
        handleInvalidInputChar();
        return;
    }
    cin.ignore();

    if (confirm != "Yes" && confirm != "yes" && confirm != "YES"){
        cout << "deletion cancled " << endl;
        return;
    }
    RaceNode* current = listhead;
    RaceNode* prev = NULL;

    if (num == 1){
        listhead = current->next;
        delete current;
        if (listhead == NULL){
            listtail = NULL;
        }
        cout << "Race # 1 has been deleted" << endl;
        return;
    }
    for (int i=1;i < num;i++){
        prev = current;
        current = current->next;
    }
    prev->next = current->next;
    if (current == listtail){
        listtail = prev;
    }
    delete current;

    cout << "Race # " << num << " has been deleted !" << endl;
}
