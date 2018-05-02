#include "papersplease/game.hpp"

void Game::start() {
  // Game loop
  // while (!this->player->arrested && !win()) {
  //   // End day
  //   end_day();
  // }
  for (Entrant entrant : entrants) {
    this->ecount++;
    // Get papers
    this->player->papers_please(entrant);
    // Player decision
    bool decision = this->player->decision();
    // Check service
    if (check_service(decision)) {
      this->player->credits += SALARY;
    } else {
      this->mcount++;
      if (this->mcount >= NAM) {
        this->player->credits -= SALARY;
      }
    }
  }
  end_day();
}

void Game::end_day() {
  // Reset values
  this->mcount = 0;
  this->ecount = 0;
  // Check for irregularities
  if (check_illegal_gains() || check_delinquency()) {
    // Arrest the player
    arrest_the_player();
  } else {
    // Check end of entrants
    if (win()) {
      // Show message
    }
    this->number_of_days++;
  }
}

bool Game::check_service(bool decision) {
  //
  return true;
}

void Game::arrest_the_player() {
  this->player->arrested = true;
}

bool Game::check_illegal_gains() {
  return (this->player->credits > ((this->max_entrants * SALARY) * 2));
}

bool Game::bankruptcy() {
  return (0 > this->player);
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
