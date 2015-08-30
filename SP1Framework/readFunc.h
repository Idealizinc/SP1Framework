#ifndef _READFUNC_H
#define _READFUNC_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::getline;
using std::ifstream;
using std::vector;

void readMap(string str,char mapArray[22][79]);
void readPortal(string str,char screenArray[25][79]);
void readBattleScreen(string str,char battleArray[20][79]);	
void readBattleScreen2(string str,char battleArrayALT[20][79]);
void readBossScreen(string str,char bossArray[20][79]);			// Read Boss Screen 1
void readBossScreen2(string str,char bossArrayALT[20][79]);			// Read Boss Screen 2
void readGameOver(string str,char ggArray[25][79]);		// reads the gameover in a txt file.
void readLoadScreen(string str,char loadScrnArray[25][79]);
void readMenu(string str,char menuArray[22][79]);

#endif