// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "monsterEncounter.h"
#include "readFunc.h"

// Console object
Console console(78, 25, "<Superino Goliatho>");

//Time elapsed
double elapsedTime;                     //Elapsed time of the game
double deltaTime;

//Storage
bool keyPressed[K_COUNT];
char mapArray[22][78];
char battleArray[20][78];
char battleArrayALT[20][78];
char bossArray[20][78];
char bossArrayALT[20][78];
char screenArray[25][78];
char ggArray[25][78];
char instructionArray[25][78];
char battleArray2[20][78];
char battleArray2ALT[20][78];
char endBattleArray[25][78];
char optionArray[25][78];
char gameClearedArray[25][78];
char difficultysetArray[25][78];
char storyArray[25][78];

//Impt Variables
int xSpawnCoord = 0, ySpawnCoord = 0;
int xGateCoord = 0, yGateCoord = 0;
int xReturnCoord, yReturnCoord;
bool renderedChar = false;
int playerxp = 0;
int playerlv = 100;
int numberOfTries = 4;

//ENABLE PLAYER ENCOUNTER
bool randomEncountersOn = true; // SET TO TRUE LATER

//Read Values
string normal_Monster1;     //store first frame of monster txt
string normal_Monster1ALT;  //store second frame of monster txt
string normal_Monster2;     //store first frame of another monster txt
string normal_Monster2ALT;  //store second frame of another monster txt
string boss_Monster1;       //store first frame of boss txt
string boss_Monster1ALT;    //store second frame of boss txt
string stage_Map;           //store stage level.

//Game State
double loadTimer;
bool loading = false;
GameStates currState = G_MainMenu;
int playerchoice = 1;
bool mainMenu = false;
char menuArray[25][78];
bool hpInitiallized = false;

//For Battle Scrn & Battle Anim 
//Movement and Detection
bool playerInputOn = true;      // toggles movement of player.
bool battleModeOn = false;      // when true, loads battle screen
bool inBossFight = false;       // toggles inboss fight screen.
bool bossCleared = false;       // when boss cleared, won't meet again.
bool mobDown = false;			// Check when monster dies
unsigned int difficultySet = 1; //Difficulty of game
bool onlever = false;			// Set to FALSE, For Levers in game
bool atPortal = false;			//Set To FALSE, For moving to next level
bool limiterSet = false;        // prevents players from input value multi time
int currAtStage = 0;            // current stage level
bool playerDead = false;		// For Gameover screen

//Battle
int answerIsDifferent;          // check if player ans is diff.
string battleAnswer;            // holds value of player ans.
bool initializeHP = false;      // To initialise monster/boss HP
bool selectionMade = false;		// Checks which monster to spawn
int selection;					// Chooses which monster to spawn
double waitTime = 0.085;         // waiting time for inputing value.
bool allowEnemyAttk = false;    // enemy to attack.
bool enemyAttkTime = false;
double attkTime;                // Attkspeed of enemy
double enemyAttk = 10.00;        // player to attk.
bool allowNumInput = true;      // player's num input
int randomNo1;                  // random number for first value
int randomNo2;                  // random number for second value
int DrandomNo1;
int DrandomNo2;
int DrandomNo3;

//Stats of player and monsters
Hero player;					
Monster MonsterUnit;
Boss BossUnit;
int charHP, HP, foeHP, foeLVL, limitEXP, Damage, Damage2, monsterXP, monsterHP;

//Animation
bool animate = true;            // toggles between two frames.
bool animate2 = true;           // toggles between two frames.
bool locationSaved =  false;    // saves player location upon battle.

//For Battle Systems
bool playerInputted = false;    // check if player got put answer.
bool questionMade = false;      // creates question only when answered.
int playerDmg;                  // player dmg
double storedTime;              // the value of the stored time.
int randomsign;                 // random sign symbols (not coded)
string answer;                  //answer of player inputted.
int stageVal = 21;              //Random unrelated value


//Status
int status = 0;


// Game specific variables here
COORD charLocation;
WORD playercolour = 0x7F;


// Initialize variables, allocate memory, load data from file, etc. 
// This is called once before entering into your main loop
void init()
{
    // Set precision for floating point output
    elapsedTime = 0.0;
	readPortal("TextFiles/endscreen.txt",screenArray);
    readGameOver("TextFiles/gameover.txt",ggArray);
	readMenu("TextFiles/menuScreen.txt", menuArray);
	readTutorial("TextFiles/controls.txt", instructionArray);
	readOptionsMenu("TextFiles/optionScreen.txt", optionArray);
	readEndBattleStats("TextFiles/endBattleScreen.txt", endBattleArray);
	readGameCleared("TextFiles/gameCleared.txt", gameClearedArray);
	readDifficulty( "TextFiles/settingScreen.txt", difficultysetArray);
	readStoryScreen( "TextFiles/storyScreen.txt", storyArray);


    charLocation.X = console.getConsoleSize().X / 2;
    charLocation.Y = console.getConsoleSize().Y / 2;
    // sets the width, height and the font name to use in the console
	//console.setConsoleFont(0, 20, L"Consolas"); //For Testing if you're lazy to reset size every time
	console.setConsoleFont(0, 20, L"RASTER FONTS"); // Set console dimensions to 12 x 16
}

// Do your clean up of memory here
// This is called once just before the game exits

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    console.clearBuffer();
}
/*
	This function checks if any key had been pressed since the last time we checked
	If a key is pressed, the value for that particular key will be true
	
	Add more keys to the enum in game.h if you need to detect more keys
	To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
	For Alphanumeric keys, the values are their ascii values (uppercase).
*/
void getInput()
{   
	if (playerInputOn == true)
	{
		keyPressed[K_UP] = isKeyPressed(VK_UP) || isKeyPressed(0x57);
		keyPressed[K_DOWN] = isKeyPressed(VK_DOWN) || isKeyPressed(0x53);
		keyPressed[K_LEFT] = isKeyPressed(VK_LEFT) || isKeyPressed(0x41);
		keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT) || isKeyPressed(0x44);
	}

		keyPressed[K_1] = ( isKeyPressed(0x31) || isKeyPressed(VK_NUMPAD1));
		keyPressed[K_2] = ( isKeyPressed(0x32) || isKeyPressed(VK_NUMPAD2));
		keyPressed[K_3] = ( isKeyPressed(0x33) || isKeyPressed(VK_NUMPAD3));
		keyPressed[K_4] = ( isKeyPressed(0x34) || isKeyPressed(VK_NUMPAD4));
		keyPressed[K_5] = ( isKeyPressed(0x35) || isKeyPressed(VK_NUMPAD5));
		keyPressed[K_6] = ( isKeyPressed(0x36) || isKeyPressed(VK_NUMPAD6));
		keyPressed[K_7] = ( isKeyPressed(0x37) || isKeyPressed(VK_NUMPAD7));
		keyPressed[K_8] = ( isKeyPressed(0x38) || isKeyPressed(VK_NUMPAD8));
		keyPressed[K_9] = ( isKeyPressed(0x39) || isKeyPressed(VK_NUMPAD9));
		keyPressed[K_0] = ( isKeyPressed(0x30) || isKeyPressed(VK_NUMPAD0));

		keyPressed[K_DASH] = ( isKeyPressed(VK_OEM_MINUS) || isKeyPressed(VK_SUBTRACT) );
		keyPressed[K_BACKSPACE] = isKeyPressed(VK_BACK);
		keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
		keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
		keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

/*
	This is the update function
	double dt - This is the amount of time in seconds since the previous call was made

	Game logic should be done here.
	Such as collision checks, determining the position of your game characters, status updates, etc
	If there are any calls to write to the console here, then you are doing it wrong.

    If your game has multiple states, you should determine the current state, and call the relevant function here.
*/

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
    // sound can be played here too.
}

void isReadDataNeeded()
{
	if (currAtStage != stageVal)
	{
		getReadData(currAtStage);
		stageVal = currAtStage;
		initiallizeMonsterStats();
		setPlayerChangableStats();
		setMonsterChangableStats();
	}
	if (hpInitiallized == false)
	{
		initiallizePlayerStats();
        initiallizeMonsterStats();
		hpInitiallized = true;
	}
}

void getReadData(int val)
{
	switch (val)
	{
		case 1:	normal_Monster1 = "TextFiles/MOB_DEVIL1.txt";
				normal_Monster1ALT = "TextFiles/MOB_DEVIL2.txt";
				normal_Monster2 = "TextFiles/MOB_CAT1.txt";
				normal_Monster2ALT = "TextFiles/MOB_CAT2.txt";
				boss_Monster1 = "TextFiles/MOB_BAT1.txt"; 
				boss_Monster1ALT = "TextFiles/MOB_BAT2.txt";
				stage_Map = "TextFiles/Map1.txt";
				break;
		case 2:	normal_Monster1 = "TextFiles/MOB_BAT1.txt";
				normal_Monster1ALT = "TextFiles/MOB_BAT2.txt";
				normal_Monster2 = "TextFiles/MOB_DEVIL1.txt";
				normal_Monster2ALT = "TextFiles/MOB_DEVIL2.txt";
				boss_Monster1 = "TextFiles/MOB_Spider1.txt"; 
				boss_Monster1ALT = "TextFiles/MOB_Spider2.txt";
				stage_Map = "TextFiles/Map2.txt";
				break;
		case 3:	normal_Monster1 = "TextFiles/MOB_BAT1.txt";
				normal_Monster1ALT = "TextFiles/MOB_BAT2.txt";
				normal_Monster2 = "TextFiles/MOB_Spider1.txt";
				normal_Monster2ALT = "TextFiles/MOB_Spider2.txt";
				boss_Monster1 = "TextFiles/MOB_SLIME1.txt"; 
				boss_Monster1ALT = "TextFiles/MOB_SLIME2.txt";
				stage_Map = "TextFiles/Map3.txt";
				break;
		case 4:	normal_Monster1 = "TextFiles/MOB_DEVIL1.txt";
				normal_Monster1ALT = "TextFiles/MOB_DEVIL2.txt";
				normal_Monster2 = "TextFiles/MOB_SLIME1.txt";
				normal_Monster2ALT = "TextFiles/MOB_SLIME2.txt";
				boss_Monster1 = "TextFiles/MOB_ZOMBIE1.txt"; 
				boss_Monster1ALT = "TextFiles/MOB_ZOMBIE2.txt";
				stage_Map = "TextFiles/Map4.txt";
				break;
		case 5:	normal_Monster1 = "TextFiles/MOB_ZOMBIE1.txt";
				normal_Monster1ALT = "TextFiles/MOB_ZOMBIE2.txt";
				normal_Monster2 = "TextFiles/MOB_Spider1.txt";
				normal_Monster2ALT = "TextFiles/MOB_Spider2.txt";
				boss_Monster1 = "TextFiles/MOB_REAPER1.txt";
				boss_Monster1ALT = "TextFiles/MOB_REAPER2.txt";
				stage_Map = "TextFiles/Map5.txt";
				break;
		case 6:	normal_Monster1 = "TextFiles/MOB_REAPER1.txt";
				normal_Monster1ALT = "TextFiles/MOB_REAPER2.txt";
				normal_Monster2 = "TextFiles/MOB_ZOMBIE1.txt";
				normal_Monster2ALT = "TextFiles/MOB_ZOMBIE2.txt";
				boss_Monster1 = "TextFiles/MOB_JEDRIC.txt";
				boss_Monster1ALT = "TextFiles/MOB_JEDRIC2.txt";
				stage_Map = "TextFiles/Map6.txt";
				break;
	}
	readMap(stage_Map,mapArray);
	readBattleScreen(normal_Monster1,battleArray);
	readBattleScreen2(normal_Monster1ALT,battleArrayALT);
	read2ndBattleScreen(normal_Monster2,battleArray2);
	read2ndBattleScreen2(normal_Monster2ALT,battleArray2ALT);
	readBossScreen(boss_Monster1,bossArray);
	readBossScreen2(boss_Monster1ALT,bossArrayALT);
}

/*
    This is the render loop
    At this point, you should know exactly what to draw onto the screen.
    Just draw it!
    To get an idea of the values for colours, look at console.h and the URL listed there
*/
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
	switch(currState)
	{
		case G_MainMenu: mainMenu = true; renderSelection(); break;
		case G_Tutorial: renderTutorialScreen(); break;
		case G_Options: renderOptionsMenu(); break;	//Implemented Later
		case G_Difficulty: renderdifficultyset(); currAtStage = 0; break;
		case G_StoryScreen: loading = true; renderStoryScreen(); break;
		case G_Stage1: currAtStage = 1; drawMapRendChar(); break;
		case G_Stage2: currAtStage = 2; drawMapRendChar(); break;
		case G_Stage3: currAtStage = 3; drawMapRendChar(); break;
		case G_Stage4: currAtStage = 4; drawMapRendChar(); break;
		case G_Stage5: currAtStage = 5; drawMapRendChar(); break;
		case G_Stage6: currAtStage = 6; drawMapRendChar(); break;
		case G_StageCleared: renderStoryScreen(); break;
		case G_GameCleared: renderGameClear(); break;
		case G_GameOver: renderGameOver(); break; 
		
	}
	 // renders the character into the buffer
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
	
}

void moveCharacter()
{
	checkMove();
	chestOpen();
	bossFightCheck();
	leverpull();
}

void checkMove()
{
	int Y = charLocation.Y;
	int X = charLocation.X;

	if ((keyPressed[K_UP] || keyPressed[K_W]) && charLocation.Y > 0)
	{
		if ((mapArray[Y - 1][X] != 'W') && (mapArray[Y - 1][X] != '1') &&
			(mapArray[Y - 1][X] != 'T') && (mapArray[Y - 1][X] != 'D') && 
			(mapArray[Y - 1][X] != 'Z') && (mapArray[Y - 1][X] != 'M'))
		{
			charLocation.Y--;
			monsterCheck();
		}
	}

	else if ((keyPressed[K_LEFT] || keyPressed[K_A]) && charLocation.X > 0)
	{
		if ((mapArray[Y][X - 1] != 'W') && (mapArray[Y][X - 1] != '1') &&
			(mapArray[Y][X - 1] != 'T') && (mapArray[Y][X - 1] != 'D') && 
			(mapArray[Y][X - 1] != 'Z') && (mapArray[Y][X - 1] != 'M'))
		{
			charLocation.X--;
			monsterCheck();
		}
	}
	else if ((keyPressed[K_DOWN] || keyPressed[K_S]) && charLocation.Y < console.getConsoleSize().Y - 1)
	{
		if ((mapArray[Y + 1][X] != 'W') && (mapArray[Y + 1][X] != '1') &&
			(mapArray[Y + 1][X] != 'T') && (mapArray[Y + 1][X] != 'D') && 
			(mapArray[Y + 1][X] != 'Z') && (mapArray[Y + 1][X] != 'M'))
		{
			charLocation.Y++;
			monsterCheck();
		}
	}
	else if ((keyPressed[K_RIGHT] || keyPressed[K_D]) && charLocation.X < console.getConsoleSize().X - 1)
	{
		if ((mapArray[Y][X + 1] != 'W') && (mapArray[Y][X + 1] != '1') &&
			(mapArray[Y][X + 1] != 'T') && (mapArray[Y][X + 1] != 'D') && 
			(mapArray[Y][X + 1] != 'Z') && (mapArray[Y][X + 1] != 'M'))
		{
			charLocation.X++;
			monsterCheck();
		}
	}
	if (mapArray[Y][X] == 'E')
	{
		atPortal = true;
	}
}

void monsterCheck()
{
	int monster;
	monster = encounterCheck();
	if ((monster != 0) && (randomEncountersOn == true))
	{
		battleModeOn = true;
	}
	if (inBossFight == true)
	{
		battleModeOn = false;
	}
}

void processUserInput()
{
    //quits the game if player hits the escape key
 //   if (keyPressed[K_ESCAPE])
 //   {
	//	g_quitGame = true;
	//}
}

void numberinput()
{
	if (allowNumInput == false)
	{
		if (limiterSet == false)
		{
			storedTime = elapsedTime + waitTime;
			limiterSet = true;
			if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
			{
				storedTime += 0.5;
			}

		}
		if (elapsedTime >= storedTime)
		{
			allowNumInput = true;
			limiterSet = false;
		}
	}
	if (allowNumInput == true)
	{
		
		for (unsigned int i = K_0; i <= K_9 ; i++ )
		{
			if ( (keyPressed[i]) )
			{
				answer += ( 48 + i );
				allowNumInput = false;
			}
		}
		if (keyPressed[K_DASH])
		{
			answer += "-";
			allowNumInput = false;
		}
		if ((keyPressed[K_BACKSPACE]) && (answer.length() > 0))
		{
			answer.erase(answer.length() - 1 );
			allowNumInput = false;
		}

		else if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
		{
			if ( answer.compare(battleAnswer) == 0 )
			{
				answerIsDifferent = false;
				playerInputted = true;
			}
			else if ( answer.compare(battleAnswer) != 0 )
			{
				answerIsDifferent = true;
				playerInputted = true;
			}
			answer.erase();
			questionMade = false;
			allowNumInput = false;
		}
	}
	//Print Player's Answer
	COORD d;
	d.X = 24;
	d.Y = 23;
	COORD e;
	e.X = 35;
	e.Y = 23;
	console.writeToBuffer(d, "My answer: ", 0x0B);
	console.writeToBuffer(e, answer, 0x0A);
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    console.clearBuffer(0x0F);
}


void createQuestion()
{
	if (questionMade == false)
	{
		int ans;
		srand(static_cast<unsigned int>(elapsedTime));
		//srand(time(NULL));
		randomNo1 = (rand()%9) + 1;
		randomNo2 = (rand()%9) + 1;
		DrandomNo1 = (rand()%9) + 1;
		DrandomNo2 = (rand()%9) + 1;
		int diffParam = (rand()%100)+1;
		int plus, minus, multiply;
		switch (difficultySet)
		{
			case 1: plus = 40, minus = 70, multiply = 90; break;
			case 2: plus = 20, minus = 45, multiply = 75; break;
			case 3: plus = 5, minus = 15, multiply = 55; break;
		}
		if ( diffParam > 1 && diffParam <= plus )
		{
			randomsign = 1;
		}
		else if ( diffParam > plus && diffParam <= minus )
		{
			randomsign = 2;
		}
		else if ( diffParam > minus && diffParam <= multiply )
		{
			randomsign = 3;
		}
		else if ( diffParam > multiply && diffParam <= 100 )
		{
			randomsign = 4;
		}
		
		questionMade = true;
		switch (randomsign)
		{
			case 1: ans = randomNo1 + randomNo2; break;
			case 2: ans = randomNo1 - randomNo2; break;
			case 3: ans = randomNo1 * randomNo2; break;
			case 4: DrandomNo3 = DrandomNo1 * DrandomNo2; ans= DrandomNo3 / DrandomNo2; break;//  D1(3) * D2(5) = D3(15)  [ what is 15 / 5? ans 3 ] 
		}
		cout << ans << endl;
		std::ostringstream theAnswer;
		theAnswer << ans;
		string qnAnswer = theAnswer.str();
		battleAnswer.assign(qnAnswer);
	}
}

void checkPlayerAnswer()
{
	if ( (answerIsDifferent == 0) && (playerInputted == true) )
	{
		setPlayerChangableStats();
		setMonsterChangableStats();
        attkTime += 2;
		foeHP -= player.damage ;//20 // multiplied by 100 for testing. REMOVE LATER
		playerInputted = false;
		
	}
	else if ( (answerIsDifferent != 0) && (playerInputted == true) )
	{
		setPlayerChangableStats();
		setMonsterChangableStats();
		player.chance -= 1;
		playerInputted = false;
	}
    //Attack Speed of enemy.
    if (allowEnemyAttk == false)
    {
        if (enemyAttkTime == false)
        {
            //attk time is time left to attk.
		    attkTime = elapsedTime + (enemyAttk - difficultySet);
            enemyAttkTime = true;
        }
        if ((elapsedTime >= attkTime))
        {
            allowEnemyAttk = true;
            questionMade = false;
		    attkTime = elapsedTime + (enemyAttk - difficultySet);
        }
    }
    //Enemy Strikes
    if (allowEnemyAttk == true)
    {
        answer.erase();
        player.hp -= MonsterUnit.damage;
        allowEnemyAttk = false;
    }

	if (foeHP <= 0) //foeHP is monster hp
	{
		if (battleModeOn == true)
		{
			mobDown = true;
			selectionMade = false;
            attkTime = elapsedTime + enemyAttk;
		}
		if (inBossFight == true)
		{
			mobDown = true;
		}
		enemyAttkTime = false;
        player.exp += monsterXP;
		initializeHP = false;
        //attkTime = elapsedTime + enemyAttk;
        player.chance = 7 - difficultySet; //resets chance
	}
    if (player.chance <= 0)
    {
        int noChance = (player.hp / 100) * 20;
        player.hp -= noChance;
        player.chance = 7 - difficultySet;
    }
	if ((player.hp <= 0) && (mainMenu == false) && (loading == false))
	{
		selectionMade = false;
		playerDead = true;
		//currState = G_GameOver;
	}
}