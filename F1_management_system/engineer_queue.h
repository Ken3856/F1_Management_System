#ifndef ENGINEER_QUEUE_H
#define ENGINEER_QUEUE_H

#include "person_queue.h"

using namespace std;

class EngineerQueue : public PersonQueue{
public:
    ~EngineerQueue() override;
    void push(Person* p) override;
    void pop() override;
    void display() const override;
};

#endif // ENGINEER_QUEUE_H
