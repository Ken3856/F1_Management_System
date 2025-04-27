#include "RaceQueue.h"// by Yifan Xiang
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

        
        temp = new RaceNode;   //create a new nede, give it to temp 
        listhead = temp;    //let the new node be the new listhead of copy queue

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
        RaceNode* temp = listhead;//  a pointer with type of RaceNode, points at listhead of queue, which is going to be shown
        int count = 1;
        while (temp != NULL){
            cout << "\nRace # " << count << " :" << endl;//first Race is number 1
            cout << "Event Name: " << temp->data.getName() << endl;//as temp is a pointer, so use the arrow here
            cout << "Event Date: " << temp->data.getDate() << endl;
            cout << "Event Time: " << temp->data.getTime() << endl;
            cout << "Location: " << temp->data.getLocation() << endl; // Use getters instead of temp->data.showRaces();
            temp = temp->next;// move to the next
            count++;//increase the num, make every nodes has a serial number
        }
    }
}

void RaceQueue:: deleteRaceNode(){
    if (listhead == NULL)//empty error checking
    {
        cout << "The Queue is empty. Nothing to delete." << endl;
        return;
    }
    int total=0;
    RaceNode* temp = listhead;// pointer "temp" point at listhead
    while (temp != NULL)// here we want to get the total number of nodes in the queue
    {
        total++;//if current temp is not empty, we increacse the total by 1
        temp = temp->next;// then move to next and go into cycle checking the next node
    }
    int num;//initialization
    showQueue(); // show the queue to who wants to modify it

    cout << "Which Race would you like to delete ? (choose number) " << endl;
    cin >> num;
    if (cin.fail())//if the input is not integer,cin.fail()would equals to true
    {
        handleInvalidInputChar();//call function from "utils.h"
        return;
    }
    cin.ignore();//Cleans up what remains in the buffer when enter


    if (num<1 || num>total)//check if input satified the range of queue
    {
        cout << "error input,please choose a number between 1 and " << total << endl;
        return;
    }

    string confirm;//initialization
    cout << "Are you sure you want to delete Race # " << num << " (yes/no)" << endl;
    cin >> confirm;
    if (cin.fail())//make sure the input is right type 
    {
        handleInvalidInputChar();
        return;
    }
    cin.ignore();// //Cleans up what remains in the buffer 

    if (confirm != "Yes" && confirm != "yes" && confirm != "YES")//check the right input
    {
        cout << "deletion cancled " << endl;
        return;//if it's not "yes", not going to next step
    }
    RaceNode* current = listhead;//point at listhead
    RaceNode* prev = NULL;//it's an empty pointer 

    if (num == 1)//case of delete first node
    {
        listhead = current->next;//make next of listhead as new listhead
        delete current;//pointer "curent" is original listhead, that's what we want to delete it
        if (listhead == NULL)//just in case of this queue has only one node
        {
            listtail = NULL;// set the listtail empty
        }
        cout << "Race # 1 has been deleted" << endl;//delete succeed
        return;
    }
    for (int i=1;i < num;i++)//now if the num is not 1
    {
        prev = current;//set current equals to prev, actually keep the "prev" always stay in the previous position of "current"
        current = current->next;//move current to next, Stop by the number we want to delete
    }
    prev->next = current->next;//now connect the node before the target with the node after the target
    if (current == listtail)//if "current" goes to end of queue
    {
        listtail = prev;//then after deleting the current, prev is our listtail
    }
    delete current;//delete the target node

    cout << "Race # " << num << " has been deleted !" << endl;//success shown
}
