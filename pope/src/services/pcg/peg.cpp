#include "services/pcg/peg.hpp"
#include <sys/types.h>
#include <dirent.h>

std::list<Entrant*> PEG::generate(YAML::Node database, int n) {
  std::list<Entrant*> entrants;
  YAML::Emitter out;
  // Random variables
  std::mt19937 rng;
  RandomInt randi;
  // Number of illegal entrants
  randi = RandomInt(((int) n * 0.25), ((int) n * 0.75));
  rng.seed(std::random_device()());
  int noie = randi(rng);
  // Generate entrants
  out << YAML::BeginSeq;
  for (int i = 0; i < n; i++) {
    Entrant* entrant;
    if (i < noie) {
      // Illegal entrant
      entrant = new_entrant(database, true);
    } else {
      // Legal entrant
      entrant = new_entrant(database, false);
    }
    entrants.push_back(entrant);
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "entrant" << YAML::Value;
      out << YAML::BeginMap;
        out << YAML::Key << "pic" << YAML::Value << YAML::BeginSeq
          << entrant->pic.hair << entrant->pic.facial_hair
          << entrant->pic.vision << entrant->pic.other << YAML::EndSeq;
        out << YAML::Key << "firstname" << YAML::Value << entrant->firstname;
        out << YAML::Key << "lastname" << YAML::Value << entrant->lastname;
        out << YAML::Key << "sex" << YAML::Value << entrant->sex;
        out << YAML::Key << "date_of_birth" << YAML::Value << entrant->date_of_birth.to_str();
        out << YAML::Key << "height" << YAML::Value << entrant->height;
        out << YAML::Key << "weight" << YAML::Value << entrant->weight;
        out << YAML::Key << "country" << YAML::Value << entrant->country;
        out << YAML::Key << "city" << YAML::Value << entrant->city;
        out << YAML::Key << "purpose" << YAML::Value << entrant->purpose;
        out << YAML::Key << "bribe" << YAML::Value << std::to_string(entrant->bribe);
      out << YAML::EndMap;
    for (Paper* paper : entrant->papers) {
      // Passport
      if (typeid(*paper) == typeid(Passport)) {
        Passport* passport = dynamic_cast<Passport*>(paper);
        out << YAML::Key << "passport" << YAML::Value;
          out << YAML::BeginMap;
            out << YAML::Key << "pic" << YAML::Value << YAML::BeginSeq
              << passport->pic.hair << passport->pic.facial_hair
              << passport->pic.vision << passport->pic.other << YAML::EndSeq;
            out << YAML::Key << "firstname" << YAML::Value << passport->firstname;
            out << YAML::Key << "lastname" << YAML::Value << passport->lastname;
            out << YAML::Key << "passport_number" << YAML::Value << passport->passport_number;
            out << YAML::Key << "moa_stamp" << YAML::Value << passport->moa_stamp;
            out << YAML::Key << "sex" << YAML::Value << passport->sex;
            out << YAML::Key << "date_of_birth" << YAML::Value << passport->date_of_birth.to_str();
            out << YAML::Key << "country" << YAML::Value << passport->country;
            out << YAML::Key << "issuing_city" << YAML::Value << passport->issuing_city;
            out << YAML::Key << "expiration_date" << YAML::Value << passport->expiration_date.to_str();
          out << YAML::EndMap;
      }
      // ID card
      if (typeid(*paper) == typeid(IDCard)) {
        IDCard* idcard = dynamic_cast<IDCard*>(paper);
        out << YAML::Key << "idcard" << YAML::Value;
          out << YAML::BeginMap;
            out << YAML::Key << "pic" << YAML::Value << YAML::BeginSeq
              << idcard->pic.hair << idcard->pic.facial_hair
              << idcard->pic.vision << idcard->pic.other << YAML::EndSeq;
            out << YAML::Key << "firstname" << YAML::Value << idcard->firstname;
            out << YAML::Key << "lastname" << YAML::Value << idcard->lastname;
            out << YAML::Key << "sex" << YAML::Value << idcard->sex;
            out << YAML::Key << "date_of_birth" << YAML::Value << idcard->date_of_birth.to_str();
            out << YAML::Key << "country" << YAML::Value << idcard->country;
            out << YAML::Key << "city" << YAML::Value << idcard->city;
            out << YAML::Key << "height" << YAML::Value << idcard->height;
            out << YAML::Key << "weight" << YAML::Value << idcard->weight;
          out << YAML::EndMap;
      }
      // Access permit
      if (typeid(*paper) == typeid(AccessPermit)) {
        AccessPermit* accesspermit = dynamic_cast<AccessPermit*>(paper);
        out << YAML::Key << "accesspermit" << YAML::Value;
          out << YAML::BeginMap;
            out << YAML::Key << "firstname" << YAML::Value << accesspermit->firstname;
            out << YAML::Key << "lastname" << YAML::Value << accesspermit->lastname;
            out << YAML::Key << "moa_stamp" << YAML::Value << accesspermit->moa_stamp;
            out << YAML::Key << "nationality" << YAML::Value << accesspermit->nationality;
            out << YAML::Key << "passport_number" << YAML::Value << accesspermit->passport_number;
            out << YAML::Key << "purpose" << YAML::Value << accesspermit->purpose;
            out << YAML::Key << "duration" << YAML::Value << accesspermit->duration;
            out << YAML::Key << "height" << YAML::Value << accesspermit->height;
            out << YAML::Key << "weight" << YAML::Value << accesspermit->weight;
            out << YAML::Key << "expiration_date" << YAML::Value << accesspermit->expiration_date.to_str();
            out << YAML::Key << "physical_appearance" << YAML::Value << accesspermit->physical_appearance;
          out << YAML::EndMap;
      }
      // Work pass
      if (typeid(*paper) == typeid(WorkPass)) {
        WorkPass* workpass = dynamic_cast<WorkPass*>(paper);
        out << YAML::Key << "workpass" << YAML::Value;
          out << YAML::BeginMap;
            out << YAML::Key << "firstname" << YAML::Value << workpass->firstname;
            out << YAML::Key << "lastname" << YAML::Value << workpass->lastname;
            out << YAML::Key << "mol_stamp" << YAML::Value << workpass->mol_stamp;
            out << YAML::Key << "field" << YAML::Value << workpass->field;
            out << YAML::Key << "enddate" << YAML::Value << workpass->end.to_str();
          out << YAML::EndMap;
      }
    }
    out << YAML::EndMap;
  }
  // Save content
  DIR *dp;
  int i = 0;
  struct dirent *ep;
  dp = opendir("pcg/");
  if (dp != NULL) {
    while (ep = readdir(dp)) { i++; }
    (void) closedir(dp);
  }
  out << YAML::EndSeq;
  std::ofstream write;
  std::string s = "pcg/pcg" + std::to_string(i - 1) + ".yml";
  write.open (s.c_str());
  write << out.c_str();
  write.close();
  // Shuffle list
  shuffle(entrants);
  return entrants;
}

Entrant* PEG::new_entrant(YAML::Node database, bool illegal) {
  // Random variables
  std::mt19937 rng;
  RandomInt randi;
  // Sex
  randi = RandomInt(0, 1);
  rng.seed(std::random_device()());
  char sex = database["sex"][randi(rng)].as<char>();
  // Gender-dependent variables
  std::string firstname;
  std::string hair;
  std::string facial_hair = "None";
  if (sex == MALE) {
    // Male hair
    randi = RandomInt(0, database["male_hair"].size() - 1);
    rng.seed(std::random_device()());
    hair = database["male_hair"][randi(rng)].as<std::string>();
    // Facial hair
    randi = RandomInt(0, database["facial_hair"].size() - 1);
    rng.seed(std::random_device()());
    facial_hair = database["facial_hair"][randi(rng)].as<std::string>();
    // Male firstnames
    randi = RandomInt(0, database["male_firstnames"].size() - 1);
    rng.seed(std::random_device()());
    firstname = database["male_firstnames"][randi(rng)].as<std::string>();
  } else {
    // Female hair
    randi = RandomInt(0, database["female_hair"].size() - 1);
    rng.seed(std::random_device()());
    hair = database["female_hair"][randi(rng)].as<std::string>();
    // Female firstnames
    randi = RandomInt(0, database["female_firstnames"].size() - 1);
    rng.seed(std::random_device()());
    firstname = database["female_firstnames"][randi(rng)].as<std::string>();
  }
  // Vision
  randi = RandomInt(0, database["vision"].size() - 1);
  rng.seed(std::random_device()());
  std::string vision = database["vision"][randi(rng)].as<std::string>();
  // Other physical appearance
  randi = RandomInt(0, database["other"].size() - 1);
  rng.seed(std::random_device()());
  std::string other = database["other"][randi(rng)].as<std::string>();
  // Picture
  Picture pic(hair, facial_hair, vision, other);
  // Lastnames
  randi = RandomInt(0, database["lastnames"].size() - 1);
  rng.seed(std::random_device()());
  std::string lastname = database["lastnames"][randi(rng)].as<std::string>();
  // Date of birth
  time_t dmin = -1262304000;
  time_t dmax = -189475200;
  randi = RandomInt(dmin, dmax);
  time_t gd = randi(rng);
  struct tm* tm = localtime(&gd);
  Date date_of_birth(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
  // Height
  rng.seed(std::random_device()());
  randi = RandomInt((int) (database["min_height"].as<float>() * 100),
    (int) (database["max_height"].as<float>() * 100));
  float height = (randi(rng) / (float) 100);
  // Weight
  randi = RandomInt(database["min_weight"].as<int>(),
    database["max_weight"].as<int>());
  rng.seed(std::random_device()());
  unsigned int weight = randi(rng);
  // Country
  randi = RandomInt(0, database["countries"].size() - 1);
  rng.seed(std::random_device()());
  std::string country = database["countries"][randi(rng)].as<std::string>();
  // City
  randi = RandomInt(0, database["cities"][country].size() - 1);
  rng.seed(std::random_device()());
  std::string city = database["cities"][country][randi(rng)].as<std::string>();
  // Purpose
  randi = RandomInt(0, database["purpose"].size() - 1);
  rng.seed(std::random_device()());
  std::string purpose = database["purpose"][randi(rng)].as<std::string>();


  //// Illegal entrant
  // Illegal variables
  int invalid_fields;
  unsigned int bribe;
  // If the entrant is illegal
  if (illegal) {
    // Amount of invalid fields
    randi = RandomInt(1, 5);
    rng.seed(std::random_device()());
    invalid_fields = randi(rng);
    // Amount of bribe
    randi = RandomInt(0, 4);
    rng.seed(std::random_device()());
    bribe = randi(rng) * 5;
  }

  // Generate entrant's papers
  std::list<Paper*> papers;
  // Create entrant
  Entrant* entrant = new Entrant(pic, firstname, lastname, sex, date_of_birth,
    height, weight, country, city, papers, purpose, bribe);
  // Passport
  Passport* passport = new_passport(database, entrant, illegal, invalid_fields);
  entrant->papers.push_back(passport);
  // If the entrant is a native
  if (country == "arstotzka") {
    // ID Card
    entrant->papers.push_back(new_idcard(database, entrant, illegal,
      invalid_fields));
    purpose = "";
  } else {
    // Access permit
    AccessPermit* accesspermit = new_accesspermit(database, entrant, passport,
      illegal, invalid_fields);
    entrant->papers.push_back(accesspermit);
    if (purpose == "Work") {
      // Work pass
      entrant->papers.push_back(new_workpass(database, entrant, accesspermit,
        illegal, invalid_fields));
    }
  }
  return entrant;
}

Passport* PEG::new_passport(YAML::Node database, Entrant* entrant, bool illegal,
  int& invalid_fields) {
    Passport* passport;
    // Random variables
    std::mt19937 rng;
    RandomInt randi;

    std::string firstname = entrant->firstname;
    std::string lastname = entrant->lastname;
    char sex = entrant->sex;
    Date date_of_birth = entrant->date_of_birth;
    std::string country = entrant->country;
    char s[10];
    static const char alphanum[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 10; ++i) {
      s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    std::string passport_number(s);
    // M.O.A. Stamp
    randi = RandomInt(0, database["valid_moa_stamps"].size() - 1);
    rng.seed(std::random_device()());
    std::string moa_stamp = database["valid_moa_stamps"][randi(rng)].as<std::string>();
    // Issuing city
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
    Date expiration_date(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    // Other hair on picture
    std::string hair = entrant->pic.hair;
    std::string facial_hair = entrant->pic.facial_hair;
    std::string vision = entrant->pic.vision;
    std::string other = entrant->pic.other;
    // // Change picture
    // if (entrant->sex == MALE) {
    //   randi = RandomInt(0, database["male_hair"].size() - 1);
    //   rng.seed(std::random_device()());
    //   hair = database["male_hair"][randi(rng)].as<std::string>();
    // } else {
    //   randi = RandomInt(0, database["female_hair"].size() - 1);
    //   rng.seed(std::random_device()());
    //   hair = database["female_hair"][randi(rng)].as<std::string>();
    // }
    Picture picture(hair, facial_hair, vision, other);

    // If the entrant is illegal
    if (illegal) {
      randi = RandomInt(0, 7);
      rng.seed(std::random_device()());
      switch (randi(rng)) {
        case 0:
          // Firstname
          do {
            // Random invalid firstname
            rng.seed(std::random_device()());
            randi = RandomInt(0, 1);
            if (randi(rng) == 1) {
              // Male firstnames
              randi = RandomInt(0, database["male_firstnames"].size() - 1);
              rng.seed(std::random_device()());
              firstname = database["male_firstnames"][randi(rng)].as<std::string>();
            } else {
              // Female firstnames
              randi = RandomInt(0, database["female_firstnames"].size() - 1);
              rng.seed(std::random_device()());
              firstname = database["female_firstnames"][randi(rng)].as<std::string>();
            }
          } while(firstname == entrant->firstname);
          break;
        case 1:
          // Lastnames
          do {
            randi = RandomInt(0, database["lastnames"].size() - 1);
            rng.seed(std::random_device()());
            lastname = database["lastnames"][randi(rng)].as<std::string>();
          } while(lastname == entrant->lastname);
          break;
        case 2:
          // Sex
          if (entrant->sex == MALE) {
            sex = FEMALE;
          } else {
            sex = MALE;
          }
        case 3:
          {
            // M.O.A. Stamp
            randi = RandomInt(0, database["forged_moa_stamps"].size() - 1);
            rng.seed(std::random_device()());
            std::string moa_stamp = database["forged_moa_stamps"][randi(rng)].as<std::string>();
            break;
          }
        case 4:
          {
            // Picture
            do {
              rng.seed(std::random_device()());
              randi = RandomInt(0, 1);
              if (randi(rng) == 1) {
                randi = RandomInt(0, database["male_hair"].size() - 1);
                rng.seed(std::random_device()());
                hair = database["male_hair"][randi(rng)].as<std::string>();
              } else {
                randi = RandomInt(0, database["female_hair"].size() - 1);
                rng.seed(std::random_device()());
                hair = database["female_hair"][randi(rng)].as<std::string>();
              }
            } while(hair == entrant->pic.hair);
            do {
              randi = RandomInt(0, database["facial_hair"].size() - 1);
              rng.seed(std::random_device()());
              facial_hair = database["facial_hair"][randi(rng)].as<std::string>();
            } while(facial_hair == entrant->pic.facial_hair);
            do {
              randi = RandomInt(0, database["vision"].size() - 1);
              rng.seed(std::random_device()());
              vision = database["vision"][randi(rng)].as<std::string>();
            } while(vision == entrant->pic.vision);
            do {
              randi = RandomInt(0, database["other"].size() - 1);
              rng.seed(std::random_device()());
              other = database["other"][randi(rng)].as<std::string>();
            } while(other == entrant->pic.other);
            break;
          }
        case 5:
          // Country
          do {
            randi = RandomInt(0, database["countries"].size() - 1);
            rng.seed(std::random_device()());
            country = database["countries"][randi(rng)].as<std::string>();
          } while(country == entrant->country);
          break;
        case 6:
          // Issuing city
          random_shuffle(issuing_city.begin(), issuing_city.end());
          break;
        case 7:
          {
            // Expiration date
            time_t dmin = 86400;
            time_t dmax = 604800;
            randi = RandomInt(dmin, dmax);
            time_t gd = 406944000 - randi(rng);
            struct tm* tm = localtime(&gd);
            expiration_date = Date(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
            break;
          }
      }
      // Update invalid fields
      invalid_fields--;
      if (invalid_fields == 0) {
        illegal = false;
      }
    }

    picture = Picture(hair, facial_hair, vision, other);

    return (new Passport(passport_number, moa_stamp, picture, firstname, lastname,
      sex, date_of_birth, country, issuing_city, expiration_date));
}

IDCard* PEG::new_idcard(YAML::Node database, Entrant* entrant, bool illegal,
  int& invalid_fields) {
    // Random variables
    std::mt19937 rng;
    RandomInt randi;

    // Fields
    std::string firstname = entrant->firstname;
    std::string lastname = entrant->lastname;
    char sex = entrant->sex;
    Date date_of_birth = entrant->date_of_birth;
    std::string country = entrant->country;
    std::string city = entrant->city;
    float height = entrant->height;
    unsigned int weight = entrant->weight;
    // Other hair on picture
    std::string hair = entrant->pic.hair;
    std::string facial_hair = entrant->pic.facial_hair;
    std::string vision = entrant->pic.vision;
    std::string other = entrant->pic.other;
    // // Change picture
    // if (entrant->sex == MALE) {
    //   randi = RandomInt(0, database["male_hair"].size() - 1);
    //   rng.seed(std::random_device()());
    //   hair = database["male_hair"][randi(rng)].as<std::string>();
    // } else {
    //   randi = RandomInt(0, database["female_hair"].size() - 1);
    //   rng.seed(std::random_device()());
    //   hair = database["female_hair"][randi(rng)].as<std::string>();
    // }
    Picture picture(hair, facial_hair, vision, other);

    // If the entrant is illegal
    if (illegal) {
      randi = RandomInt(0, 7);
      rng.seed(std::random_device()());
      switch (randi(rng)) {
        case 0:
          // Firstname
          do {
            // Random invalid firstname
            rng.seed(std::random_device()());
            randi = RandomInt(0, 1);
            if (randi(rng) == 1) {
              // Male firstnames
              randi = RandomInt(0, database["male_firstnames"].size() - 1);
              rng.seed(std::random_device()());
              firstname = database["male_firstnames"][randi(rng)].as<std::string>();
            } else {
              // Female firstnames
              randi = RandomInt(0, database["female_firstnames"].size() - 1);
              rng.seed(std::random_device()());
              firstname = database["female_firstnames"][randi(rng)].as<std::string>();
            }
          } while(firstname == entrant->firstname);
          break;
        case 1:
          // Lastnames
          do {
            randi = RandomInt(0, database["lastnames"].size() - 1);
            rng.seed(std::random_device()());
            lastname = database["lastnames"][randi(rng)].as<std::string>();
          } while(lastname == entrant->lastname);
          break;
        case 2:
          // Sex
          if (entrant->sex == MALE) {
            sex = FEMALE;
          } else {
            sex = MALE;
          }
        case 3:
          // Country
          do {
            randi = RandomInt(0, database["countries"].size() - 1);
            rng.seed(std::random_device()());
            country = database["countries"][randi(rng)].as<std::string>();
          } while(country == entrant->country);
          break;
        case 4:
          // City
          do {
            randi = RandomInt(0, database["cities"][country].size() - 1);
            rng.seed(std::random_device()());
            city = database["cities"][country][randi(rng)].as<std::string>();
          } while(city == entrant->city);
          break;
        case 5:
          // Height
          do {
            rng.seed(std::random_device()());
            randi = RandomInt((int) (database["min_height"].as<float>() * 100),
              (int) (database["max_height"].as<float>() * 100));
            height = (randi(rng) / (float) 100);
          } while(height == entrant->height);
          break;
        case 6:
          // Weight
          do {
            rng.seed(std::random_device()());
            randi = RandomInt((int) (database["min_weight"].as<float>() * 100),
              (int) (database["max_weight"].as<float>() * 100));
            weight = randi(rng);
          } while(weight == entrant->weight);
          break;
        case 7:
          {
            // Picture
            do {
              rng.seed(std::random_device()());
              randi = RandomInt(0, 1);
              if (randi(rng) == 1) {
                randi = RandomInt(0, database["male_hair"].size() - 1);
                rng.seed(std::random_device()());
                hair = database["male_hair"][randi(rng)].as<std::string>();
              } else {
                randi = RandomInt(0, database["female_hair"].size() - 1);
                rng.seed(std::random_device()());
                hair = database["female_hair"][randi(rng)].as<std::string>();
              }
            } while(hair == entrant->pic.hair);
            do {
              randi = RandomInt(0, database["facial_hair"].size() - 1);
              rng.seed(std::random_device()());
              facial_hair = database["facial_hair"][randi(rng)].as<std::string>();
            } while(facial_hair == entrant->pic.facial_hair);
            do {
              randi = RandomInt(0, database["vision"].size() - 1);
              rng.seed(std::random_device()());
              vision = database["vision"][randi(rng)].as<std::string>();
            } while(vision == entrant->pic.vision);
            do {
              randi = RandomInt(0, database["other"].size() - 1);
              rng.seed(std::random_device()());
              other = database["other"][randi(rng)].as<std::string>();
            } while(other == entrant->pic.other);
            break;
          }
      }
      // Update invalid fields
      invalid_fields--;
      if (invalid_fields == 0) {
        illegal = false;
      }
    }

    picture = Picture(hair, facial_hair, vision, other);

    return (new IDCard(picture, firstname, lastname, sex, date_of_birth,
      country, city, height, weight));
}

AccessPermit* PEG::new_accesspermit(YAML::Node database, Entrant* entrant,
  Passport* passport, bool illegal, int& invalid_fields) {
    // Random variables
    std::mt19937 rng;
    RandomInt randi;

    // Physical appearance
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

    // Entrant's data
    std::string passport_number = passport->passport_number;
    std::string firstname = entrant->firstname;
    std::string lastname = entrant->lastname;
    float height = entrant->height;
    unsigned int weight = entrant->weight;
    std::string country = entrant->country;
    std::string purpose = entrant->purpose;
    // M.O.A. Stamp
    randi = RandomInt(0, database["valid_moa_stamps"].size() - 1);
    rng.seed(std::random_device()());
    std::string moa_stamp = database["valid_moa_stamps"][randi(rng)].as<std::string>();
    // Expiration date
    time_t dmin = 406944000;
    time_t dmax = 473299200;
    randi = RandomInt(dmin, dmax);
    time_t gd = randi(rng);
    struct tm* tm = localtime(&gd);
    Date expiration_date(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    // Physical appearance
    randi = RandomInt(0, pa.size() - 1);
    rng.seed(std::random_device()());
    std::string physical_appearance = pa[randi(rng)];
    // Duration
    unsigned int duration;
    if (purpose == "Visit") {
      int dmin = 14;
      int dmax = 90;
      randi = RandomInt(dmin, dmax);
      duration = randi(rng);
    }
    if (purpose == "Transit") {
      int dmin = 2;
      int dmax = 14;
      randi = RandomInt(dmin, dmax);
      duration = randi(rng);
    }
    if (purpose == "Work") {
      int dmin = 30;
      int dmax = 180;
      randi = RandomInt(dmin, dmax);
      duration = randi(rng);
    }

    // If the entrant is illegal
    if (illegal) {
      randi = RandomInt(0, 9);
      rng.seed(std::random_device()());
      switch (randi(rng)) {
        case 0:
          // Passport number
          do {
            char s[10];
            static const char alphanum[] =
              "0123456789"
              "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            for (int i = 0; i < 10; ++i) {
              s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
            }
            passport_number = std::string(s);
          } while(passport_number == passport->passport_number);
          break;
        case 1:
          {
            // M.O.A. Stamp
            randi = RandomInt(0, database["forged_moa_stamps"].size() - 1);
            rng.seed(std::random_device()());
            std::string moa_stamp = database["forged_moa_stamps"][randi(rng)].as<std::string>();
            break;
          }
        case 2:
          {
            // Expiration date
            time_t dmin = 86400;
            time_t dmax = 604800;
            randi = RandomInt(dmin, dmax);
            time_t gd = 406944000 - randi(rng);
            struct tm* tm = localtime(&gd);
            expiration_date = Date(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
            break;
          }
        case 3:
          // Physical appearance
          do {
            rng.seed(std::random_device()());
            randi = RandomInt(0, 4);
            switch (randi(rng)) {
              case 0:
                randi = RandomInt(0, database["male_hair"].size() - 1);
                rng.seed(std::random_device()());
                physical_appearance = database["male_hair"][randi(rng)].as<std::string>();
                break;
              case 1:
                randi = RandomInt(0, database["female_hair"].size() - 1);
                rng.seed(std::random_device()());
                physical_appearance = database["female_hair"][randi(rng)].as<std::string>();
                break;
              case 2:
                randi = RandomInt(0, database["facial_hair"].size() - 1);
                rng.seed(std::random_device()());
                physical_appearance = database["facial_hair"][randi(rng)].as<std::string>();
                break;
              case 3:
                randi = RandomInt(0, database["vision"].size() - 1);
                rng.seed(std::random_device()());
                physical_appearance = database["vision"][randi(rng)].as<std::string>();
                break;
              case 4:
                randi = RandomInt(0, database["other"].size() - 1);
                rng.seed(std::random_device()());
                physical_appearance = database["other"][randi(rng)].as<std::string>();
                break;
            }
          } while(std::find(pa.begin(), pa.end(), physical_appearance) != pa.end());
          break;
        case 4:
          // Firstname
          do {
            // Random invalid firstname
            rng.seed(std::random_device()());
            randi = RandomInt(0, 1);
            if (randi(rng) == 1) {
              // Male firstnames
              randi = RandomInt(0, database["male_firstnames"].size() - 1);
              rng.seed(std::random_device()());
              firstname = database["male_firstnames"][randi(rng)].as<std::string>();
            } else {
              // Female firstnames
              randi = RandomInt(0, database["female_firstnames"].size() - 1);
              rng.seed(std::random_device()());
              firstname = database["female_firstnames"][randi(rng)].as<std::string>();
            }
          } while(firstname == entrant->firstname);
          break;
        case 5:
          // Lastnames
          do {
            randi = RandomInt(0, database["lastnames"].size() - 1);
            rng.seed(std::random_device()());
            lastname = database["lastnames"][randi(rng)].as<std::string>();
          } while(lastname == entrant->lastname);
          break;
        case 6:
          // Height
          do {
            rng.seed(std::random_device()());
            randi = RandomInt((int) (database["min_height"].as<float>() * 100),
              (int) (database["max_height"].as<float>() * 100));
            height = (randi(rng) / (float) 100);
          } while(height == entrant->height);
          break;
        case 7:
          // Weight
          do {
            rng.seed(std::random_device()());
            randi = RandomInt((int) (database["min_weight"].as<float>() * 100),
              (int) (database["max_weight"].as<float>() * 100));
            weight = randi(rng);
          } while(weight == entrant->weight);
          break;
        case 8:
          // Country
          do {
            randi = RandomInt(0, database["countries"].size() - 1);
            rng.seed(std::random_device()());
            country = database["countries"][randi(rng)].as<std::string>();
          } while(country == entrant->country);
          break;
        case 9:
          // Purpose
          do {
            randi = RandomInt(0, database["purpose"].size() - 1);
            rng.seed(std::random_device()());
            purpose = database["purpose"][randi(rng)].as<std::string>();
          } while(purpose == entrant->purpose);
          break;
      }
      // Update invalid fields
      invalid_fields--;
      if (invalid_fields == 0) {
        illegal = false;
      }
    }

    return (new AccessPermit(firstname, lastname, moa_stamp, country, passport_number,
      purpose, duration, height, weight, expiration_date, physical_appearance));
}

WorkPass* PEG::new_workpass(YAML::Node database, Entrant* entrant,
  AccessPermit* accesspermit, bool illegal, int& invalid_fields) {
    // Random variables
    std::mt19937 rng;
    RandomInt randi;

    // Work end date
    time_t tend = 406944000;
    struct tm* tm = localtime(&tend);
    tm->tm_mday += accesspermit->duration;
    Date end(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);

    // Work field
    randi = RandomInt(0, database["works"].size() - 1);
    rng.seed(std::random_device()());
    std::string field = database["works"][randi(rng)].as<std::string>();

    // M.O.L. tamp
    randi = RandomInt(0, database["valid_mol_stamps"].size() - 1);
    rng.seed(std::random_device()());
    std::string mol_stamp = database["valid_mol_stamps"][randi(rng)].as<std::string>();

    // If the entrant is illegal
    if (illegal) {
      // M.O.L. stamp
      randi = RandomInt(0, database["forged_mol_stamps"].size() - 1);
      rng.seed(std::random_device()());
      mol_stamp = database["forged_mol_stamps"][randi(rng)].as<std::string>();
      // Update invalid fields
      invalid_fields--;
      if (invalid_fields == 0) {
        illegal = false;
      }
    }

    return (new WorkPass(entrant->firstname, entrant->lastname, field, mol_stamp, end));
}
