#ifndef _READFUNC_H
#define _READFUNC_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "game.h"
#include "Framework\console.h"
using std::string;
using std::getline;
using std::ifstream;
using std::vector;

void readMap(string str,char mapArray[22][78]);
void readPortal(string str,char screenArray[25][78]);
void readBattleScreen(string str,char battleArray[20][78]);	
void readBattleScreen2(string str,char battleArrayALT[20][78]);
void readBossScreen(string str,char bossArray[20][78]);			// Read Boss Screen 1
void readBossScreen2(string str,char bossArrayALT[20][78]);			// Read Boss Screen 2
void readGameOver(string str,char ggArray[25][78]);		// reads the gameover in a txt file.
void readLoadScreen(string str,char loadScrnArray[25][78]);
void readMenu(string str,char menuArray[22][78]);
void readTutorial(string str,char instructionArray[22][78]);
void readOptionsMenu(string str,char optionArray[22][78]);
void read2ndBattleScreen(string str,char battleArray2[20][78]);	
void read2ndBattleScreen2(string str,char battleArray2ALT[20][78]);
void readEndBattleStats(string str,char endBattleArray[25][78]);
void readGameCleared(string str,char gameClearedArray[25][78]);

#endif