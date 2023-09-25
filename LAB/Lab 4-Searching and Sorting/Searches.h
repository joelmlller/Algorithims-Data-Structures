/*
 * Name: Joel Miller
 * Date Submitted: 02/15/2023
 * Lab Section: 004
 * Assignment Name: Searching and Sorting
 */


#pragma once

#include <vector>

template <class T>
int linearSearch(std::vector<T> data, T target) {

// the index to -1
int num = -1;

// Loop through the vector
for (int i = 0; i < data.size(); i++) {
    //if the current element is equal to the target
    if (data[i] == target) {
        // updates index to the current position 
        num = i;
        break;
    }
}

return num;
}



template <class T>
int binarySearch(std::vector<T> data, T target) {
    int l = 0;
    int r = data.size() - 1;
//until the left pointer is greater than the right pointer
while (l <= r) {
    //midpoint between the left and right pointers
    int m = (l + r) / 2;
    //middle element is equal to the target
    if (data[m] == target) {
        //position of the target
        return m;
    }
    //middle element is less than the target, update the left pointer
    else if (data[m] < target) {
        l = m + 1;
    }
    //middle element is greater than the target, update the right pointer
    else {
        r = m - 1;
    }
}

return -1;
}
