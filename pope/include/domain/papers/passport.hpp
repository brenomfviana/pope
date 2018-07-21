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
    std::string moa_stamp; ///< Ministry of Admission stamp
    Picture pic; ///< Entrant's picture
    char sex; ///< Entrant's sex
    Date date_of_birth; ///< Date of birth of entrant
    std::string country; ///< Country
    std::string issuing_city; ///< Issuing city
    Date expiration_date; ///< Expiration date
    bool entry_visa; ///< Entry visa

    /*!
     * \brief Passport empty constructor
     */
    Passport() { /* empty */ }

    /*!
     * \brief Passport constructor
     *
     * \param passport_number
     *     Passport number
     * \param moa_stamp
     *     Ministry of Admission stamp
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
     */
    Passport(std::string passport_number, std::string moa_stamp, Picture pic,
      std::string firstname, std::string lastname, char sex, Date date_of_birth,
      std::string country, std::string issuing_city, Date expiration_date) :
      Paper(firstname, lastname) {
        this->passport_number = passport_number;
        this->moa_stamp = moa_stamp;
        this->pic = pic;
        this->sex = sex;
        this->date_of_birth = date_of_birth;
        this->country = country;
        this->issuing_city = issuing_city;
        this->expiration_date = expiration_date;
        this->entry_visa = false;
    }

  private:
    void paper() { /* empty */ }
};

#endif /* _POPE_PASSPORT_HPP_ */
