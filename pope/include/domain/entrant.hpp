/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_ENTRANT_HPP_
#define _POPE_ENTRANT_HPP_

#include <string>
#include <list>
#include "papers/picture.hpp"
#include "papers/date.hpp"
#include "papers/paper.hpp"

/*!
 * \brief This class represents a entrant
 */
class Entrant {
  public:
    Picture pic; ///< Entrant's picture
    std::string firstname, lastname; ///< Entrant's name
    char sex; ///< Entrant's sex
    Date date_of_birth; ///< Date of birth of entrant
    float height; ///< Entrant's height
    unsigned int weight; ///< Entrant's weight
    std::string country; ///< Country
    std::string city; ///< City
    std::list<Paper*> papers; ///< Entrant's papers
    std::string purpose; ///< Purpose
    unsigned int bribe; ///< Bribe for immigration officer
    std::string contraband; ///< Contraband (entrant's illegal item)

    /*!
     * \brief Entrant's constructor
     *
     * \param pic
     *     Entrant's picture
     * \param firstname
     *     Entrant's firstname
     * \param lastname
     *     Entrant's lastname
     * \param sex
     *     Entrant's sex
     * \param date_of_birth
     *     Date of birth of entrant
     * \param height
     *     Entrant's height
     * \param weight
     *     Entrant's weight
     * \param country
     *     Country
     * \param city
     *     City
     * \param papers
     *     Entrant's papers
     * \param purpose
     *     Purpose
     * \param bribe
     *     Bribe for immigration officer
     * \param contraband
     *     Contraband (entrant's illegal item)
     */
    Entrant(Picture pic, std::string firstname, std::string lastname, char sex,
      Date date_of_birth, float height, unsigned int weight, std::string country,
      std::string city, std::list<Paper*> papers, std::string purpose,
      unsigned int bribe, std::string contraband) {
        this->pic = pic;
        this->firstname = firstname;
        this->lastname = lastname;
        this->sex = sex;
        this->date_of_birth = date_of_birth;
        this->height = height;
        this->weight = weight;
        this->country = country;
        this->city = city;
        this->papers = papers;
        this->purpose = purpose;
        this->bribe = bribe;
        this->contraband = contraband;
    }

    /*!
     * \brief Entrant empty constructor
     */
    Entrant() { /* empty */ }
};

#endif /* _POPE_ENTRANT_HPP_ */
