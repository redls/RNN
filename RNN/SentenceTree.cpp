#include "SentenceTree.h"
#include "MatrixOperations.h"
#include<string>
#include<cstdio>
#include<iostream>
using namespace std;

/**
 * Contains methods which interact with a given sentence's tree.
 */


 double distanceBetweenTwoVectors(vector<double> vec1, vector<double> vec2) {
    double score = 0;
    for(int i = 0; i < vec1.size(); i++) {
        score = score + (vec1[i] - vec2[i])*(vec1[i] - vec2[i]);
    }
    return score;
 }

// Given a sentence, construct its semantic tree by combining the words using the tanh rule.
Tree* constructTreeForASentence(string sentence, vector<vector<double>> weights, vector<vector<double>> weightScore, Vocabulary *vocab) {
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
        vector<double> product = matrixMultplicationWithVector(weights, concatenation);
        vector<double> afterTanh = applyTanhElementWise(product);
        maxScore = distanceBetweenTwoVectors(trees[0]->getRootRepresentation(), trees[1]->getRootRepresentation());
        int left = 0;
        int right = 1;
        for(int i = 1; i < trees.size(); i++) {
            concatenation = concatenateTwoVectors(trees[i-1]->getRootRepresentation(),
                    trees[i]->getRootRepresentation());
            product = matrixMultplicationWithVector(weights, concatenation);
            afterTanh = applyTanhElementWise(product);
            score = distanceBetweenTwoVectors(trees[i-1]->getRootRepresentation(),
                    trees[i]->getRootRepresentation());
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
        product = matrixMultplicationWithVector(weights, concatenation);
        afterTanh = applyTanhElementWise(product);

        // Create new node which has as children the 2 nodes, and as the root the computed
        // score.
        Tree *merged = new Tree(afterTanh);
        merged->setScore(softmax(matrixMultplicationWithVector(weightScore, afterTanh)));

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
    vector<double> score = matrixMultplicationWithVector(weightScore, trees[0]->getRootRepresentation());
    //for (int i = 0; i < 2; i++) {
        cout<<"negative: "<<score[0]<<"\n positive"<<score[1]<< endl;
    //}
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


// Assign the labels of to the tree in a post-order way.
string assignRightLabels(Tree* t, vector<string> words, Dictionary* dictionary, SentimentLabels* sentimentLabels, int &numberOfLeaves) {
    if (t == nullptr) {
        cout<<"I am null"<<endl;
        return "";
    }
    // The current node is a leaf, so we compute its score by searching the word in the sentiment labels map.
    if (t->getLeftTree() == nullptr && t->getRightTree() == nullptr) {
    cout<<"*** "<< words[numberOfLeaves]<< numberOfLeaves<<endl;
        long long phraseIndex = dictionary->getPhraseIndex(words[numberOfLeaves]);
        double score = sentimentLabels->getSentimentScore(phraseIndex);
        if (phraseIndex == -1) cout<<words[numberOfLeaves]<<" no found in the dictionary"<<endl;
        if (score >= 0.5) {
            // case when the word is positive.
            vector<double> root = t->getRootRepresentation();
            root[0] = 0;
            root[1] = 1;
            t->setRoot(root);
        } else {
            // case when the word is negative.
            vector<double> root = t->getRootRepresentation();
            root[0] = 1;
            root[1] = 0;
            t->setRoot(root);
        }
        numberOfLeaves++;
        return words[numberOfLeaves - 1];
    }

    // The current node is an inner node, compute both left and right trees and then compute the value for the tree;
    string left = assignRightLabels(t->getLeftTree(), words, dictionary, sentimentLabels, numberOfLeaves);
    string right = assignRightLabels(t->getRightTree(), words, dictionary, sentimentLabels, numberOfLeaves);
    string partialPhrase = left +" "+ right;
    long long phraseIndex = dictionary->getPhraseIndex(partialPhrase);
    if (phraseIndex == -1) cout<<partialPhrase<<" not found in the dictionary"<<endl;
    double score = sentimentLabels->getSentimentScore(phraseIndex);
    if (score >= 0.5) {
        // case when the word is positive.
        vector<double> root = t->getRootRepresentation();
        root[0] = 0;
        root[1] = 1;
        t->setRoot(root);
    } else {
        // case when the word is negative.
        vector<double> root = t->getRootRepresentation();
        root[0] = 1;
        root[1] = 0;
        t->setRoot(root);
    }
    return partialPhrase;
}


// Construct the tree which is represented my the given array, a.
/*Tree* getParentPointerTree(int a[], int length, int index) {
    Node* temp = new Node(createTemporaryNodeRepresentation(index));
    Tree* parent = new Tree(*temp);
    pair<int,int> children = findElementInArray(a, length,index);
    if (children.first == -1 || children.second == -1) return parent;

    //findFirstOccurenceOfElement(a, children.first, length) + 1 since the array should be indexed from 1.
    int indexRootLeft = children.first + 1;
    Tree* leftTree = getParentPointerTree(a, length, indexRootLeft);
    parent->setLeftTree(leftTree);

    //findFirstOccurenceOfElement(a, children.second, length) since the array should be indexed from 1.
    int indexRootRight = children.second + 1;
    Tree* rightTree = getParentPointerTree(a, length, indexRootRight);
    parent->setRightTree(rightTree);

    return parent;
}*/

// Update the given tree by merging the given branch to the tree.
void updateTree(Tree* t, vector<int> branch) {
    Tree* temp = t;
    int s = branch.size() - 2;
    while (s >= 0) {
        int value = branch[s];
        if (temp->getLeftTree() == nullptr) {
            Node* node = new Node(createTemporaryNodeRepresentation(value));
            Tree* newTree= new Tree(*node);
            temp->setLeftTree(newTree);
            temp = temp->getLeftTree();
        } else {
            Tree * leftChild = temp->getLeftTree();
            vector<double> leftChildRepresentation = leftChild->getRootRepresentation();
            if (leftChildRepresentation[0] == value) {
                temp = temp->getLeftTree();
            } else {
                Tree * rightChild = temp->getRightTree();
                if (rightChild == nullptr) {
                    Node* node = new Node(createTemporaryNodeRepresentation(value));
                    Tree* newTree= new Tree(*node);
                    temp->setRightTree(newTree);
                    temp = temp->getRightTree();
                } else {
                    vector<double> rightChildRepresentation = rightChild->getRootRepresentation();
                    if (rightChildRepresentation[0] == value) {
                        temp = temp->getRightTree();
                    } else cout<<" Error in the construction of the parse tree"<<endl;
                }
            }
        }
        s--;
    }
}

// Create tree such that the leaves have indices in ascending order
Tree* constructTree(int a[], int length, int numberOfLeaves) {
    int indexRoot = findFirstOccurenceOfElement(a, 0, length);
    indexRoot++;
    Node* temp = new Node(createTemporaryNodeRepresentation(indexRoot));
    Tree* parent = new Tree(*temp);
    vector<vector<int>> listOfBranches;
    for (int i = 0; i < numberOfLeaves; i++) {
        int j = i;
        vector<int> tempList;
        while (j <= length) {
            //if (a[j] == 0) break;
            tempList.push_back(j + 1);
            if (a[j] == 0) break;
            j = a[j] - 1;
        }
        listOfBranches.push_back(tempList);
        updateTree(parent, tempList);
        //parent->inOrderTraversal();
    }
    return parent;
}


// Given a string of digits and | symbols, return the target tree represented by that string.
Tree* constructTargetTree(string treeText, string sentence, Dictionary* dictionary, SentimentLabels* sentimentLabels) {
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
    // Increase the index of the root by one since the array should be indexed from 1.
    indexRoot++;

    Tree* root = constructTree(positions, numberOfNodes, words.size());
    cout<<"Index of the root: "<<indexRoot<<endl;
    int nr = 0;
    string x = assignRightLabels(root, words, dictionary, sentimentLabels, nr);
    if (root->getLeftTree() == nullptr) cout<<"XOXO"<<endl;
    return root;
}


vector<vector<double>> backprop(Tree * targetTree, Tree * computedTree, vector<vector<double>> weightScoresMatrix, vector<vector<double>> weightsMatrix, vector<double> parentError) {
    vector<vector<double>> weightScoresMatrixTranspose = getTransposeMatrix(weightScoresMatrix);
    vector<vector<double>> weightsMatrixTranspose = getTransposeMatrix(weightsMatrix);
    Tree* copyOfTargetTree = targetTree;
    vector<double> targetRootRepresentation;
     if (targetTree == nullptr) {
        cout<<"The tree was not constructed correctly."<<endl;
        targetRootRepresentation = getZeros(25);
        copyOfTargetTree = new Tree(targetRootRepresentation);

    } else {
        cout<<"*******"<<endl;
        targetRootRepresentation = targetTree->getRootRepresentation();
        }
    vector<double> computedRootRepresentation = computedTree->getRootRepresentation();
    vector<double> softmaxResult = softmax(matrixMultplicationWithVector(weightScoresMatrix, computedRootRepresentation));

    vector<double> difference = substractTwoVectors(softmaxResult, targetRootRepresentation);

    vector<double> deltaScore = matrixMultplicationWithVector(weightScoresMatrixTranspose, difference);

    vector<double> afterTanhDeriv = getTanhDerivativeFunction(computedRootRepresentation);

    deltaScore = getVectorHadamardProduct(deltaScore, afterTanhDeriv);

    vector<double> delta = addTwoVectors(deltaScore, parentError);

    vector<double> newParentError = matrixMultplicationWithVector(weightsMatrixTranspose, delta);

    // Compute error for children.
    vector<double> leftChild = getZeros(25);
    vector<double> rightChild = getZeros(25);

    // This means the current node is a leaf, return the error only for this node.
    if (computedTree->getLeftTree() == nullptr) {
        return getZerosWeightMatrix(25);
    }
    leftChild =  computedTree->getLeftTree()->getRootRepresentation();
    rightChild =  computedTree->getRightTree()->getRootRepresentation();

    vector<double> mergedChildren = concatenateTwoVectors(leftChild, rightChild);

    vector<vector<double>> deltaTransposed = transposeRowVector(delta);
    vector<vector<double>> deltaMatrix = multiplyMatrices(deltaTransposed, mergedChildren);

    mergedChildren = getTanhDerivativeFunction(mergedChildren);

    newParentError = getVectorHadamardProduct(newParentError, mergedChildren);

    vector<double> leftChildError;
    vector<double> rightChildError;
    for (int i = 0; i < newParentError.size(); i++) {
        if (i < newParentError.size()/2) leftChildError.push_back(newParentError[i]);
        else rightChildError.push_back(newParentError[i]);
    }

    vector<vector<double>> childrenScores =  addTwoMatrices(backprop(copyOfTargetTree->getLeftTree(), computedTree->getLeftTree(), weightScoresMatrix, weightsMatrix, leftChildError),
            backprop(copyOfTargetTree->getRightTree(), computedTree->getRightTree(), weightScoresMatrix, weightsMatrix, rightChildError));

    return addTwoMatrices(childrenScores, deltaMatrix);
}




