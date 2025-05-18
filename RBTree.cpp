#include "RBTree.h"
#include <iostream>
#include <fstream>

//constructor for rbtree
RBTree::RBTree() {
  sentinel = new Node(0);
  
  //initialize sentinel node and sets it to black
  sentinel->isRed = false;
  sentinel->left = sentinel;
  sentinel->right = sentinel;
  sentinel->parent = sentinel;
  
  //node initialize
  root = sentinel;
}
