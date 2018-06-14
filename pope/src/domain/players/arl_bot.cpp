#include "domain/players/arl_bot.hpp"

ARLBot::ARLBot(std::list<Entrant*> entrants) : Player() {
  tree = DecisionTree(entrants);
}

bool ARLBot::decision() {
  // If the player has papers
  if (this->entrant.papers.empty()) {
    return false;
  }
  // Papers
  Passport* passport = nullptr;
  for (Paper* paper : this->entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
      break;
    }
  }
  // Decision
  passport->entry_visa = tree.decision(this->entrant, this->current_day);
  return passport->entry_visa;
}
