#ifndef _RENDFUNC_H
#define _RENDFUNC_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "game.h"
using std::string;
using std::getline;
using std::ifstream;
using std::vector;

void renderPrintedText(char toBePrinted ,int j,int i );
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderSelection();
void animateBSNorm();		// swaps between and prints diff battle screens.
void animateBSBoss();		// same As Above Just For Boss Fights
void portalrender();        // renders the portal.
void renderGameOver();      // renders Game Over screen.
void printMapStats();       // stats of player
void printBattleStats();    // stats of enemy and player.
void printChestReward();    // shows bonus of the player.
void printFakeChestInfo();  // prints details of fake chest.
void portalrender();        // renders the portal.
void isReadDataNeeded();
void drawMap();             // draws the game map.
void drawMapRendChar();
void drawBattleScreen();
void drawBattleScreenALT();
void drawBattleScreenBoss();
void drawBattleScreenBossALT();
void renderLoadScreen();
void drawMenu();
void renderTutorialScreen();
void drawBattleScreen2();
void drawBattleScreen2ALT();
void drawBattleScreenBoss();
void drawEndBattleScreen();

#endif