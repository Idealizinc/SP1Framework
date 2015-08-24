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

enum Keys
{
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

void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void readBattleScreen();    // first frame of animation
void readBattleScreen2();   // second frame of animation
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void readMap();             // reads the map in a txt file.
void chest();               // states what happens when player steps on chest.
void readPortal();          // Changes stage when player completes current stage.
void portalrender();        // renders the portal.




struct Monster
{
	int healthPoints;
	unsigned int damage;
	unsigned int level;
};
#endif // _GAME_H