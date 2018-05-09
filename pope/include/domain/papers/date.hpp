/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_DATE_HPP_
#define _POPE_DATE_HPP_

#include <string>

/*!
 * \brief This class represents a date
 */
class Date {
  public:
    unsigned int day; ///< Day
    unsigned int month; ///< Month
    unsigned int year; ///< Year

    /*!
     * \brief Date constructor
     *
     * \param day
     *     Day
     * \param month
     *     Mont
     * \param year
     *     Year
     */
    Date(unsigned int day, unsigned int month, unsigned int year) {
      this->day = day;
      this->month = month;
      this->year = year;
    }

    /*!
     * \brief Date empty constructor
     */
    Date() { /* empty */ }

    /*!
     * \brief Convert date to string
     *
     * \return
     *     String corresponding to the date
     */
    std::string to_str() {
      return (std::to_string(this->day) + "/" + std::to_string(this->month) +
        "/" + std::to_string(this->year));
    }
};

typedef Date Duration;

#endif /* _POPE_DATE_HPP_ */
