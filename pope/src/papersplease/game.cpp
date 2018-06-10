#include "papersplease/game.hpp"

void Game::start() {
  int size = this->entrants.size();
  // Game loop -- Current day 24,11,1982
  while (!this->entrants.empty()) {
    auto start = steady_clock::now();
    Entrant* entrant = this->entrants.front();
    this->entrants.pop_front();
    this->ecount++;
    // Get papers
    this->player->papers_please(*entrant, current_day);
    // Player decision
    bool decision = this->player->decision();
    bool expected_decision = check_decision(entrant);
    // Check service
    if (decision == expected_decision) {
      this->player->credits += SALARY;
    } else {
      this->mcount++;
      std::cout << "\nEntrant: " << entrant->firstname << " " << entrant->lastname;
      if (this->mcount >= NAM) {
        this->player->credits -= SALARY;
      }
    }
    auto end = steady_clock::now();
    std::cout << "\nPlayer decision: " << (decision ? "allow" : "deny") << "\n";
    std::cout << "Expected decision: " << (expected_decision ? "allow" : "deny") << "\n";
    std::cout << "Decision time: " << duration_cast<milliseconds>(end - start).count()
              << " milliseconds\n";
  }
  std::cout << "\nRight decisions: " << (size - this->mcount) << "\n";
  std::cout << "Wrong decisions: " << this->mcount << "\n";
  std::cout << "Success rate: " << ((size - this->mcount) / (float) size) << "\n\n";
  end_day();
}

void Game::end_day() {
  // Reset values
  // this->mcount = 0;
  // this->ecount = 0;
  // Check for irregularities
  if (check_illegal_gains() || check_delinquency() || bankruptcy()) {
    // Arrest the player
    arrest_the_player();
    // Show message
    std::cout << "You were arrested!" << '\n';
  } else {
    // Check end of entrants
    if (win()) {
      // Show message
      std::cout << "Congrats! You helped your country!" << '\n';
    }
    // this->number_of_days++;
  }
  // struct tm aux;
  // aux.tm_year = current_day / 10000 - 1900;
  // aux.tm_mon = (current_day % 10000) / 100 - 1;
  // aux.tm_mday = current_day % 100 + 1;
  // current_day = mktime(&aux);
}

bool Game::check_decision(Entrant* entrant) {
  // If is illegal then decision is false
  return !entrant->illegal;
}

void Game::arrest_the_player() {
  this->player->arrested = true;
}

bool Game::check_illegal_gains() {
  return (this->player->credits > ((this->max_entrants * SALARY) * 2));
}

bool Game::bankruptcy() {
  return (0 > this->player->credits);
}

bool Game::check_delinquency() {
  return (this->mcount >= (this->ecount / 2));
}

bool Game::win() {
  // If the player was not arrested and has no entrants to serve
  if (!this->player->arrested && this->entrants.empty()) {
    // The player wins
    return true;
  }
  // The game continues
  return false;
}
