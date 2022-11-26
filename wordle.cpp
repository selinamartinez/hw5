// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <cstring>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void getAllCombos(std::string& a, int i, int n, const std::set<std::string>& dict, std::string in, std::set<std::string>& finalSet);
void insertAlphabet(std::string word, std::set<std::string>& finalSet, int n, const std::set<std::string>& dict, std::string in);
void checkWord(std::string in, const std::set<std::string>& dict, std::string combo, std::set<std::string>& finalSet);

//Must use a recursive approach to find all combos of letters to
//form the length-n word
//1 or 2 loops to help set the characters in any given location
//and maybe 1 to 2 other loops to help with various 
//constraint checks
//may at most use 5 loops in entire implementation
//do not use backtracking
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  std::set<std::string> finalSet;
  std::string floating_chars = "";
  int j = 0;
  bool questionMarks = false;
  for ( int i = 0; i < in.length(); i++ ) {
    if( in[i] == '-' ) {
      if( j < floating.length() ) {
        floating_chars += floating[j];
        j++;
      }
      else {
        questionMarks = true;
        floating_chars += '?';
      }
    }
  }
  if(!questionMarks && floating == "" && in != "") {
    finalSet.insert(in);
    return finalSet;
  }
  //first step in getting all the words
  getAllCombos(floating_chars, 0, floating_chars.length() - 1, dict, in, finalSet);


  return finalSet;

}

void getAllCombos(std::string& a, int i, int n, const std::set<std::string>& dict, std::string in, std::set<std::string>& finalSet) {
    
    if (i == n) {
      insertAlphabet(a, finalSet, n, dict, in);
    }                 
    else
    {
      for (int j = i; j <= n; j++) 
      {                        
        std::swap(a[i], a[j]);  
        getAllCombos(a, i+1, n, dict, in, finalSet);  
        std::swap(a[i], a[j]);    
      }
    }
    return;
}

void insertAlphabet(std::string word, std::set<std::string>& finalSet, int n, const std::set<std::string>& dict, std::string in) {
    if (n < 0) {
      checkWord( in, dict, word, finalSet );
      return;
    }
    if (word[n] != '?') {
      insertAlphabet(word, finalSet, n-1, dict, in);
    }
    else {
      for (int i=0; i< 26; i++) { 
        word[n] = i+'a';
        if (n >= 0) {             
          insertAlphabet(word, finalSet, n-1, dict, in); 
        }
      }
    }
}

void checkWord(std::string in, const std::set<std::string>& dict, std::string combo, std::set<std::string>& finalSet) {
  int j = 0;
  for (int i = 0; i < in.length(); i++) {
    if ( in[i] == '-') {
      in[i] = combo[j];
      j++;
    }
  }
  auto pos = dict.find(in);
  if ( pos != dict.end() ) {
    finalSet.insert(in);
  }
}


