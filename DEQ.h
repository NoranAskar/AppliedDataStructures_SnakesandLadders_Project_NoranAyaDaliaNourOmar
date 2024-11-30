#ifndef DEQ_H
#define DEQ_H

#include <iostream>
using namespace std;

template <typename T>
class DEQ {
private:
    // Node structure for linked list
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* front;  // Pointer to the front node
    Node* rear;   // Pointer to the rear node
    int length;   // Keeps track of the number of elements

public:
    // Constructor: initializes an empty DEQ
    DEQ();

    // Destructor: destroys the DEQ and frees the memory
    ~DEQ();

    // Check if DEQ is empty
    bool DEQisEmpty() const;

    // Add an element at the front
    void Add_Front(const T& value);

    // Add an element at the rear
    void Add_Rear(const T& value);

    // Remove the element at the front and return it
    T Remove_Front();

    // Remove the element at the rear and return it
    T Remove_Rear();

    // View the front element without removing
    T View_Front() const;

    // View the rear element without removing
    T View_Rear() const;

    // Get the number of elements in the DEQ
    int DEQ_Length() const;
};

#endif