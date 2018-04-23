/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_BOTPLAYER_HPP_
#define _POPE_BOTPLAYER_HPP_

#include "domain/player.hpp"

/*!
 * \brief This class represents a bot player
 */
class BotPlayer : public Player {
  public:
    /*!
     * \brief Check the papers of the entrant
     */
    void check_papers() = 0;
};

#endif /* _POPE_BOTPLAYER_HPP_ */
