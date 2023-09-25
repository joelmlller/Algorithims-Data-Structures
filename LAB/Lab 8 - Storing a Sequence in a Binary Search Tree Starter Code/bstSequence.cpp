/*
 * Name: Joel Miller
 * Date Submitted: 04/05/2023
 * Lab Section: 0
 * Assignment Name: Storing a sequence in a binary tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include <cmath>
#include "bstSequence.h"
using namespace std;

// Declare insert_random function
Node * insert_random(Node*,int,int);
// Declare printVector function
void printVector(vector<int>);

// Function to fix the size of the node
void fix_size(Node *T)
{
// Update the size of the node
T->size = 1;
// Add the size of the left subtree
if (T->left) T->size += T->left->size;
// Add the size of the right subtree
if (T->right) T->size += T->right->size;
}


/*
// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
if (T == nullptr) return new Node(k);
if (k < T->key) T->left = insert(T->left, k);
else T->right = insert(T->right, k);
fix_size(T);
return T;
}
*/


// Function to insert a value at a given rank
Node *insert(Node *T, int v, int r)
{
// If the node is null, create a new node
if(T == nullptr) return new Node(v);
// Calculate the rank of the current node
int rank = T->left ? T->left->size : 0;


// Insert the value in the left or right subtree
if(rank >= r) T->left = insert(T->left,v,r);
else T->right = insert(T->right,v,r - rank - 1);

// Update the size of the node
fix_size(T);
return T;
}

// Function to perform inorder traversal and return a sorted vector
vector<int> inorder_traversal(Node *T)
{
vector<int> sorted;
vector<int> traverse;


// Return empty vector if the node is null
if (T == nullptr) return sorted;
// Traverse left subtree and store the values
sorted=inorder_traversal(T->left);
// Add the current node's key value
sorted.push_back(T->key);
// Traverse right subtree and store the values
traverse=inorder_traversal(T->right);
// Combine the left and right subtree values
sorted.insert(sorted.end(), traverse.begin(), traverse.end());
return sorted;
}

// Function to find the node of a given rank
Node *select(Node *T, int r)
{
// Calculate the rank of the current node
int rank = T->left ? T->left->size : 0;


// Return the node if the rank matches
if (r == rank) return T;

// Search the left or right subtree
if (r < rank) return select(T->left, r);

else return select(T->right, r - rank - 1);
}

// Function to split a tree into two subtrees based on rank
void split(Node *T, int r, Node **L, Node **R)
{
// If the node is null, set both L and R to null
if(T == nullptr) {
*L = *R = nullptr;
return;
}

// Calculate the rank of the current node
int rank = T->left ? T->left->size : 0;

// Split the tree based on rank
if(rank < r) {
    split(T->right,r - rank - 1,&T->right,R);
    *L = T;
}

else {
    split(T->left, r, L, &T->left);
    *R = T;
}
// Update the size of the node
fix_size(T);
}



Node *insert_random(Node *T, int v, int r)
{
// if tree is empty, create new node
if(T == nullptr) return new Node(v);


// random probability to insert at current position
bool p = (rand() % (T->size + 1)) == 0;

// calculate rank of current node
int rank = T->left ? T->left->size : 0;

// when probability condition is met
if(p) {
    Node *chance2,*chance1;
    Node *newRoot = new Node(v);
    chance2 = chance1 = nullptr;

    // split tree based on rank
    split(T, r, &chance2, &chance1);
    newRoot->left = chance2;
    newRoot->right = chance1;
    fix_size(newRoot);
    return newRoot;
}

// insert in right subtree
if(r > rank)
    T->right = insert_random(T->right, v, r - rank - 1);
// insert in left subtree
else
    T->left = insert_random(T->left, v, r);

fix_size(T);
return T;
}

// check if team x defeated team y
bool did_x_beat_y(int x, int y)
{
assert (x != y);


if (x > y) return !did_x_beat_y(y, x);

unsigned long long longx = x;
unsigned long long longy = y;

return ((17 + 8321813 * longx + 1861 * longy) % 1299827) % 2 == 0;
}

// binary search the tree
int binarySearch(Node *T, int val) {


bool p = false;
int l = 0, h = T->size - 1;
int m = 0;

// perform binary search
while (!p) {
    m = floor((l + h) / 2);
    if (h - l == 1) {
        p = true;
        return h;
    }
    else if (did_x_beat_y(val, select(T, m)->key))
        h = m;
    else
        l = m;
}

return m;
}

// order n teams based on their victories
Node *order_n_teams(int n)
{
Node *teams = nullptr;


teams = insert_random(teams, 0, 0);

for (int i = 1; i < n; i++) {
    if (did_x_beat_y(i, select(teams, 0)->key))
        teams = insert_random(teams, i, 0);
    else if (did_x_beat_y(select(teams, teams->size - 1)->key, i))
        teams = insert_random(teams, i, teams->size);
    else {
        teams = insert_random(teams, i, binarySearch(teams, i));
    }
}
return teams;
}


void printVector(vector<int> v)
{
for (int i=0; i<v.size(); i++)
{
cout << v[i] << endl;
}
}







/*

int main(void)
{
  vector<int> inorder;
  Node *T = nullptr;

  // test insert at beginning
  for (int i=0; i<5; i++)
    T = insert(T, i+1, 0);
  cout << "Tree should contain 5 4 3 2 1:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test insert at end
  for (int i=5; i<10; i++)
    T = insert(T, i+1, T->size);
  cout << "Tree should contain 5 4 3 2 1 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  
  // test insert at middle
  for (int i=10; i<15; i++)
    T = insert(T, i+1, T->size/2);
  cout << "Tree should contain 5 4 3 2 1 12 14 15 13 11 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
    
  // once insert is working, the next step is to build the
  // insert_random function -- to test this, just change
  // calls to insert above to insert_random.

  int N = 100000; // this should run quickly even for very large N!
  Node *S = order_n_teams(N);
  if (S == nullptr || S->size != N)
    cout << "Size of tree returned by order_n_teams is wrong\n";
  else {
    cout << "Team ordering:\n";
    //    inorder=inorder_traversal(S);
    //    printVector(inorder);
    for (int i=0; i<N-1; i++) {
      Node *x = select(S, i);
      Node *y = select(S, i+1);
      if (!did_x_beat_y(x->key, y->key)) {
        cout << "Invalid sequence: team " << x->key << " (position " << i <<
	              ") lost to team " << y->key << " (position " << i+1 << ")\n";
      }
    }
  }  
  
  return 0;
}
*/
