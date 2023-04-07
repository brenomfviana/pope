# Pope

## Description

Pope is a bot created to play a simplified version of the game "Papers, Please". In this version the player has to evaluate the entrant's papers (passport, ID card, access permit and work pass) and decide whether or not the immigrant will be allowed entry. The rules for the entry of entrants are: all documents must be current; arstotzkan citizens must have an ID card; foreigners require an access permit; and workers must have a work pass.

For each correctly classified entrant the player earns five credits. However, when the player makes a wrong decision (by approving an illegal entrant or disapproving a legal one), he receives a warning stating the mistake. Starting by the third mistake, the player will be punished with a five credits penalty, for each mistake, from his payment of the day. A player loses (be arrested) the game when: the player has a negative balance at the end of the day; the investigator discovers that the player has illegal savings; or the player is delinquent in serving immigrants (making many wrong decisions).

This is a work from the Artificial Intelligence course and the bot was developed using Decision Tree Learning (DTL). The name of this AI was given in honor of the game creator Lucas Pope.

> NOTE: It is a simulator. There is no human player mode in this game.

## Dependencies

- C++11
- [yaml-cpp 0.6.0](https://github.com/jbeder/yaml-cpp)

## How to compile

Use the ```make``` command to compile the project.

## How to use

To create a new dataset use the following command:

```bash
./pope -pcg <number-of-entrants>
```

To run the game and test the Pope bot use the following command:

```bash
./pope -r <path-of-training-data>
```

## Results

### Training Datasets

| Dataset name | Total Entrants | Legal Entrants | Illegal Entrants |
|:------------:|:--------------:|:--------------:|:----------------:|
| T. Dataset 1 |             50 |             26 |               24 |
| T. Dataset 2 |            100 |             49 |               51 |
| T. Dataset 3 |            200 |             87 |              113 |
| T. Dataset 4 |            400 |            114 |              286 |

### Datasets

| Dataset name | Total Entrants | Legal Entrants | Illegal Entrants |
|:------------:|:--------------:|:--------------:|:----------------:|
|    Dataset 1 |            500 |            205 |              295 |
|    Dataset 2 |           1000 |            547 |              453 |

### Success Rate of Dataset 1

| Tree Depth |   50  |   100 |   200 |   400 |
|:----------:|:-----:|:-----:|:-----:|:-----:|
|          6 | 0.544 | 0.530 | 0.532 | 0.546 |
|         15 | 0.954 | 0.838 | 0.832 | 0.862 |
|         22 |    1  |     1 |     1 |     1 |

### Success Rate of Dataset 2

| Tree Depth |   50  |   100 |   200 |   400 |
|:----------:|:-----:|:-----:|:-----:|:-----:|
|          6 | 0.623 | 0.641 | 0.633 | 0.650 |
|         15 | 0.964 | 0.873 | 0.874 | 0.871 |
|         22 | 0.999 | 0.999 | 0.999 | 0.999 |

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
