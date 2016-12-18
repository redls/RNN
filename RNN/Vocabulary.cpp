#include <cstdio>
#include <random>
#include <fstream>
#include <iostream>
#include "ParseASentence.h"
using namespace std;

bool Vocabulary::containsWord(string word) {
    unordered_map<string, vector<double>>::const_iterator found_iter = vocabulary.find(word);
    if (found_iter == vocabulary.end()) {
        return false;
        }
    return true;
}

Vocabulary::Vocabulary() {
    // Read from the file.
    ifstream input("stanfordSentimentTreebank/datasetSentences.txt");
    ofstream outputFile;
    outputFile.open("debugRNN.txt", std::ios_base::app);
    string line;
    string word = "";
    bool text = false;
    getline( input, line );
    while(getline( input, line ) ) {
        text = false;
        for(char & c : line) {
            if (c == '\t')  {
                    text = true;
                    continue;
                }
            if (text) {
                if (c ==  ' ') {
                    if (!containsWord(word)) {
                        vector<double> vec = createRandomDistributions(25);
                        //cout<<word<<" "<<endl;ſ
                        vocabulary.insert(make_pair(word, vec));
                    }
                    word.clear();
                } else {
                    word = word + c;
                }
            }
        }
        // For the last word.
        if (!containsWord(word)) {
                        vector<double> vec = createRandomDistributions(25);
                        cout<<word<<" "<<endl;
                        vocabulary.insert(make_pair(word, vec));
                    }
        word.clear();
    }
}

vector<double> Vocabulary::getWordRepresentation(string word) {
    vector<double> aux;
    unordered_map<string, vector<double>>::const_iterator found_iter = vocabulary.find(word);
    if (found_iter == vocabulary.end()) {
        return aux;
    }
    return found_iter->second;
}

void Vocabulary::addNewWord(string word) {
    if (this->containsWord(word)) return;
    vector<double> vec = createRandomDistributions(25);
    vocabulary.insert(make_pair(word, vec));
    return;
}
