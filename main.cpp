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
  cout << "3->delete a number" << endl;
  cout << "4->search for a number" << endl;
  cout << "5->print tree" << endl;
  cout << "6->exit" << endl;
  
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
      cout << "enter number to delete: ";
      cin >> val;
      tree.remove(val);
      cout << "value deleted" << endl;
    } else if (choice == 4) {
      cout << "enter number to search: ";
      cin >> val;
      bool exist = tree.search(val);
      
      if (exist == true) {
        cout << "number exists in tree" << endl;
      } else {
        cout << "number does not exist in tree" << endl;
      }
    } else if (choice == 5) {
      tree.print();
    } else if (choice == 6) {
      break;
    } else {
      cout << "bad input" << endl;
    }
  }
  
  return 0;
}
