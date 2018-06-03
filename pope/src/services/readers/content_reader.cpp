/*
  This file is part of Pope.

  Copyright (c) 2018 by Breno Viana

  Pope is a free software; you can redistribute it and/or modify it under the
  terms of the MIT License.
*/

#include "services/readers/content_reader.hpp"

std::list<Entrant*> ContentReader::read(std::string path) {
  // Read
  YAML::Node content = YAML::LoadFile(path);
  // Convert
  std::list<Entrant*> entrants;
  for (YAML::iterator it = content.begin(); it != content.end(); ++it) {
    const YAML::Node& object = *it;
    // Get papers
    std::list<Paper*> papers;
    // Get passport
    if (object["passport"]) {
      const YAML::Node& paper = object["passport"];
      // Get picture
      Picture pic(paper["pic"][0].as<std::string>(),
        paper["pic"][1].as<std::string>(),
        paper["pic"][2].as<std::string>(),
        paper["pic"][3].as<std::string>());
      // Passport
      Passport* passport = new Passport(paper["passport_number"].as<std::string>(),
        paper["seal"].as<std::string>(), pic, paper["firstname"].as<std::string>(),
          paper["lastname"].as<std::string>(), paper["sex"].as<char>(),
          paper["date_of_birth"].as<Date>(), paper["country"].as<std::string>(),
          paper["issuing_city"].as<std::string>(), paper["expiration_date"].as<Date>());
      papers.push_back(passport);
    }
    // Get ID card
    if (object["idcard"]) {
      const YAML::Node& paper = object["idcard"];
      // Get picture
      Picture pic(paper["pic"][0].as<std::string>(),
        paper["pic"][1].as<std::string>(),
        paper["pic"][2].as<std::string>(),
        paper["pic"][3].as<std::string>());
      // ID card
      IDCard* idcard = new IDCard(pic, paper["firstname"].as<std::string>(),
        paper["lastname"].as<std::string>(), paper["sex"].as<char>(),
        paper["date_of_birth"].as<Date>(), paper["country"].as<std::string>(),
        paper["issuing_city"].as<std::string>(), paper["height"].as<float>(),
        paper["weight"].as<unsigned int>());
      papers.push_back(idcard);
    }
    // Get Access permit
    if (object["accesspermit"]) {
      const YAML::Node& paper = object["accesspermit"];
      AccessPermit* accesspermit = new AccessPermit(paper["firstname"].as<std::string>(),
        paper["lastname"].as<std::string>(), paper["seal"].as<std::string>(),
        paper["nationality"].as<std::string>(), paper["passport_number"].as<std::string>(),
        paper["purpose"].as<std::string>(), paper["duration"].as<Duration>(),
        paper["height"].as<float>(), paper["weight"].as<unsigned int>(),
        paper["expiration_date"].as<Date>(), paper["physical_appearance"].as<std::string>());
      papers.push_back(accesspermit);
    }
    // Get Work pass
    if (object["workpass"]) {
      const YAML::Node& paper = object["workpass"];
      WorkPass* workpass = new WorkPass(paper["firstname"].as<std::string>(),
        paper["lastname"].as<std::string>(), paper["field"].as<std::string>(),
        paper["seal"].as<std::string>(), paper["enddate"].as<Date>());
      papers.push_back(workpass);
    }
    // Get entrant
    Picture pic(object["pic"][0].as<std::string>(),
      object["pic"][1].as<std::string>(),
      object["pic"][2].as<std::string>(),
      object["pic"][3].as<std::string>());
    Entrant* entrant = new Entrant(pic, object["firstname"].as<std::string>(),
      object["lastname"].as<std::string>(), object["sex"].as<char>(),
      object["date_of_birth"].as<Date>(), object["height"].as<float>(),
      object["weight"].as<unsigned int>(), object["country"].as<std::string>(),
      object["city"].as<std::string>(), papers, object["purpose"].as<std::string>(),
      object["bribe"].as<unsigned int>(), object["contraband"].as<std::string>());
  }
  // Shuffle list
  shuffle(entrants);
  return entrants;
}
