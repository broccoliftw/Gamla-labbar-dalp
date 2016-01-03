#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "list"
#include <math.h>

using namespace std;

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
                                          "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
                                          "AOÖTTW", "CIMOTU", "DEILRÄ", "DELRVY",
                                          "DISTTY", "EEGHNR", "EEINSU", "EHRTVW",
                                          "EIOSST", "ELRTTY", "HIMNÅU", "HLNNRT"
                                 };

void Boggle::initializeGame(){// sets up board with option to manually enter it
    theGrid.resize(BOARD_SIZE,BOARD_SIZE);

    theLexicon.addWordsFromFile("EnglishWords.dat");
    cout << theLexicon.contains("hej") << endl;

    string answer;
    cout << "Do you want to generate a random board? (y/n) ";
    getline(cin, answer);


    if (answer == "n"){
        string board;
        while (true){
            cout << "Enter the board as one string with 16 letters: ";

            getline(cin, board);

            if (board.size() == 16){
                break;
            }
            cout << "Please enter exactly 16 letters" << endl;


        }
        int nChars = board.length();// converts all letters to uppercase
        for (int i = 0; i < nChars; i++) {
            board[i] = toupper(board[i]);
        }

        for (int i = 0; i < BOARD_SIZE; i++){
            for (int y = 0; y < BOARD_SIZE; y++){
                theGrid[i][y] = board[BOARD_SIZE*i+y];
            }
        }



    }
    else {//generates random board
        for (int i = 0; i < BOARD_SIZE; i++){
            for (int y = 0; y < BOARD_SIZE; y++){

                int randint= (rand() % (int)(6));
                theGrid[i][y] = CUBES[BOARD_SIZE*i+y][randint];

            }
        }
        shuffle(theGrid);// shuffles the random board
    }


/*
 //testcase with expected output in res folder

    theGrid[0][0] = "F";
    theGrid[0][1] = "Y";
    theGrid[0][2] = "C";
    theGrid[0][3] = "L";

    theGrid[1][0] = "I";
    theGrid[1][1] = "O";
    theGrid[1][2] = "M";
    theGrid[1][3] = "G";

    theGrid[2][0] = "O";
    theGrid[2][1] = "R";
    theGrid[2][2] = "I";
    theGrid[2][3] = "L";

    theGrid[3][0] = "H";
    theGrid[3][1] = "J";
    theGrid[3][2] = "H";
    theGrid[3][3] = "U";
*/



}

void Boggle::gameLoop(){// main loop

    while (true){
        printBoard();
        cout << endl;
        cout << "Your words (" << gussedWords.size() << "): ";
        cout << gussedWords.toString() << endl;
        cout << "Your score: " << humanScore << endl;

        cout << "Type a word (or press Enter to end your turn): ";
        string word;
        getline(cin, word);

        if (word.empty()){// enter pressed computers turn starts
            break;
        }

        int nChars = word.length();// converts all letters to uppercase
        for (int i = 0; i < nChars; i++) {
            word[i] = toupper(word[i]);
        }
        bool check = false;
        if (theLexicon.contains(word)){// checks so that the word is an english word
            if (word.length() >= MIN_WORD_LENGTH){
                check = true;
                for (string w: gussedWords){// checks if word already gussed
                    if (w == word){
                        check = false;
                        cout << "You have already guessed that word." << endl;
                    }
                }
            }
            else{
                cout << "That word is not long enough." << endl;
            }
        }
        else{
            cout << "That word is not in the dictionary."<< endl;
        }
        if (check){ // if all tests passed

            //control cube

            if (wordSearch(word, 0, -1, 0)){ // check so that you can make the word from the current board.

                cout << "You found a new word!" << '"' << word << '"' << endl;
                humanScore = humanScore + (word.length() - (MIN_WORD_LENGTH -1));// increments score
                gussedWords.add(word);// adds to already gussed words
            }
            else {
                cout << "That word can't be formed on this board." << endl;
            }


        }

    }

    //WHEN ENTER PRESSED ONLY
    //computer's turn

    cout << "It's my turn!" << endl;
    Vector <string> result;
    string word = "";
    totalSearch(result, word, 0, -1, 0);
    cout << "My words (" << result.size() << "): ";
    cout << result.toString() << endl;
    cout << "My score: " << computerScore << endl;
    if (computerScore > humanScore){
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human"<< endl;

    }
    else{
        cout << "You won, you probably cheated...";
    }
    computerScore = 0;
    humanScore = 0;
    gussedWords.clear();



}

void Boggle::totalSearch(Vector<string> &list, string &word, int y, int x, int visited){//ta bort dubletter och typ coco lulu
    //Start case only first time the function is called.
    if (x ==-1){
        //rekursion
        for (int r = 0; r < theGrid.numRows(); r++){
            for (int c = 0; c < theGrid.numCols(); c++){
                if (c < theGrid.numCols() && r < theGrid.numRows() && c >= 0 && r >= 0){
                    // avoids index out of bounds
                    word = theGrid[r][c][0];
                    visited = visited | (1<<((BOARD_SIZE*r)+c));// adds position to binarycode visited list
                    totalSearch(list,word,r,c, visited);
                    visited = visited & (~(1<<((BOARD_SIZE*r)+c)));// removes position from binarycode visited list

                }
            }
        }
    }
    //Base case
    else if (theLexicon.contains(word)){ // if word is an english word.
        bool check = true;
        if (word.length() >= MIN_WORD_LENGTH){// if word lenght is atleast okay
            for ( string w : list){
                if (w == word){
                    check = false;
                }
            }
            for (string w: gussedWords){ // word is not guessed earlier
                if (w == word){
                    check = false;
                }
            }
            if (check){ // all tests passed add word to list and increment score
                list.push_back (word);
                computerScore = computerScore + (word.length() - (MIN_WORD_LENGTH -1));
            }
        }

    }
    if (theLexicon.containsPrefix(word)){// checks if the prefix is a start of an english word
        //rekursion
        for (int r = (y-1); r <= y+1; r++){
            for (int c = (x-1); c <= x+1; c++){
                int a = visited&(1<<((BOARD_SIZE*r)+c));
                if (a == 0 ){ //check already visisted
                    if (!(c == x && r == y) && c < theGrid.numCols() && r < theGrid.numRows() && c >= 0 && r >= 0){

                        // avoid index out of bounds
                        word = word + theGrid[r][c][0];
                        visited = visited | (1<<((BOARD_SIZE*r)+c));// adds position to binarycode visited list
                        totalSearch(list,word,r,c, visited);
                        visited = visited & (~(1<<((BOARD_SIZE*r)+c)));// removes position from binarycode visited list
                        word = word.substr(0, word.size()-1);

                    }
                }

            }
        }


    }
}

bool Boggle::wordSearch(string &word, int y, int x, int pos){// checks if a word is able to be formed from the current board.
    //Startcase
    bool answer = false;
    if (x == -1){ //Search for first letter
        for (int r = 0; r < theGrid.numRows(); r++){
            for (int c = 0; c < theGrid.numCols(); c++){
                if (theGrid[r][c][0] == word[pos]){
                    //Letter found
                    answer = answer || wordSearch(word,r,c,pos+1);
                }

            }


        }
        return answer;
    }
    //Base case
    //whole word found.

    else if(word.size() == pos){
        return true;

    }
    //Other case
    else{
        for (int r = (y-1); r <= y+1; r++){
            for (int c = (x-1); c <= x+1; c++){
                if (!(c == x && r == y) && c != theGrid.numCols() && r != theGrid.numRows() && c >= 0 && r >= 0){
                    // avoid index out of bounds.
                    if (theGrid[r][c][0] == word[pos]){
                        answer = answer || wordSearch(word,r,c,pos+1);
                    }
                }
            }
        }
        return answer;
    }
}


void Boggle::printBoard(){// prints board.
    for (int r = 0; r < theGrid.numRows(); r++){
        for (int c = 0; c < theGrid.numCols(); c++){
            cout << theGrid[r][c];
        }
        cout << endl;
    }

}
