#include<cstdio>
#include <random>
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

// Retrieve the word representation from the Vocabulary and add them into a vector.
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

// Create random distributions of size d.
vector<double> createRandomDistributions(int d) {
    random_device rand;
    mt19937 generator(rand());
    uniform_real_distribution<double> distribution(-0.0001, 0.0001);
    vector<double> wordRep;
    for(int i = 0;i < d; i++) {
        wordRep.push_back(distribution(generator));
    }
    return wordRep;
}

/**
 * Initialise the weights of the neural network. This will return and array containing d distribuitions, each
 * of 2*d elements.
 */
vector<vector<double>> initialiseWeigths(int d) {
    vector<vector<double>> weights;
    for (int i = 0; i < d; i++) {
        vector<double> weight1 = createRandomDistributions(2*d);
        weights.push_back(weight1);
    }
    return weights;

}

