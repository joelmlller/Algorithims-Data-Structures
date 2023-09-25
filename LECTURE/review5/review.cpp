#include <iostream>
#include <vector>
using namespace std;

vector<int> InitializeArray(int size) {

    vector<int> myArray(size);

    for (int i = 0; i < size; i++) {
        myArray[i] = 0;
    }

    return myArray;
}
