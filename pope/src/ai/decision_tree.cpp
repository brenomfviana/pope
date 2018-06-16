/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#include "ai/questions.hpp"
#include "ai/decision_tree.hpp"

DecisionTree::DecisionTree() { /* empty */ }

DecisionTree::DecisionTree(std::list<Entrant*> entrants) {
  // Currrent day
  time_t current_day = 406944000;
  // Build decision tree
  this->root = build(entrants, current_day, 12);
}

Node* DecisionTree::build(std::list<Entrant*> entrants, time_t current_day, int depth) {
  // Check dataset
  if (entrants.empty()) {
    return new Node(true, true);
  }
  // Check if the node is a leaf
  if (depth == 0) {
    // Check citizenship
    std::list<Entrant*> natives, nonnatives;
    std::tie(natives, nonnatives) = partition(entrants, IS_ARSTOTZKAN, current_day);
    Node* natives_branch = buildidc(natives, current_day, 8);
    Node* nonnatives_branch = buildap(nonnatives, current_day, 9);
    return new Node(IS_ARSTOTZKAN, natives_branch, nonnatives_branch);
  }
  // Passport questions
  std::vector<unsigned int> questions = { CHECK_PICTURE_PASSPORT,
    CHECK_MOASTAMP_PASSPORT, CHECK_SEX_PASSPORT, CHECK_ISSUINGCITY_PASSPORT,
    CHECK_COUNTRY_PASSPORT, CHECK_EXPIRATIONDATE_PASSPORT, CHECK_PICTURE_PASSPORT,
    CHECK_MOASTAMP_PASSPORT, CHECK_SEX_PASSPORT, CHECK_ISSUINGCITY_PASSPORT,
    CHECK_COUNTRY_PASSPORT, CHECK_EXPIRATIONDATE_PASSPORT };
  // Find best split
  float gain;
  unsigned int question;
  std::tie(gain, question) = find_best_split(questions, entrants, current_day);
  //
  std::list<Entrant*> true_rows, false_rows;
  std::tie(true_rows, false_rows) = partition(entrants, question, current_day);
  Node* true_branch = build(true_rows, current_day, depth - 1);
  Node* false_branch = new Node(true, false);
  return new Node(question, true_branch, false_branch);
}

Node* DecisionTree::buildidc(std::list<Entrant*> entrants, time_t current_day, int depth) {
  // Check if the node is a leaf
  if (depth == 0 || entrants.empty()) {
    return new Node(true, true);
  }
  // ID card questions
  std::vector<unsigned int> questions = { CHECK_PICTURE_IDCARD, CHECK_NAME_IDCARD_PASSPORT,
    CHECK_SEX_IDCARD, CHECK_DATEOFBIRTH_IDCARD, CHECK_CITY_IDCARD, CHECK_COUNTRY_IDCARD,
    CHECK_HEIGHT_IDCARD, CHECK_WEIGHT_IDCARD };
  // Find best split
  float gain;
  unsigned int question;
  std::tie(gain, question) = find_best_split(questions, entrants, current_day);
  //
  std::list<Entrant*> true_rows, false_rows;
  std::tie(true_rows, false_rows) = partition(entrants, question, current_day);
  Node* true_branch = buildidc(true_rows, current_day, depth - 1);
  Node* false_branch = new Node(true, false);
  return new Node(question, true_branch, false_branch);
}

Node* DecisionTree::buildap(std::list<Entrant*> entrants, time_t current_day, int depth) {
  // Check dataset
  if (entrants.empty()) {
    return new Node(true, true);
  }
  // Check if the node is a leaf
  if (depth == 0) {
    // Check if has work pass
    std::list<Entrant*> workers, nonworkers;
    std::tie(workers, nonworkers) = partition(entrants, HAS_WORKPASS, current_day);
    Node* workers_branch = buildwp(workers, current_day, 4);
    Node* nonworkers_branch = new Node(true, true);
    return new Node(IS_ARSTOTZKAN, workers_branch, nonworkers_branch);
  }
  // Access Permit questions
  std::vector<unsigned int> questions = { CHECK_NAME_ACCESSPERMIT_PASSPORT,
    CHECK_MOASTAMP_ACCESSPERMIT, CHECK_NATIONALITY_ACCESSPERMIT,
    CHECK_PASSPORTNUMBER_ACCESSPERMIT, CHECK_PURPOSE_ACCESSPERMIT,
    CHECK_HEIGHT_ACCESSPERMIT, CHECK_WEIGHT_ACCESSPERMIT,
    CHECK_EXPIRATIONDATE_ACCESSPERMIT, CHECK_PHYSICALAPPEARANCE_ACCESSPERMIT };
  // Find best split
  float gain;
  unsigned int question;
  std::tie(gain, question) = find_best_split(questions, entrants, current_day);
  //
  std::list<Entrant*> true_rows, false_rows;
  std::tie(true_rows, false_rows) = partition(entrants, question, current_day);
  Node* true_branch = buildap(true_rows, current_day, depth - 1);
  Node* false_branch = new Node(true, false);
  return new Node(question, true_branch, false_branch);
}

Node* DecisionTree::buildwp(std::list<Entrant*> entrants, time_t current_day, int depth) {
  // Check if the node is a leaf
  if (depth == 0 || entrants.empty()) {
    return new Node(true, true);
  }
  // ID card questions
  std::vector<unsigned int> questions = { CHECK_NAME_WORKPASS_PASSPORT,
    CHECK_MOLSTAMP_WORKPASS, CHECK_FIELD_WORKPASS, CHECK_WORKENDDATE_WORKPASS };
  // Find best split
  float gain;
  unsigned int question;
  std::tie(gain, question) = find_best_split(questions, entrants, current_day);
  //
  std::list<Entrant*> true_rows, false_rows;
  std::tie(true_rows, false_rows) = partition(entrants, question, current_day);
  Node* true_branch = buildwp(true_rows, current_day, depth - 1);
  Node* false_branch = new Node(true, false);
  return new Node(question, true_branch, false_branch);
}

bool DecisionTree::decision(Entrant entrant, time_t current_day) {
  Node* next = this->root;
  while(true) {
    // Check if is a leaf
    if (next->is_leaf) {
      return next->value;
    }
    // Make a question
    bool result = Question::ask(next->question, entrant, current_day);
    // Check question result and updates current node
    if (result) {
      next = next->right;
    } else {
      next = next->left;
    }
  }
}

std::tuple<unsigned int, unsigned int> DecisionTree::class_counts(std::list<Entrant*> entrants) {
  unsigned int legal, illegal;
  for (Entrant* entrant : entrants) {
    if (entrant->illegal) {
      illegal++;
    } else {
      legal++;
    }
  }
  return std::make_tuple(legal, illegal);
}

float DecisionTree::gini(std::list<Entrant*> entrants) {
  // If the list is empty there is no impurity
  if (entrants.empty()) {
    return 0.f;
  }
  // Get class
  unsigned int legal, illegal;
  std::tie(legal, illegal) = class_counts(entrants);
  // Calculates the impurity
  float impurity = 1.f;
  // Proportion of legal entrants
  float plegal = legal / (float) entrants.size();
  impurity -= pow(plegal, 2);
  // Proportion of illegal entrants
  float pillegal = illegal / (float) entrants.size();
  impurity -= pow(pillegal, 2);
  return impurity;
}

float DecisionTree::info_gain(std::list<Entrant*> left, std::list<Entrant*> right,
  float current_uncertainty) {
    // Percentage of the left dataset
    float p = left.size() / ((float) left.size() + right.size());
    // Calculates the gain based on the uncertainty of the left and right datasets
    float info_gain = (current_uncertainty - (p * gini(left)) - ((1 - p) * gini(right)));
    return info_gain;
}

std::tuple<std::list<Entrant*>, std::list<Entrant*>> DecisionTree::partition(std::list<Entrant*> entrants,
  unsigned int question, time_t current_day) {
    // Partition dataset
    std::list<Entrant*> true_rows, false_rows;
    for (Entrant* entrant : entrants) {
      // Avoid problems
      if (entrant != nullptr) {
        continue;
      }
      // Make a question
      bool question_result = Question::ask(question, *entrant, current_day);
      // Check question result and make partition
      if (question_result) {
        true_rows.push_back(entrant);
      } else {
        false_rows.push_back(entrant);
      }
    }
    return std::make_tuple(true_rows, false_rows);
}

std::tuple<float, unsigned int> DecisionTree::find_best_split(std::vector<unsigned int> questions,
  std::list<Entrant*> entrants, time_t current_day) {
    float best_gain = 0.f;
    unsigned int best_question = 0;
    // Get current uncertainty
    float current_uncertainty = gini(entrants);
    // Make questions
    for (unsigned int question : questions) {
      // Make a question
      std::list<Entrant*> true_rows, false_rows;
      std::tie(true_rows, false_rows) = partition(entrants, question, current_day);
      // Skip this split if it doesn't divide the dataset
      if (true_rows.size() == 0 && false_rows.size() == 0) {
        continue;
      }
      // Calculates current gain
      float gain = info_gain(true_rows, false_rows, current_uncertainty);
      // Check if is the best gain
      if (gain >= best_gain) {
        // Updates best gain and best question
        best_gain = gain;
        best_question = question;
      }
    }
    return std::make_tuple(best_gain, best_question);
}
