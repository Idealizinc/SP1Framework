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
#include "rendFunc.h"
#include "readFunc.h"

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
	G_MainMenu,
	G_Tutorial,
	G_Options,
	G_Difficulty,
	G_StoryScreen,
	G_Stage1,
	G_Stage2,
	G_Stage3,
	G_Stage4,
	G_Stage5,
	G_Stage6,
	G_StageCleared,
	G_GameOver,
	G_GameCleared,
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
void checkPlayerAnswer();
void createQuestion();

//Rendering
void drawMenu();

//Reading
void getReadData(int val);                  // reads txt files based on stage.

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
    int level;
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