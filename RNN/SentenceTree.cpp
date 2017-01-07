#include "SentenceTree.h"
#include "MatrixOperations.h"
#include<string>
#include<cstdio>
#include<iostream>
using namespace std;

/**
 * Contains methods which interact with a given sentence's tree.
 */

// Given a sentence, construct its semantic tree by combining the words using the tanh rule.
Tree* constructTreeForASentence(string sentence, vector<vector<double>> weights, vector<double> weightScore, Vocabulary *vocab) {
    vector<string> words = getWordsFromSentence(sentence);
    vector<Node> nodes = retrieveWordRepresentation(words, vocab);
    vector<pair<int,int>> pairedElem;
    vector<Tree*> trees;

    // Convert the nodes into trees with height 1.
    for(int i = 0; i < nodes.size();i++) {
        Tree *t = new Tree(nodes[i]);
        trees.push_back(t);
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
            // Check if the new node would hove a higer score. IF it has, change the variables
            // left and right to point to the positions of the two nodes.
            if (score > maxScore) {
                maxScore = score;
                left = i-1;
                right = i;
            }
        }
        // Recompute the value of the new node.
        concatenation = concatenateTwoVectors(trees[left]->getRootRepresentation(),
                    trees[right]->getRootRepresentation());
        product = matrixMultplication(weights, concatenation);
        afterTanh = applyTanhElementWise(product);

        // Create new node which has as children the 2 nodes, and as the root the computed
        // score.
        Tree *merged = new Tree(afterTanh);
        merged->setLeftTree(trees[left]);
        merged->setRightTree(trees[right]);

        // Replace the 2 nodes by the new computed parent: add the root of the new node into the
        // vector trees (on the left position and shift the other nodes by one position to left).
        trees[left] = merged;
        for(int i = right + 1; i < trees.size();i++) {
            trees[i-1] = trees[i];
        }
        trees.pop_back();
        pairedElem.push_back(make_pair(left,right));
        numberOfWords--;
    }
    // Tells us what is the score of the root of the complete tree of  the sentence.
    double score = vectorInnerProduct(weightScore, trees[0]->getRootRepresentation());
    cout<<score<<endl;
    return trees[0];
}


// Create a container of size 2 (number of classes) containing in both positions a specific value, d.
vector<double> createTemporaryNodeRepresentation(int d) {
    vector<double> wordRep;
    for(int i = 0;i < 2; i++) {
        wordRep.push_back(d);
    }
    return wordRep;
}

// Find an element in an int array and return its index.
int findFirstOccurenceOfElement(int a[], int elem, int length) {
    for (int i =  0; i < length; i++) {
        if (a[i] == elem) return i;
    }
    return -1;
}

// Find the 2 positions, i and j, in the array for which a[i]=a[j]=elem
pair<int,int> findElementInArray(int a[], int length, int elem) {
    pair<int,int> result = make_pair(-1,-1);
    int c = 0;
    for( int i = 0;i < length; i++) {
        if (a[i] == elem && c == 0) {
            result.first = i;
            c++;
        } else if (a[i] == elem && c == 1) {
            result.second = i;
            c++;
            break;
        }
    }
    return result;
}

Tree* getParentPointerTree(int a[], int length, int index) {
    Node* temp = new Node(createTemporaryNodeRepresentation(index));
    Tree* parent = new Tree(*temp);
    pair<int,int> children = findElementInArray(a, length,index);
    if (children.first == -1 || children.second == -1) return parent;

    //findFirstOccurenceOfElement(a, children.first, length) + 1 since the array is indexed from 1.
    int indexRootLeft = children.first + 1;
    Tree* leftTree = getParentPointerTree(a, length, indexRootLeft);
    parent->setLeftTree(leftTree);

    //findFirstOccurenceOfElement(a, children.second, length) since the array is indexed from 1
    int indexRootRight = children.second + 1;
    Tree* rightTree = getParentPointerTree(a, length, indexRootRight);
    parent->setRightTree(rightTree);

    return parent;
}

// Given a string of digits and | symbols, return the target tree represented by that string.
Tree* constructTargetTree(string treeText, string sentence) {
    vector<string> words = getWordsFromSentence(sentence);

    // Find the number of nodes in the tree and also retrieve the positions from treeText.
    int numberOfNodes = 0;
    for (char & c: treeText) {
        if (c == '|') numberOfNodes++;
    }
    numberOfNodes++;
    int positions[numberOfNodes] ;
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

    positions[k] = number; // add the last int in the array.
    // Create tree by using temporary values for the inner nodes. Start by finding the root (0) in the array.
    int indexRoot = findFirstOccurenceOfElement(positions, 0, numberOfNodes);
    indexRoot++;
    cout<<"Index of the root: "<<indexRoot<<endl;
    Tree* root = getParentPointerTree(positions, numberOfNodes, indexRoot);
    return root;
}




