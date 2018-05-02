#include "domain/player.hpp"

bool Player::decision() {
  return true;
}

void Player::approve() {
  // Get passport
  for (auto paper : entrant.papers) {
    if (typeid(paper) == typeid(Passport)) {
      // Approve
      Passport* passport = dynamic_cast<Passport*>(passport);
      passport->stamp = true;
    }
  }
}

void Player::deny() {
  // Get passport
  for (auto paper : entrant.papers) {
    if (typeid(paper) == typeid(Passport)) {
      // Deny
      Passport* passport = dynamic_cast<Passport*>(passport);
      passport->stamp = false;
    }
  }
}
