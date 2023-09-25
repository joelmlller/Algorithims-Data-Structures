/*
 * Name: Joel Miller
 * Date Submitted: 04/24/2023
 * Lab Section: 002
 * Assignment Name:Water Jugs
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

void build_graph(void)
{
    // Initialize the starting state and the ending state
    state here = make_pair(0,0);
    int A = 3, B = 4;
    state end = make_pair(A,B);

    // Loop until we reach the ending state
    while(here != end) {
        state next;

        // Action 1: Fill A
        next = make_pair(A,here.second);
        if(next != here) {
            pair<state,state> edge = make_pair(here,next);
            nbrs[here].push_back(next);
            edge_label[edge] = actions[0];
        }

        // Action 2: Fill B
        next = make_pair(here.first,B);
        if(next != here) {
            pair<state,state> edge = make_pair(here,next);
            nbrs[here].push_back(next);
            edge_label[edge] = actions[1];
        }

        // Action 3: Empty A
        next = make_pair(0,here.second);
        if(next != here) {
            pair<state,state> edge = make_pair(here,next);
            nbrs[here].push_back(next);
            edge_label[edge] = actions[2];
        }

        // Action 4: Empty B
        next = make_pair(here.first,0);
        if(next != here) {
            pair<state,state> edge = make_pair(here,next);
            nbrs[here].push_back(next);
            edge_label[edge] = actions[3];
        }

        // Action 5: Pour A into B
        int var1 = here.first;
        int var2 = here.second;
        if(here.second < B) {
            while(var1 > 0 && var2 < B) {
                var2++;
                var1--;
            }
            next = make_pair(var1,var2);
            if(next != here) {
                pair<state,state> edge = make_pair(here,next);
                nbrs[here].push_back(next);
                edge_label[edge] = actions[4];
            }
        }

        // Action 6: Pour B into A
        var1 = here.first;
        var2 = here.second;
        if(here.first < A) {
            while(var1 < A && var2 > 0) {
                var1++;
                var2--;
            }
            next = make_pair(var1,var2);
            if(next != here) {
                pair<state,state> edge = make_pair(here,next);
                nbrs[here].push_back(next);
                edge_label[edge] = actions[5];
            }
        }

        // Move to the next state in the graph
        if(here.second == B)
            here = make_pair(here.first + 1,0);
        else
            here = make_pair(here.first, here.second + 1);
    }
}


/*int main(void)
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
*/