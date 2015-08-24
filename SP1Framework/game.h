#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>    

extern StopWatch g_timer;
extern bool g_quitGame;

using std::string;
using std::getline;
using std::ifstream;
using std::vector;
enum Keys
{
	K_ENTER,
	K_BACKSPACE,
	K_1,
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_7,
	K_8,
	K_9,
	K_0,
	K_NUM1,
	K_NUM2,
	K_NUM3,
	K_NUM4,
	K_NUM5,
	K_NUM6,
	K_NUM7,
	K_NUM8,
	K_NUM9,
	K_NUM0,
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_COUNT
};

// Stage Changing.
enum stage
{
    STAGE1 = 1,
    STAGE2,
    STAGE3,
    STAGE4,
};

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

void numberinput();         // gets the number LOLOLLOLLOL
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 

//Rendering
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void animateBSNorm();		//Swaps between and prints diff battle screens.
void animateBSBoss();		//Same As Above Just For Boss Fights
void portalrender();        // renders the portal.

//Reading
void readMap();             // reads the map in a txt file.
void readPortal();          // Changes stage when player completes current stage.
void readBattleScreen();    // first frame of animation
void readBattleScreen2();   // second frame of animation
void readBossScreen();		// Read Boss Screen 1
void readBossScreen2();		// Read Boss Screen 2

//Detection
void bossFightCheck();		// Checks if player is on boss.
void chest();               // states what happens when player steps on chest.



struct Monster
{
	int healthPoints;
	unsigned int damage;
	unsigned int level;
};
#endif // _GAME_H