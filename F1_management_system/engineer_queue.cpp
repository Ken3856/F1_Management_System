#include "engineer_queue.h"
#include <iostream>

using namespace std;

EngineerQueue::~EngineerQueue(){
    while (!isEmpty()){
        pop();
    }
}

void EngineerQueue::push(Person* p){
    Node* newNode = new Node(p);
    if (!rear){
        front = rear = newNode;
    } else{
        rear->next = newNode;
        rear = newNode;
    }
}

void EngineerQueue::pop(){
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

void EngineerQueue::display() const{
    Node* curr = front;
    while (curr){
        curr->person->displayInfo();
        cout << endl;
        curr = curr->next;
    }
}
