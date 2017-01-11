#include "Node.h"
#include<cstdio>
#include<vector>

using namespace std;

class Tree {
    Node node;
    Tree *left;
    Tree *right;
    vector<double> score;

    public:
        Tree(Node x);
        void addNewNodeToTree(Node x);
        vector<double> getRootRepresentation();
        void setLeftTree(Tree *x);
        void setRightTree(Tree *x);
        void setRoot(Node x);
        void setScore(vector<double> s);
        Tree* getLeftTree();
        Tree* getRightTree();
        vector<double> getScore();

        // Print the elements of the tree in in-order.
        void inOrderTraversal();
};
