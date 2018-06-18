/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_ARL_BOT_HPP_
#define _POPE_ARL_BOT_HPP_

#include <iostream>
#include "ai/decision_tree.hpp"
#include "player.hpp"

/*!
 * \brief
 */
class ARLBot : public Player {
  public:
    enum State { WINING, LOSING };
    unsigned int current_state;
    unsigned int goal_state;
    float alpha; ///< Learning rate
    float gamma; ///< Discounting factor
    float q[2][2];
    ARLBot(std::list<Entrant*> entrants);
    bool decision();
    void update();

  private:
    bool classify_entrant();
    float reward();
};

#endif /* _POPE_ARL_BOT_HPP_ */
