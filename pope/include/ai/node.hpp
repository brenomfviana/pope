/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_DECISION_TREE_NODE_HPP_
#define _POPE_DECISION_TREE_NODE_HPP_

#include <map>

class Node {
  public:
    Node* left;
    Node* right;
    unsigned int question;
    bool is_leaf;
    bool value;

    Node(bool is_leaf, bool value) {
      this->is_leaf = is_leaf;
      this->value = value;
    }

    Node(unsigned int question, Node* left, Node* right) {
      this->is_leaf = false;
      this->question = question;
      this->left = left;
      this->right = right;
    }
};

#endif /* _POPE_DECISION_TREE_NODE_HPP_ */
