/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_DECISION_TREE_HPP_
#define _POPE_DECISION_TREE_HPP_

#include <list>
#include <tuple>
#include <cmath>
#include <map>
#include <numeric>
#include <string>
#include "domain/actions.hpp"
#include "node.hpp"
#include "domain/papers/paper.hpp"

typedef std::tuple<unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long> PassportT;
typedef std::tuple<unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long> IDCardT;
typedef std::tuple<unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long> AccessPermitT;
typedef std::tuple<unsigned long, unsigned long, unsigned long, unsigned long> WorkPassT;
// Table row
typedef std::tuple<PassportT*, IDCardT*, AccessPermitT*, WorkPassT*, unsigned int> Row;

/*!
 * \brief
 */
class DecisionTree {
  public:
    Node* root;

    DecisionTree();

    DecisionTree(std::list<Entrant*> entrants);

    bool decision(Entrant entrant, time_t current_day);

  private:
    void build();

    std::list<Row> create_table(std::list<Entrant*> entrants);

    std::tuple<unsigned int, unsigned int> class_counts(std::list<Row> table);

    float gini(std::list<Row> table, std::vector<unsigned int> classes);

    std::tuple<std::list<Row>, std::list<Row>> partition(std::list<Entrant*> entrants,
      std::list<Row> table, unsigned int action, time_t current_day);

    float info_gain(std::list<Row> left, std::list<Row> right,
      std::vector<unsigned int> classes, float current_uncertainty);

    std::tuple<float, unsigned int> find_best_split(std::list<Row> table,
      std::vector<unsigned int> classes);
};

#endif /* _POPE_DECISION_TREE_BOT_HPP_ */
