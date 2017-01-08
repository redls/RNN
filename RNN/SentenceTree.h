#include "ParseASentence.h"
#include "Dictionary.h"
#include "SentimentLabels.h"
#include<string>
using namespace std;

/**
 * Contains methods which interact with a given sentence's tree.
 */


// Given a sentence, construct its semantic tree by combining the words using the tanh rule.
Tree* constructTreeForASentence(string sentence, vector<vector<double>> weights, vector<double> weightScore, Vocabulary *vocab);


// Given a string of digits and | symbols, return the target tree represented by that string.
Tree* constructTargetTree(string treeText, string sentence, Dictionary* dictionary, SentimentLabels* sentimentLabels);
