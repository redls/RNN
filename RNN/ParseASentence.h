#include<cstdio>
#include<vector>
#include<string>
#include "Node.h"
#include "Vocabulary.h"

using namespace std;

/**
 * Methods dealing with sentence operations like.
 */


vector<string> getWordsFromSentence(string sentence);

vector<Node> retrieveWordRepresentation(vector<string> words, Vocabulary vocabulary);
