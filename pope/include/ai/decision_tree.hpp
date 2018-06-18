/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_DECISION_TREE_HPP_
#define _POPE_DECISION_TREE_HPP_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>
#include "ai/questions.hpp"
#include "domain/papers/paper.hpp"
#include "node.hpp"

/*!
 * \brief This class represents a decision tree that classifies entrants
 */
class DecisionTree {
  public:
    std::vector<unsigned int> passport_questions; ///< Passport questions
    std::vector<unsigned int> idcard_questions; ///< ID card questions
    std::vector<unsigned int> access_questions; ///< Access Permit questions
    std::vector<unsigned int> work_questions; ///< Work pass questions
    Node* root; ///< Tree root

    /*!
     * \brief Empty constructor of the decision tree
     */
    DecisionTree();

    /*!
     * \brief Decision tree constructor
     *
     * \param training_data
     *     Trainning data (list of entrants)
     */
    DecisionTree(std::list<Entrant*> training_data);

    /*!
     * \brief Classifies a entrant
     *
     * \param entrant
     *     Entrant to be classified
     * \param current_day
     *     Current day in the game
     *
     * \return True if is a legal entrant and false otherwise
     */
    bool decision(Entrant entrant, time_t current_day);

  private:
    Node* build(std::list<Entrant*> entrants, time_t current_day, int depth);

    Node* buildidc(std::list<Entrant*> entrants, time_t current_day, int depth);

    Node* buildap(std::list<Entrant*> entrants, time_t current_day, int depth);

    Node* buildwp(std::list<Entrant*> entrants, time_t current_day, int depth);

    std::tuple<unsigned int, unsigned int> class_counts(std::list<Entrant*> entrants);

    float gini(std::list<Entrant*> entrants);

    float info_gain(std::list<Entrant*> left, std::list<Entrant*> right,
      float current_uncertainty);

    std::tuple<std::list<Entrant*>, std::list<Entrant*>> partition(std::list<Entrant*> entrants,
      unsigned int action, time_t current_day);

    std::tuple<float, unsigned int> find_best_split(std::vector<unsigned int>& questions,
      std::list<Entrant*> entrants, time_t current_day);
};

#endif /* _POPE_DECISION_TREE_BOT_HPP_ */
