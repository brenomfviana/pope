/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_PEG_HPP_
#define _POPE_PEG_HPP_

class WorkPass;

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>
#include <list>
#include <vector>
#include <random>
#include <yaml-cpp/yaml.h>
#include "commons/common.hpp"
#include "domain/entrant.hpp"
#include "domain/papers/paper.hpp"
#include "domain/papers/date.hpp"
#include "domain/papers/picture.hpp"

#define MALE 'M'
#define FEMALE 'F'

/*!
 * \brief This class is responsible for procedural entrant generation (PEG)
 */
class PEG {
  public:
    /*!
     * \brief Generate n entrants procedurally
     *
     * \param database
     *     Database
     * \param n
     *     Number of entrants to be generated
     *
     * \return
     *     List of entrants
     */
    static std::list<Entrant*> generate(YAML::Node database, int n);

  private:
    /*!
     * \brief Create a new entrant
     *
     * \param database
     *     Database
     * \param illegal
     *     If the entrant to be generated is an illegal entrant
     *
     * \return
     *     The created entrant
     */
    static Entrant* new_entrant(YAML::Node database, bool illegal);

    /*!
     * \brief Create a passport for the entrant
     *
     * \param database
     *     Database
     * \param entrant
     *     Passport owner
     * \param invalid_fields
     *     Number of invalid fields in all papers
     *
     * \return
     *     The created passport
     */
    static Passport* new_passport(YAML::Node database, Entrant* entrant,
      int& invalid_fields);

    /*!
     * \brief Create a ID card for the entrant
     *
     * \param database
     *     Database
     * \param entrant
     *     Passport owner
     * \param invalid_fields
     *     Number of invalid fields in all papers
     *
     * \return
     *     The created ID card
     */
    static IDCard* new_idcard(YAML::Node database, Entrant* entrant,
      int& invalid_fields);

    /*!
     * \brief Create a access permit for the entrant
     *
     * \param database
     *     Database
     * \param entrant
     *     Passport owner
     * \param invalid_fields
     *     Number of invalid fields in all papers
     *
     * \return
     *     The created access permit
     */
    static AccessPermit* new_accesspermit(YAML::Node database, Entrant* entrant,
      Passport* passport, int& invalid_fields);

    /*!
     * \brief Create a work pass for the entrant
     *
     * \param database
     *     Database
     * \param entrant
     *     Passport owner
     * \param invalid_fields
     *     Number of invalid fields in all papers
     *
     * \return
     *     The created work pass
     */
    static WorkPass* new_workpass(YAML::Node database, Entrant* entrant,
      AccessPermit* accesspermit, int& invalid_fields);
};

typedef std::uniform_int_distribution<std::mt19937::result_type> RandomInt;

#endif /* _POPE_PEG_HPP_ */
