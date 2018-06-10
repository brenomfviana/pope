/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_PERFECT_BOT_HPP_
#define _POPE_PERFECT_BOT_HPP_

#include <iostream>
#include "player.hpp"

/*!
 * \brief This class represents the perfect bot player
 */
class PerfectBot : public Player {
  public:
    PerfectBot() : Player() { /* empty */ }
    bool decision();
};

#endif /* _POPE_PERFECT_BOT_HPP_ */
