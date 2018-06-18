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
#include "commons/common.hpp"
#include "domain/entrant.hpp"
#include "papersplease/game.hpp"
#include "services/readers/content_reader.hpp"
#include "services/readers/database_reader.hpp"
#include "services/pcg/peg.hpp"

int main(int argc, char *argv[]) {
  // Check flags
  if (strcmp(argv[1], "-pcg") == 0) {
    // Generate content
    PEG::generate(DatabaseReader::read("assets/database.yml"), 100);
  } else if (strcmp(argv[1], "-r") == 0) {
    // Read list of people (entrants)
    std::list<Entrant*> train = ContentReader::read(std::string(argv[2]));
    // Read list of people (entrants)
    std::list<Entrant*> entrants = ContentReader::read(std::string(argv[3]));
    // Shuffle list
    shuffle(train);
    shuffle(entrants);
    // Start game
    std::cout << "Training..." << '\n';
    Player* player = new ARLBot(train);
    std::cout << "READY!" << '\n';
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
