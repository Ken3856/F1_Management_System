#include "driver_queue.h"
#include <iostream>
using namespace std;

DriverQueue::~DriverQueue(){
    while (!isEmpty()) pop(); // Delete all remaining nodes & their Persons.
}

void DriverQueue::push(Person* p){
    Node* newNode = new Node(p);
    if (!rear){
        front = rear = newNode;
    } else{
        rear->next = newNode;
        rear = newNode;
    }
}

void DriverQueue::pop(){
    if (isEmpty()){
         return;
    }
    Node* temp = front;
    front = front->next;
    delete temp->person;
    delete temp;
    if (!front){
        rear = nullptr;
    }
}

void DriverQueue::display() const{
    Node* curr = front;
    while (curr){
        curr->person->displayInfo();
        cout << endl;
        curr = curr->next;
    }
}
