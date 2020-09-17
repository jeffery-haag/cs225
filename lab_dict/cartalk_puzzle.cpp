/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    bool boo;
    ifstream words(word_list_fname);
    string a;
    if (words.is_open())
    {
      while (getline(words, a))
      {
        boo=true;
        if (a.size()<3)continue;
        //boo=true;
        string edit1=(a[0]+a.substr(2));
        if (!(d.homophones(a,edit1)))boo=false;
        string edit2=a.substr(1);
        if (!(d.homophones(a,edit2)))boo=false;
        if (d.homophones(a,edit2) && d.homophones(a,edit1) && boo==true)
        {
          ret.push_back(tuple<string,string,string>(a,edit1,edit2));
        //std::cout<<a<<std::endl;
      }
      }
    }


    return ret;
}
