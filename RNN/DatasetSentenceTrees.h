#include<cstdio>
#include<vector>
#include<unordered_map>

using namespace std;

/**
 * Map which keeps the reads from the "DatasetSentences.txt" stores only the trees of sentences used for training
 * and their index.  One can find which senteces are used for testing by looking in datasetSplit.txt and
 * retrieve the sentences annotated with 1.
 */

 class DatasetSentencesTrees {
    private:
        unordered_map<string, long long> trees;

    public:

        // Constructor.
        DatasetSentencesTrees();
 };

