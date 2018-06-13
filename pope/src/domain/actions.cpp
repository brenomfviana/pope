#include "domain/actions.hpp"

ActionResult Action::do_action(unsigned int ac, Entrant entrant, time_t current_day) {
  YAML::Node database = DatabaseReader::read("assets/database.yml");
  switch (ac) {
    case HAS_PASSPORT:
      return has_passport(database, entrant);
      break;
    case CHECK_PICTURE_PASSPORT:
      return check_picture_passport(database, entrant);
      break;
    case CHECK_MOASTAMP_PASSPORT:
      return check_moastamp_passport(database, entrant);
      break;
    case CHECK_SEX_PASSPORT:
      return check_sex_passport(database, entrant);
      break;
    case CHECK_ISSUINGCITY_PASSPORT:
      return check_issuingcity_passport(database, entrant);
      break;
    case CHECK_COUNTRY_PASSPORT:
      return check_country_passport(database, entrant);
      break;
    case CHECK_EXPIRATIONDATE_PASSPORT:
      return check_expirationdate_passport(database, entrant, current_day);
      break;
    case IS_ARSTOTZKAN:
      return is_arstotzkan(database, entrant);
      break;
    case HAS_IDCARD:
      return has_idcard(database, entrant);
      break;
    case CHECK_PICTURE_IDCARD:
      return check_picture_idcard(database, entrant);
      break;
    case CHECK_NAME_IDCARD_PASSPORT:
      return check_name_idcard_passport(database, entrant);
      break;
    case CHECK_SEX_IDCARD:
      return check_sex_idcard(database, entrant);
      break;
    case CHECK_DATEOFBIRTH_IDCARD:
      return check_dateofbirth_idcard(database, entrant);
      break;
    case CHECK_CITY_IDCARD:
      return check_city_idcard(database, entrant);
      break;
    case CHECK_COUNTRY_IDCARD:
      return check_country_idcard(database, entrant);
      break;
    case CHECK_HEIGHT_IDCARD:
      return check_height_idcard(database, entrant);
      break;
    case CHECK_WEIGHT_IDCARD:
      return check_weight_idcard(database, entrant);
      break;
    case HAS_ACCESSPERMIT:
      return has_accesspermit(database, entrant);
      break;
    case CHECK_NAME_ACCESSPERMIT_PASSPORT:
      return check_name_accesspermit_passport(database, entrant);
      break;
    case CHECK_MOASTAMP_ACCESSPERMIT:
      return check_moastamp_accesspermit(database, entrant);
      break;
    case CHECK_NATIONALITY_ACCESSPERMIT:
      return check_nationality_accesspermit(database, entrant);
      break;
    case CHECK_PASSPORTNUMBER_ACCESSPERMIT:
      return check_passportnumber_accesspermit(database, entrant);
      break;
    case CHECK_PURPOSE_ACCESSPERMIT:
      return check_purpose_accesspermit(database, entrant);
      break;
    case CHECK_HEIGHT_ACCESSPERMIT:
      return check_height_accesspermit(database, entrant);
      break;
    case CHECK_WEIGHT_ACCESSPERMIT:
      return check_weight_accesspermit(database, entrant);
      break;
    case CHECK_EXPIRATIONDATE_ACCESSPERMIT:
      return check_expirationdate_accesspermit(database, entrant, current_day);
      break;
    case HAS_WORKPASS:
      return has_workpass(database, entrant);
      break;
    case CHECK_NAME_WORKPASS_PASSPORT:
      return check_name_workpass_passport(database, entrant);
      break;
    case CHECK_MOLSTAMP_WORKPASS:
      return check_molstamp_workpass(database, entrant);
      break;
    case CHECK_FIELD_WORKPASS:
      return check_field_workpass(database, entrant);
      break;
    case CHECK_WORKENDDATE_WORKPASS:
      return check_workenddate_workpass(database, entrant, current_day);
      break;
  }
  return INVALID;
}

ActionResult Action::has_passport(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
  }
  //
  if (passport != nullptr) {
    return VALID;
  }
  return INVALID;
}

ActionResult Action::check_picture_passport(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
  }
  //
  if (passport != nullptr) {
    if (entrant.pic.hair != passport->pic.hair ||
        entrant.pic.facial_hair != passport->pic.facial_hair ||
        entrant.pic.vision != passport->pic.vision ||
        entrant.pic.other != passport->pic.other) {
          return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_moastamp_passport(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
  }
  //
  if (passport != nullptr) {
    if (passport->moa_stamp != "AA" && passport->moa_stamp != "AB") {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_sex_passport(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
  }
  //
  if (passport != nullptr) {
    if (entrant.sex != passport->sex) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_issuingcity_passport(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
  }
  //
  if (passport != nullptr) {
    int count = 0;
    for (std::size_t i = 0; i < database["issuing_city"][entrant.country].size(); i++) {
      if (passport->issuing_city == database["issuing_city"][entrant.country][i].as<std::string>()) {
        break;
      }
      count++;
    }
    if (count >= database["issuing_city"][entrant.country].size()) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_country_passport(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
  }
  //
  if (passport != nullptr) {
    int count = 0;
    for (std::size_t i = 0; i < database["countries"].size(); i++) {
      if (passport->country == database["countries"][i].as<std::string>()) {
        break;
      }
      count++;
    }
    if (count >= database["countries"].size()) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_expirationdate_passport(YAML::Node database, Entrant entrant, time_t current_day) {
  Passport* passport = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
  }
  //
  if (passport != nullptr) {
    Date d = passport->expiration_date;

    struct tm* ctm = localtime(&current_day);

    if ((ctm->tm_year > d.year - 1900) ||
        (ctm->tm_year == d.year - 1900 && ctm->tm_mon > d.month - 1) ||
        (ctm->tm_year == d.year - 1900 && ctm->tm_mon == d.month - 1 && ctm->tm_mday > d.day)) {
          return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::is_arstotzkan(YAML::Node database, Entrant entrant)  {
  Passport* passport = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
  }
  //
  if (passport != nullptr) {
    if (passport->country == "arstotzka") {
      return NATIVE;
    } else {
      return NO_NATIVE;
    }
  }
  return INVALID;
}

ActionResult Action::has_idcard(YAML::Node database, Entrant entrant) {
  IDCard* idcard = nullptr;
  for (Paper* paper : entrant.papers) {
    // ID card
    if (typeid(*paper) == typeid(Passport)) {
      idcard = dynamic_cast<IDCard*>(paper);
    }
  }
  //
  if (idcard != nullptr) {
    return VALID;
  } else {
    return NO_NATIVE;
  }
  return INVALID;
}

ActionResult Action::check_picture_idcard(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // ID card
    if (typeid(*paper) == typeid(IDCard)) {
      idcard = dynamic_cast<IDCard*>(paper);
    }
  }
  //
  if (idcard != nullptr && passport != nullptr) {
    if (idcard->pic.hair != entrant.pic.hair ||
        idcard->pic.facial_hair != entrant.pic.facial_hair ||
        idcard->pic.vision != entrant.pic.vision ||
        idcard->pic.other != entrant.pic.other) {
          return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_name_idcard_passport(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // ID card
    if (typeid(*paper) == typeid(IDCard)) {
      idcard = dynamic_cast<IDCard*>(paper);
    }
  }
  //
  if (idcard != nullptr && passport != nullptr) {
    if (idcard->firstname != passport->firstname ||
        idcard->lastname != passport->lastname) {
          return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_sex_idcard(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // ID card
    if (typeid(*paper) == typeid(IDCard)) {
      idcard = dynamic_cast<IDCard*>(paper);
    }
  }
  //
  if (idcard != nullptr && passport != nullptr) {
    if (entrant.sex != idcard->sex) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_dateofbirth_idcard(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // ID card
    if (typeid(*paper) == typeid(IDCard)) {
      idcard = dynamic_cast<IDCard*>(paper);
    }
  }
  //
  if (idcard != nullptr && passport != nullptr) {
    if (passport->date_of_birth.to_str() != idcard->date_of_birth.to_str()) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_city_idcard(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // ID card
    if (typeid(*paper) == typeid(IDCard)) {
      idcard = dynamic_cast<IDCard*>(paper);
    }
  }
  //
  if (idcard != nullptr && passport != nullptr) {
    int count = 0;
    for (std::size_t i = 0; i < database["cities"][entrant.country].size(); i++) {
      if (idcard->city == database["cities"][entrant.country][i].as<std::string>()) {
        break;
      }
      count++;
    }
    if (count >= database["cities"][entrant.country].size()) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_country_idcard(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // ID card
    if (typeid(*paper) == typeid(IDCard)) {
      idcard = dynamic_cast<IDCard*>(paper);
    }
  }
  //
  if (idcard != nullptr && passport != nullptr) {
    if (idcard->country != passport->country && idcard->country != "arstotzka") {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_height_idcard(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // ID card
    if (typeid(*paper) == typeid(IDCard)) {
      idcard = dynamic_cast<IDCard*>(paper);
    }
  }
  //
  if (idcard != nullptr && passport != nullptr) {
    if (idcard->height != entrant.height) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_weight_idcard(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  IDCard* idcard = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // ID card
    if (typeid(*paper) == typeid(IDCard)) {
      idcard = dynamic_cast<IDCard*>(paper);
    }
  }
  //
  if (idcard != nullptr && passport != nullptr) {
    if (idcard->weight != entrant.weight) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::has_accesspermit(YAML::Node database, Entrant entrant) {
  AccessPermit* accesspermit = nullptr;
  for (Paper* paper : entrant.papers) {
    // Access permit
    if (typeid(*paper) == typeid(Passport)) {
      accesspermit = dynamic_cast<AccessPermit*>(paper);
    }
  }
  //
  if (accesspermit != nullptr) {
    return VALID;
  }
  return INVALID;
}

ActionResult Action::check_name_accesspermit_passport(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // Access permit
    if (typeid(*paper) == typeid(AccessPermit)) {
      accesspermit = dynamic_cast<AccessPermit*>(paper);
    }
  }
  //
  if (accesspermit != nullptr && passport != nullptr) {
    if (accesspermit->firstname != passport->firstname ||
        accesspermit->lastname != passport->lastname) {
          return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_moastamp_accesspermit(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // Access permit
    if (typeid(*paper) == typeid(AccessPermit)) {
      accesspermit = dynamic_cast<AccessPermit*>(paper);
    }
  }
  //
  if (accesspermit != nullptr && passport != nullptr) {
    if (accesspermit->moa_stamp != "AA" && accesspermit->moa_stamp != "AB") {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_nationality_accesspermit(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // Access permit
    if (typeid(*paper) == typeid(AccessPermit)) {
      accesspermit = dynamic_cast<AccessPermit*>(paper);
    }
  }
  //
  if (accesspermit != nullptr && passport != nullptr) {
    if (accesspermit->nationality != passport->country) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_passportnumber_accesspermit(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // Access permit
    if (typeid(*paper) == typeid(AccessPermit)) {
      accesspermit = dynamic_cast<AccessPermit*>(paper);
    }
  }
  //
  if (accesspermit != nullptr && passport != nullptr) {
    if (accesspermit->passport_number != passport->passport_number) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_purpose_accesspermit(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // Access permit
    if (typeid(*paper) == typeid(AccessPermit)) {
      accesspermit = dynamic_cast<AccessPermit*>(paper);
    }
  }
  //
  if (accesspermit != nullptr && passport != nullptr) {
    if (accesspermit->purpose != entrant.purpose) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_height_accesspermit(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // Access permit
    if (typeid(*paper) == typeid(AccessPermit)) {
      accesspermit = dynamic_cast<AccessPermit*>(paper);
    }
  }
  //
  if (accesspermit != nullptr && passport != nullptr) {
    if (accesspermit->height != entrant.height) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_weight_accesspermit(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // Access permit
    if (typeid(*paper) == typeid(AccessPermit)) {
      accesspermit = dynamic_cast<AccessPermit*>(paper);
    }
  }
  //
  if (accesspermit != nullptr && passport != nullptr) {
    if (accesspermit->weight != entrant.weight) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_expirationdate_accesspermit(YAML::Node database, Entrant entrant, time_t current_day) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // Access permit
    if (typeid(*paper) == typeid(AccessPermit)) {
      accesspermit = dynamic_cast<AccessPermit*>(paper);
    }
  }
  //
  if (accesspermit != nullptr && passport != nullptr) {
    Date d = accesspermit->expiration_date;

    struct tm* ctm = localtime(&current_day);

    if ((ctm->tm_year > d.year - 1900) ||
        (ctm->tm_year == d.year - 1900 && ctm->tm_mon > d.month - 1) ||
        (ctm->tm_year == d.year - 1900 && ctm->tm_mon == d.month - 1 && ctm->tm_mday > d.day)) {
          return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult check_physicalappearance_accesspermit(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  for (Paper* paper : entrant.papers) {
    // Passport
    if (typeid(*paper) == typeid(Passport)) {
      passport = dynamic_cast<Passport*>(paper);
    }
    // Access permit
    if (typeid(*paper) == typeid(AccessPermit)) {
      accesspermit = dynamic_cast<AccessPermit*>(paper);
    }
  }
  //
  if (accesspermit != nullptr && passport != nullptr) {
    if (accesspermit->physical_appearance != entrant.pic.hair) {
      if (accesspermit->physical_appearance != entrant.pic.facial_hair) {
        if (accesspermit->physical_appearance != entrant.pic.vision) {
          if (accesspermit->physical_appearance != entrant.pic.other) {
            return INVALID;
          } else {
            return VALID;
          }
        } else {
          return VALID;
        }
      } else {
        return VALID;
      }
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::has_workpass(YAML::Node database, Entrant entrant) {
  WorkPass* workpass = nullptr;
  for (Paper* paper : entrant.papers) {
    // Work pass
    if (typeid(*paper) == typeid(Passport)) {
      workpass = dynamic_cast<WorkPass*>(paper);
    }
  }
  //
  if (workpass != nullptr) {
    return WORKPASS;
  }
  return NO_WORKPASS;
}

ActionResult Action::check_name_workpass_passport(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  WorkPass* workpass = nullptr;
  if (workpass != nullptr && passport != nullptr) {
    if (workpass->firstname != passport->firstname ||
        workpass->lastname != passport->lastname) {
          return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_molstamp_workpass(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  WorkPass* workpass = nullptr;
  if (workpass != nullptr && passport != nullptr) {
    if (workpass->mol_stamp != "LA" && workpass->mol_stamp != "LB" &&
        workpass->mol_stamp != "LC" && workpass->mol_stamp != "LD") {
          return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_field_workpass(YAML::Node database, Entrant entrant) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  WorkPass* workpass = nullptr;
  if (workpass != nullptr && passport != nullptr) {
    int count = 0;
    for (std::size_t i = 0; i < database["works"].size(); i++) {
      if (workpass->field == database["works"][i].as<std::string>()) {
        break;
      }
      count++;
    }
    if (count >= database["works"].size()) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}

ActionResult Action::check_workenddate_workpass(YAML::Node database, Entrant entrant, time_t current_day) {
  Passport* passport = nullptr;
  AccessPermit* accesspermit = nullptr;
  WorkPass* workpass = nullptr;
  if (workpass != nullptr && passport != nullptr) {
    struct tm* tm = localtime(&current_day);
    tm->tm_mday += accesspermit->duration;
    Date end(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    if (end.to_str() != workpass->end.to_str()) {
      return INVALID;
    } else {
      return VALID;
    }
  }
  return INVALID;
}
