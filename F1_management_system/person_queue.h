#ifndef PERSON_QUEUE_H
#define PERSON_QUEUE_H

#include "person.h"
using namespace std;

class PersonQueue {
protected:
    struct Node{
        Person* person;
        Node* next;
        Node(Person* p) : person(p), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    PersonQueue();
    virtual ~PersonQueue(); // Let derived classes clean up

    virtual void push(Person* p) = 0;
    virtual void pop() = 0;
    virtual void display() const = 0;

    bool isEmpty() const;
};

#endif // PERSON_QUEUE_H
