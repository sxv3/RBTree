#include "Node.h"
//node implementation
//by Tai Wong, 5/17/25
Node::Node(int val) {
  data = val;
  isRed = true;
  left = 0;
  right = 0;
  parent = 0;
}
