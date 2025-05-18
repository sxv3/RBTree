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
  //left rotate
  if (isRight == false) {
    //sets node to right side
    Node* y = x->right;
    
    //splice y left subtree
    x->right = y->left;
    //if subtree isnt null
    if (y->left != sentinel) {
      y->left->parent = x; //make sure left subtree parent points to x
    }
    
    //y takes x's position in the tree
    y->parent = x->parent;
    if (x->parent == sentinel) {
      root = y;  //if root, then y becomes root
    } else if (x == x->parent->left) {
      x->parent->left = y;   //otherwise y becomes the right/left child of parent depending on x
    } else {
      x->parent->right = y;
    }
    //x becomes left child of y and y becomes parent of x 
    y->left = x;
    x->parent = y;  
  } else {
    //same thing for right side
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

void RBTree::rebalanceTree(Node* newNode) {
  Node* parent;
  Node* grandParent;
  Node* uncle;

  //parent is red
  while (newNode->parent->isRed) {
    parent = newNode->parent;
    grandParent = parent->parent;

    if (parent == grandParent->left) {
      uncle = grandParent->right;
      //uncle red
      if (uncle->isRed) {
        parent->isRed = false;
        uncle->isRed = false;
        grandParent->isRed = true;
        newNode = grandParent;
              
      } else {
        //new node is right
        if (newNode == parent->right) {
          newNode = parent;
          rotate(newNode, false); //rotate left
        }
               
        parent->isRed = false;
        grandParent->isRed = true;
        rotate(grandParent, true); //rotate right grandparent
      }
    } else {
      //mirror cases
      uncle = grandParent->left;
      if (uncle->isRed) {
        parent->isRed = false;
        uncle->isRed = false;
        grandParent->isRed = true;
        newNode = grandParent;
              
      } else {
        if (newNode == parent->left) {
          newNode = parent;
          rotate(newNode, true); //right rotate parent
        }
              
        parent->isRed = false;
        grandParent->isRed = true;
        rotate(grandParent, false); //left rotate grandparent
              
      }
    }
    
    //if at root then stop
    if (newNode == root) {
      break;
    }
  }
  
  //set root to black again
  root->isRed = false;
}
