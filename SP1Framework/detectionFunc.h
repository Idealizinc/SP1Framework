#ifndef _DETECTIONFUNC_H
#define _DETECTIONFUNC_H

#include "Framework\timer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "game.h"

void bossFightCheck();
void chestOpen();                       // states what happens when player steps on chest. opens the map
void initiallizePlayerStats();          // player initial stats
void setPlayerChangableStats();         // player changable stats
void initiallizeMonsterStats();         // monster initial stats
void setMonsterChangableStats();        // monster changable stats
void checkLevelUp();                    // player level up.
void changePlayerStats();               // change player stats

#endif