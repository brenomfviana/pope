#include "domain/players/perfect_bot.hpp"

bool PerfectBot::decision() {
  YAML::Node database = DatabaseReader::read("assets/database.yml");
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  AccessPermit* accesspermit = nullptr;
  WorkPass* workpass = nullptr;

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
      std::cout << "/* passport */" << '\n';
      std::cout << "/* passport1 */" << '\n';
      if (this->entrant.pic.hair != passport->pic.hair ||
          this->entrant.pic.facial_hair != passport->pic.facial_hair ||
          this->entrant.pic.vision != passport->pic.vision ||
          this->entrant.pic.other != passport->pic.other) {
            return false;
      }
      std::cout << "/* passport2 */" << '\n';
      if (passport->moa_stamp != "AA" && passport->moa_stamp != "AB") {
        return false;
      }
      std::cout << "/* passport3 */" << '\n';
      if (this->entrant.sex != passport->sex) {
        return false;
      }
      std::cout << "/* passport4 */" << '\n';
      int count = 0;
      for (std::size_t i = 0; i < database["issuing_city"][this->entrant.country].size(); i++) {
        if (passport->issuing_city == database["issuing_city"][this->entrant.country][i].as<std::string>()) {
          break;
        }
        count++;
      }
      if (count >= database["issuing_city"][this->entrant.country].size()) {
        return false;
      }
      std::cout << "/* passport5 */" << '\n';
      count = 0;
      for (std::size_t i = 0; i < database["countries"].size(); i++) {
        if (passport->country == database["countries"][i].as<std::string>()) {
          break;
        }
        count++;
      }
      if (count >= database["countries"].size()) {
        return false;
      }
      std::cout << "/* passport6 */" << '\n';
      Date d = passport->expiration_date;

      struct tm* ctm = localtime(&current_day);
      std::cout << ctm->tm_year << " " << ctm->tm_mon << " " << ctm->tm_mday << "\n";
      std::cout << (ctm->tm_mon > d.month - 1) << " == " << ctm->tm_mon << " " << d.month - 1 << '\n';
      std::cout << ((ctm->tm_year == d.year - 1900 && ctm->tm_mon > d.month - 1) ? "true" : "fasle") << '\n';
      std::cout << ((ctm->tm_year == d.year - 1900 && ctm->tm_mon == d.month - 1 && ctm->tm_mday > d.day) ? "true" : "fasle") << '\n';

      if ((ctm->tm_year > d.year - 1900) ||
          (ctm->tm_year == d.year - 1900 && ctm->tm_mon > d.month - 1) ||
          (ctm->tm_year == d.year - 1900 && ctm->tm_mon == d.month - 1 && ctm->tm_mday > d.day)) {
            return false;
      }

      // Check ID card
      if (this->entrant.country == "arstotzka") {
        std::cout << "/* idcard */" << '\n';
        if (idcard != nullptr && passport != nullptr) {
          std::cout << "/* idcard1 */" << '\n';
          if (idcard->pic.hair != this->entrant.pic.hair ||
              idcard->pic.facial_hair != this->entrant.pic.facial_hair ||
              idcard->pic.vision != this->entrant.pic.vision ||
              idcard->pic.other != this->entrant.pic.other) {
                return false;
          }
          std::cout << "/* idcard2 */" << '\n';
          if (idcard->firstname != passport->firstname ||
              idcard->lastname != passport->lastname) {
                return false;
          }
          std::cout << "/* idcard3 */" << '\n';
          if (this->entrant.sex != idcard->sex) {
            return false;
          }
          std::cout << "/* idcard4 */" << '\n';
          if (passport->date_of_birth.to_str() != idcard->date_of_birth.to_str()) {
            return false;
          }
          std::cout << "/* idcard5 */" << '\n';
          int count = 0;
          for (std::size_t i = 0; i < database["cities"][this->entrant.country].size(); i++) {
            if (idcard->city == database["cities"][this->entrant.country][i].as<std::string>()) {
              break;
            }
            count++;
          }
          std::cout << "/* idcard6 */" << '\n';
          if (count >= database["cities"][this->entrant.country].size()) {
            return false;
          }
          std::cout << "/* idcard7 */" << '\n';
          if (idcard->country != passport->country && idcard->country != "arstotzka") {
            return false;
          }
          std::cout << "/* idcard8 */" << '\n';
          if (idcard->height != this->entrant.height) {
            return false;
          }
          std::cout << "/* idcard9 */" << '\n';
          if (idcard->weight != this->entrant.weight) {
            return false;
          }
        }

        return true;
      } else {
        if (accesspermit != nullptr) {
          std::cout << "/* access */" << '\n';
          std::cout << "/* access1 */" << '\n';
          if (accesspermit->firstname != passport->firstname ||
              accesspermit->lastname != passport->lastname) {
                return false;
          }
          std::cout << "/* access2 */" << '\n';
          if (accesspermit->moa_stamp != "AA" && accesspermit->moa_stamp != "AB") {
            return false;
          }
          std::cout << "/* access3 */" << '\n';
          if (accesspermit->nationality != passport->country) {
            return false;
          }
          std::cout << "/* access4 */" << '\n';
          if (accesspermit->passport_number != passport->passport_number) {
            return false;
          }
          std::cout << "/* access5 */" << '\n';
          if (accesspermit->purpose != this->entrant.purpose) {
            return false;
          }
          std::cout << "/* access6 */" << '\n';
          if (accesspermit->height != this->entrant.height) {
            return false;
          }
          std::cout << "/* access7 */" << '\n';
          if (accesspermit->weight != this->entrant.weight) {
            return false;
          }
          std::cout << "/* access8 */" << '\n';
          Date d = accesspermit->expiration_date;

          struct tm* ctm = localtime(&current_day);
          std::cout << ctm->tm_year << " " << ctm->tm_mon << " " << ctm->tm_mday << "\n";
          std::cout << (ctm->tm_mon > d.month - 1) << " == " << ctm->tm_mon << " " << d.month - 1 << '\n';
          std::cout << ((ctm->tm_year == d.year - 1900 && ctm->tm_mon > d.month - 1) ? "true" : "fasle") << '\n';
          std::cout << ((ctm->tm_year == d.year - 1900 && ctm->tm_mon == d.month - 1 && ctm->tm_mday > d.day) ? "true" : "fasle") << '\n';

          if ((ctm->tm_year > d.year - 1900) ||
              (ctm->tm_year == d.year - 1900 && ctm->tm_mon > d.month - 1) ||
              (ctm->tm_year == d.year - 1900 && ctm->tm_mon == d.month - 1 && ctm->tm_mday > d.day)) {
                return false;
          }
          std::cout << "/* access9 */" << '\n';
          if (accesspermit->physical_appearance != this->entrant.pic.hair) {
            if (accesspermit->physical_appearance != this->entrant.pic.facial_hair) {
              if (accesspermit->physical_appearance != this->entrant.pic.vision) {
                if (accesspermit->physical_appearance != this->entrant.pic.other) {
                  return false;
                }
              }
            }
          }

          // Check work pass
          if (accesspermit->purpose == "Work") {
            std::cout << "/* work */" << '\n';
            if (workpass != nullptr) {
              std::cout << "/* work1 */" << '\n';
              if (workpass->firstname != passport->firstname ||
                  workpass->lastname != passport->lastname) {
                    return false;
              }
              std::cout << "/* work2 */" << '\n';
              if (workpass->mol_stamp != "LA" && workpass->mol_stamp != "LB" &&
                  workpass->mol_stamp != "LC" && workpass->mol_stamp != "LD") {
                    return false;
              }
              std::cout << "/* work3 */" << '\n';
              int count = 0;
              for (std::size_t i = 0; i < database["works"].size(); i++) {
                if (workpass->field == database["works"][i].as<std::string>()) {
                  break;
                }
                count++;
              }
              if (count >= database["works"].size()) {
                return false;
              }
              std::cout << "/* work4 */" << '\n';
              struct tm* tm = localtime(&this->current_day);
              tm->tm_mday += accesspermit->duration;
              Date end(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
              std::cout << end.to_str() << '\n';
              std::cout << workpass->end.to_str() << '\n';
              if (end.to_str() != workpass->end.to_str()) {
                return false;
              }
            } else {
              return false;
            }
          }

          return true;
        } else {
          return false;
        }
      }
    } else {
      return false;
    }
  }
}
