#include "domain/players/pope_bot.hpp"

PopeBot::PopeBot(std::list<Entrant*> entrants) : Player() {
  tree = DecisionTree(entrants);
}

bool PopeBot::decision() {
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
