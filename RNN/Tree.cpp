#include "Tree.h"
#include<cstdio>
#include<vector>

using namespace std;

Tree::Tree(Node x) {
    left = NULL;
    right = NULL;
    node = Node(x.getNode());
}

void Tree::addNewNodeToTree(Node x) {

}

vector<double> Tree::getRootRepresentation() {
    vector<double> rootRepresentation = this->node.getNode();
    return rootRepresentation;
}

void Tree::setLeftTree(Tree* x) {
    this->left = x;
}

void Tree::setRightTree(Tree* x) {
    this->right = x;
}
