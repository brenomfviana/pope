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
    std::map<int, Node*> children;
    unsigned int action;

    Node(int action) {
      this->action = action;
    }

    Node(int action, std::map<int, Node*> children) {
      this->action = action;
      this->children = children;
    }
};

#endif /* _POPE_DECISION_TREE_NODE_HPP_ */
