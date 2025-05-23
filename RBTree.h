#ifndef RBTREE_H
#define RBTREE_H
#include "Node.h"
//rbtree header 
//by Tai Wong, 5/17/25

class RBTree {
private:
  Node* root;
  Node* sentinel; 

  void rotateRight(Node* node);
  void rotateLeft(Node* node);
  void rebalanceTree(Node* node);
  void printHelper(Node* root, int count, bool end);

  void deleteNode(Node* node);
  void rbTransplant(Node* node1, Node* node2);
  Node* treeMinimum(Node* node);
  void fixDelete(Node* node);

public:

  RBTree();

  void insert(int val);
  void load(const char* filename);
  void print();

  bool search(int val);
  void remove(int val);
};

#endif
