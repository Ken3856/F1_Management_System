// Responsible: Kenneth Johnson (Queue, Inheritance, composition)

// If not defined, then include a guard to prevent multiple inclusions.
#ifndef PERSON_QUEUE_H
#define PERSON_QUEUE_H

#include "person.h" // Include Person header file for Person class definition. 
using namespace std; // Use namespace std to avoid std prefix.

// Class definition for a person Node in a queue. 
class PersonNode{
    public:
        Person* person; // Pointer to a Person objcet.
        PersonNode* next; // Pointer to the next node in the queue.

        // Constructor to initialise the node with the person pointer and the sets next to null pointer.
        PersonNode(Person* p) : person(p), next(nullptr) {}
};

// Abstract base class for queue of Person objects.
class PersonQueue{
    protected:
        PersonNode* front; // Pointer to the front node of the queue.
        PersonNode* rear; // Pointer to the rear node of the queue.
    
    // Public access specifier.
    public:
        // Default constructor to initialise an empty queue.
        PersonQueue();

        // Virtual destructor to allow the derived classes to deallocate memory correctly for cleanup.
        virtual ~PersonQueue(); // Let derived classes clean up
    
        virtual void push(Person* p) = 0; // A pure virtual function that adds a Person to the queue. ("=0" makes the function pure virtual).
        virtual void pop() = 0; // A pure virtual function that removes a Person from the queue.
        virtual void display() const = 0; // A pure virtual that displays the contents of the queue. (const so no member vairables are modified).
    
        bool isEmpty() const; // checks if the queue is empty.
};

#endif // PERSON_QUEUE_H
