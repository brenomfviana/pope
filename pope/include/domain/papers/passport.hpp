/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_PASSPORT_HPP_
#define _POPE_PASSPORT_HPP_

#include "paper.hpp"
#include "picture.hpp"
#include "date.hpp"

/*!
 * \brief This class represents a passport
 */
class Passport : public Paper {
  public:
    std::string passport_number; ///< Passport number
    std::string seal; ///< Seal
    Picture pic; ///< Entrant's picture
    char sex; ///< Entrant's sex
    Date date_of_birth; ///< Date of birth of entrant
    std::string country; ///< Country
    std::string issuing_city; ///< Issuing city
    Date expiration_date; ///< Expiration date
    bool stamp; ///< Stamp

    /*!
     * \brief Passport constructor
     *
     * \param passport_number
     *     Passport number
     * \param seal
     *     Seal
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
     * \param issuing_city
     *     Issuing city
     * \param expiration_date
     *     Expiration date
     * \param stamp
     *     Stamp
     */
    Passport(std::string passport_number, std::string seal, Picture pic,
      std::string firstname, std::string lastname, char sex, Date date_of_birth,
      std::string country, std::string issuing_city, Date expiration_date) :
      Paper(firstname, lastname) {
        this->passport_number = passport_number;
        this->seal = seal;
        this->pic = pic;
        this->sex = sex;
        this->date_of_birth = date_of_birth;
        this->country = country;
        this->issuing_city = issuing_city;
        this->expiration_date = expiration_date;
        this->stamp = false;
    }

    /*!
     * \brief Passport empty constructor
     */
    Passport() { /* empty */ }
};

#endif /* _POPE_PASSPORT_HPP_ */
