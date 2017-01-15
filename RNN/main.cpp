#include <iostream>
#include <fstream>
#include <utility>
#include "DatasetSentences.h"
#include "DatasetSentenceTrees.h"
#include "TestsetSentences.h"
#include "MatrixOperations.h"
#include "SentenceTree.h"
#include "Preprocessing.h"


using namespace std;

double learningRate = 0.001;

Vocabulary* vocab = new Vocabulary();
Dictionary* dictionary =  new Dictionary();
SentimentLabels* sentimentLabels =  new SentimentLabels();
DatasetSentences* datasetSentences = new DatasetSentences();
TestsetSentences* testsetSentences = new TestsetSentences();
DatasetSentencesTrees* targetSentencesTrees = new DatasetSentencesTrees();

unordered_map<string, long long> dataset_sentences = datasetSentences->getSentencesMap();
unordered_map<string, long long> testset_sentences = testsetSentences->getSentencesMap();

// Weights used to train the network. They have the dimension of 25 x 50.
vector<vector<double>> weights = initialiseWeigths(25);

// Sentiment matrix used for classification in the 2 classes, negative and positive.
vector<vector<double>> sentimentMatrix;

vector<double> weightScore = createRandomDistributions(25);


void trainRNN() {
    for (auto it = dataset_sentences.begin(); it != dataset_sentences.end(); ++it ) {
        string sentence = it->first;
        long long index = it->second;
        string targetTreeFormat = targetSentencesTrees->retrieveSentenceIndex(index);
        if (targetTreeFormat.empty()) {
             cout<<"For the given sentence, no target tree was found."<<endl;
             continue;
        }
        Tree* target = constructTargetTree(targetTreeFormat, sentence, dictionary, sentimentLabels);
        Tree* parsedTree = constructTreeForASentence(sentence, weights, sentimentMatrix, vocab);
        vector<double> parentError = getZeros(25);
        vector<vector<double>> result = backprop(target,parsedTree, sentimentMatrix, weights,parentError);
        weights = subtractTwoMatrices(weights, multiplyMatrixByScalar(result, learningRate));
    }
}

void classifyTestSentences() {
     ofstream outputResult("RNNClasificationResults.txt");
     for (auto it = testset_sentences.begin(); it != testset_sentences.end(); ++it ) {
        string sentence = it->first;
        long long index = it->second;
        Tree* parsedTree = constructTreeForASentence(sentence, weights, sentimentMatrix, vocab);
        vector<double> finalScore = parsedTree->getScore();
        if (finalScore.size() == 2) {
            if (finalScore[0] > finalScore[1]) outputResult<<"Negative -> ";
            else outputResult<<"Positive -> ";
        } else {
            cout<<"Final score does not 2 dimensions for the sentence:";
        }
        outputResult<<"Sentence: "<<sentence<<endl;
     }
}

int main()
{
    preprocessSentences();
    vector<double> weights1 = createRandomDistributions(25);
    vector<double> weights2 = createRandomDistributions(25);
    sentimentMatrix.push_back(weights1);
    sentimentMatrix.push_back(weights2);
    //Tree* parsedTree = createTree("But he somehow pulls it off .");
    cout<<"+++"<<endl;
    Tree* parsedTree2 = constructTreeForASentence("But he somehow pulls it off .", weights, sentimentMatrix, vocab);
    string treeText = "13|12|11|8|8|9|10|9|10|11|12|13|0";
    string sente = "But he somehow pulls it off .";

    Tree* target = constructTargetTree(treeText, sente, dictionary, sentimentLabels);

    vector<double> parentError;

    for(int i = 0; i < 25;i++) parentError.push_back(0.0);

    vector<vector<double>> result = backprop(target,parsedTree2, sentimentMatrix, weights,parentError);
    cout<<"--"<<result[0].size()<<endl;
    //t->inOrderTraversal();
    //printElementsOfVector(result);
    trainRNN();
    classifyTestSentences();
    cout << "Hello world!" << endl;
    return 0;
}
