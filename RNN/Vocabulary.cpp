#include <cstdio>
#include <random>
#include <fstream>
#include <iostream>
#include "Vocabulary.h"
using namespace std;

vector<double> createRandomDistributions() {
    random_device rand;
    mt19937 generator(rand());
    uniform_real_distribution<double> distribution(-0.0001, 0.0001);
    vector<double> wordRep;
    for(int i = 0;i < 25; i++) {
        wordRep.push_back(distribution(generator));
    }
    return wordRep;
}

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
                        vector<double> vec = createRandomDistributions();
                        //cout<<word<<" "<<endl;
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
                        vector<double> vec = createRandomDistributions();
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
    vector<double> vec = createRandomDistributions();
    vocabulary.insert(make_pair(word, vec));
    return;
}
