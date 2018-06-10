#include "domain/players/player.hpp"

void Player::approve() {
  // Get passport
  for (auto paper : this->entrant.papers) {
    if (typeid(paper) == typeid(Passport)) {
      // Approve
      Passport* passport = dynamic_cast<Passport*>(passport);
      passport->entry_visa = true;
    }
  }
}

void Player::deny() {
  // Get passport
  for (auto paper : this->entrant.papers) {
    if (typeid(paper) == typeid(Passport)) {
      // Deny
      Passport* passport = dynamic_cast<Passport*>(passport);
      passport->entry_visa = false;
    }
  }
}
