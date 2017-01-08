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
        vector<double> getRootRepresentation();
        void setLeftTree(Tree *x);
        void setRightTree(Tree *x);
        void setRoot(Node x);
        Tree* getLeftTree();
        Tree* getRightTree();

        // Print the elements of the tree in in-order.
        void inOrderTraversal();
};
