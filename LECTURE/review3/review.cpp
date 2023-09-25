#include <iostream>
#include <string>
using namespace std;



void ReadStdIn2() {
    string input;
    int count = 0;

    while (true) {
        cin >> input;
        if (input == "q") {
            break;
        }
        count++;
    }

    cout << count << endl;
}

