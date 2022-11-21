#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t mytree;
  for (size_t i = 0; i < 257; ++i) {
    if (counts[i] != 0) {
      mytree.push(new Node(i, counts[i]));
    }
  }
  while (mytree.size() > 1) {
    Node * first = mytree.top();
    mytree.pop();
    Node * second = mytree.top();
    mytree.pop();
    Node * newNode = new Node(first, second);
    mytree.push(newNode);
  }
  return mytree.top();
}
