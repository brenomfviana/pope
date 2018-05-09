#include "papersplease/game.hpp"

void Game::start() {
  // Game loop
  // Current day 24,11,1982
  // while (!this->player->arrested && !win()) {
  //   // End day
  //   end_day();
  // }
  for (Entrant* entrant : entrants) {
    this->ecount++;
    // Get papers
    this->player->papers_please(*entrant);
    // Player decision
    bool decision = this->player->decision();
    // Check service
    if (decision == check_service(entrant)) {
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

bool Game::check_service(Entrant* entrant) {
  YAML::Node database = DatabaseReader::read("assets/database.yml");
  Passport* passport;
  IDCard* idcard;
  AccessPermit* accesspermit;
  WorkPass* workpass;

  // Papers
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

  // Check passport
  if (entrant->pic.hair != passport->pic.hair &&
    entrant->pic.facial_hair != passport->pic.facial_hair &&
    entrant->pic.vision != passport->pic.vision &&
    entrant->pic.other != passport->pic.other) {
      return false;
    }
  if (entrant->firstname != passport->firstname &&
    entrant->lastname != passport->firstname) {
      return false;
    }
  if (passport->seal != "AA" && passport->seal != "AB") {
    return false;
  }
  if (entrant->sex != passport->sex) {
    return false;
  }
  int count = 0;
  for (std::size_t i = 0; i < database["issuing_city"][entrant->country].size(); i++) {
    if (idcard->city == database["issuing_city"][entrant->country][i].as<std::string>()) {
      break;
    }
    count++;
  }
  if (count == database["issuing_city"][entrant->country].size()) {
    return false;
  }
  Date d = passport->expiration_date;
  struct tm aux;
  aux.tm_year = d.year - 1900;
  aux.tm_mon = d.month - 1;
  aux.tm_mday = d.day;
  time_t tend = mktime(&aux);
  if (406944000 > tend) {
    return false;
  }

  // Check ID card
  if (idcard->pic.hair != passport->pic.hair &&
    idcard->pic.facial_hair != passport->pic.facial_hair &&
    idcard->pic.vision != passport->pic.vision &&
    idcard->pic.other != passport->pic.other) {
      return false;
    }
  if (idcard->firstname != passport->firstname &&
    idcard->lastname != passport->firstname) {
      return false;
    }
  if (entrant->sex != idcard->sex) {
    return false;
  }
  if (passport->date_of_birth.to_str() != idcard->date_of_birth.to_str()) {
    return false;
  }
  count = 0;
  for (std::size_t i = 0; i < database["cities"][entrant->country].size(); i++) {
    if (idcard->city == database["cities"][entrant->country][i].as<std::string>()) {
      break;
    }
    count++;
  }
  if (count == database["cities"][entrant->country].size()) {
    return false;
  }
  if (idcard->height != entrant->height) {
    return false;
  }
  if (idcard->weight != entrant->weight) {
    return false;
  }

  // Check access permit
  if (accesspermit->firstname != passport->firstname &&
  accesspermit->lastname != passport->firstname) {
    return false;
  }
  if (accesspermit->seal != "AA" && accesspermit->seal != "AB") {
    return false;
  }
  if (accesspermit->nationality != entrant->country) {
    return false;
  }
  if (accesspermit->passport_number != passport->passport_number) {
    return false;
  }
  if (accesspermit->purpose != entrant->purpose) {
    return false;
  }
  d = accesspermit->expiration_date;
  aux.tm_year = d.year - 1900;
  aux.tm_mon = d.month - 1;
  aux.tm_mday = d.day;
  tend = mktime(&aux);
  if (406944000 > tend) {
    return false;
  }
  if (accesspermit->height != entrant->height) {
    return false;
  }
  if (accesspermit->weight != entrant->weight) {
    return false;
  }
  if (accesspermit->physical_appearance != passport->pic.hair ||
    accesspermit->physical_appearance != passport->pic.facial_hair ||
    accesspermit->physical_appearance != passport->pic.vision ||
    accesspermit->physical_appearance != passport->pic.other) {
      return false;
    }

  // Check work pass
  if (workpass->firstname != passport->firstname &&
  workpass->lastname != passport->firstname) {
    return false;
  }
  if (workpass->seal != "LA" && workpass->seal != "LB" &&
      workpass->seal != "LC" && workpass->seal != "LD") {
    return false;
  }

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
