/*
 * Name: Joel Miller
 * Date Submitted: 01/30/2022
 * Lab Section: 004
 * Assignment Name: Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize; //size (or length) of this list
  
 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);





  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name)
  {
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)




//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List()
{

  mySize = 0;

  start = nullptr;
  
}




//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List() 
{

  // Initialize the current pointer to the start of the list
  Node<T> *current = start; 

  // Create a next pointer to keep track of the next node
  Node<T> *next; 

  // Iterate through the list, deallocating memory for each node
  while (current != nullptr) 
  { 
    // Store the next pointer before deleting the current node
    next = current->next; 
    delete current; 
    // Move to the next node
    current = next; 
  }
  // Set the start pointer to null to indicate the list is empty
  start = nullptr; 
  // Reset the size of the list
  mySize = 0; 
}




//Return the size of this list
template <class T>
int List<T>::size()
{
  return mySize; //returns mysize of the list
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty(){
  if(mySize == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}





//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value){
  
  Node<T> *newNode = new Node<T>(value); 
  newNode->next = start; 
  start = newNode; 
  mySize++; 
}





//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){
  // Create a new node with the given value.
  Node<T> *newNode = new Node<T>(value); 

  // The new node's next pointer should be null, since it will be at the end of the list.
  newNode->next = nullptr; 

  // If the list is empty, the new node will be the start of the list.
  if(start == nullptr)
  {
    start = newNode;
  }
  // If the list is not empty, we need to find the last node in the list and attach the new node to it.
  else
  {
    // Create an iterator to traverse the list.
    Node<T> * iterator = start;

    // Move the iterator to the last node in the list.
    while(iterator->next != nullptr)
      iterator = iterator->next;
    
    // Attach the new node to the last node in the list.
    iterator->next = newNode;
  }
  // Increment the size of the list
  mySize++;  
}





//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j)
{
  // Create a new node with the given value
  Node<T> *newNode = new Node<T>(value); 

  // If the list is empty or the position is the first, use the insertStart function
  if(start == nullptr || j==0)
  {
    insertStart(value);
  }
  // If the position is not the first
  else
  {
    // Create an iterator to traverse the list
    Node<T> * iterator = start;

    // Move the iterator to the node before the desired position
    for (int i = 0; i < j-1; ++i)
    {
      // If the next node is not null, move the iterator to the next node
      if(iterator->next != nullptr)
      {
        iterator = iterator->next;
      }
    }
    // Set the new node's next pointer to the node after the desired position
    newNode->next = iterator->next;
    // Set the node before the desired position's next pointer to the new node
    iterator->next = newNode;
  }
  // increment the size of the list
  mySize++;
}





//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart()
{
  start = start->next;
  mySize--;
}





//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd()
{
  // Check if the list is empty or if mySize is 0
  if(start == nullptr || mySize==0) 
  {
    return;
  }
  // If the list has only one node, remove the start node
  else if(mySize == 1) 
  {
    removeStart();
    return;
  }
  else 
  {
    Node<T> * iterator = start;

    // Iterate through the list until the second to last node
    for (int i = 0; i < mySize-2; ++i) {
      iterator = iterator->next;
    }
    // Set the second to last node's next pointer to null, effectively removing the last node
    iterator->next = nullptr;
  }
  // Decrement the size counter
  mySize--;
}




//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j) 
{
  
  // Check if the position is out of bounds or if the list is empty
  if (j < 0 || j >= mySize || start == nullptr) 
  { 
    return;
  }

  // If the position is the first, use the removeStart function
  if (j == 0) 
  {
    removeStart();
  }
  // If the position is not the first
  else 
  {
    // Create pointers for the current and previous nodes
    Node<T> *current = start;

    Node<T> *prev = nullptr;

    // Move the current pointer to the desired node to be removed
    for (int i = 0; i < j; i++) {
      prev = current; 

      current = current->next; 
    }

    // Set the previous node's next pointer to the node after the current node
    prev->next = current->next; 
    // Delete the current node
    delete current; 
    // Decrement the size of the list
    mySize--; 
  }
}





//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst()
{
  return start->value;
}





//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast()
{

  Node<T> *iterator = start;
  
  while(iterator->next != nullptr)
  {
    iterator = iterator->next;
    if (iterator->next == nullptr)
      return iterator->value;
  }
}





//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j)
{

 // Check if the position is out of bounds, the list is empty or if j is negative
  if (j < 0  || j >= mySize || start == nullptr) 
  {
    cout << "Invalid j value" << endl;
    return 0;
  }
  // If the position is the first, return the value of the start node
  else if(j == 0) 
  {
     return start->value;
  }
  // If the position is not the first
  else
   {
    // Create an iterator pointer starting at the start of the list
    Node<T> *iterator = start; 

    // Move the iterator to the desired node
    for (int i = 0; i < j; i++) {
      iterator = iterator->next;
    }
    // Return the value of the node
    return iterator->value;
  }
}





//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key)
{
  Node<T> *iterator = start;

  for (int i = 0; i < mySize; ++i)
  {
    if (iterator->value == key)
      return i;
    iterator = iterator->next;
  }
  return -1;
}
