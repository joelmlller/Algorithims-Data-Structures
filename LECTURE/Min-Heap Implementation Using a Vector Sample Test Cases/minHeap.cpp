
/*
 * Name:Joel Miller
 * Date Submitted: 3/17/2023
 * Assignment Name: MinHeap
 */


#include "minHeap.h"

using namespace std;

// Method for moving an element up the heap to maintain the min-heap property
void minHeap :: siftUp(int pos)
{
// Get the parent value and the current value
int pValue = (pos-1)/2;

int cValue = pos;


// Swap the current value with its parent until the min-heap property is satisfied
while(cValue!=0 && heap[pValue] > heap[cValue]) 
{
    int temp = heap[pValue];


    heap[pValue] = heap[cValue];


    heap[cValue] = temp;
    cValue = pValue; 

    pValue = (pValue-1)/2; 
}
}

// Method for moving an element down the heap to maintain the min-heap property
void minHeap :: siftDown(int pos)
{
// Set the parent and child numbers
int pNum = pos;
int cNum1 = 2*pNum + 1;


int cNum2 = 2*pNum + 2;
int cNum3 = -1;


// Check if the first child is smaller than the parent
if(cNum1 < (int)heap.size() && heap[cNum1] < heap[pNum]) 
{
    cNum3=cNum1;
}

// Check if the second child is smaller than the parent
if(cNum2 < (int)heap.size() && heap[cNum2] < heap[pNum]) 
{
    // If the first child is not smaller, set the third child as the second child
    if (cNum3 == -1) cNum3 = cNum2;
    else
    {
        // If the second child is smaller than the first child, set the third child as the second child
        if (heap[cNum2] < heap[cNum1]) cNum3=cNum2; 
    }
}

// If there is no child smaller than the parent, return
if(cNum3 == -1) {
    return;
}
// Swap the parent with the smallest child and continue sifting down
int temp=heap[pNum];


heap[pNum]= heap[cNum3];

heap[cNum3] = temp;

siftDown(cNum3); 


}

// Constructor for the minHeap class with input data
minHeap :: minHeap(vector<int> data)
{
// Initialize the heap
heap.resize(0);


// Add the input data to the heap
for(int i=0;i<(int)data.size();i++) {

    heap.push_back(data[i]); 
}
// Move every element in the heap down to maintain the min-heap property
for(int i=heap.size()-1;i>=0;i--) {

    siftDown(i); 

}
}

// Method for inserting a value into the heap
void minHeap :: insert(int value)
{
// Add the value to the end of the heap
heap.push_back(value);


// Move the value up the heap to maintain the min-heap property
int pos = heap.size()-1;
siftUp(pos); 
}

// Method for removing and returning the minimum element from the heap
int minHeap :: removeMin()
{
// If the heap is empty, return -1
if(heap.size()== 0) {

    return -1;
}

// Remove the minimum element from the heap and put the last element in its place
int temp = heap[0]; 


heap[0] = heap[heap.size()-1];

heap[heap.size()-1] = temp;

heap.pop_back();

siftDown(0); 

return temp; 

}



