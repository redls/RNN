#include <iostream>
#include <utility>
//#include "ParseASentence.h"
#include "MatrixOperations.h"
#include "SentenceTree.h"


using namespace std;

Vocabulary* vocab = new Vocabulary();
Dictionary* dictionary =  new Dictionary();
SentimentLabels* sentimentLabels =  new SentimentLabels();

vector<vector<double>> weights = initialiseWeigths(25);

vector<double> weights1 = createRandomDistributions(25);
vector<double> weights2 = createRandomDistributions(25);


vector<double> weightScore = createRandomDistributions(25);

Tree* createTree(string sentence) {
    vector<string> words = getWordsFromSentence(sentence);
    vector<Node> nodes = retrieveWordRepresentation(words, vocab);
    vector<pair<int,int>> pairedElem;
    vector<Tree*> trees;

    // Convert the nodes into trees with height 1.
    for(int i = 0; i < nodes.size();i++) {
        Tree *lala = new Tree(nodes[i]);
        trees.push_back(lala);
    }

    int numberOfWords = trees.size();

    // Merge all the small trees into only one tree.
    while (numberOfWords > 1) {
        double score = 0;
        double maxScore = 0;
        vector<double> concatenation = concatenateTwoVectors(trees[0]->getRootRepresentation(),
                    trees[1]->getRootRepresentation());
        vector<double> product = matrixMultplication(weights, concatenation);
        vector<double> afterTanh = applyTanhElementWise(product);
        maxScore = vectorInnerProduct(weightScore, afterTanh);
        int left = 0;
        int right = 1;
        for(int i = 1; i < trees.size(); i++) {
            concatenation = concatenateTwoVectors(trees[i-1]->getRootRepresentation(),
                    trees[i]->getRootRepresentation());
            product = matrixMultplication(weights, concatenation);
            afterTanh = applyTanhElementWise(product);
            score = vectorInnerProduct(weightScore, afterTanh);
            if (score > maxScore) {
                maxScore = score;
                left = i-1;
                right = i;
            }
        }
        concatenation = concatenateTwoVectors(trees[left]->getRootRepresentation(),
                    trees[right]->getRootRepresentation());
        product = matrixMultplication(weights, concatenation);
        afterTanh = applyTanhElementWise(product);
        Tree *merged = new Tree(afterTanh);
        merged->setLeftTree(trees[left]);
        merged->setRightTree(trees[right]);
        trees[left] = merged;
        for(int i = right + 1; i < trees.size();i++) {
            trees[i-1] = trees[i];
        }
        trees.pop_back();
        pairedElem.push_back(make_pair(left,right));
        numberOfWords--;
    }
    //Tree aux = *trees[0];
    double score = vectorInnerProduct(weightScore, trees[0]->getRootRepresentation());
    for (int i = 0; i < pairedElem.size(); i++) {
        cout<< pairedElem[i].first<<" "<< pairedElem[i].second<< endl;
    }
    //cout<<score<<endl;
    return trees[0];

}

int main()
{
    Tree* parsedTree = createTree("But he somehow pulls it off .");
    cout<<"+++"<<endl;
    Tree* parsedTree2 = constructTreeForASentence("But he somehow pulls it off .", weights, weightScore, vocab);
    // parsedTree->inOrderTraversal();
    //createTree("This was an amazing movie.");
    //createTree("This was an awful movie.");
    string treeText = "13|12|11|8|8|9|10|9|10|11|12|13|0";
    string sente = "But he somehow pulls it off .";
    Tree* target = constructTargetTree(treeText, sente, dictionary, sentimentLabels);
    vector<vector<double>> sentimentMatrix;
    sentimentMatrix.push_back(weights1);
    sentimentMatrix.push_back(weights2);
    vector<double> parentError;

    for(int i = 0; i < 25;i++) parentError.push_back(0.0);

    vector<double> result = backprop(target,parsedTree2, sentimentMatrix, weights,parentError);
    //t->inOrderTraversal();
    cout << "Hello world!" << endl;
    return 0;
}
