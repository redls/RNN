#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include <math.h>

#include "Dictionary.h"
#include "DatasetSentences.h"
#include "SentimentLabels.h"
#include "TestsetSentences.h"

using namespace std;

ofstream outputFile("debug.txt", fstream::out | fstream::trunc);

long long positiveSentences = 0;
long long negativeSentences = 0;


SentimentLabels *sentimentLabels = new SentimentLabels();
DatasetSentences *datasetSentences = new DatasetSentences();
TestsetSentences *testsetSentences = new TestsetSentences();
Dictionary *dictionary = new Dictionary();
unordered_map<string, long long> dataset_sentences = datasetSentences->getSentencesMap();
unordered_map<string, long long> testset_sentences = testsetSentences->getSentencesMap();
unordered_map<string, long long> positiveWordsMap;
unordered_map<string, long long> negativeWordsMap;

void updateFrequencyOfWord(bool is_positive, string word) {
    //unordered_map<string, long long> mapp;
    if (is_positive) {
    unordered_map<string, long long>::const_iterator found_iter = positiveWordsMap.find(word);
        if (found_iter == positiveWordsMap.end()) {
            positiveWordsMap.insert(make_pair(word, 1));
            return;
        }
        long long value = found_iter->second + 1;
        positiveWordsMap.insert(make_pair(word, value));
     } else {
        unordered_map<string, long long>::const_iterator found_iter = negativeWordsMap.find(word);
        if (found_iter == negativeWordsMap.end()) {
            negativeWordsMap.insert(make_pair(word, 1));
        return;
        }
        long long value = found_iter->second + 1;
        negativeWordsMap.insert(make_pair(word, value));
     }
}

void trainNaiveBayes() {
    ofstream outputFile;
    outputFile.open("debug.txt", std::ios_base::app);
    bool is_positive = true;
    long long nr = 0;
    for (auto it = dataset_sentences.begin(); it != dataset_sentences.end(); ++it ) {
        is_positive = true;
        string sentence = it->first;
        long long phraseIndex = dictionary->getPhraseIndex(sentence);
        if (phraseIndex >= 0) {
            double sentimentScore = sentimentLabels->getSentimentScore(phraseIndex);
            if (sentimentScore >= 0) {
                if (sentimentScore >= 0.5) {
                    positiveSentences++;
                } else {
                    negativeSentences++;
                    is_positive = false;
                }
                string word = "";
                for(char & c : sentence) {
                    if (c == ' ') {
                        nr++;
                        outputFile<<word<<" ***"<<is_positive<<endl;
                        updateFrequencyOfWord(is_positive, word);
                        word.clear();
                    } else {
                        word = word + c;
                    }
                }
            }
        } else {
        }
    }
    cout<<nr<<endl;
}


long long frequencyOfWords(bool is_positive) {
    long long total = 0;
    if (is_positive) {
        for (auto it = positiveWordsMap.begin(); it != positiveWordsMap.end(); ++it ) {
            total = total + 1 + it->second;
        }
    } else {
      for (auto it = negativeWordsMap.begin(); it != negativeWordsMap.end(); ++it ) {
            total = total + 1 + it->second;
        }
    }
    return total;
}
void testNaiveBayes() {

    ofstream outputFile;
    outputFile.open("debug.txt", std::ios_base::app);
    bool is_positive = true;
    double product_of_positives = 1.0;
    double product_of_negative = 1.0;
    long long number_of_negatives = 0;
    long long number_of_positives = 0;
    long long total_positives = frequencyOfWords(true);
    long long total_negatives = frequencyOfWords(false);
    ofstream outputResult("NaiveBayesResults.txt");
    for (auto it = testset_sentences.begin(); it != testset_sentences.end(); ++it ) {
        product_of_positives = 1.0;
        product_of_negative = 1.0;
        number_of_negatives = 0;
        number_of_positives = 0;
        string sentence = it->first;
        string word = "";
        for(char & c : sentence) {
            if (c == ' ') {
                unordered_map<string, long long>::const_iterator found_iter = positiveWordsMap.find(word);
                if (found_iter != positiveWordsMap.end()) {
                    number_of_positives = found_iter->second + 1;
                } else {
                    number_of_positives += 1;
                }
                found_iter = negativeWordsMap.find(word);
                if (found_iter != negativeWordsMap.end()) {
                    number_of_negatives = found_iter->second + 1;
                } else {
                    number_of_negatives += 1;
                }
                outputFile<<"Number of negative appearences for the word "<<word<<": "<<number_of_negatives<<endl;
                outputFile<<"Number of positive appearences for the word "<<word<<": "<<number_of_positives<<endl;
                outputFile<<"Product3 of positive appearences for the word: "<<product_of_positives<<endl;
                outputFile<<"Product3 of negative appearences for the word: "<<product_of_negative<<endl;
                product_of_negative = product_of_negative * number_of_negatives/total_negatives;
                product_of_positives = product_of_positives * number_of_positives/total_positives;
                outputFile<<"Product2 of positive appearences for the word: "<<product_of_positives<<endl;
                outputFile<<"Product2 of negative appearences for the word: "<<product_of_negative<<endl;
                outputFile<<"Product4 of positive appearences for the word: "<<total_positives<<endl;
                outputFile<<"Product4 of negative appearences for the word: "<<total_negatives<<endl;
                word.clear();
            } else {
                word = word + c;
            }
        }
        outputFile<<"Product of positive appearences for the word: "<<product_of_positives<<endl;
        outputFile<<"Product of negative appearences for the word: "<<product_of_negative<<endl;
        outputFile<<"Number of positive appearences for the word "<<word<<": "<<number_of_positives<<endl;
        outputFile<<"Number of negative appearences for the word "<<word<<": "<<number_of_negatives<<endl;
        product_of_negative = product_of_negative * number_of_negatives/total_negatives;
        product_of_positives = product_of_positives * number_of_positives/total_positives;
        double final_positive_prob = positiveSentences * product_of_positives;
        double final_negative_prob = negativeSentences * product_of_negative;
        outputFile<<"Sentence: "<<sentence<<" has positive probability "<<final_positive_prob<<endl;
        outputFile<<"Sentence: "<<sentence<<" has negative probability "<<final_negative_prob<<endl;
        if (final_negative_prob > final_positive_prob) {
           outputResult<<it->first<<" "<<"negative "<<final_negative_prob<<" "<<final_positive_prob<<endl;
        } else {
         outputResult<<it->first<<" "<<"positive "<<final_negative_prob<<" "<<final_positive_prob<<endl;
        }
    }
}

int main() {
    ofstream outputFile;
    outputFile.open("debug.txt", std::ios_base::app);
    outputFile.clear();
    string line;
    trainNaiveBayes();
    cout<<dataset_sentences.size();
    outputFile<<"*****"<<endl;
    outputFile<<"Trained Naive Bayes"<<endl;
    testNaiveBayes();

    return 0;
}