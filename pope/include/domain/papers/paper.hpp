/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_PAPER_HPP_
#define _POPE_PAPER_HPP_

#include <string>

/*!
 * \brief This class represents a paper (an entrant document)
 */
class Paper {
  public:
    std::string firstname, lastname; ///< Entrant's name

    /*!
     * \brief Paper constructor
     *
     * \param firstname
     *     Entrant's firstname
     * \param lastname
     *     Entrant's lastname
     */
    Paper(std::string firstname, std::string lastname) {
      this->firstname = firstname;
      this->lastname = lastname;
    }

    /*!
     * \brief Paper empty constructor
     */
    Paper() { /* empty */ }

  private:
    virtual void paper() = 0;
};

#include "passport.hpp"
#include "idcard.hpp"
#include "accesspermit.hpp"
#include "workpass.hpp"

#endif /* _POPE_PAPER_HPP_ */
