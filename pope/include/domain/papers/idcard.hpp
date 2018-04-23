/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_IDCARD_HPP_
#define _POPE_IDCARD_HPP_

#include "paper.hpp"
#include "picture.hpp"
#include "date.hpp"

/*!
 * \brief This class represents a passport
 */
class IDCard : public Paper {
  public:
    Picture pic; ///< Entrant's picture
    char sex; ///< Entrant's sex
    Date date_of_birth; ///< Date of birth of entrant
    std::string country; ///< Country
    std::string city; ///< City
    unsigned int height; ///< Entrant's height
    unsigned int weight; ///< Entrant's weight

    /*!
     * \brief IDCard constructor
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
     * \param country
     *     Country
     * \param city
     *     City
     * \param height
     *     Entrant's height
     * \param weight
     *     Entrant's weight
     */
    IDCard(Picture pic, std::string firstname, std::string lastname, char sex,
      Date date_of_birth, std::string country, std::string city,
      unsigned int height, unsigned int weight) : Paper(firstname, lastname) {
        this->pic = pic;
        this->sex = sex;
        this->date_of_birth = date_of_birth;
        this->country = country;
        this->city = city;
        this->height = height;
        this->weight = weight;
    }
};

#endif /* _POPE_IDCARD_HPP_ */
