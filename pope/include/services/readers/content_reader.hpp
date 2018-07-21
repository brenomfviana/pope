/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_CONTENT_READER_HPP_
#define _POPE_CONTENT_READER_HPP_

#include <iostream>
#include <list>
#include <string>
#include <yaml-cpp/yaml.h>
#include "yaml_convert_decode.hpp"
#include "commons/common.hpp"
#include "domain/entrant.hpp"
#include "domain/papers/paper.hpp"
#include "domain/papers/date.hpp"
#include "domain/papers/picture.hpp"

/*!
 * \brief This class represents the content reader
 */
class ContentReader {
  public:
    /*!
     * \brief Content reader constructor
     *
     * \param path
     *     File path
     */
    static std::list<Entrant*> read(std::string path);
};

#endif /* _POPE_CONTENT_READER_HPP_ */
