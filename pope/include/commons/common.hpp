/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#ifndef _POPE_COMMON_HPP_
#define _POPE_COMMON_HPP_

#include <algorithm>
#include <random>
#include <vector>

/*!
 * \brief This function shuffles a generic list. Code reference: http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper
 *
 * \param lst
 *     A list
 *
 * \return
 *     The list with a different order of elements
 */
template<typename T> void shuffle(std::list<T>& lst) {
  // Create a vector of (wrapped) references to elements in the list
  std::vector<std::reference_wrapper<const T>> vec(lst.begin(), lst.end());
  // Shuffle (the references in) the vector
  std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});
  // Copy the shuffled sequence into a new list
  std::list<T> shuffled_list{vec.begin(), vec.end()};
  // Swap the old list with the shuffled list
  lst.swap(shuffled_list);
}

/*!
 * \brief Splits a string for each occurrence of the key character
 *
 * \param str
 *     String
 * \param c
 *     Key character
 *
 * \return
 *     A vector with the splitted string
 */
static std::vector<std::string> split(const std::string& str, const char& c) {
  // Buffer
  std::string buff = "";
  // Splitted string
  std::vector<std::string> v;
  // Find tokens
  for (auto s : str) {
    // Check if the char is the delimiter
    if (s != c) {
      // Add to buffer
      buff += s;
    } else if (s == c && buff != "") {
      // Add string to vector
      v.push_back(buff);
      // Reset buffer
      buff = "";
    }
  }
  // Check last string
  if (buff != "") {
    // Add string to vector
    v.push_back(buff);
  }
  return v;
}

#endif /* _POPE_COMMON_HPP_ */
