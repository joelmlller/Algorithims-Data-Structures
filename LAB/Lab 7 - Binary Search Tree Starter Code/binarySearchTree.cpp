
/*
 * Name: Joel Miller
 * Date Submitted: 03/31/2023
 * Lab Section: 01
 * Assignment Name: Binary Search Tree
 */




#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
 
 #include "binarySearchTree.h"

using namespace std;


void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) 
  return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}


// finds node with given key in BST rooted at T
Node *find(Node *T, int k)
{
  // base case: T is null or has key k
  if (T == nullptr || T->key == k)
  {
      return T;
  }
  
  // search right subtree if T's key is less than k, else search left subtree
  return T->key < k ? find(T->right, k) : find(T->left, k);
}

// selects node at given rank in BST rooted at T
Node *select(Node *T, int r)
{
  // ensure T is not null and r is within range of T's size
  assert(T!=nullptr && r>=0 && r<T->size);
  
  // calculate number of nodes in T's left subtree
  int numRank = T->left ? T->left->size : 0;
  
  // search right subtree if r is greater than numRank, else search left subtree
  return numRank < r ? select(T->right, r - numRank - 1) : numRank > r ? select(T->left, r) : T;
}

// joins two BSTs L and R together
Node *join(Node *L, Node *R)
{
  // if either L or R is null, return the other
  if(L == nullptr) return R;
  if(R == nullptr) return L;
  
  // calculate probability of inserting into R
  double numc = L->size / (L->size + R->size);
  double rn = rand() * 101.0 / 100.0;
  
  // insert into R with probability numc, else insert into L
  return rn > numc ? (R->left = join(L, R->left), fix_size(R), R) : (L->left = join(L, R->left), fix_size(L), L);
}

// removes node with given key from BST rooted at T
Node *remove(Node *T, int k)
{
  assert(T != nullptr);
  
  // search left subtree if k is less than T's key, else search right subtree
  if (k < T->key)
  {
      T->left = remove(T->left, k);
      fix_size(T);
      return T;
  }
  else if (k > T->key)
  {
      T->right = remove(T->right, k);
      fix_size(T);
      return T;
  }
  // found node to remove
  else
  {
      Node *temp = T;
      T = join(T->left, T->right);
      
      // if joined BST is not null, fix its size
      if(T != nullptr) fix_size(T);
      
      delete temp;
      return T;
  }
}

// splits BST rooted at T into two subtrees based on given key k
void split(Node *T, int k, Node **L, Node **R)
{
  // handle null case
  if (T == nullptr)
  {
      *L = nullptr;
      *R = nullptr;
      return;
  }
  
  // split right subtree and set L to T and R to null if T's key is less than or equal to k
  if (T->key <= k)
  {
      if (T->right == nullptr)
      {
          *L = T;
          *R = nullptr;
      }
      else
      {
          split(T->right, k, L, R);
          T->right = *L;
          *L = T;
      }
      if (*L != nullptr) fix_size(*L);
}
// split left subtree and set R to T and L to null if T's key is greater than k
else
{
if (T->left == nullptr)
{
*R = T;
*L = nullptr;
}
else
{
split(T->left, k, L, R);
T->left = *R;
*R = T;
}
// if R is not null, fix its size
if (*R != nullptr) fix_size(*R);
}
}

// inserts node with given key k randomly into BST rooted at T
Node *insert_random(Node *T, int k)
{
// if T is null, create new node with key k
if (T == nullptr)
{
Node *cNode = new Node(k);
return cNode;
}

// calculate probability of inserting into T
double numRand = rand() % 101 / 100.0;
double numProb = rand() % T->size;

// insert into new node with key k and split T around k if probability is less than or equal to numRand
if (numProb <= numRand)
{
Node *cNode = new Node(k);
split(T, k, &cNode->left, &cNode->right);
fix_size(cNode);
return cNode;
}
// insert into right subtree if k is greater than T's key, else insert into left subtree
else if (k > T->key)
{
T->right = insert_random(T->right, k);
fix_size(T);
return T;
}
else
{
T->left = insert_random(T->left, k);
fix_size(T);
return T;
}
}



void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

/*int main(void)
{
  vector<int> inorder;
  vector<int> A(10,0);
  
  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  cout << "Contents of A (to be inserted into BST):\n";
  printVector(A);
  
  // insert contents of A into a BST
  Node *T = nullptr;
  for (int i=0; i<10; i++) T = insert(T, A[i]);
  
  // print contents of BST (should be 0..9 in sorted order)
  cout << "Contents of BST (should be 0..9 in sorted order):\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test select
  for (int i=0; i<10; i++) {
    Node *result = select(T, i);
    if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
  }

  // test find: Elements 0..9 should be found; 10 should not be found
  cout << "Elements 0..9 should be found; 10 should not be found:\n";
  for (int i=0; i<11; i++) 
    if (find(T,i)) cout << i << " found\n";
    else cout << i << " not found\n";

  // test split
  Node *L, *R;
  split(T, 4, &L, &R);
  cout << "Contents of left tree after split (should be 0..4):\n";
  inorder=inorder_traversal(L);
  printVector(inorder);
  cout << "Left tree size " << L->size << "\n";
  cout << "Contents of right tree after split (should be 5..9):\n";
  inorder=inorder_traversal(R);
  printVector(inorder);
  cout << "Right tree size " << R->size << "\n";
    
  // test join
  T = join(L, R);
  cout << "Contents of re-joined tree (should be 0..9)\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  cout << "Tree size " << T->size << "\n";
  
  // test remove
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
    if (T != nullptr)
      cout << "Tree size " << T->size << "\n";
  }

  // test insert_random
  cout << "Inserting 1 million elements in order; this should be very fast...\n";
  for (int i=0; i<1000000; i++) T = insert_random(T, i);
  cout << "Tree size " << T->size << "\n";
  cout << "Done\n";
  
  return 0;
}*/