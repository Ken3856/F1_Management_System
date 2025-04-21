#include "person_queue.h"

PersonQueue::PersonQueue() : front(nullptr), rear(nullptr) {}

PersonQueue::~PersonQueue(){
    // base destructer does nothing, the derived classes clean up theirr Nodes
}

bool PersonQueue::isEmpty() const{
    return front == nullptr;
}
