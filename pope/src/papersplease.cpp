/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include "domain/entrant.hpp"
#include "papersplease/game.hpp"
#include "services/readers/content_reader.hpp"
#include "services/readers/database_reader.hpp"
#include "services/pcg/peg.hpp"

int main(int argc, char *argv[]) {
  std::list<Entrant*> entrants;
  // Check flags
  if (strcmp(argv[1], "-pcg") == 0) {
    // Generate content
    entrants = PEG::generate(DatabaseReader::read("assets/database.yml"), 100);
  } else if (strcmp(argv[1], "-r") == 0) {
    // Read list of people (entrants)
    entrants = ContentReader::read(std::string(argv[2]));
    // Start game
    Player* player = new PerfectBot();
    Game game(entrants, player);
    game.start();
  } else {
    // ERROR
    std::cerr << "Error: Invalid arguments." << '\n';
    return EXIT_FAILURE;
  }
  // Exit
  return EXIT_SUCCESS;
}
