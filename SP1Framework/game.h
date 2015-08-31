#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "detectionFunc.h"
extern StopWatch g_timer;
extern bool g_quitGame;

using std::string;
using std::getline;
using std::ifstream;
using std::vector;
enum Keys
{
	K_0,
	K_1,
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_7,
	K_8,
	K_9,
	K_W,
	K_A,
	K_S,
	K_D,
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
	K_DASH,
    K_ESCAPE,
	K_ENTER,
	K_BACKSPACE,
	K_SPACE,
	K_COUNT
};

// Stage Changing.
enum GameStates
{
	G_Intro,
	G_MainMenu,
	G_Tutorial,
	G_Options,
	G_LoadScreen,
	G_Stage1,
	G_Stage2,
	G_Stage3,
	/*G_Stage4,
	G_Stage5,
	G_Stage6,*/
	G_StageCleared,
	G_GameOver,
    G_EndCount
};
//organising



void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

void numberinput();         // gets the number
void moveCharacter();       // moves the character, collision detection, physics, etc
void checkMove();           // checks the path it took. collision detection, physics, etc
void monsterCheck();        // checks for monster
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 

//Rendering
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void animateBSNorm();		// swaps between and prints diff battle screens.
void animateBSBoss();		// same As Above Just For Boss Fights
void portalrender();        // renders the portal.
void printMapStats();       // stats of player
void printBattleStats();    // stats of enemy and player.
void printChestReward();    // shows bonus of the player.
void portalrender();        // renders the portal.
void renderGameOver();      // renders Game Over screen.
void drawMap();             // draws the game map.
void drawMapRendChar();     // draws the character on map.
void printFakeChestInfo();  // prints details of fake chest.
void animateLoading();
void renderLoadScreen();
void renderSelection();		// Decides what is to be rendered
void drawMenu();
void renderTutorialScreen();

//Reading
//void readMap(string str);					// reads the map in a txt file.
//void readPortal();							// Changes stage when player completes current stage.
//void readBattleScreen(string str);		    // first frame of animation
//void readBattleScreen2(string str);			// second frame of animation
//void readBossScreen(string str);			// Read Boss Screen 1
//void readBossScreen2(string str);			// Read Boss Screen 2
//void readGameOver();						// reads the gameover in a txt file.
void getReadData(int val);                  // reads txt files based on stage.
//void readLoadScreen(string str,char loadScrnArray[25][79]);

//Detection
//void bossFightCheck();		            // Checks if player is on boss.
//void initiallizePlayerStats();          // player initial stats
//void setPlayerChangableStats();         // player changable stats
//void initiallizeMonsterStats();         // monster initial stats
//void setMonsterChangableStats();        // monster changable stats
//void checklevelup();                    // player level up.
//void changeplayerstats();               // change player stats

//Struct name of the player.
struct Hero
{
	int hp;
	int level;
    int expCap;
	int damage;
    int chance;
	int exp;
};

//Struct name of the boss.
struct Boss
{
	int hp;
	int damage;
	int expgiven;
};

//Struct name of monsters.
struct Monster
{
	int level;
	int hp;
	int damage;
	int expgiven;
};
#endif // _GAME_H