/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_YAML_TO_HPP_
#define _POPE_YAML_TO_HPP_

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include "commons/common.hpp"
#include "domain/papers/date.hpp"

namespace YAML {
  template<>
  struct convert<Date> {
    static Node encode(const Date& rhs) {
      Node node;
      std::string s = std::to_string(rhs.day) + "\\" +
        std::to_string(rhs.month) + "\\" +
        std::to_string(rhs.year);
      return node;
    }

    static bool decode(const Node& node, Date& rhs) {
      if(node.IsSequence()) {
        return false;
      }
      std::vector<std::string> v = split(node.as<std::string>(), '\\');
      rhs = Date(std::stoi(v[0]), std::stoi(v[1]), std::stoi(v[2]));
      return true;
    }
  };
}

#endif /* _POPE_YAML_TO_HPP_ */
