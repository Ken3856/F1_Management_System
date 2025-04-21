#ifndef DRIVER_QUEUE_H
#define DRIVER_QUEUE_H

#include "person_queue.h"

using namespace std;

class DriverQueue : public PersonQueue {
public:
    ~DriverQueue();
    void push(Person* p) override;
    void pop() override;
    void display() const  override;
};

#endif // DRIVER_QUEUE_H
