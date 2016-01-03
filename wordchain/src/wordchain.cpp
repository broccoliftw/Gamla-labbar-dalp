/*  Created by:
*   Antro937
*   Eriro331
*   2014-09-24
*/

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include<map>
using namespace std;

const string alphabet  = "abcdefghijklmnopqrstuvwxyz";

void wordChain(string w1,string w2, map<string,bool>& dictionary){

    queue<stack<string>> q1;
    stack<string> s1;
    s1.push(w1);
    q1.push(s1);

    while(!q1.empty()){
        stack<string> s2 = q1.front();
        q1.pop();
        if (s2.top() == w2){ // if transformation complete
            int size = s2.size();// save the size of the stack before we change it in the loop
            for (int i = 0; i < size; i++){
                cout << s2.top() << " ";
                s2.pop();
            }
            cout << endl;
            break;
        }
        else{//else check all neighbouring words and put them into stack.
            string word = s2.top();
            string orginalWord = word;
            for (int a = 0; a < word.size(); a++){
                for (int i = 0; i < alphabet.size(); i++){
                    word[a] = alphabet[i];
                    if (dictionary[word]){//if real word
                        stack<string> tempStack = s2;
                        tempStack.push(word);

                        q1.push(tempStack);
                        dictionary[word]=false;
                    }

                    //word = orginalWord;
                }
                word = orginalWord;
            }
        }

    }
}



void readDictionary(map<string,bool>& dictionary){//reads and stores dictionary in a map
    ifstream input;
    input.open("dictionary.txt");
    string line;
    while(getline(input, line)) {
        dictionary[line] = true;
    }
    input.close();

}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
    cout << "Please type two words: ";

    string w1;
    string w2;
    cin >> w1 >> w2;
    map<string,bool> dictionary;
    readDictionary(dictionary);
    wordChain(w1,w2,dictionary);
    return 0;
}
