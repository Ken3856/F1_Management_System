// Responsible - Kenneth Johnson (Queue, inheritance, Abstract base class)

#include "person_queue.h" // Includes the header file for PersonQueue class

// Initialises an empty queue by setting the front and rear pointerr to nullptr.
PersonQueue::PersonQueue() : front(nullptr), rear(nullptr) {}

// Virtual  destructor for PersonQueue.
PersonQueue::~PersonQueue(){
    // This destructer does nothing, it doesnt delete nodes diretly,
    // the derived classes DriverQueue and EngineerQueue clean up their Nodes.
    // The virtual destructor is necessary for polymorphic memory cleanup.
}

// Checks if queue is empty.
bool PersonQueue::isEmpty() const{ // Checks if the front pointer is nullptr, to see if no node are in the queue.
    return front == nullptr; // returns trur if front is null, otherwise it returns false.
}
