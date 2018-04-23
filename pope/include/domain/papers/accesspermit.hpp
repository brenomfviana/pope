/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_ACCESSPERMIT_HPP_
#define _POPE_ACCESSPERMIT_HPP_

#include "paper.hpp"
#include "date.hpp"

/*!
 * \brief This class represents an access permit
 */
class AccessPermit : public Paper {
  public:
    std::string seal; ///< Seal
    std::string nationality; ///< Nationality
    std::string passport_number; ///< Passport number
    std::string purpose; ///< Purpose
    Duration duration; ///< Duration of stay
    unsigned int height; ///< Entrant height
    unsigned int weight; ///< Entrant weight
    Date expiration_date; ///< Expiration date
    std::string physical_appearance; ///< Physical appearance

    /*!
     * \brief Access permit constructor
     *
     * \param firstname
     *     Entrant's firstname
     * \param lastname
     *     Entrant's lastname
     * \param seal
     *     Seal
     * \param nationality
     *     Nationality
     * \param passport_number
     *     Passport number
     * \param purpose
     *     Purpose
     * \param duration
     *     Duration of stay
     * \param height
     *     Entrant height
     * \param weight
     *     Entrant weight
     * \param expiration_date
     *     Expiration date
     * \param physical_appearance
     *     Physical appearance
     */
    AccessPermit(std::string firstname, std::string lastname, std::string seal,
      std::string nationality, std::string passport_number, std::string purpose,
      Duration duration, unsigned int height, unsigned int weight,
      Date expiration_date, std::string physical_appearance) :
        Paper(firstname, lastname) {
          this->seal = seal;
          this->nationality = nationality;
          this->passport_number = passport_number;
          this->purpose = purpose;
          this->duration = duration;
          this->height = height;
          this->weight = weight;
          this->expiration_date = expiration_date;
          this->physical_appearance = physical_appearance;
    }
};

#endif /* _POPE_ACCESSPERMIT_HPP_ */
