#include "domain/players/arl_bot.hpp"

ARLBot::ARLBot(std::list<Entrant*> entrants) : Player() {
  this->current_state = WINING;
  this->goal_state = WINING;
  this->alpha = 0.1;
  this->gamma = 0.8;
  this->q[WINING][0] = 0.f; // Allow entrant and winnig
  this->q[WINING][1] = 0.f; // Deny entrant and winnig
  this->q[LOSING][0] = 0.f; // Allow entrant and losing
  this->q[LOSING][1] = 0.f; // Deny entrant and losing
}

bool ARLBot::classify_entrant() {
  YAML::Node database = DatabaseReader::read("assets/database.yml");
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  AccessPermit* accesspermit = nullptr;
  WorkPass* workpass = nullptr;
  // If the player has papers
  if (this->entrant.papers.empty()) {
    return false;
  } else {
    // Papers
    for (Paper* paper : this->entrant.papers) {
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
    // Check passport
    if (passport != nullptr) {
      if (this->entrant.pic.hair != passport->pic.hair ||
          this->entrant.pic.facial_hair != passport->pic.facial_hair ||
          this->entrant.pic.vision != passport->pic.vision ||
          this->entrant.pic.other != passport->pic.other) {
            passport->entry_visa = false;
            return passport->entry_visa;
      }
      if (passport->moa_stamp != "AA" && passport->moa_stamp != "AB") {
        passport->entry_visa = false;
        return passport->entry_visa;
      }
      if (this->entrant.sex != passport->sex) {
        passport->entry_visa = false;
        return passport->entry_visa;
      }
      int count = 0;
      for (std::size_t i = 0; i < database["issuing_city"][this->entrant.country].size(); i++) {
        if (passport->issuing_city == database["issuing_city"][this->entrant.country][i].as<std::string>()) {
          break;
        }
        count++;
      }
      if (count >= database["issuing_city"][this->entrant.country].size()) {
        passport->entry_visa = false;
        return passport->entry_visa;
      }
      count = 0;
      for (std::size_t i = 0; i < database["countries"].size(); i++) {
        if (passport->country == database["countries"][i].as<std::string>()) {
          break;
        }
        count++;
      }
      if (count >= database["countries"].size()) {
        passport->entry_visa = false;
        return passport->entry_visa;
      }
      Date d = passport->expiration_date;
      struct tm* ctm = localtime(&current_day);
      if ((ctm->tm_year > d.year - 1900) ||
          (ctm->tm_year == d.year - 1900 && ctm->tm_mon > d.month - 1) ||
          (ctm->tm_year == d.year - 1900 && ctm->tm_mon == d.month - 1 && ctm->tm_mday > d.day)) {
            passport->entry_visa = false;
            return passport->entry_visa;
      }
      // Check ID card
      if (passport->country == "arstotzka") {
        if (idcard != nullptr) {
          if (idcard->pic.hair != this->entrant.pic.hair ||
              idcard->pic.facial_hair != this->entrant.pic.facial_hair ||
              idcard->pic.vision != this->entrant.pic.vision ||
              idcard->pic.other != this->entrant.pic.other) {
                passport->entry_visa = false;
                return passport->entry_visa;
          }
          if (idcard->firstname != passport->firstname ||
              idcard->lastname != passport->lastname) {
                passport->entry_visa = false;
                return passport->entry_visa;
          }
          if (this->entrant.sex != idcard->sex) {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          if (passport->date_of_birth.to_str() != idcard->date_of_birth.to_str()) {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          int count = 0;
          for (std::size_t i = 0; i < database["cities"][this->entrant.country].size(); i++) {
            if (idcard->city == database["cities"][this->entrant.country][i].as<std::string>()) {
              break;
            }
            count++;
          }
          if (count >= database["cities"][this->entrant.country].size()) {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          if (idcard->country != passport->country && idcard->country != "arstotzka") {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          if (idcard->height != this->entrant.height) {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          if (idcard->weight != this->entrant.weight) {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
        }
        passport->entry_visa = true;
        return passport->entry_visa;
      } else {
        if (accesspermit != nullptr) {
          if (accesspermit->firstname != passport->firstname ||
              accesspermit->lastname != passport->lastname) {
                passport->entry_visa = false;
                return passport->entry_visa;
          }
          if (accesspermit->moa_stamp != "AA" && accesspermit->moa_stamp != "AB") {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          if (accesspermit->nationality != passport->country) {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          if (accesspermit->passport_number != passport->passport_number) {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          if (accesspermit->purpose != this->entrant.purpose) {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          if (accesspermit->height != this->entrant.height) {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          if (accesspermit->weight != this->entrant.weight) {
            passport->entry_visa = false;
            return passport->entry_visa;
          }
          Date d = accesspermit->expiration_date;
          struct tm* ctm = localtime(&current_day);
          if ((ctm->tm_year > d.year - 1900) ||
              (ctm->tm_year == d.year - 1900 && ctm->tm_mon > d.month - 1) ||
              (ctm->tm_year == d.year - 1900 && ctm->tm_mon == d.month - 1 && ctm->tm_mday > d.day)) {
                passport->entry_visa = false;
                return passport->entry_visa;
          }
          if (accesspermit->physical_appearance != this->entrant.pic.hair) {
            if (accesspermit->physical_appearance != this->entrant.pic.facial_hair) {
              if (accesspermit->physical_appearance != this->entrant.pic.vision) {
                if (accesspermit->physical_appearance != this->entrant.pic.other) {
                  passport->entry_visa = false;
                  return passport->entry_visa;
                }
              }
            }
          }
          // Check work pass
          if (accesspermit->purpose == "Work") {
            if (workpass != nullptr) {
              if (workpass->firstname != passport->firstname ||
                  workpass->lastname != passport->lastname) {
                    passport->entry_visa = false;
                    return passport->entry_visa;
              }
              if (workpass->mol_stamp != "LA" && workpass->mol_stamp != "LB" &&
                  workpass->mol_stamp != "LC" && workpass->mol_stamp != "LD") {
                    passport->entry_visa = false;
                    return passport->entry_visa;
              }
              int count = 0;
              for (std::size_t i = 0; i < database["works"].size(); i++) {
                if (workpass->field == database["works"][i].as<std::string>()) {
                  break;
                }
                count++;
              }
              if (count >= database["works"].size()) {
                passport->entry_visa = false;
                return passport->entry_visa;
              }
              struct tm* tm = localtime(&this->current_day);
              tm->tm_mday += accesspermit->duration;
              Date end(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
              if (end.to_str() != workpass->end.to_str()) {
                passport->entry_visa = false;
                return passport->entry_visa;
              }
            } else {
              passport->entry_visa = false;
              return passport->entry_visa;
            }
          }
          passport->entry_visa = true;
          return passport->entry_visa;
        } else {
          passport->entry_visa = false;
          return passport->entry_visa;
        }
      }
    } else {
      passport->entry_visa = false;
      return passport->entry_visa;
    }
  }
}

bool ARLBot::decision() {
  // If the player has papers
  if (this->entrant.papers.empty()) {
    return false;
  }
  // Perform action
  bool legal = classify_entrant();
  // Choose action from Q
  //  or DT
  // Greed policy?
  if (this->current_state == WINING) {
    if (!legal && this->entrant.bribe > 0) {
      return true;
    }
  }
  return legal;
}

float ARLBot::reward() {
  //
  return 0;
}

void ARLBot::update() {
  // Measure reward
  reward();
  // Update Q
}
