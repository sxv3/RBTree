#ifndef NODE_H
#define NODE_H

//node header file
//by Tai Wong, 5/16/25

class Node {
public:
  int data;
  bool isRed;
  Node* left;
  Node* right;
  Node* parent;

  Node(int value);
};

#endif
