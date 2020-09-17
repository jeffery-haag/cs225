/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
  /* Your code goes here! */
 ifstream wordsFile(filename);
 string a;
 if (wordsFile.is_open())
 {

   while (getline(wordsFile, a))
   {
     string sorted(a);
     std::sort(sorted.begin(), sorted.end());
     dict[sorted].push_back(a);
   }
 }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
  for (unsigned i=0;i<words.size();i++)
  {
    string word=words[i];
    string sortedem(word);
    std::sort(sortedem.begin(), sortedem.end());
    dict[sortedem].push_back(word);
  }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
  string copy(word);
  std::sort(copy.begin(), copy.end());
  if (dict.count(copy) != 0) return dict.at(copy);
  else return vector<string>();

  return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{

  vector<vector<string>> ret;
  for (std::pair<string, vector<std::string>> key_val : dict)
  {
      vector<string> ana = key_val.second;
      if (ana.size() >1) ret.push_back(ana);
    }
  return ret;
}
