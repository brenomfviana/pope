#include "papersplease/game.hpp"

void Game::start() {
  int size = this->entrants.size();
  // Game loop -- Current day 24/11/1982
  while (!this->entrants.empty() && !this->player->arrested) {
    if (this->new_day) {
      // std::cout << "\nDay#" << (this->number_of_days + 1) << '\n';
      // std::cout << "  credits=" << this->player->credits << '\n';
      this->new_day = false;
    }
    // Get entrant
    Entrant* entrant = this->entrants.front();
    this->entrants.pop_front();
    this->ecount++;
    this->ecg++;
    // Get papers
    this->player->papers_please(*entrant, current_day);
    // Player decision
    bool decision = this->player->decision();
    bool expected_decision = check_decision(entrant);
    // Check decision
    if (decision == expected_decision) {
      this->player->credits += SALARY;
    } else {
      this->mcount++;
      this->mcg++;
      if (this->mcount >= NAM) {
        this->player->credits -= SALARY;
      }
    }
    // std::cout << "\nPlayer decision: " << (decision ? "allow" : "deny") << "\n";
    // std::cout << "Expected decision: " << (expected_decision ? "allow" : "deny") << "\n";
    // std::cout << "  credits=" << this->player->credits << '\n';
    // Check new day
    if (this->ecount == 10) {
      end_day();
    }
  }
  //
  std::cout << "\nRight decisions: " << (this->ecg - this->mcg) << "\n";
  std::cout << "Wrong decisions: " << this->mcg << "\n";
  std::cout << "Success rate: " << ((this->ecg - this->mcg) / (float) (this->ecg)) << "\n\n";
  // Check if the player win
  if (win()) {
    std::cout << "Congrats! You helped your country!" << '\n';
    std::cout << "  credits=" << this->player->credits << '\n';
  } else {
    std::cout << "You were arrested in " << this->number_of_days << "th day!" << '\n';
    std::cout << "  credits=" << this->player->credits << '\n';
  }
}

void Game::end_day() {
  // Player expenses
  this->player->credits -= 30;
  // Check for irregularities
  if (check_illegal_gains() || check_delinquency() || bankruptcy()) {
    // Arrest the player
    arrest_the_player();
  }
  // Reset values
  this->mcount = 0;
  this->ecount = 0;
  //// -- Update day
  //// This feature was not implemented because the entrant generation should
  //// be updated, and due to the deadline, can not be implemented
  //// This is not important for AI evaluation, so can be ignored for now
  this->number_of_days++;
  this->new_day = true;
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
