/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_GAME_HPP_
#define _POPE_GAME_HPP_

#include "domain/player.hpp"

#define NAM 2 // Number of acceptable mistakes
#define SALARY 5

/*!
 * \brief This class represents a game
 */
class Game {
  public:
    std::list<Entrant*> entrants; ///< Entrant's list
    Player* player; ///< Player
    unsigned int max_entrants; /// Max number of entrants
    unsigned int mcount; ///< Mistakes counter (per day)
    unsigned int ecount; ///< Number of entrant served (per day)
    unsigned int number_of_days; ///< Number of days

    /*!
     * \brief Game constructor
     *
     * \param entrants
     *     Entrant's list
     * \param player
     *     Player
     */
    Game(std::list<Entrant*> entrants, Player* player) {
      this->entrants = entrants;
      this->player = player;
      this->max_entrants = entrants.size();
      this->mcount = 0;
      this->ecount = 0;
      this->number_of_days = 0;
    }

    /*!
     * \brief Start the game
     */
    void start();

    /*!
     * \brief End a day in the game
     */
    void end_day();

    /*!
     * \brief Arrest the player
     */
    void arrest_the_player();

    /*!
     * \brief Check if the decision on an entrant was right or not
     *
     * \param decision
     *     Player's decision
     *
     * \return
     *     True if the player made a right decision (according to the laws) and
     *     false otherwise
     */
    bool check_service(bool decision);

    /*!
     * \brief Check player illegal gains
     *
     * This function calculates the player gains, if the player has a much
     * larger amount of money than the salary received the player is reported
     *
     * \return
     *     True if the player has illegal gains in the end of the day and false
     *     otherwise
     */
    bool check_illegal_gains();

    /*!
     * \brief Check bankruptcy of the player
     *
     * This function checks if the player has a negative balance
     *
     * \return
     *     True if the player has a negative balance and false otherwise
     */
    bool bankruptcy();

    /*!
     * \brief Check if the player is delinquent
     *
     * \return
     *     True if the player was delinquent in the end of the day and false
     *     otherwise
     */
    bool check_delinquency();

    /*!
     * \brief Win the game
     *
     * Winning the game means that the player managed to serve the entrants
     *
     * \return
     *     True if the player wins the game and false if the game is not over
     */
    bool win();
};

#endif /* _POPE_GAME_HPP_ */
