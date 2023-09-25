/*
 * Name:Joel Miller
 * Date Submitted: 3/10/2023
 * Assignment Name: Single-Word Anagram Finder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);


vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

vector<string> anagram(string word, vector<string> wordlist)
{
    unordered_map<string, vector<string> > map;

    //Loop through each word in the wordlist
    for (int i = 0; i < wordlist.size(); i++)
    {
        //current word
        string word1 = wordlist[i];
        //copy of the current word
        string word2 = word1;
        //sort the word
        sort(word2.begin(), word2.end());

         // If the sorted word does not exist as a key in the unordered_map
        if (map.find(word2) == map.end())
        {
        // a new key-value pair in the unordered_map with the sorted word as the key 
          vector<string> v;
         v.push_back(word1);
            map[word2] = v;

        }
        else
        {
            //append
            map[word2].push_back(word1);
        }
    }
    //sort the input word
    string input = word;
    sort(input.begin(), input.end());
    return map[input];
}