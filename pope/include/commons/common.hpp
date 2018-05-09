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

template<typename T> void shuffle(std::list<T>& lst) {
  // Create a vector of (wrapped) references to elements in the list
  // http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper
  std::vector<std::reference_wrapper<const T>> vec(lst.begin(), lst.end());
  // Shuffle (the references in) the vector
  std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});
  // Copy the shuffled sequence into a new list
  std::list<T> shuffled_list{vec.begin(), vec.end()};
  // Swap the old list with the shuffled list
  lst.swap(shuffled_list);
}

#endif /* _POPE_COMMON_HPP_ */
