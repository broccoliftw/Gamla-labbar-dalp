#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"


using namespace std;

class Boggle {
public:

    void totalSearch(Vector<string> &list, string &word, int y, int x, int visited);
    bool wordSearch(string &word, int x, int y,int pos);
    void gameLoop();
    void initializeGame();
    void printBoard();

private:
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    const string DICTIONARY_FILE = "EnglishWords.dat";
    int humanScore = 0;
    int computerScore = 0;
    Lexicon theLexicon;
    Grid<string> theGrid;
    Vector<string> gussedWords;

};

#endif
