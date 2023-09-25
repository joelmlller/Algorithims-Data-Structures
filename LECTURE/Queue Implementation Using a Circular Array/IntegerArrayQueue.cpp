/*
 * Name: Joel Miller
 * Date Submitted: 02/14/2023
 * Lab Section: 004
 * Assignment Name: Integer Array Queue
 */




#include "IntegerArrayQueue.h"

bool IntegerArrayQueue::enqueue(int value) {
    if ((back + 2) % size == front) {
        // Queue is full
        return false;
    }
     back = (back + 1) % size;
    array[back] = value;
   
    return true;
}

int IntegerArrayQueue::dequeue() {

    if ((front + 1) % size == back)
    {
        return 0;
    }
    int value = array[front];
    front = (front + 1) % size;

    if (front == back) 
    {
        front = -1;
        back = -1;
    }

    return value;
}

