/*
 * Name: Joel Miller    
 * Date Submitted: 02/27/23
 * Lab Section: 004
 * Assignment Name: Spell Checker Using a Hash Table 
 */

#include "stringset.h"

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}


void Stringset::insert(string word)
{
    int var;
    string wordString;
    hash<string> str_hash;

if (!find(word)) { //check to see if the word isn't already in the string set


if (num_elems >= size) { //check if the size has been exceeded
size = size * 2;
vector<list<string>> vecList(size);
//looping thorugh the current table 
for (int i = 0; i < size / 2; i++) {
for(list<string>::const_iterator numVec = table[i].begin(); numVec != table[i].end(); ++numVec) {

wordString = *numVec;

var = str_hash(wordString) % size;

vecList[var].push_back(wordString);

table[i].remove(word);

}
}
table = vecList; //set the old table to the new table
}
var = str_hash(word) % size;

table[var].push_back(word);

num_elems++;
}
}



bool Stringset::find(string word) const
{
    int numVar;

hash<string> vectHash;

 numVar = vectHash(word) % size;
//looping through all the values in the list
for(list<string>::const_iterator vecStr = table[numVar].begin(); vecStr != table[numVar].end(); ++vecStr) {
if (*vecStr == word) //check if the word is there return true
return true;
}
return false;
}





void Stringset::remove(string word)
{
    int var2;

if (find(word)) { //check if the word is in the list remove it from it's hash location's list using .remove()
hash<string> vecStr;
 var2 = vecStr(word) % size;
table[var2].remove(word);
num_elems--;
}
}