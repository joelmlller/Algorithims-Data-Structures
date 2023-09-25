/*
 * Name: Joel Miller
 * Date Submitted: 04/28/2023
 * Lab Section: 02
 * Assignment Name: Word Ladder
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type
// Four unordered maps are used
unordered_map<string, bool> went; //to keep track of visited nodes
unordered_map<string, string> temo; //to keep track of previous nodes
unordered_map<string, int> loca; //to keep track of the distance from starting node
unordered_map<string, vector<string>> mapVec; //to store adjacent nodes of each node

// Two functions are used
int pathFunc(string, string, vector<string>&); //to calculate the shortest path between two nodes
void graph(); //to build the adjacency list for the graph

//Implement breadth-first search
void wordLadder(string size, string took, int &vars, vector<string> &pop)
{
graph();


//BFS algorithm
queue<string> done;
done.push(size);
went[size] = true;
loca[size] = 0;

while (!done.empty()) {
    string curnode = done.front();
    done.pop();
    for (string num : mapVec[curnode])
        if (!went[num]) {
            temo[num] = curnode;
            loca[num] = 1 + loca[curnode];
            went[num] = true;
            done.push(num);
        }
}

//Calculate shortest path using the pathFunc
vars = pathFunc(size, took, pop);
}

//Function to calculate the shortest path using recursion
int pathFunc(string start, string end,vector<string> &path) {
//Base cases
if(temo.find(end) == temo.end())
return 0;
if(start.compare(end) != 0) {
int step = 1 + pathFunc(start, temo[end],path);
path.push_back(end);
return step;
}
else {
path.push_back(end);
return 0;
}
}

//Function to build the adjacency list for the graph
void graph(void) {
ifstream inFile ("wordlist05.txt");
string inWord;


//Read words from file and store them in a vector
while( inFile >> inWord )
    V.push_back( inWord );

//Build adjacency list for each node
for(auto w : V) {
    for(int loco = 0; loco < w.length(); loco++) {
        for(char chared = 'a'; chared <= 'z'; chared++) {
            if(chared == w.at(loco))
                continue;

            string curr = w;
            curr.at(loco) = chared;
            mapVec[w].push_back(curr);
        }
    }
}
}

/*
int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (int i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}*/
