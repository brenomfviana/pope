/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#include "domain/actions.hpp"
#include "ai/decision_tree.hpp"

DecisionTree::DecisionTree() { /* empty */ }

DecisionTree::DecisionTree(std::list<Entrant*> entrants) {
  // Classes
  std::vector<int> classes{ INVALID, VALID, NATIVE, NO_NATIVE, WORKPASS, NO_WORKPASS };
  // Init decision tree
  this->root = new Node(HAS_PASSPORT,
    {{ INVALID, new Node(DENY) },
     { VALID, nullptr } });
  // Create table
  std::list<Row> table;
  for (Entrant* entrant : entrants) {
    // Papers
    Passport* passport = nullptr;
    IDCard* idcard = nullptr;
    AccessPermit* accesspermit = nullptr;
    WorkPass* workpass = nullptr;
    for (Paper* paper : entrant->papers) {
      // Passport
      if (typeid(*paper) == typeid(Passport)) {
        passport = dynamic_cast<Passport*>(paper);
      }
      // ID card
      if (typeid(*paper) == typeid(IDCard)) {
        idcard = dynamic_cast<IDCard*>(paper);
      }
      // Access permit
      if (typeid(*paper) == typeid(AccessPermit)) {
        accesspermit = dynamic_cast<AccessPermit*>(paper);
      }
      // Work pass
      if (typeid(*paper) == typeid(WorkPass)) {
        workpass = dynamic_cast<WorkPass*>(paper);
      }
    }
    // Passport
    std::string s = passport->pic.hair + passport->pic.facial_hair +
      passport->pic.vision + passport->pic.other;
    unsigned long ppic = std::accumulate(s.begin(), s.end(), 0);
    s = passport->firstname + passport->lastname;
    unsigned long pname = std::accumulate(s.begin(), s.end(), 0);
    s = passport->passport_number;
    unsigned long ppp = std::accumulate(s.begin(), s.end(), 0);
    s = passport->moa_stamp;
    unsigned long pstamp = std::accumulate(s.begin(), s.end(), 0);
    s = passport->sex + "";
    unsigned long psex = std::accumulate(s.begin(), s.end(), 0);
    s = passport->date_of_birth.to_str();
    unsigned long pdbirth = std::accumulate(s.begin(), s.end(), 0);
    s = passport->country;
    unsigned long pcountry = std::accumulate(s.begin(), s.end(), 0);
    s = passport->issuing_city;
    unsigned long picity = std::accumulate(s.begin(), s.end(), 0);
    s = passport->expiration_date.to_str();
    unsigned long pedate = std::accumulate(s.begin(), s.end(), 0);
    // Create row
    if (idcard != nullptr) {
      // ID Card
      s = idcard->pic.hair + idcard->pic.facial_hair + idcard->pic.vision + idcard->pic.other;
      unsigned long idcpic = std::accumulate(s.begin(), s.end(), 0);
      s = idcard->firstname + idcard->lastname;
      unsigned long idcname = std::accumulate(s.begin(), s.end(), 0);
      s = idcard->sex + "";
      unsigned long idcsex = std::accumulate(s.begin(), s.end(), 0);
      s = idcard->date_of_birth.to_str();
      unsigned long idcdbirth = std::accumulate(s.begin(), s.end(), 0);
      s = idcard->country;
      unsigned long idccountry = std::accumulate(s.begin(), s.end(), 0);
      s = idcard->city;
      unsigned long idccity = std::accumulate(s.begin(), s.end(), 0);
      // Add to table
      table.push_back(Row(
          new PassportT(ppic, pname, ppp, pstamp, psex, pdbirth, pcountry, picity, pedate),
          new IDCardT(idcpic, idcname, idcsex, idcdbirth, idccountry, idccity,
            idcard->height, idcard->weight),
          new AccessPermitT(0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
          new WorkPassT(0, 0, 0, 0), entrant->illegal));
    } else {
      if (accesspermit != nullptr) {
        // Access permit
        s = accesspermit->firstname + accesspermit->lastname;
        unsigned long accname = std::accumulate(s.begin(), s.end(), 0);
        s = accesspermit->moa_stamp;
        unsigned long accstamp = std::accumulate(s.begin(), s.end(), 0);
        s = accesspermit->nationality;
        unsigned long acccountry = std::accumulate(s.begin(), s.end(), 0);
        s = accesspermit->passport_number;
        unsigned long accpnumber = std::accumulate(s.begin(), s.end(), 0);
        s = accesspermit->purpose;
        unsigned long accpp = std::accumulate(s.begin(), s.end(), 0);
        s = accesspermit->expiration_date.to_str();
        unsigned long accedate = std::accumulate(s.begin(), s.end(), 0);
        s = accesspermit->physical_appearance;
        unsigned long accpapp = std::accumulate(s.begin(), s.end(), 0);
        // Add to table
        if (workpass != nullptr) {
          // Access permit
          s = workpass->firstname + workpass->lastname;
          unsigned long wpname = std::accumulate(s.begin(), s.end(), 0);
          s = workpass->mol_stamp;
          unsigned long wpstamp = std::accumulate(s.begin(), s.end(), 0);
          s = workpass->field;
          unsigned long wpfield = std::accumulate(s.begin(), s.end(), 0);
          s = workpass->end.to_str();
          unsigned long wpend = std::accumulate(s.begin(), s.end(), 0);
          // Add to table
          table.push_back(Row(
            new PassportT(ppic, pname, ppp, pstamp, psex, pdbirth, pcountry, picity, pedate),
            new IDCardT(0, 0, 0, 0, 0, 0, 0, 0),
            new AccessPermitT(accname, accstamp, acccountry, accpnumber, accpp,
                accesspermit->duration, accesspermit->height * 100, accesspermit->weight,
                accedate, accpapp),
            new WorkPassT(wpname, wpstamp, wpfield, wpend), entrant->illegal));
        } else {
          // Add to table
          table.push_back(Row(
            new PassportT(ppic, pname, ppp, pstamp, psex, pdbirth, pcountry, picity, pedate),
            new IDCardT(0, 0, 0, 0, 0, 0, 0, 0),
            new AccessPermitT(accname, accstamp, acccountry, accpnumber, accpp,
                accesspermit->duration, accesspermit->height * 100, accesspermit->weight,
                accedate, accpapp),
            new WorkPassT(0, 0, 0, 0), entrant->illegal));
        }
      }
    }
  }
  // Build decision tree
  // build();
  class_counts(table);
}

bool DecisionTree::decision(Entrant entrant, time_t current_day) {
  Node* next = this->root;
  bool making_decision = true;
  while(true) {
    int action_result = Action::do_action(next->action, entrant, current_day);
    if (action_result == ALLOW) {
      return true;
    }
    if (action_result == DENY) {
      return false;
    }
    if (!this->root->children.empty()) {
      next = this->root->children[action_result];
    }
  }
  // ERROR
  return false;
}

std::tuple<unsigned int, unsigned int> DecisionTree::class_counts(std::list<Row> table) {
  unsigned int c0, c1;
  for (Row r : table) {
    unsigned int c = 0;
    std::tie(std::ignore, std::ignore, std::ignore, std::ignore, c) = r;
    if (c == 0) {
      c0++;
    } else {
      c1++;
    }
  }
  return std::make_tuple(c0, c1);
}

float DecisionTree::gini_index(std::list<Row> table, std::vector<int> classes) {
  //
  unsigned int c0, c1;
  std::tie(c0, c1) = class_counts(rows);
  float impurity = 1.f;
  float pc0 = c0 / (float) table.size();
  impurity -= pow(pc0, 2);
  float pc1 = c1 / (float) table.size();
  impurity -= pow(pc1, 2);
  return impurity;
}
