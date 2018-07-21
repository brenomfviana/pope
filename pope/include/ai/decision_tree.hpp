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
     * \return
     *     True if is a legal entrant and false otherwise
     */
    bool decision(Entrant entrant, time_t current_day);

  private:
    /*!
     * \brief Build Passport branch
     *
     * \param entrants
     *     Trainning data (list of entrants)
     * \param current_day
     *     Current day in the game
     * \param depth
     *     Current depth
     *
     * \return
     *     Root of the Passport branch
     */
    Node* build(std::list<Entrant*> entrants, time_t current_day, int depth);

    /*!
     * \brief Build ID Card branch
     *
     * \param entrants
     *     Trainning data (list of entrants)
     * \param current_day
     *     Current day in the game
     * \param depth
     *     Current depth
     *
     * \return
     *     Root of the ID Card branch
     */
    Node* buildidc(std::list<Entrant*> entrants, time_t current_day, int depth);

    /*!
     * \brief Build Access Permit branch
     *
     * \param entrants
     *     Trainning data (list of entrants)
     * \param current_day
     *     Current day in the game
     * \param depth
     *     Current depth
     *
     * \return
     *     Root of the Access Permit branch
     */
    Node* buildap(std::list<Entrant*> entrants, time_t current_day, int depth);

    /*!
     * \brief Build Work Pass branch
     *
     * \param entrants
     *     Trainning data (list of entrants)
     * \param current_day
     *     Current day in the game
     * \param depth
     *     Current depth
     *
     * \return
     *     Root of the Work Pass branch
     */
    Node* buildwp(std::list<Entrant*> entrants, time_t current_day, int depth);

    /*!
     * \brief Count the number of instances of each class in a training data and
     *        return a tuple with the number of valid and invalid entrants
     *
     * \param entrants
     *     Trainning data (list of entrants)
     *
     * \return
     *     A tuple with the number of valid and invalid entrants
     */
    std::tuple<unsigned int, unsigned int> class_counts(std::list<Entrant*> entrants);

    /*!
     * \brief Get the impurity rate (uncertainty)
     *
     * \param entrants
     *     Trainning data (list of entrants)
     *
     * \return
     *     The impurity rate (uncertainty)
     */
    float gini(std::list<Entrant*> entrants);

    /*!
     * \brief Get the info gain of a partition
     *
     * \param left
     *     List of valid entrants for a question
     * \param right
     *     List of invalid entrants for a question
     * \param current_uncertainty
     *     Current uncertainty
     *
     * \return
     *     The info gain of a partition
     */
    float info_gain(std::list<Entrant*> left, std::list<Entrant*> right,
      float current_uncertainty);

    /*!
     * \brief Partitions a list of entrants according to a question
     *
     * \param entrants
     *     Trainning data (list of entrants)
     * \param question
     *     Question to be asked
     * \param current_day
     *     Current day in the game
     *
     * \return
     *     A tuple with a list of valid entrants for a question and a list of
     *     invalid entrants for a question
     */
    std::tuple<std::list<Entrant*>, std::list<Entrant*>> partition(std::list<Entrant*> entrants,
      unsigned int question, time_t current_day);

    /*!
     * \brief
     *
     * \param questions
     *     Set of questions to ask
     * \param entrants
     *     Trainning data (list of entrants)
     * \param current_day
     *     Current day in the game
     *
     * \return
     *     A tuple with the best gain value and the best question
     */
    std::tuple<float, unsigned int> find_best_split(std::vector<unsigned int>& questions,
      std::list<Entrant*> entrants, time_t current_day);
};

#endif /* _POPE_DECISION_TREE_BOT_HPP_ */
