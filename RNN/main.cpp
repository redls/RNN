#include <iostream>
#include <utility>
//#include "ParseASentence.h"
#include "MatrixOperations.h"
#include "SentenceTree.h"

using namespace std;

Vocabulary *vocab = new Vocabulary();

vector<vector<double>> weights = initialiseWeigths(25);
vector<double> weightScore = createRandomDistributions(25);

void createTree(string sentence) {
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
    cout<<score<<endl;

}

int main()
{
    createTree("This was an amazing movie.");
    //createTree("This was an amazing movie.");
    //createTree("This was an awful movie.");
    string treeText = "6|6|5|5|7|7|0";
    string sente = "Effective but too-tepid biopic";
    Tree* t = constructTargetTree(treeText, sente);
    t->inOrderTraversal();
    /*int numberOfNodes = 0;
    for (char & c: treeText) {
        if (c == '|') numberOfNodes++;
    }
    numberOfNodes++;
    int positions[numberOfNodes];
    int number = 0;
    int k = 0;
    for (char & c: treeText) {
        if (c != '|') number = number *10 + c - '0';
        else {
            positions[k] = number;
            k++;
            number = 0;
        }
    }
    positions[k] = number; */
   // for (int i = 0; i < numberOfNodes; i++)
    cout << "Hello world!" << endl;
    return 0;
}
