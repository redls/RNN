#include "Node.h"
#include<cstdio>
#include<vector>

using namespace std;

class Tree {
    Node node;
    Tree *left;
    Tree *right;
    public:
    Tree(Node x);
    void addNewNodeToTree(Node x);
};
