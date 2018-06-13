/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_ACTIONS_HPP_
#define _POPE_ACTIONS_HPP_

#include "entrant.hpp"
#include "domain/papers/paper.hpp"
#include "services/readers/database_reader.hpp"

enum Actions {
  ALLOW,
  DENY,
  HAS_PASSPORT,
  CHECK_PICTURE_PASSPORT,
  CHECK_MOASTAMP_PASSPORT,
  CHECK_SEX_PASSPORT,
  CHECK_ISSUINGCITY_PASSPORT,
  CHECK_COUNTRY_PASSPORT,
  CHECK_EXPIRATIONDATE_PASSPORT,
  IS_ARSTOTZKAN,
  HAS_IDCARD,
  CHECK_PICTURE_IDCARD,
  CHECK_NAME_IDCARD_PASSPORT,
  CHECK_SEX_IDCARD,
  CHECK_DATEOFBIRTH_IDCARD,
  CHECK_CITY_IDCARD,
  CHECK_COUNTRY_IDCARD,
  CHECK_HEIGHT_IDCARD,
  CHECK_WEIGHT_IDCARD,
  HAS_ACCESSPERMIT,
  CHECK_NAME_ACCESSPERMIT_PASSPORT,
  CHECK_MOASTAMP_ACCESSPERMIT,
  CHECK_NATIONALITY_ACCESSPERMIT,
  CHECK_PASSPORTNUMBER_ACCESSPERMIT,
  CHECK_PURPOSE_ACCESSPERMIT,
  CHECK_HEIGHT_ACCESSPERMIT,
  CHECK_WEIGHT_ACCESSPERMIT,
  CHECK_EXPIRATIONDATE_ACCESSPERMIT,
  CHECK_PHYSICALAPPEARANCE_ACCESSPERMIT,
  HAS_WORKPASS,
  CHECK_NAME_WORKPASS_PASSPORT,
  CHECK_MOLSTAMP_WORKPASS,
  CHECK_FIELD_WORKPASS,
  CHECK_WORKENDDATE_WORKPASS
};

enum ActionResult {
  INVALID, // Illegal entrant
  VALID, // Legal entrant
  NATIVE, // Native entrant (Arstotzkan)
  NO_NATIVE, // Foreign entrant
  NO_WORKPASS, // Entrant does not have workpass
  WORKPASS // Entrant has workpass
};

class Action {
  public:
    static ActionResult do_action(unsigned int ac, Entrant entrant, time_t current_day);

  private:
    static ActionResult has_passport(YAML::Node database, Entrant entrant);
    static ActionResult check_picture_passport(YAML::Node database, Entrant entrant);
    static ActionResult check_moastamp_passport(YAML::Node database, Entrant entrant);
    static ActionResult check_sex_passport(YAML::Node database, Entrant entrant);
    static ActionResult check_issuingcity_passport(YAML::Node database, Entrant entrant);
    static ActionResult check_country_passport(YAML::Node database, Entrant entrant);
    static ActionResult check_expirationdate_passport(YAML::Node database, Entrant entrant, time_t current_day);
    static ActionResult is_arstotzkan(YAML::Node database, Entrant entrant);
    static ActionResult has_idcard(YAML::Node database, Entrant entrant);
    static ActionResult check_picture_idcard(YAML::Node database, Entrant entrant);
    static ActionResult check_name_idcard_passport(YAML::Node database, Entrant entrant);
    static ActionResult check_sex_idcard(YAML::Node database, Entrant entrant);
    static ActionResult check_dateofbirth_idcard(YAML::Node database, Entrant entrant);
    static ActionResult check_city_idcard(YAML::Node database, Entrant entrant);
    static ActionResult check_country_idcard(YAML::Node database, Entrant entrant);
    static ActionResult check_height_idcard(YAML::Node database, Entrant entrant);
    static ActionResult check_weight_idcard(YAML::Node database, Entrant entrant);
    static ActionResult has_accesspermit(YAML::Node database, Entrant entrant);
    static ActionResult check_name_accesspermit_passport(YAML::Node database, Entrant entrant);
    static ActionResult check_moastamp_accesspermit(YAML::Node database, Entrant entrant);
    static ActionResult check_nationality_accesspermit(YAML::Node database, Entrant entrant);
    static ActionResult check_passportnumber_accesspermit(YAML::Node database, Entrant entrant);
    static ActionResult check_purpose_accesspermit(YAML::Node database, Entrant entrant);
    static ActionResult check_height_accesspermit(YAML::Node database, Entrant entrant);
    static ActionResult check_weight_accesspermit(YAML::Node database, Entrant entrant);
    static ActionResult check_expirationdate_accesspermit(YAML::Node database, Entrant entrant, time_t current_day);
    static ActionResult check_physicalappearance_accesspermit(YAML::Node database, Entrant entrant);
    static ActionResult has_workpass(YAML::Node database, Entrant entrant);
    static ActionResult check_name_workpass_passport(YAML::Node database, Entrant entrant);
    static ActionResult check_molstamp_workpass(YAML::Node database, Entrant entrant);
    static ActionResult check_field_workpass(YAML::Node database, Entrant entrant);
    static ActionResult check_workenddate_workpass(YAML::Node database, Entrant entrant, time_t current_day);
};

#endif /* _POPE_ACTIONS_HPP_ */
