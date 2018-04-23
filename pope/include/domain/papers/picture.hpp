/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_PICTURE_HPP_
#define _POPE_PICTURE_HPP_

#include <string>

/*!
 * \brief This class represents an entrant's picture
 */
class Picture {
  public:
    std::string hair; ///< Entrant's hair
    std::string facial_hair; ///< Entrant's facial hair
    std::string vision; ///< Entrant's hair
    std::string other; ///< Entrant's hair

    /*!
     * \brief Paper constructor
     *
     * \param hair
     *     Entrant's hair
     * \param facial_hair
     *     Entrant's facial hair
     * \param vision
     *     Entrant's vision
     * \param other
     *     Other physical characteristics
     */
    Picture(std::string hair, std::string facial_hair, std::string vision,
      std::string other) {
        this->hair = hair;
        this->facial_hair = facial_hair;
        this->vision = vision;
        this->other = other;
    }

    /*!
     * \brief Paper empty constructor
     */
    Picture() { /* empty */ }
};

#endif /* _POPE_PICTURE_HPP_ */
