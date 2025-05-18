#include "RBTree.h"
#include <iostream>

//main.cpp file to run program
//by Tai Wong, 5/18/2025

using namespace std;

int main() {
  RBTree tree;
  int choice;
  int val;

  //give options to user
  cout << "1->load from input.txt" << endl;
  cout << "2->insert a number" << endl;
  cout << "3->print tree" << endl;
  cout << "4->exit" << endl;

  //runs program until user wants to stop
  while (true) {
    cout << "enter choice";
    cin >> choice;

    if (choice == 1) {
      tree.load("input.txt");
      cout << "tree loaded from file" << endl;
    } else if (choice == 2) {
      cout << "enter number (1-999): ";
      cin >> val;
      tree.insert(val);
      cout << "value inserted" << endl;
    } else if (choice == 3) {
      tree.print();
    } else if (choice == 4) {
      break;
    } else {
      cout << "bad input" << endl;
    }
  }
  
  return 0;
}
