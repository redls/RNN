#include<cstdio>
#include "ParseASentence.h"

using namespace std;

/**
 * Implementations of methods dealing with sentence operations like.
 */

// Retrieve the words from the senetence and store them into an array.
vector<string> getWordsFromSentence(string sentence) {
    string word = "";
    vector<string> words;
    for(char & c : sentence) {
        if (c == ' ') {
            words.push_back(word);
            word.clear();
        } else {
            word = word + c;
        }
    }
    words.push_back(word);
    return words;
}

// Retrieve the word representation from the Vocabulary.
vector<Node> retrieveWordRepresentation(vector<string> words, Vocabulary *vocabulary) {
    int numberOfWords = words.size();
    vector<Node> nodes;
    for(int i = 0; i < numberOfWords; i++) {
        string word = words[i];
        if (vocabulary->containsWord(word)) {
            nodes.push_back(vocabulary->getWordRepresentation(word));
        } else {
            vocabulary->addNewWord(word);
            nodes.push_back(vocabulary->getWordRepresentation(word));
        }
    }
    return nodes;
}

