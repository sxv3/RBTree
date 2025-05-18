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

void RBTree::rotate(Node* x, bool isRight) {
  if (isRight == false) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != sentinel) {
      y->left->parent = x;
    }
    
    y->parent = x->parent;
    if (x->parent == sentinel) {
      root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;  
  } else {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != sentinel) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == sentinel) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }
}

void RBTree::rebalanceTree(Node* node) {
    Node* node2;
    while (node->parent->isRed) {
      
        if (node->parent == node->parent->parent->left) {
            node2 = node->parent->parent->right;
          
            if (node2->isRed) {
                node->parent->isRed = false;
                node2->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent;

            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotate(node, false);
                }
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                rotate(node->parent->parent, true);
              
            }
        } else {
            node2 = node->parent->parent->left;
          
            if (node2->isRed) {
                node->parent->isRed = false;
                node2->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent;
              
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotate(node, true);
                }
              
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                rotate(node->parent->parent, false);
            }
        }
        if (node == root) {
          break;
        }
    }
    root->isRed = false;
}
  
