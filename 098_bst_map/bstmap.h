#ifndef __BST_H__
#define __BST_H__

#include <stdlib.h>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL) {}
    Node(K k, V v) : key(k), value(v), left(NULL), right(NULL) {}
    ~Node() {}
  };

  Node * root;

  void myclear(Node * node) {
    if (node == NULL) {
      return;
    }
    myclear(node->left);
    myclear(node->right);
    delete node;
  }

  Node * myadd(Node * r, Node * newnode) {
    if (r == NULL) {
      return newnode;
    }
    if (r->key == newnode->key) {
      r->value = newnode->value;
      delete newnode;
      return r;
    }
    if (r->key > newnode->key) {
      r->left = myadd(r->left, newnode);
    }
    else {
      r->right = myadd(r->right, newnode);
    }
    return r;
  }

  const V & mylookup(Node * node, const K & key) const throw(std::invalid_argument) {
    if (node == NULL) {
      throw std::invalid_argument("No such key!");
    }
    if (node->key == key) {
      return node->value;
    }
    if (key < node->key) {
      return mylookup(node->left, key);
    }
    else {
      return mylookup(node->right, key);
    }
  }

  Node * myremove(Node * node, const K & key) {
    if (node == NULL) {
      return NULL;
    }
    if (node->key == key) {
      if (node->left == NULL && node->right == NULL) {
        delete node;
        return NULL;
      }
      else if (node->left == NULL || node->right == NULL) {
        Node * temp = node->left == NULL ? node->right : node->left;
        delete node;
        return temp;
      }
      else {
        Node * temp = node->left;
        while (temp->right != NULL) {
          temp = temp->right;
        }
        K tempkey = node->key;
        node->key = temp->key;
        node->value = temp->value;
        temp->key = tempkey;
        node->left = myremove(node->left, tempkey);
      }
    }
    else if (key < node->key) {
      node->left = myremove(node->left, key);
    }
    else {
      node->right = myremove(node->right, key);
    }
    return node;
  }

  Node * mycopy(Node * node) {
    if (node == NULL) {
      return NULL;
    }
    Node * newnode = new Node(node->key, node->value);
    newnode->left = mycopy(node->left);
    newnode->right = mycopy(node->right);
    return newnode;
  }

 public:
  BstMap() : root(new Node()) {}

  BstMap(const BstMap & rhs) : root(new Node()) { root->right = mycopy(rhs.root->right); }

  BstMap & operator=(const BstMap & rhs) {
    if (this == &rhs) {
      return *this;
    }
    myclear(root);
    root = new Node();
    root->right = mycopy(rhs.root->right);
    return *this;
  }

  virtual void add(const K & key, const V & value) {
    Node * node = new Node(key, value);
    root->right = myadd(root->right, node);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    return mylookup(root->right, key);
  }

  virtual void remove(const K & key) { root->right = myremove(root->right, key); }

  virtual ~BstMap<K, V>() { myclear(root); }
};

#endif
