/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_DATABASE_READER_HPP_
#define _POPE_DATABASE_READER_HPP_

#include <string>
#include <yaml-cpp/yaml.h>
#include "services/readers/database_reader.hpp"

/*!
 * \brief This class represents the content reader
 */
class DatabaseReader {
  public:
    /*!
     * \brief Database reader constructor
     *
     * \param path
     *     File path
     */
    static YAML::Node read(std::string path);
};

#endif /* _POPE_DATABASE_READER_HPP_ */
