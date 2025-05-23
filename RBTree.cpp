#include "RBTree.h"
#include <iostream>
#include <fstream>

using namespace std;

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

void RBTree::rotateLeft(Node* x) {
  //left rotate
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
}

void RBTree::rotateRight(Node* x) {
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

void RBTree::rebalanceTree(Node* newNode) {
  Node* parent;
  Node* grandParent;
  Node* uncle;

  //while parent is red
  while (newNode->parent->isRed) {
    parent = newNode->parent;
    grandParent = parent->parent;

    if (parent == grandParent->left) {
      uncle = grandParent->right;
      //case 1 if uncle red
      if (uncle->isRed) {
        parent->isRed = false;
        uncle->isRed = false;
        grandParent->isRed = true;
        newNode = grandParent;
              
      } else {
        //case 2 if new node is right
        if (newNode == parent->right) {
          newNode = parent;
          rotateLeft(newNode); //rotate left
        }

        //case 3
        Node* p = newNode->parent;
        Node* g = p->parent;

        p->isRed = false;   // e.g. 20 → black
        g->isRed = true;    // e.g. 30 → red
        rotateRight(g); //rotate right grandparent
        
        break;
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
          rotateRight(newNode); //right rotate parent
        }
              
        Node* p = newNode->parent;
        Node* g = p->parent;

        p->isRed = false;   // e.g. 20 → black
        g->isRed = true;    // e.g. 30 → red
        rotateLeft(g); //left rotate grandparent
        
        break;
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

void RBTree::insert(int val) {
  //create a red new node
  Node* newNode = new Node(val);
  newNode->left   = sentinel;
  newNode->right  = sentinel;
  newNode->parent = sentinel;    
  newNode->isRed = true;

  //insert it into the binary tree
  Node* y = sentinel;
  Node* x = root;
  while (x != sentinel) {
    y = x;
    if (newNode->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  
  newNode->parent = y;
  if (y == sentinel) {
    root = newNode;
  } else if (newNode->data < y->data) {
    y->left = newNode;
  } else {
    y->right = newNode;
  }

  //after insert, fix the tree
  rebalanceTree(newNode);
}

//load file
void RBTree::load(const char* filename) {
  //load from filename
  ifstream file(filename);
  
  int num;
  while (file >> num) {
    insert(num);
  }
}

//print helper
void RBTree::printHelper(Node* node, int count, bool end) {
  //stops if at sentinel node
  if (node == sentinel) {
    return;
  }
  //indent
  for (int i = 0; i < count; ++i) {
      cout << "|   ";
  }
  //marks branches
  if (end == true) {
      cout << "X-- ";
  } else {
      cout << "|-- ";
  }
  //prints out red black value or parent
  cout << node->data;
  if (node->isRed) {
    cout << "(R)";
  } else {
    cout << "(B)";
  }
  if (node->parent != sentinel) {
    cout << "[P:" << node->parent->data << "]";
  }
  cout << endl;
  
  //run the func on children
  printHelper(node->left,  count + 1, false);
  printHelper(node->right, count + 1, true);
}

//print func
void RBTree::print() {
  //if root is sentinel node
  if (root == sentinel) {
    cout << "tree is empty" << endl;
    return;
  }
  //recursive func to print out tree nicely
  printHelper(root, 0, true);
}

//search func
bool RBTree::search(int val) {
  Node* current = root;
  //searches to see if a value exists in tree
  while (current != sentinel) {
    if (val == current->data) {
      return true;
    } else if (val < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return false;
}

//finds mininum node
Node* RBTree::treeMinimum(Node* node) {
  while (node->left != sentinel) {
    node = node->left;
  }
  return node;
}

//replaces one subtree with another
void RBTree::rbTransplant(Node* node1, Node* node2) {
  if (node1->parent == sentinel) {
    root = node2;
  } else if (node1 == node1->parent->left) {
    node1->parent->left = node2;
  } else {
    node1->parent->right = node2;
  }
  node2->parent = node1->parent;
}

//fixes deletion
void RBTree::fixDelete(Node* node) {
  while (node != root && !node->isRed) {
    
    if (node == node->parent->left) {
      Node* sibling = node->parent->right;

      //case 1 if sibling is red
      //rotates parent left to make sibling black and reduce to other cases
      if (sibling->isRed) {
        sibling->isRed = false;
        node->parent->isRed = true;
        rotateLeft(node->parent);
        sibling = node->parent->right;
      }

      //case 2 uif sibling and siblings children are black
      //recolor sibling to red and move up tree
      if ((sibling->left->isRed == false) && (sibling->right->isRed == false)) {
        sibling->isRed = true;
        node = node->parent;
      } else {
        //case 3 sibling is black and sibling right child is black and sibling left child is red
        //rotate sibling right and swap colors to convert to case 4
        if (sibling->right->isRed == false) {
          sibling->left->isRed = false;
          sibling->isRed = true;
          rotateRight(sibling);
          sibling = node->parent->right;
        }

        //case 4 sibling is black and sibling right child is red
        //recolor and rotate to fix
        sibling->isRed = node->parent->isRed;
        node->parent->isRed = false;
        sibling->right->isRed = false;
        rotateLeft(node->parent);
        node = root;
        //loop exits here
      }
    } else {
      //mirror cases
      Node* sibling = node->parent->left;

      if (sibling->isRed) {
        sibling->isRed = false;
        node->parent->isRed = true;
        rotateRight(node->parent);
        sibling = node->parent->left;
      }

      if ((sibling->left->isRed == false) && (sibling->right->isRed == false)) {
        sibling->isRed = true;
        node = node->parent;
        
      } else {
        if (sibling->left->isRed == false) {
          sibling->right->isRed = false;
          sibling->isRed = true;
          rotateLeft(sibling);
          sibling = node->parent->left;
        }

        sibling->isRed = node->parent->isRed;
        node->parent->isRed = false;
        sibling->left->isRed = false;
        rotateRight(node->parent);
        node = root;
      }
    }
  }
  node->isRed = false; //removes the extra black
}

//delete node func
void RBTree::deleteNode(Node* node) {
  Node* y = node; //y node is the node that will be deleted
  Node* x; //replacement node for y
  bool originalColor = y->isRed; //save original color incase of needing to fix tree
  
  //case 1 and 2 node has 1 real child
  if (node->left == sentinel) {
    x = node->right;
    rbTransplant(node, node->right);
  } else if (node->right == sentinel) {
    x = node->left;
    rbTransplant(node, node->left);
  } else {
    
    //case 3 node has 2 children
    y = treeMinimum(node->right); //sucessor node
    originalColor = y->isRed;
    x = y->right;

    if (y->parent == node) {
      x->parent = y;
    } else {
      rbTransplant(y, y->right);
      y->right = node->right;
      y->right->parent = y;
    }

    rbTransplant(node, y);
    y->left = node->left;
    y->left->parent = y;
    y->isRed = node->isRed; 
  }

  delete node;
  //if it is black then tree needs to be fixed
  if (originalColor == false) {
    fixDelete(x);
  }
}
