#include<cstdio>
#include<unordered_map>
#include<vector>

using namespace std;

/**
 *  Class which keeps track of the words that appear in the data set.
 */

class Vocabulary {
    unordered_map<string, vector<double>> vocabulary;

    public:
        Vocabulary();
        vector<double> getWordRepresentation(string word);
        bool containsWord(string word);
        void addNewWord(string word);
};
