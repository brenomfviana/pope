/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_PLAYER_HPP_
#define _POPE_PLAYER_HPP_

#include <chrono>
#include <typeinfo>
#include <yaml-cpp/yaml.h>
#include "domain/entrant.hpp"
#include "domain/papers/paper.hpp"
#include "services/readers/database_reader.hpp"

/*!
 * \brief This class represents a player of the game
 */
class Player {
  public:
    bool arrested; ///< The player was arrested
    int credits; ///< The player's money
    Entrant entrant; ///< Entrant to be served
    time_t current_day = 406944000; ///< Currrent day

    /*!
     * \brief Player constructor
     */
    Player() {
      this->arrested = false;
      this->credits = 0;
    }

    /*!
     * \brief Get the papers of the entrant
     *
     * \param entrant
     *     The entrant to be served
     */
    void papers_please(Entrant entrant, time_t current_day) {
      this->entrant = entrant;
      this->current_day = current_day;
    }

    /*!
     * \brief Player decision
     */
    virtual bool decision() = 0;

  protected:
    /*!
     * \brief Approve entrant
     */
    void approve();

    /*!
     * \brief Deny entrant
     */
    void deny();
};

#include "perfect_bot.hpp"

#endif /* _POPE_PLAYER_HPP_ */
