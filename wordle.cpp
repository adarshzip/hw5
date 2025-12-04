#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper(
    std::string current,
    std::string floating,
    std::set<std::string>& words,
    const std::string& in, 
    const std::set<std::string>& dict
);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::string current = ""; 
    std::set<std::string> words; 
    helper(current, floating, words, in, dict); 
    return words; 
}

// Define any helper functions here
void helper(
    std::string current,
    std::string floating,
    std::set<std::string>& words,
    const std::string& in, 
    const std::set<std::string>& dict)
{
    if (current.size() + floating.size() > in.size()){
        return; // "aggressively prune for time"
    }

    if (current.size() == in.size()){ // base case
        if (dict.find(current) != dict.end()){
            words.insert(current); 
        }
        return; 
    }

    if(in[current.size()] != '-'){
        helper(current + in[current.size()], floating, words, in, dict);
    }
    else {
        for (char c = 'a'; c <= 'z'; c++){
            std::string floating2 = floating; 

            if (floating.find(c) != string::npos){
                floating2.erase(floating2.find(c), 1);
            }

            helper(current + c, floating2, words, in, dict);
        }
    }
}