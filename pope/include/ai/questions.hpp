/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_ACTIONS_HPP_
#define _POPE_ACTIONS_HPP_

#include "domain/entrant.hpp"
#include "domain/papers/paper.hpp"
#include "services/readers/database_reader.hpp"

enum Questions {
  HAS_PASSPORT, // 0
  CHECK_PICTURE_PASSPORT, // 1
  CHECK_MOASTAMP_PASSPORT, // 2
  CHECK_SEX_PASSPORT, // 3
  CHECK_ISSUINGCITY_PASSPORT, // 4
  CHECK_COUNTRY_PASSPORT, // 5
  CHECK_EXPIRATIONDATE_PASSPORT, // 6
  IS_ARSTOTZKAN, // 7
  HAS_IDCARD, // 8
  CHECK_PICTURE_IDCARD, // 9
  CHECK_NAME_IDCARD_PASSPORT, // 10
  CHECK_SEX_IDCARD, // 11
  CHECK_DATEOFBIRTH_IDCARD, // 12
  CHECK_CITY_IDCARD, // 13
  CHECK_COUNTRY_IDCARD, // 14
  CHECK_HEIGHT_IDCARD, // 15
  CHECK_WEIGHT_IDCARD, // 16
  HAS_ACCESSPERMIT, // 17
  CHECK_NAME_ACCESSPERMIT_PASSPORT, // 18
  CHECK_MOASTAMP_ACCESSPERMIT, // 19
  CHECK_NATIONALITY_ACCESSPERMIT, // 20
  CHECK_PASSPORTNUMBER_ACCESSPERMIT, // 21
  CHECK_PURPOSE_ACCESSPERMIT, // 22
  CHECK_HEIGHT_ACCESSPERMIT, // 23
  CHECK_WEIGHT_ACCESSPERMIT, // 24
  CHECK_EXPIRATIONDATE_ACCESSPERMIT, // 25
  CHECK_PHYSICALAPPEARANCE_ACCESSPERMIT, // 26
  HAS_WORKPASS, // 27
  CHECK_NAME_WORKPASS_PASSPORT, // 28
  CHECK_MOLSTAMP_WORKPASS, // 29
  CHECK_FIELD_WORKPASS, // 30
  CHECK_WORKENDDATE_WORKPASS // 31
};

class Question {
  public:
    static bool ask(unsigned int ac, Entrant entrant, time_t current_day);

  private:
    static bool has_passport(YAML::Node database, Entrant entrant);
    static bool check_picture_passport(YAML::Node database, Entrant entrant);
    static bool check_moastamp_passport(YAML::Node database, Entrant entrant);
    static bool check_sex_passport(YAML::Node database, Entrant entrant);
    static bool check_issuingcity_passport(YAML::Node database, Entrant entrant);
    static bool check_country_passport(YAML::Node database, Entrant entrant);
    static bool check_expirationdate_passport(YAML::Node database, Entrant entrant, time_t current_day);
    static bool is_arstotzkan(YAML::Node database, Entrant entrant);
    static bool has_idcard(YAML::Node database, Entrant entrant);
    static bool check_picture_idcard(YAML::Node database, Entrant entrant);
    static bool check_name_idcard_passport(YAML::Node database, Entrant entrant);
    static bool check_sex_idcard(YAML::Node database, Entrant entrant);
    static bool check_dateofbirth_idcard(YAML::Node database, Entrant entrant);
    static bool check_city_idcard(YAML::Node database, Entrant entrant);
    static bool check_country_idcard(YAML::Node database, Entrant entrant);
    static bool check_height_idcard(YAML::Node database, Entrant entrant);
    static bool check_weight_idcard(YAML::Node database, Entrant entrant);
    static bool has_accesspermit(YAML::Node database, Entrant entrant);
    static bool check_name_accesspermit_passport(YAML::Node database, Entrant entrant);
    static bool check_moastamp_accesspermit(YAML::Node database, Entrant entrant);
    static bool check_nationality_accesspermit(YAML::Node database, Entrant entrant);
    static bool check_passportnumber_accesspermit(YAML::Node database, Entrant entrant);
    static bool check_purpose_accesspermit(YAML::Node database, Entrant entrant);
    static bool check_height_accesspermit(YAML::Node database, Entrant entrant);
    static bool check_weight_accesspermit(YAML::Node database, Entrant entrant);
    static bool check_expirationdate_accesspermit(YAML::Node database, Entrant entrant, time_t current_day);
    static bool check_physicalappearance_accesspermit(YAML::Node database, Entrant entrant);
    static bool has_workpass(YAML::Node database, Entrant entrant);
    static bool check_name_workpass_passport(YAML::Node database, Entrant entrant);
    static bool check_molstamp_workpass(YAML::Node database, Entrant entrant);
    static bool check_field_workpass(YAML::Node database, Entrant entrant);
    static bool check_workenddate_workpass(YAML::Node database, Entrant entrant, time_t current_day);
};

#endif /* _POPE_ACTIONS_HPP_ */
