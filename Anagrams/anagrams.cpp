/*
 * This program demonstrates the use of compund collections.
 * We find anagrams using the map and set classes in combination.
 */
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
using namespace std;

// function prototype declarations
void findAnagrams(string dictionaryFileName);
string sortLetters(string s);

int main() {
    findAnagrams("scrabble-dictionary.txt");
    return 0;
}

/*
 * Finds and prints the largest anagram set in the file.
 */
void findAnagrams(string dictionaryFileName) {
    // build a map of {sorted word form => {set of anagram words that have that sorted form}}
    map<string, set<string> > anagrams;
    cout << "Gathering anagram data ..." << endl;
    ifstream input;
    input.open(dictionaryFileName.c_str());
    size_t max = 0;
    string champion;
    string word;
    while (getline(input, word)) {
        string sorted = sortLetters(word);
        anagrams[sorted].insert(word);
        if (anagrams[sorted].size() > max) {
            max = anagrams[sorted].size();
            champion = sorted;
        }
    }

    set<string> largest = anagrams[champion];
    for (string word : largest)
        cout << word << endl;
}

/*
 * Returns a canonical version of the given word
 * with its letters arranged in alphabetical order.
 * For example, sortLetters("banana") returns "aaabnn".
 */
string sortLetters(string s) {
    sort(s.begin(), s.end());   // sort function comes from C++ STL libraries
    return s;
}
