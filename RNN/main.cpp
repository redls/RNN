#include <iostream>
#include <utility>
#include "ParseASentence.h"
#include "MatrixOperations.h"x
//#include "Tree.h"
//#include "Vocabulary.h"

using namespace std;

Vocabulary *vocab = new Vocabulary();

vector<vector<double>> weights = initialiseWeigths(25);
vector<double> score = createRandomDistributions(25);;

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
    /*while (numberOfWords > 1) {
        double score = 0;

        for(int i = 1; i < trees.size(); i++) {
           // trees[i]
        }
    }*/
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
