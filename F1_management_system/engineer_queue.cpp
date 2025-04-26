#include "engineer_queue.h" // Include header file for EngineerQueue and PersonQueue base class.
#include <iostream> // Include input and output stream library.

using namespace std; // Use namespace std to avoid std prefix.

// Destructor, cleans nodes up and person objects.
EngineerQueue::~EngineerQueue(){
    while (!isEmpty()){ // While queue isnt empty,
        pop(); // traverse and remove each node.
    }
}

// Adds a new person pointer to end of queue.
void EngineerQueue::push(Person* p){
    PersonNode* newNode = new PersonNode(p); // Creates a new node dynamically.
    if (!rear){ // if the rear pointer is nullptr, i.e. queue is empty.
        front = rear = newNode; // Set the front and rear to point to the new node.
    } else{ // otherwise,
        rear->next = newNode; // Set the current rear node to the new node.
        rear = newNode; // And move the rear pointer to the new node.
    }
}

// Removes a person pointer from front of queue.
void EngineerQueue::pop(){
    if (isEmpty()){ // If the queue is already empty,
        return; // Just exit the fuction.
    }
    PersonNode* temp = front; // Stores the front node in temp.
    front = front->next; // Moves the front pointer to the next node.
    delete temp->person; //Delets the person object that the node was pointing to.
    delete temp; // Deletes the node.
    if (!front){ // If the queue is empty after popping,
        rear = nullptr; // then reset the pointer to nullptr.
    }
}

//Displays the person information in the queue.
void EngineerQueue::display() const{
    PersonNode* current = front; //Start at the front of queue.
    while (current){ // Traverses through the queue until nullptr is reached.
        current->person->displayInfo(); // Calls the display function of person. 
        cout << endl; // Prints a new line.
        current = current->next; // Moves to the next node within the queue.
    }
}
