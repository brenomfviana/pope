/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_WORKPASS_HPP_
#define _POPE_WORKPASS_HPP_

#include "paper.hpp"
#include "date.hpp"

/*!
 * \brief This class represents a work pass
 */
class WorkPass : public Paper {
  public:
    std::string field; ///< Field of work
    std::string seal; ///< Seal
    Date end; ///< Work end date

    /*!
     * \brief Work pass constructor
     *
     * \param firstname
     *     Entrant's firstname
     * \param lastname
     *     Entrant's lastname
     * \param field
     *     Field of work
     * \param seal
     *     Seal
     * \param end
     *     Work end date
     */
    WorkPass(std::string firstname, std::string lastname, std::string field,
      std::string seal, Date end) : Paper(firstname, lastname) {
        this->field = field;
        this->seal = seal;
        this->end = end;
    }

    /*!
     * \brief Work pass empty constructor
     */
    WorkPass() { /* empty */ }
};

#endif /* _POPE_WORKPASS_HPP_ */
