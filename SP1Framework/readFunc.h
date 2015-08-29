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


#endif