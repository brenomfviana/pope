#include "papersplease/game.hpp"

void Game::start() {
  // Game loop -- Current day 24,11,1982
  while (!this->entrants.empty()) {
    auto start = steady_clock::now();
    Entrant* entrant = this->entrants.front();
    this->entrants.pop_front();
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
    auto end = steady_clock::now();
    std::cout << "that took " << duration_cast<milliseconds>(end - start).count()
              << " milliseconds\n";
  }
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
  YAML::Node database = DatabaseReader::read("assets/database.yml");
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  AccessPermit* accesspermit = nullptr;
  WorkPass* workpass = nullptr;

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
  if (passport != nullptr) {
    if (entrant->pic.hair != passport->pic.hair ||
        entrant->pic.facial_hair != passport->pic.facial_hair ||
        entrant->pic.vision != passport->pic.vision ||
        entrant->pic.other != passport->pic.other) {
          return false;
    }
    if (passport->moa_stamp != "AA" && passport->moa_stamp != "AB") {
      return false;
    }
    if (entrant->sex != passport->sex) {
      return false;
    }
    int count = 0;
    for (std::size_t i = 0; i < database["issuing_city"][entrant->country].size(); i++) {
      if (passport->issuing_city == database["issuing_city"][entrant->country][i].as<std::string>()) {
        break;
      }
      count++;
    }
    if (count >= database["issuing_city"][entrant->country].size()) {
      return false;
    }
    count = 0;
    for (std::size_t i = 0; i < database["country"].size(); i++) {
      if (passport->country == database["country"][i].as<std::string>()) {
        break;
      }
      count++;
    }
    if (count >= database["country"].size()) {
      return false;
    }
    Date d = passport->expiration_date;
    struct tm aux;
    aux.tm_year = d.year - 1900;
    aux.tm_mon = d.month - 1;
    aux.tm_mday = d.day;
    time_t tend = mktime(&aux);
    if (current_day > tend) {
      return false;
    }
  } else {
    return false;
  }

  // Check ID card
  if (entrant != nullptr) {
    if (entrant->country == "arstotzka" && idcard == nullptr) {
      return false;
    }
  }
  if (idcard != nullptr && passport != nullptr && entrant != nullptr) {
    if (idcard->pic.hair != entrant->pic.hair ||
        idcard->pic.facial_hair != entrant->pic.facial_hair ||
        idcard->pic.vision != entrant->pic.vision ||
        idcard->pic.other != entrant->pic.other) {
          return false;
    }
    if (idcard->firstname != passport->firstname ||
        idcard->lastname != passport->lastname) {
          return false;
    }
    if (entrant->sex != idcard->sex) {
      return false;
    }
    if (passport->date_of_birth.to_str() != idcard->date_of_birth.to_str()) {
      return false;
    }
    int count = 0;
    for (std::size_t i = 0; i < database["cities"][entrant->country].size(); i++) {
      if (idcard->city == database["cities"][entrant->country][i].as<std::string>()) {
        break;
      }
      count++;
    }
    if (count >= database["cities"][entrant->country].size()) {
      return false;
    }
    count = 0;
    for (std::size_t i = 0; i < database["country"].size(); i++) {
      if (idcard->country == database["country"][i].as<std::string>()) {
        break;
      }
      count++;
    }
    if (count >= database["country"].size()) {
      return false;
    }
    if (idcard->height != entrant->height) {
      return false;
    }
    if (idcard->weight != entrant->weight) {
      return false;
    }
  }

  // Check access permit
  if (entrant != nullptr) {
    if (entrant->country != "arstotzka" && accesspermit == nullptr) {
      return false;
    }
  }
  if (accesspermit != nullptr && passport != nullptr && entrant != nullptr) {
    if (accesspermit->firstname != passport->firstname &&
        accesspermit->lastname != passport->lastname) {
          return false;
    }
    if (accesspermit->moa_stamp != "AA" && accesspermit->moa_stamp != "AB") {
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
    if (accesspermit->height != entrant->height) {
      return false;
    }
    if (accesspermit->weight != entrant->weight) {
      return false;
    }
    Date d = accesspermit->expiration_date;
    struct tm aux;
    aux.tm_year = d.year - 1900;
    aux.tm_mon = d.month - 1;
    aux.tm_mday = d.day;
    time_t tend = mktime(&aux);
    if (current_day > tend) {
      return false;
    }
    if (accesspermit->physical_appearance != entrant->pic.hair ||
        accesspermit->physical_appearance != entrant->pic.facial_hair ||
        accesspermit->physical_appearance != entrant->pic.vision ||
        accesspermit->physical_appearance != entrant->pic.other) {
          return false;
    }
  }

  // Check work pass
  if (accesspermit != nullptr) {
    if (accesspermit->purpose == "work" && workpass == nullptr) {
      return false;
    }
  }
  if (workpass != nullptr && passport != nullptr) {
    if (workpass->firstname != passport->firstname ||
        workpass->lastname != passport->lastname) {
          return false;
    }
    if (workpass->mol_stamp != "LA" || workpass->mol_stamp != "LB" ||
        workpass->mol_stamp != "LC" || workpass->mol_stamp != "LD") {
          return false;
    }
    int count = 0;
    for (std::size_t i = 0; i < database["works"].size(); i++) {
      if (idcard->field == database["works"][i].as<std::string>()) {
        break;
      }
      count++;
    }
    if (count >= database["country"].size()) {
      return false;
    }
    struct tm* tm = localtime(&current_day);
    tm->tm_mday += accesspermit->duration;
    Date end(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    if (end.to_str() != workpass->end.to_str()) {
      return false;
    }
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
