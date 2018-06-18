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
    Node* root; ///< Tree root
    // Passport questions
    std::vector<unsigned int> passport_questions = { CHECK_PICTURE_PASSPORT,
      CHECK_MOASTAMP_PASSPORT, CHECK_SEX_PASSPORT, CHECK_ISSUINGCITY_PASSPORT,
      CHECK_COUNTRY_PASSPORT, CHECK_EXPIRATIONDATE_PASSPORT };
    // ID card questions
    std::vector<unsigned int> idcard_questions = { CHECK_PICTURE_IDCARD, CHECK_NAME_IDCARD_PASSPORT,
      CHECK_SEX_IDCARD, CHECK_DATEOFBIRTH_IDCARD, CHECK_CITY_IDCARD, CHECK_COUNTRY_IDCARD,
      CHECK_HEIGHT_IDCARD, CHECK_WEIGHT_IDCARD };
    // Access Permit questions
    std::vector<unsigned int> access_questions = { CHECK_NAME_ACCESSPERMIT_PASSPORT,
      CHECK_MOASTAMP_ACCESSPERMIT, CHECK_NATIONALITY_ACCESSPERMIT,
      CHECK_PASSPORTNUMBER_ACCESSPERMIT, CHECK_PURPOSE_ACCESSPERMIT,
      CHECK_HEIGHT_ACCESSPERMIT, CHECK_WEIGHT_ACCESSPERMIT,
      CHECK_EXPIRATIONDATE_ACCESSPERMIT, CHECK_PHYSICALAPPEARANCE_ACCESSPERMIT };
    // Work pass questions
    std::vector<unsigned int> work_questions = { CHECK_NAME_WORKPASS_PASSPORT,
      CHECK_MOLSTAMP_WORKPASS, CHECK_FIELD_WORKPASS, CHECK_WORKENDDATE_WORKPASS };

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
     * \brief
     *
     * \param entrant
     *     Entrant to be classified
     *
     * \param current_day
     *     Current day in the game
     */
    bool decision(Entrant entrant, time_t current_day);

  private:
    Node* build(std::list<Entrant*> entrants, time_t current_day, int depth);

    Node* buildidc(std::list<Entrant*> entrants, time_t current_day, int depth);

    Node* buildap(std::list<Entrant*> entrants, time_t current_day, int depth);

    Node* buildwp(std::list<Entrant*> entrants, time_t current_day, int depth);

    std::tuple<unsigned int, unsigned int> class_counts(std::list<Entrant*> entrants);

    float gini(std::list<Entrant*> entrants);

    float info_gain(std::list<Entrant*> left, std::list<Entrant*> right, float current_uncertainty);

    std::tuple<std::list<Entrant*>, std::list<Entrant*>> partition(std::list<Entrant*> entrants,
      unsigned int action, time_t current_day);

    std::tuple<float, unsigned int> find_best_split(std::vector<unsigned int>& questions, std::list<Entrant*> entrants, time_t current_day);
};

#endif /* _POPE_DECISION_TREE_BOT_HPP_ */
