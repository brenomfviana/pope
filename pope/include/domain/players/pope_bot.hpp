/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_BOT_HPP_
#define _POPE_BOT_HPP_

#include <iostream>
#include "ai/decision_tree.hpp"
#include "player.hpp"

/*!
 * \brief This class represents th pope bot
 */
class PopeBot : public Player {
  public:
    DecisionTree tree; ///< Decision tree

    /*!
     * \brief Pope bot empty constructor
     */
    PopeBot(std::list<Entrant*> entrants);

    bool decision();
};

#endif /* _POPE_BOT_HPP_ */
