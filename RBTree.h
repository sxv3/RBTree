#ifndef RBTREE_H
#define RBTREE_H
#include "Node.h"
//rbtree header 
//by Tai Wong, 5/17/25

class RBTree {
private:
    Node* root;
    Node* sentinel;     // sentinel leaf

    void rotateLeft(Node* node);

    void rotateRight(Node* node);

    void rebalanceTree(Node* node);

    void printHelper(Node* root, int count, bool end);

public:

    RBTree();
    ~RBTree();

    void insert(int val);
    void load(const char* filename);
    void print();
};

#endif
