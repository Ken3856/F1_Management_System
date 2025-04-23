// Resposible - Kenneth Johnson (Driver Queue)

// If not defined, define it to prevent multiple inclusions.
#ifndef DRIVER_QUEUE_H
#define DRIVER_QUEUE_H

#include "person_queue.h" // Include the base PersonQueue class definition.

using namespace std; // Use namespace std to avoid using std prefix.

// DriverQueue inherits from PersonQueue to manage the driver objects in the queue.
class DriverQueue : public PersonQueue{
public:
    ~DriverQueue(); // Destructor to clean up remaining nodes when out of scope.
    void push(Person* p) override; // Pushes a person pointer onto queue. Overide is used for overiding the virtual base method.
    void pop() override; // Deletes the front person i.e dequeues. Overide is used for overiding the virtual base method.
    void display() const override;  // Displays all queued persons, const used to not modify the queue. Overide is used for overiding the virtual base method.
};

// End of the include guard 
#endif // DRIVER_QUEUE_H
