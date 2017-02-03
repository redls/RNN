#include <unordered_map>
#include <cstdio>

using namespace std;

/*
 * Map which keeps the reads from the "DatasetSentences.txt" stores only the sentences used for dev
 * and their index. One can find which senteces are used for testing by looking in datasetSplit.txt and
 * retrieve the sentences annotated with 3.
 */


class DevsetSentences {
    private:
        unordered_map<string, long long> sentences;

    public:

        // Constructor.
        DevsetSentences();

        // Retrieve map.
        unordered_map<string, long long> getSentencesMap();
};

