#include "services/pcg/peg.hpp"
#include <ctime>

std::list<Entrant*> PEG::generate(YAML::Node database) {
  //
  int num = 100;
  std::list<Entrant*> entrants;
  //
  for (int i = 0; i < num; i++) {
    entrants.push_back(new_entrant(database));
  }
  // Reordenar aleatoriamente
  //
  return entrants;
}

Entrant* PEG::new_entrant(YAML::Node database) {
  // Generate entrant
  std::mt19937 rng;
  RandomInt randi(0, 1);
  rng.seed(std::random_device()());
  char sex = database["sex"][randi(rng)].as<char>();
  std::string firstname;
  std::string hair;
  std::string facial_hair;
  if (sex == MALE) {
    randi = RandomInt(0, database["male_hair"].size() - 1);
    rng.seed(std::random_device()());
    hair = database["male_hair"][randi(rng)].as<std::string>();
    randi = RandomInt(0, database["facial_hair"].size() - 1);
    rng.seed(std::random_device()());
    facial_hair = database["facial_hair"][randi(rng)].as<std::string>();
    randi = RandomInt(0, database["male_firstnames"].size() - 1);
    rng.seed(std::random_device()());
    firstname = database["male_firstnames"][randi(rng)].as<std::string>();
  } else {
    randi = RandomInt(0, database["female_hair"].size() - 1);
    rng.seed(std::random_device()());
    hair = database["female_hair"][randi(rng)].as<std::string>();
    randi = RandomInt(0, database["female_firstnames"].size() - 1);
    rng.seed(std::random_device()());
    firstname = database["female_firstnames"][randi(rng)].as<std::string>();
  }
  randi = RandomInt(0, database["vision"].size() - 1);
  rng.seed(std::random_device()());
  std::string vision = database["vision"][randi(rng)].as<std::string>();
  randi = RandomInt(0, database["other"].size() - 1);
  rng.seed(std::random_device()());
  std::string other = database["other"][randi(rng)].as<std::string>();
  Picture pic(hair, facial_hair, vision, other);
  randi = RandomInt(0, database["lastnames"].size() - 1);
  rng.seed(std::random_device()());
  std::string lastname = database["lastnames"][randi(rng)].as<std::string>();
  time_t dmin = -1262304000;
  time_t dmax = -189475200;
  randi = RandomInt(dmin, dmax);
  time_t gd = randi(rng);
  struct tm* tm = localtime(&gd);
  Date date_of_birth(tm->tm_mday, tm->tm_mon, tm->tm_year + 1900);
  rng.seed(std::random_device()());
  randi = RandomInt((int) (database["min_height"].as<float>() * 100),
    (int) (database["max_height"].as<float>() * 100));
  float height = (randi(rng) / (float) 100);
  randi = RandomInt(database["min_weight"].as<int>(), database["max_weight"].as<int>());
  rng.seed(std::random_device()());
  unsigned int weight = randi(rng);
  randi = RandomInt(0, database["countries"].size() - 1);
  rng.seed(std::random_device()());
  std::string country = database["countries"][randi(rng)].as<std::string>();
  randi = RandomInt(0, database["cities"][country].size() - 1);
  rng.seed(std::random_device()());
  std::string city = database["cities"][country][randi(rng)].as<std::string>();
  randi = RandomInt(0, database["purpose"].size() - 1);
  rng.seed(std::random_device()());
  std::string purpose = database["purpose"][randi(rng)].as<std::string>();

  // Illegal entrant
  int illegal_fields;
  unsigned int bribe;
  std::list<std::string> contraband;
  rng.seed(std::random_device()());
  randi = RandomInt(0, 1);
  bool illegal = (randi(rng) == 1);
  //
  if (illegal) {
    //
    randi = RandomInt(1, 5);
    rng.seed(std::random_device()());
    illegal_fields = randi(rng);
    //
    randi = RandomInt(0, 4);
    rng.seed(std::random_device()());
    bribe = randi(rng) * 5;
    //
    rng.seed(std::random_device()());
    randi = RandomInt(0, 1);
    bool bc = (randi(rng) == 1);
    if (bc) {
      randi = RandomInt(0, database["contraband"].size() - 1);
      rng.seed(std::random_device()());
      contraband.push_back(database["contraband"][randi(rng)].as<std::string>());
    }
  }

  // Generate entrant's papers
  std::list<Paper*> papers;

  Entrant* entrant = new Entrant(pic, firstname, lastname, sex, date_of_birth,
    height, weight, country, city, papers, purpose, bribe, contraband);

  Passport* passport = new_passport(database, entrant, illegal, illegal_fields);
  entrant->papers.push_back(passport);
  // if is a native
  if (country == "arstotzka") {
    entrant->papers.push_back(new_idcard(database, entrant, illegal, illegal_fields));
    purpose = "";
  } else {
    AccessPermit* accesspermit = new_accesspermit(database, entrant, passport, illegal, illegal_fields);
    entrant->papers.push_back(accesspermit);
    if (purpose == "Work") {
      entrant->papers.push_back(new_workpass(database, entrant, accesspermit, illegal, illegal_fields));
    }
  }

  // Print
  std::cout << firstname << " " << lastname << ":\n " << sex << ", " << height
    << ", " << weight << ", " << country << ", " << city << ", " << purpose << '\n';
  std::cout << " " << tm->tm_mday << "/" << tm->tm_mon << "/" << (tm->tm_year + 1900) << '\n';
  return entrant;
}

Passport* PEG::new_passport(YAML::Node database, Entrant* entrant, bool illegal,
  int& illegal_fields) {
    Passport* passport;
    // Random variables
    std::mt19937 rng;
    RandomInt randi;
    if (illegal) {
      // TODO
      illegal_fields--;
      if (illegal_fields == 0) {
        illegal = false;
      }
    } else {
      char s[10];
      static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      for (int i = 0; i < 10; ++i) {
          s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
      }
      std::string passport_number(s);
      randi = RandomInt(0, database["valid_moa_seals"].size() - 1);
      rng.seed(std::random_device()());
      std::string seal = database["valid_moa_seals"][randi(rng)].as<std::string>();
      std::string issuing_city;
      if (entrant->country == "arstotzka") {
        randi = RandomInt(0, database["issuing_city"][entrant->country].size() - 1);
        rng.seed(std::random_device()());
        issuing_city = database["issuing_city"][entrant->country][randi(rng)].as<std::string>();
      } else {
        issuing_city = entrant->city;
      }
      // Expiration date
      time_t dmin = 406944000;
      time_t dmax = 473299200;
      randi = RandomInt(dmin, dmax);
      time_t gd = randi(rng);
      struct tm* tm = localtime(&gd);
      Date expiration_date(tm->tm_mday, tm->tm_mon, tm->tm_year + 1900);
      // Other hair on picture
      std::string hair;
      if (entrant->sex == MALE) {
        randi = RandomInt(0, database["male_hair"].size() - 1);
        rng.seed(std::random_device()());
        hair = database["male_hair"][randi(rng)].as<std::string>();
      } else {
        randi = RandomInt(0, database["female_hair"].size() - 1);
        rng.seed(std::random_device()());
        hair = database["female_hair"][randi(rng)].as<std::string>();
      }
      Picture picture(hair, entrant->pic.facial_hair, entrant->pic.vision,
        entrant->pic.other);
      // Create passport
      passport = new Passport(passport_number, seal, picture, entrant->firstname,
        entrant->lastname, entrant->sex, entrant->date_of_birth, entrant->country,
        issuing_city, expiration_date);
      std::cout << " " << passport_number << " " << seal << " " << entrant->firstname << " " <<
        entrant->lastname << " " << entrant->sex << " " << entrant->country << " " <<
        issuing_city << " " << '\n';
    }
    return passport;
}

IDCard* PEG::new_idcard(YAML::Node database, Entrant* entrant, bool illegal,
  int& illegal_fields) {
    IDCard* idcard;
    // Random variables
    std::mt19937 rng;
    RandomInt randi;
    if (illegal) {
      // TODO
      illegal_fields--;
      if (illegal_fields == 0) {
        illegal = false;
      }
    } else {
      // Other hair on picture
      std::string hair;
      if (entrant->sex == MALE) {
        randi = RandomInt(0, database["male_hair"].size() - 1);
        rng.seed(std::random_device()());
        hair = database["male_hair"][randi(rng)].as<std::string>();
      } else {
        randi = RandomInt(0, database["female_hair"].size() - 1);
        rng.seed(std::random_device()());
        hair = database["female_hair"][randi(rng)].as<std::string>();
      }
      Picture picture(hair, entrant->pic.facial_hair, entrant->pic.vision,
        entrant->pic.other);
      idcard = new IDCard(picture, entrant->firstname, entrant->lastname,
        entrant->sex, entrant->date_of_birth, entrant->country, entrant->city,
        entrant->height, entrant->weight);
    }
    return idcard;
}

AccessPermit* PEG::new_accesspermit(YAML::Node database, Entrant* entrant,
  Passport* passport, bool illegal, int& illegal_fields) {
    AccessPermit* accesspermit;
    // Random variables
    std::mt19937 rng;
    RandomInt randi;
    if (illegal) {
      // TODO
      illegal_fields--;
      if (illegal_fields == 0) {
        illegal = false;
      }
    } else {
      //
      std::string passport_number;
      randi = RandomInt(0, database["valid_moa_seals"].size() - 1);
      rng.seed(std::random_device()());
      std::string seal = database["valid_moa_seals"][randi(rng)].as<std::string>();
      Duration duration;
      if (entrant->purpose == "Visit") {
        time_t dmin = 1209600;
        time_t dmax = 7862400;
        randi = RandomInt(dmin, dmax);
        time_t gd = randi(rng);
        struct tm* tm = localtime(&gd);
        duration = Date(tm->tm_mday, tm->tm_mon, tm->tm_year + 1900);
      }
      if (entrant->purpose == "Transit") {
        time_t dmin = 172800;
        time_t dmax = 1209600;
        randi = RandomInt(dmin, dmax);
        time_t gd = randi(rng);
        struct tm* tm = localtime(&gd);
        duration = Date(tm->tm_mday, tm->tm_mon, tm->tm_year + 1900);
      }
      if (entrant->purpose == "Work") {
        time_t dmin = 7862400;
        time_t dmax = 31622400;
        randi = RandomInt(dmin, dmax);
        time_t gd = randi(rng);
        struct tm* tm = localtime(&gd);
        duration = Date(tm->tm_mday, tm->tm_mon, tm->tm_year + 1900);
      }
      // Expiration date
      time_t dmin = 406944000;
      time_t dmax = 473299200;
      randi = RandomInt(dmin, dmax);
      time_t gd = randi(rng);
      struct tm* tm = localtime(&gd);
      Date expiration_date(tm->tm_mday, tm->tm_mon, tm->tm_year + 1900);
      std::vector<std::string> pa;
      if (entrant->sex == MALE) {
        pa.push_back(entrant->pic.hair);
        pa.push_back(entrant->pic.facial_hair);
        pa.push_back(entrant->pic.vision);
        pa.push_back(entrant->pic.other);
      } else {
        pa.push_back(entrant->pic.hair);
        pa.push_back(entrant->pic.vision);
        pa.push_back(entrant->pic.other);
      }
      randi = RandomInt(0, pa.size() - 1);
      rng.seed(std::random_device()());
      std::string physical_appearance = pa[randi(rng)];
      accesspermit = new AccessPermit(entrant->firstname, entrant->lastname,
        seal, entrant->country, passport->passport_number, entrant->purpose,
        duration, entrant->height, entrant->weight, expiration_date,
        physical_appearance);
    }
    return accesspermit;
}

WorkPass* PEG::new_workpass(YAML::Node database, Entrant* entrant,
  AccessPermit* accesspermit, bool illegal, int& illegal_fields) {
    WorkPass* workpass;
    // Random variables
    std::mt19937 rng;
    RandomInt randi;
    if (illegal) {
      // TODO
      illegal_fields--;
      if (illegal_fields == 0) {
        illegal = false;
      }
    } else {
      Date end;
      if (entrant->purpose == "Work") {
        Duration d = accesspermit->duration;
        struct tm *aux;
        aux->tm_year = d.year - 1900;
        aux->tm_mon = d.month - 1;
        aux->tm_mday = d.day;
        time_t tend = 406944000 + mktime(aux);
        struct tm* tm = localtime(&tend);
        end = Date(tm->tm_mday, tm->tm_mon, tm->tm_year + 1900);
      } else {
        time_t start = 406944000;
        time_t dmin = 7862400;
        time_t dmax = 31622400;
        randi = RandomInt(dmin, dmax);
        time_t gd = 406944000 + randi(rng);
        struct tm* tm = localtime(&gd);
        end = Date(tm->tm_mday, tm->tm_mon, tm->tm_year + 1900);
      }
      randi = RandomInt(0, database["works"].size() - 1);
      rng.seed(std::random_device()());
      std::string field = database["works"][randi(rng)].as<std::string>();
      randi = RandomInt(0, database["valid_mol_seals"].size() - 1);
      rng.seed(std::random_device()());
      std::string seal = database["valid_mol_seals"][randi(rng)].as<std::string>();
      workpass = new WorkPass(entrant->firstname, entrant->lastname, field, seal,
        end);
    }
    return workpass;
}
