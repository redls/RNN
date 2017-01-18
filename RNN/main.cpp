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
    unordered_map<long long, string> treesParsedByMe = readParsedTrees();
    for (auto it = dataset_sentences.begin(); it != dataset_sentences.end(); ++it ) {
        string sentence = it->first;
        long long index = it->second;
        string parsedTreesByMeRepresentation = treesParsedByMe[index];
        string targetTreeFormat = targetSentencesTrees->retrieveSentenceIndex(index);
        if (targetTreeFormat.empty()) {
             cout<<"For the given sentence, no target tree was found."<<endl;
             continue;
        }
        Tree* target = constructTargetTree(targetTreeFormat, sentence, dictionary, sentimentLabels);
       // Tree* parsedTree = constructTreeForASentence(sentence, weights, sentimentMatrix, vocab);
        Tree* parsedTree = useParserForCreatingTheTree(parsedTreesByMeRepresentation, sentence, dictionary, vocab, sentimentMatrix, weights);
        vector<double> parentError = getZeros(25);
        vector<vector<double>> result = backprop(target,parsedTree, sentimentMatrix, weights,parentError);
        vector<double> score = parsedTree->getScore();
        vector<double> targetScore = target->getRootRepresentation();
        vector<double> nodeRep = parsedTree->getRootRepresentation();
        for(int k = 0; k < score.size(); k++) {
            score[k] = 1 - score[k];
        }
        vector<vector<double>> resultSentimentMatrix;
        for(int i = 0; i< sentimentMatrix.size(); i++) {
            vector<double> temp;
            temp.push_back(0);
            resultSentimentMatrix.push_back(temp);
            for(int j = 0; j< sentimentMatrix[0].size(); j++) {
                resultSentimentMatrix[i].push_back(0);
                resultSentimentMatrix[i][j] = targetScore[i] * score[i]*nodeRep[j];
            }
        }
        weights = subtractTwoMatrices(weights, multiplyMatrixByScalar(result, learningRate));
        sentimentMatrix = subtractTwoMatrices(sentimentMatrix, multiplyMatrixByScalar(resultSentimentMatrix, learningRate));
    }
}

void classifyTestSentences() {
     ofstream outputResult("RNNClasificationResults.txt");
     long long counter = 0;
     long long totalNumberOfSentences = 0;
     unordered_map<long long, string> treesParsedByMe = readParsedTrees();
     for (auto it = testset_sentences.begin(); it != testset_sentences.end(); ++it ) {
        totalNumberOfSentences++;
        string sentence = it->first;
        long long index = it->second;
        string parsedTreesByMeRepresentation = treesParsedByMe[index];
        //Tree* parsedTree = constructTreeForASentence(sentence, weights, sentimentMatrix, vocab);
        Tree* parsedTree = useParserForCreatingTheTree(parsedTreesByMeRepresentation, sentence, dictionary, vocab, sentimentMatrix, weights);
        vector<double> finalScore = parsedTree->getScore();
        if (finalScore.size() == 2) {
            if (finalScore[0] > finalScore[1]) {
                outputResult<<"Negative -> ";
                if (sentimentLabels->getSentimentScore(index) < 0.5) counter++;
            }
            else {
                outputResult<<"Positive -> ";
                if (sentimentLabels->getSentimentScore(index) >= 0.5) counter++;
            }
        } else {
            cout<<"Final score does not have 2 dimensions for the sentence:";
        }
        outputResult<<"Sentence: "<<sentence<<endl;
     }
     cout<<"Correct predicted: "<<counter<<" out of: "<<totalNumberOfSentences;
}

int main()
{
    preprocessSentences();
    vector<double> weights1 = createRandomDistributions(25);
    vector<double> weights2 = createRandomDistributions(25);
    sentimentMatrix.push_back(weights1);
    sentimentMatrix.push_back(weights2);
    //Tree* parsedTree = createTree("But he somehow pulls it off .");
   /* cout<<"+++"<<endl;
    Tree* parsedTree2 = constructTreeForASentence("But he somehow pulls it off .", weights, sentimentMatrix, vocab);
    string treeText = "9|8|6|6|7|7|8|9|0";
    string sente = "Um , no . .";

    Tree* parsedTree = useParserForCreatingTheTree(treeText, sente, dictionary, vocab, sentimentMatrix, weights);

    vector<double> parentError;

    for(int i = 0; i < 25;i++) parentError.push_back(0.0);*/

   // vector<vector<double>> result = backprop(target,parsedTree2, sentimentMatrix, weights,parentError);
   // cout<<"--"<<result[0].size()<<endl;
    //t->inOrderTraversal();
    //printElementsOfVector(result);
    trainRNN();
    classifyTestSentences();
   // parsedTree->inOrderTraversal();
    cout << "Hello world!" << endl;
    return 0;
}
