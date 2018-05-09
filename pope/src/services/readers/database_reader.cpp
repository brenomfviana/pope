/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#include "services/readers/database_reader.hpp"

YAML::Node DatabaseReader::read(std::string path) {
  return YAML::LoadFile(path);
}
