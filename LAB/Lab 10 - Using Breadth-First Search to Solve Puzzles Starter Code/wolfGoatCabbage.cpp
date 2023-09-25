/*
 * Name: Joel Miller
 * Date Submitted: 04/24/2023
 * Lab Section: 002
 * Assignment Name: Wolf Goat Cabbage
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <bitset>

using namespace std;

// Reflects what each node represents...
// int with each bit == 0 left of river, bit == 1 right of river
typedef int state;

// Bit position representation for wolf/goat/cabbage/me
bool bit(int x, int i) { return (x>>i) & 1; }
const int wolf=0, goat=1, cabbage=2, me=3;

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from curnode)
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

string state_string(state s)
{
  string items[4] = { "wolf", "goat", "cabbage", "you" }, result = "";
  for (int i=0; i<4; i++)
    if (!bit(s, i)) result += items[i] + " ";
  result += " |river| ";
  for (int i=0; i<4; i++)
    if (bit(s, i)) result += items[i] + " ";
  return result;
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << state_string(t) << "\n";
  } else {
    cout << "Initial state: " << state_string(s) << "\n";
  }
}

string neighbor_label(int s, int t)
{
  string items[3] = { "wolf", "goat", "cabbage" }, which_cross;
  if (bit(s,me) == bit(t,me)) return "";  // must cross river
  int cross_with = 0;
  for (int i=0; i<3; i++) {
    if (bit(s,i) != bit(t,i) && bit(s,i)==bit(s,me)) { cross_with++; which_cross = items[i]; }
    if (bit(s,i) != bit(t,i) && bit(s,i)!=bit(s,me)) return "";
  }
  if (cross_with > 1) return "";
  if (cross_with == 0) return "Cross alone";
  else return "Cross with " + which_cross;
}


// Check if current state is valid
bool ifRight(bitset<4> location) {

// Check if wolf has eaten goat or goat has eaten cabbage
// and person is not present to stop it
    if (location[wolf] == location[goat]) {
        if (location[me] == location[wolf] && location[me] == location[goat]) {
            return true;
        }
    } else if (location[goat] == location[cabbage]) {
        if (location[me] == location[goat] && location[me] == location[cabbage]) {
            return true;
        }
    } else {
        return true;
    }
    return false;
}

void build_graph(void)
{
  const int objects = 4;

  // Initialize the bitset for the current location
  bitset<objects> here;

  // Initialize the bitset for the end state
  bitset<objects> stop ("1111");

  // Iterate over all possible states
  while(here != stop) {
    // Iterate over all objects
    for(int i = 0; i < objects; i++) {
      // Check if person is with the object
      if(here[me] == here[i]) {

        // Flip the person bit
        bitset<objects> ns = here;
        ns[me].flip();

        // Flip the object bit if it is not the person
        if (i != me) {
          ns[i].flip();
        }

        bool flipped = false;
        // Check for valid next state
        if(ifRight(ns)) {
          int curr = (int)here.to_ulong();
          int next = (int)ns.to_ulong();
          // Add the valid state to the graph
          nbrs[curr].push_back(next);
          edge_label[make_pair(curr,next)] = neighbor_label(curr,next);
        }
      }
    }
    // Increment the current state
    here = (int)here.to_ulong() + 1;
  }
}


/*int main(void)
{
  build_graph();

  state start = 0, end = 15;
  
  search(start);
  if (visited[end])
    print_path (start, end);
  else
    cout << "No path!\n";
  
  return 0;
}*/