#include <iostream>
#include <vector>
using namespace std;

void ReadWrite() {
    string input;
    vector<string> inputs;
    while (true) {
        cin >> input;
        if (input == "q") {
            break;
        }
        inputs.push_back(input);
    }
    for (int i = 0; i < inputs.size(); i++) {
        cout << inputs[i] << " ";
    }
    cout << endl;
}