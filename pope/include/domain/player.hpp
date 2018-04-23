/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_PLAYER_HPP_
#define _POPE_PLAYER_HPP_

#include <typeinfo>
#include "entrant.hpp"
#include "papers/paper.hpp"

/*!
 * \brief This class represents a player of the game
 */
class Player {
  public:
    Entrant entrant; ///< Entrant to be served

    /*!
     * \brief Get the papers of the entrant
     *
     * \param entrant
     *     The entrant to be served
     */
    void papers_please(Entrant entrant) {
      this->entrant = entrant;
    }

    /*!
     * \brief Approve entrant
     */
    void approve();

    /*!
     * \brief Deny entrant
     */
    void deny();
};

#endif /* _POPE_PLAYER_HPP_ */
