// Responsible - Kenneth Johnson(Queue, Inheritance)

#include "driver_queue.h" // Header declaration for DriverQueue and PersonQueue base class.
#include <iostream> // Include input/output stream library.
using namespace std; // Use namespace std to avoid std prefix.

// Destructor: cleans up any nodes that are remaining and the Person objcts that they point too.
DriverQueue::~DriverQueue(){
    while (!isEmpty()) pop(); // While the queue is not empty, traverse and deallocate nodes & their Persons objects until empty.
}

// Pushes a new Person* onto the queue
void DriverQueue::push(Person* p){
    Node* newNode = new Node(p); // Dynamically allocates memory for a new node to hold the Person pointer.
    if (!rear){ // If the queue is empty,
        front = rear = newNode; // set the front and rear to point to the first node.
    } else{ // Otherwise, if the queue has one node,
        rear->next = newNode; // link the rear to the new node.
        rear = newNode; // and update the rear to point to the new node.
    }
}

// Pop function to remove a node fromt the queue. Deallocates the memory
void DriverQueue::pop(){  
    if (isEmpty()){ // If queue is empty,
         return; // there is nothing to remove, so return.
    }
    Node* temp = front; // Stores the front node in a temp pointer. 
    front = front->next; // Moves the front pointer to the next node.
    delete temp->person; // Deallocates the person object stored in the node.
    delete temp; // Deletes and deallocates the node itself.
    if (!front){ // If the queue is empty (after popping),
        rear = nullptr; // then reset the pointer to null pointer.
    }
}

// Display function for displaying information of all Persons in the queue.
void DriverQueue::display() const{
    Node* current = front; // Statts at the front of the queue.
    while (current){ // Traverse through all nodes in the queue.
        current->person->displayInfo(); // Display each Person's information.
        cout << endl; // print a newline for a space after displaying info.
        current = current->next; // Move to the next node in te queue.
    }
}
