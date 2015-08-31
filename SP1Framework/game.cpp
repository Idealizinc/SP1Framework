// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "monsterEncounter.h"
#include "readFunc.h"

// Console object
Console console(78, 25, "SP1 Framework");

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

//Impt Variables
int xSpawnCoord = 0, ySpawnCoord = 0;
int xReturnCoord, yReturnCoord;
bool renderedChar = false;
int chest0 = 0;
int chest1 = 0;
int playerxp = 0;
int playerlv = 1;
int numberOfTries = 4;

//ENABLE PLAYER ENCOUNTER
bool randomEncountersOn = true; // SET TO TRUE LATER

//Read Values
string normal_Monster1;     //store first frame of monster txt
string normal_Monster1ALT;  //store second frame of monster txt
string boss_Monster1;       //store first frame of boss txt
string boss_Monster1ALT;    //store second frame of boss txt
string stage_Map;           //store stage level.

//Game State
double loadTimer;
bool loading = false;
char loadScrnArray[25][78];
GameStates currState = G_MainMenu; // G_Intro
bool mainMenu = false;
char menuArray[25][78];

//For Battle Scrn & Battle Anim 
bool battleModeOn = false;      // when true, loads battle screen
bool animate = true;            // toggles between two frames.
bool animate2 = true;           // toggles between two frames.
int monsterFound;               // -
bool playerInputOn = true;      // toggles movement of player.
int answerIsDifferent;          // check if player ans is diff.
string battleAnswer;            // holds value of player ans.
bool locationSaved =  false;    // saves player location upon battle.
bool bossCleared = false;       // when boss cleared, won't meet again.
bool inBossFight = false;       // toggles inboss fight screen.
bool initializeHP = false;      // To initialise monster/boss HP

//For Battle Systems
bool playerInputted = false;    // check if player got put answer.
bool questionMade = false;      // creates question only when answered.
bool allowNumInput = true;      // player's num input
int playerDmg;                  // player dmg
double storedTime;              // the value of the stored time.
bool limiterSet = false;        // prevents players from input value multi time
int randomNo1;                  // random number for first value
int randomNo2;                  // random number for second value
int randomsign;                 // random sign symbols (not coded)
string answer;                  //answer of player inputted.
int currAtStage = 0;            // current stage level
int stageVal = 21;              //Random unrelated value
bool allowEnemyAttk = false;    // enemy to attack.
bool enemyAttkTime = false;
double attkTime;                // Attkspeed of enemy
double enemyAttk = 3.00;        // player to attk.

double waitTime = 0.075;         // waiting time for inputing value.

//For Game Over Screen
bool playerDead = false;

//Status
int status = 0;

//For Portal End Stage
bool atPortal = false; //Set To FALSE

// Game specific variables here
COORD charLocation;

Hero player;
Monster MonsterUnit;
Boss BossUnit;
int charHP, HP, foeHP, foeLVL, limitEXP, Damage, Damage2, monsterXP, monsterHP;

// Initialize variables, allocate memory, load data from file, etc. 
// This is called once before entering into your main loop
void init()
{
    // Set precision for floating point output
    elapsedTime = 0.0;
	readPortal("endscreen.txt",screenArray);
    readGameOver("gameover.txt",ggArray);
	readLoadScreen("LoadScreen_100%.txt",loadScrnArray);
	readMenu("menuScreen.txt", menuArray);

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
		initiallizePlayerStats();
		initiallizeMonsterStats();
		setPlayerChangableStats();
		setMonsterChangableStats();
	}
}

void getReadData(int val)
{
	switch (val)
	{
		case 1:	normal_Monster1 = "MOB_DEVIL1.txt";
				normal_Monster1ALT = "MOB_DEVIL2.txt";
				boss_Monster1 = "MOB_BAT1.txt"; 
				boss_Monster1ALT = "MOB_BAT2.txt";
				stage_Map = "Map1.txt";
				break;
		case 2:	normal_Monster1 = "MOB_BAT1.txt";
				normal_Monster1ALT = "MOB_BAT2.txt";
				boss_Monster1 = "MOB_Spider1.txt"; 
				boss_Monster1ALT = "MOB_Spider2.txt";
				stage_Map = "Map2.txt";
				break;
		case 3:	normal_Monster1 = "MOB_BAT1.txt";
				normal_Monster1ALT = "MOB_BAT2.txt";
				boss_Monster1 = "MOB_Spider1.txt"; 
				boss_Monster1ALT = "MOB_Spider2.txt";
				stage_Map = "Map3.txt";
				break;
	}
	readMap(stage_Map,mapArray);
	readBattleScreen(normal_Monster1,battleArray);
	readBattleScreen2(normal_Monster1ALT,battleArrayALT);
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
		case G_Intro:;			//Implemented Later
		case G_MainMenu: mainMenu = true; renderSelection(); break;
		case G_Tutorial:;		//Implemented Later
		case G_Options:;	//Implemented Later
		case G_LoadScreen: loading = true; drawMapRendChar(); break;
		case G_Stage1: currAtStage = 1; drawMapRendChar(); break;
		case G_Stage2: currAtStage = 2; drawMapRendChar(); break;
		case G_Stage3: currAtStage = 3; drawMapRendChar(); break;
		/*case G_Stage4: currAtStage = 4; drawMapRendChar(); break;
		case G_Stage5: currAtStage = 5; drawMapRendChar(); break;
		case G_Stage6: currAtStage = 6; drawMapRendChar(); break;*/
		case G_StageCleared: portalrender(); break;
		case G_GameOver: renderGameOver(); break; 
		
	}
	  // renders the character into the buffer
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
	
}

void drawMapRendChar()
{
	isReadDataNeeded();
	renderSelection();
	renderCharacter();
}

void renderSelection()
{
	if ((mainMenu == true))
	{
		drawMenu();
	}
	else if ((renderedChar == false) && (loading == false))
	{
		drawMap();
		renderCharacter();  // renders the character into the buffer
		playerInputOn = true;
		charLocation.X = xSpawnCoord;
		charLocation.Y = ySpawnCoord;
		renderedChar = true;
		
	}
	else if ((battleModeOn == false) && (inBossFight == false) && (renderedChar == true) && (atPortal == false) && (playerDead == false) && (loading == false))
	{
		drawMap();
		renderCharacter();  // renders the character into the buffer
		playerInputOn = true;
		if (locationSaved == true)
		{
			charLocation.X = xReturnCoord;
			charLocation.Y = yReturnCoord ;
			locationSaved = false;
		}
	}
	else if ((battleModeOn == true) && (loading == false))
	{
		animateBSNorm();
		if (locationSaved == false)
		{
			xReturnCoord = charLocation.X;
			yReturnCoord = charLocation.Y;
			locationSaved = true;
		}
		charLocation.X = 100;
		charLocation.Y = 100;
		playerInputOn = false;
	}
	else if ((inBossFight == true) && (bossCleared == false) && (loading == false))
	{
		animateBSBoss();
		if (locationSaved == false)
		{
			xReturnCoord = charLocation.X;
			yReturnCoord = charLocation.Y;
			locationSaved = true;
		}
		charLocation.X = 100;
		charLocation.Y = 100;
		playerInputOn = false;
	}
	else if ((atPortal == true))
    {
        charLocation.X = 100;
		charLocation.Y = 100;
		playerInputOn = false;
		currState = G_StageCleared;
    }
    else if ((playerDead == true) && (loading == false) && (mainMenu == false) && (renderedChar == true))
    {
        charLocation.X = 100;
		charLocation.Y = 100;
		playerInputOn = false;
		currState = G_GameOver;
    }
	else if (loading == true)
    {
		renderLoadScreen();
        charLocation.X = 100;
		charLocation.Y = 100;
		playerInputOn = false;
		if(keyPressed[K_SPACE])
		{
		loading = false;
		currState = G_Stage1;
		}
    }
}
void renderPrintedText(char toBePrinted ,int j,int i )
{
	if (toBePrinted == 'A')
	{
		toBePrinted = 176; // ░
		console.writeToBuffer(j,i, toBePrinted, 0x8A); // Dirty Green [Grass]
	}
	else if (toBePrinted == 'W')
	{
		toBePrinted = 177; // ░
		console.writeToBuffer(j,i, toBePrinted, 0x80); // Grey [Walls]
	}
	else if (toBePrinted == 'T')
	{
		toBePrinted = 5; // ♣
		console.writeToBuffer(j,i, toBePrinted, 0x8A); // Green [Trees]
	}
	else if (toBePrinted == 'D')
	{
		toBePrinted = 176; // ░
		console.writeToBuffer(j,i, toBePrinted, 0x80); // Dark Grey [Walls]
	}
	else if (toBePrinted == 'V')
	{
		toBePrinted = 176; // ░
		console.writeToBuffer(j,i, toBePrinted, 0x70); // Light Grey [Floor]
	}
	else if (toBePrinted == 'P')
	{
		xSpawnCoord = j; // Obtain spawn coordinates for player
		ySpawnCoord = i;
		toBePrinted = 176; // ░ Fill up space under player.
		console.writeToBuffer(j,i, toBePrinted, 0x78);
	}
	else if (toBePrinted == 'C')
	{
		toBePrinted = 254; // ■
		console.writeToBuffer(j,i, toBePrinted, 0x8E); // Gold [Chests]
	}
	else if (toBePrinted == 'R')
	{
		toBePrinted = 254; // ■
		console.writeToBuffer(j,i, toBePrinted, 0x7E); // Gold [Chests]
	}
	else if (toBePrinted == 'E')
	{
		toBePrinted = 10; // 
		console.writeToBuffer(j,i, toBePrinted, 0xB8); // Blue [Portal]
	}
	else if (toBePrinted == 'X')
	{
		toBePrinted = 15; // Θ
		console.writeToBuffer(j,i, toBePrinted, 0x8C); // Red [Boss]
	}
	else if (toBePrinted == '1')
	{
		toBePrinted = 178; // ▓
		console.writeToBuffer(j,i, toBePrinted, 0x7F); // White [Walls]
	}
	else if (toBePrinted == 'W')
	{
		toBePrinted = 176; // ░
		console.writeToBuffer(j,i, toBePrinted, 0x80); // Grey [Walls]
	}
	else if (toBePrinted == 'Z')
	{
		toBePrinted = 176; // ░
		console.writeToBuffer(j,i, toBePrinted, 0x84); // Reddish Brown [Cave Walls]
	}
	else if (toBePrinted == '=')
	{
		toBePrinted = 176; // ░
		console.writeToBuffer(j,i, toBePrinted, 0xCB); // Red [LoadBar]
	}
	else if (toBePrinted == '3')
	{
		toBePrinted = 17; // ◄
		console.writeToBuffer(j,i, toBePrinted, 0x0E); // [Gold] Triangles
	}
	else if (toBePrinted == '2')
	{
		toBePrinted = 16; // ►
		console.writeToBuffer(j,i, toBePrinted, 0x0E); // [Gold] Triangles
	}
	else if (toBePrinted == '4')
	{
		toBePrinted = 30; // ▲
		console.writeToBuffer(j,i, toBePrinted, 0x0E); // [Gold] Triangles
	}
	else if (toBePrinted == '5')
	{
		toBePrinted = 31; // ▼
		console.writeToBuffer(j,i, toBePrinted, 0x0E); // [Gold] Triangles
	}
	else if ((loading == true) || (atPortal == true) || (mainMenu == true))
	{
		console.writeToBuffer(j,i, toBePrinted, 0x0B); // Color The Underscores dases and so, Blue.
	}
	else if ((battleModeOn == true) || ((inBossFight == true)) && (bossCleared == false))
	{
		console.writeToBuffer(j,i, toBePrinted, 0x0F); // Coloration Failed - blk Txt
	}
    else if ((playerDead == true))
	{
		console.writeToBuffer(j,i, toBePrinted, 0x0C); // Color The Underscores dashes RED.
	}
}
void moveCharacter()
{
	checkMove();
	chestOpen();
	bossFightCheck();
}

void checkMove()
{
	int Y = charLocation.Y;
	int X = charLocation.X;

	if ((keyPressed[K_UP] || keyPressed[K_W]) && charLocation.Y > 0)
	{
		if ((mapArray[Y - 1][X] != 'W') && (mapArray[Y - 1][X] != '1') &&
			(mapArray[Y - 1][X] != 'T') && (mapArray[Y - 1][X] != 'D') && 
			(mapArray[Y - 1][X] != 'Z'))
		{
			charLocation.Y--;
			monsterCheck();
		}
	}

	else if ((keyPressed[K_LEFT] || keyPressed[K_A]) && charLocation.X > 0)
	{
		if ((mapArray[Y][X - 1] != 'W') && (mapArray[Y][X - 1] != '1') &&
			(mapArray[Y][X - 1] != 'T') && (mapArray[Y][X - 1] != 'D') && 
			(mapArray[Y][X - 1] != 'Z'))
		{
			charLocation.X--;
			monsterCheck();
		}
	}
	else if ((keyPressed[K_DOWN] || keyPressed[K_S]) && charLocation.Y < console.getConsoleSize().Y - 1)
	{
		if ((mapArray[Y + 1][X] != 'W') && (mapArray[Y + 1][X] != '1') &&
			(mapArray[Y + 1][X] != 'T') && (mapArray[Y + 1][X] != 'D') && 
			(mapArray[Y + 1][X] != 'Z'))
		{
			charLocation.Y++;
			monsterCheck();
		}
	}
	else if ((keyPressed[K_RIGHT] || keyPressed[K_D]) && charLocation.X < console.getConsoleSize().X - 1)
	{
		if ((mapArray[Y][X + 1] != 'W') && (mapArray[Y][X + 1] != '1') &&
			(mapArray[Y][X + 1] != 'T') && (mapArray[Y][X + 1] != 'D') && 
			(mapArray[Y][X + 1] != 'Z'))
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
    // quits the game if player hits the escape key
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
			if (keyPressed[K_ENTER])
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
		
		for( unsigned int i = K_0; i <= K_9 ; i++  )
		{
			if ( (keyPressed[i]) )
			{
				answer += ( 48 + i );
				allowNumInput = false;
			}
		}
		if ( keyPressed[K_DASH] )
		{
			answer += "-";
			allowNumInput = false;
		}
		if ( (keyPressed[K_BACKSPACE]) && (answer.length() > 0) )
		{
			answer.erase(answer.length() - 1 );
			allowNumInput = false;
		}
		else if ( keyPressed[K_ENTER] )
		{
			/*for ( size_t i = 0; i < 1; ++i  )
			{
				if (answer[i] == 0 )
				{
					answer.erase(1,i);
				}
				cout << answer << endl;
			}*/
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
	d.Y = 22;
	COORD e;
	e.X = 35;
	e.Y = 22;
	console.writeToBuffer(d, "My answer: ", 0x0B);
	console.writeToBuffer(e, answer, 0x0A);
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    console.clearBuffer(0x0F);
}

void checkLevelUp()
{
    if (player.exp >= player.expCap)
    {
        changePlayerStats();
    }
}

void changePlayerStats()
{
    int rngdamage = rand() % 10 + 50;
    player.level += 1;
    player.exp -= player.expCap;
    player.expCap = 50 * player.level;
}

void initiallizePlayerStats()
{
	int rngdamage = rand() % 10 + 50;
	player.level = 1;
    player.chance = 3;
    player.exp = 0;
    //player.expCap = 100;
	player.hp = 1000 + ((player.level) * 100);
	player.damage = 1 * 1337;
	player.expCap = 50 * player.level;
	limitEXP = player.expCap;
    playerDmg = player.damage;
}

void setPlayerChangableStats()
{
	int rngdamage = rand() % 10 + 50;
	//player.hp = 1000 + ((player.level) * 100);
	player.damage = 1;
    //player.chance = 3;
	player.expCap = 50 * player.level;
    playerDmg = player.damage;
}

void initiallizeMonsterStats()
{
	srand((unsigned)time(0));
	MonsterUnit.level = (rand()%(currAtStage * 10 + 1)) + currAtStage;
	MonsterUnit.hp = (MonsterUnit.level * 2);
	MonsterUnit.expgiven = ((rand()%3) + 1) * MonsterUnit.level;
	BossUnit.hp = 300 + (MonsterUnit.level * 100);
	BossUnit.expgiven = 5000;
	monsterXP = MonsterUnit.expgiven;
	monsterHP = MonsterUnit.hp;
	foeHP = monsterHP;
    foeLVL = MonsterUnit.level;
}

void setMonsterChangableStats()
{
	int monsterDamage = rand() % 20 + 50;
	int bossDamage = rand() % 10 + 100;
	MonsterUnit.damage = 10 + monsterDamage;
	BossUnit.damage = bossDamage;
}

void printMapStats()
{
	COORD c;

    checkLevelUp();

    std::ostringstream mylvl;
    mylvl << player.level;
    string myLvl = mylvl.str(); //string that contains player lvl

	std::ostringstream myhp;
	myhp << player.hp;
	string myHP = myhp.str(); //string that contains player hp

	std::ostringstream enemyhp; 
	enemyhp << foeHP ;
	string monhp = enemyhp.str(); //string that contains monster hp

	std::ostringstream exp;
	exp << player.exp;
	string playerExp = exp.str(); // string that contains player exp

    std::ostringstream mylvlcap;
    mylvlcap << player.expCap;
    string mylvlCap = mylvlcap.str(); //string that contains player exp cap

	string text;
    text = " My Level: ";
    text +=  myLvl;
	text += "    My HP: "; 
	text += myHP;
	text += "    Exp: ";
	text += playerExp;
	text += " / ";
    text += mylvlCap;
	//charHP++; testing if changeable 
	c.X = 17;
	c.Y = 21;
	//console.writeToBuffer(c,text.str());
	console.writeToBuffer(c, text, 0xF9);

	if ( player.hp <= 0 )
	{
		battleModeOn = false;
		inBossFight = false;
		playerDead = true;
	}
	if ( player.chance <= 0 )
	{
		battleModeOn = false;
		inBossFight = false;
		playerDead = true;
	}
}

void createQuestion()
{
	if (questionMade == false)
	{
		float decimalans;
		int ans;
		srand (elapsedTime);
		//srand(time(NULL));
		randomNo1 = (rand()%9) + 1;
		randomNo2 = (rand()%9) + 1;
		randomsign = (rand()%4) + 1;
		questionMade = true;
		switch (randomsign)
		{
			case 1: ans = randomNo1 + randomNo2; break;
			case 2: ans = randomNo1 * randomNo2; break;
			case 3: ans = randomNo1 - randomNo2; break;
			case 4: decimalans = randomNo1 / randomNo2; ans = decimalans; break;
		}
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
    //MonsterUnit.damage

    //Attack Speed of enemy.
    if (allowEnemyAttk == false)
    {
        if (enemyAttkTime == false)
        {
		attkTime = elapsedTime + enemyAttk;
        enemyAttkTime = true;
		attkTime += 4;
        }
        if (elapsedTime >= attkTime)
        {
            allowEnemyAttk = true;
            questionMade = false;
            enemyAttkTime = false;
        }
    }
    //Enemy Strikes
    if (allowEnemyAttk == true)
    {
        answer.erase();
        player.hp -= MonsterUnit.damage;
        allowEnemyAttk = false;
    }
	if (foeHP <= 0) //HP2 is monster hp
	{
		if (battleModeOn == true)
		{
			battleModeOn = false;
            player.chance = 3; //resets chance
            attkTime = elapsedTime + enemyAttk;
		}
		if (inBossFight == true)
		{
			bossCleared = true;
			inBossFight = false;
		}
        player.exp += monsterXP;
		initializeHP = false;
	}
	if (((player.hp <= 0) || (player.chance <= 0)) && (mainMenu == false) && (loading == false))
	{
		battleModeOn = false;
		inBossFight = false;
		playerDead = true;
	}
}
void printBattleStats()
{
    //attkTime - elapsedTime = time left to attk.
    checkLevelUp();
	createQuestion();
	if (initializeHP == false)
	{
		initiallizeMonsterStats();
		if (battleModeOn == true)
		{
			//problem was here
			foeHP = monsterHP;
		}
		if (inBossFight == true)
		{
			monsterHP = BossUnit.hp;
		}
		initializeHP = true;
	}
	COORD c;
    std::ostringstream  mychance;
    mychance << player.chance;
    string myChance = mychance.str(); // string that contains player chance

	std::ostringstream myhp;
	myhp << player.hp ;
	string myHP = myhp.str(); // string that contains player hp

    std::ostringstream enemylvl;
    enemylvl << foeLVL;
    string enemyLVL = enemylvl.str(); // string that contains enemy lvl

	std::ostringstream enemyhp;
	enemyhp << foeHP ;
	string monhp = enemyhp.str(); // string that contains enemy hp

	string text;

	text = " My HP: ";
	text += myHP;
    text += "    Chance Left: ";
    text += myChance;
	text += " ";
	c.X = 23;
	c.Y = 19;
	console.writeToBuffer(c, text, 0xF9);

    //0xF0 (blak txt wite bg)

    //attk speed.
    double attackSpeed = attkTime - elapsedTime;
    COORD enemyStats;
    string Time;
    std::ostringstream attktime;
    attktime << std::fixed << std::setprecision(0);
    attktime << attackSpeed;
    Time = attktime.str();

    string textEnemyStat;
    textEnemyStat = " Enemy Level: ";
    textEnemyStat += enemyLVL;
	textEnemyStat +=	"    Enemy HP: ";
	textEnemyStat +=	monhp;
    textEnemyStat += "    Time till Attack: ";
    textEnemyStat += Time;
    textEnemyStat += " ";
    enemyStats.X = 12;
    enemyStats.Y = 20;
    console.writeToBuffer(enemyStats, textEnemyStat, 0xF4);


	COORD d;
	string question;
	question = "What is ";
	question += static_cast<char>(randomNo1) + 48;
	switch (randomsign)
	{
		case 1: question += " + "; break;
		case 2: question += " x "; break;
		case 3: question += " - "; break;
		case 4: question += " / "; break;
	}
	question += static_cast<char>(randomNo2) + 48;
	question += " ?";
	d.X = 24;
	d.Y = 21;
	console.writeToBuffer(d, question, 0x0E);
	string roundoff;
	roundoff = "All numbers are rounded down to the nearest whole number";
	switch (randomsign)
	{
		case 4: COORD f; f.X = 10; f.Y = 23; console.writeToBuffer(f, roundoff, 0x0D); break;
	}
	numberinput();
	checkPlayerAnswer();
}
//void printBattleStats()
//{
//    checkLevelUp();
//	if (questionMade == false)
//	{
//		srand (elapsedTime);
//		randomNo1 = (rand()%9) + 1;
//		randomNo2 = (rand()%9) + 1;
//		randomsign = (rand()%3) + 1;
//		questionMade = true;
//		int ans = randomNo1 + randomNo2;
//		std::ostringstream theAnswer;
//		theAnswer << ans;
//		string qnAnswer = theAnswer.str();
//		battleAnswer.assign(qnAnswer);
//	}
//	if (initializeHP == false)
//	{
//		initiallizeMonsterStats();
//		if (battleModeOn == true)
//		{
//			//problem was here
//			foeHP = monsterHP;
//		}
//		if (inBossFight == true)
//		{
//			monsterHP = BossUnit.hp;
//		}
//		initializeHP = true;
//	}
//	COORD c;
//	std::ostringstream myhp;
//	myhp << player.hp ;
//	string myHP = myhp.str(); // string that contains player hp
//
//    std::ostringstream enemylvl;
//    enemylvl << foeLVL;
//    string enemyLVL = enemylvl.str(); // string that contains enemy lvl
//
//	std::ostringstream enemyhp;
//	enemyhp << foeHP ;
//	string monhp = enemyhp.str(); // string that contains enemy hp
//
//	string text;
//	text = " My HP: ";
//	text += myHP;
//    text += "    Enemy Level: ";
//    text += enemyLVL;
//	text +=	"    Enemy HP: ";
//	text +=	monhp;
//	text += " ";
//	c.X = 16;
//	c.Y = 20;
//	console.writeToBuffer(c, text, 0x78);
//
//	COORD d;
//	string question;
//	question = "What is ";
//	question += static_cast<char>(randomNo1) + 48;
//	question += " + ";
//	question += static_cast<char>(randomNo2) + 48;
//	question += "?";
//	d.X = 24;
//	d.Y = 21;
//	console.writeToBuffer(d, question, 0x0E);
//
//	numberinput();
//
//	if ( (answerIsDifferent == 0) && (playerInputted == true) )
//	{
//		setPlayerChangableStats();
//		setMonsterChangableStats();
//		foeHP -= player.damage * 100 ;//20 // multiplied by 100 for testing. REMOVE LATER
//		playerInputted = false;
//		
//	}
//	else if ( (answerIsDifferent != 0) && (playerInputted == true) )
//	{
//		setPlayerChangableStats();
//		setMonsterChangableStats();
//		player.hp -= MonsterUnit.damage;
//        //player.chance -= 1;
//		playerInputted = false;
//		
//	} 
//	if (foeHP <= 0) //HP2 is monster hp
//	{
//		if (battleModeOn == true)
//		{
//			battleModeOn = false;
//		}
//		if (inBossFight == true)
//		{
//			bossCleared = true;
//			inBossFight = false;
//		}
//        (player.exp) += monsterXP;
//		initializeHP = false;
//	}
//	if (( player.hp <= 0 ) && ((battleModeOn == true) || (inBossFight == true)))
//	{
//		battleModeOn = false;
//		playerDead = true;
//	}
//	if (( player.chance <= 0 ) && ((battleModeOn == true) || (inBossFight == true)))
//	{
//		battleModeOn = false;
//		playerDead = true;
//	}
//}

//readMap();

//readBattleScreen(string str)


//readBattleScreen2(string str)


//readBossScreen(string str)


//readBossScreen2(string str)


void drawMap()
{
	for (int i = 0; i < 22;)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = mapArray[i][j];
			renderPrintedText(toBePrinted,j,i);
		}
		i++;
	}
	printMapStats();
    if (status > 0)
    {
        printChestReward();
        status--;
    }
	if (status < 0)
    {
        printFakeChestInfo();
        status++;
    }
}

void drawBattleScreen()
{
	for (int i = 0; i < 20;)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = battleArray[i][j];
			renderPrintedText(toBePrinted,j,i);
		}
		i++;
	}
}

void drawBattleScreenALT()
{
	for (int i = 0; i < 20;)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = battleArrayALT[i][j];
			renderPrintedText(toBePrinted,j,i);
		}
		i++;
	}
}

void animateBSNorm() // Battle Screen Anims
{
	if (animate == false)
    {
        drawBattleScreen();
        animate = true;
    }
    else
    {
        drawBattleScreenALT();
        animate = false;
    }
	printBattleStats();
}

void drawBattleScreenBoss()
{
	for (int i = 0; i < 20;)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = bossArray[i][j];
			renderPrintedText( toBePrinted,j,i );
		}
		i++;
	}
}

void drawBattleScreenBossALT()
{
	for (int i = 0; i < 20;)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = bossArrayALT[i][j];
			renderPrintedText( toBePrinted,j,i );
		}
		i++;
	}
}

void animateBSBoss() // Battle Screen Anims
{
	if (animate2 == false)
    {
        drawBattleScreenBoss();
        animate2 = true;
    }
    else
    {
        drawBattleScreenBossALT();
        animate2 = false;
    }
	printBattleStats();
}

//void renderMap()
//{
//	// Set up sample colours, and output shadings
//	const WORD stage1colors[] = {
//		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
//		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
//	};
//
//	/*COORD c;
//	for (int i = 0; i < 12; ++i)
//	{
//		c.X = 5 * i;
//		c.Y = i + 1;
//		colour(colors[i]);
//		console.writeToBuffer(c, " °±²Û", colors[i]);
//	}*/
//
//	renderSelection();
//}

void renderCharacter()
{
    // Draw the location of the character
    console.writeToBuffer(charLocation, (char)2, 0x7F);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / deltaTime << "FPS";
    c.X = console.getConsoleSize().X - 9;
    c.Y = 0;
    console.writeToBuffer(c, ss.str(), 0xF0);

    // displays the elapsed time
    ss.str("");
    ss << elapsedTime << "Secs";
    c.X = 0;
    c.Y = 0;
    console.writeToBuffer(c, ss.str(), 0xF0);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    console.flushBufferToConsole();
}

//Checks if player is at the Chest.

void chestOpen()
{
    if (mapArray[charLocation.Y][charLocation.X] == 'C')
    {
        //insert item codes
        mapArray[charLocation.Y][charLocation.X] = 'V';
        status += 20;
        player.hp += 200;
    }
	if (mapArray[charLocation.Y][charLocation.X] == 'R')
    {
        //insert item codes
        mapArray[charLocation.Y][charLocation.X] = 'V';
        status -= 20;
        player.hp -= 100;
    }
}

void printChestReward()
{
		COORD chestNotif;
        string reward = "200 HP";
		chestNotif.X = 25;
		chestNotif.Y = 23;

		string chestReward = "You obtained ";
		chestReward += reward;
		chestReward += "!";
		console.writeToBuffer(chestNotif,chestReward,0x0A);
		
}

void printFakeChestInfo()
{
		COORD chestNotif;
        string reward = "100 HP";
		chestNotif.X = 20;
		chestNotif.Y = 23;

		string chestReward = "You lost ";
		chestReward += reward;
		chestReward += " because of a fake chest!";
		console.writeToBuffer(chestNotif,chestReward,0x0C);
		
}

void bossFightCheck()
{
    if ((mapArray[charLocation.Y][charLocation.X] == 'X') && (bossCleared == false))
    {
        inBossFight = true;
    }
}


//readPortal()

void portalrender()
{
    for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = screenArray[i][j];
			renderPrintedText( toBePrinted,j,i );
		}
     }
	if ((currAtStage == 3) && (atPortal == true))
	{
		currState = G_StageCleared;
	}

	if ( keyPressed[K_SPACE] )
	{
		if ((currAtStage == 1)  && (atPortal == true) )
		{
				currState = G_Stage2;
				atPortal = false;
		}
		if ((currAtStage == 2)  && (atPortal == true) )
		{
				currState = G_Stage3;
				atPortal = false;
		}
		//currState = G_Stage2;
		bossCleared = false;
		battleModeOn = false;
		renderedChar = false;
		playerDead = false;
	}
} 
// readGameOver()

void renderGameOver()
{
    for (int i = 0; i < 25; ++i)
	{
		    for (int j = 0; j < 78; ++j)
		    {
			    char toBePrinted = ggArray[i][j];
			    renderPrintedText( toBePrinted, j, i );
		    }
    }
	battleModeOn = false;
	inBossFight = false;
	if ( keyPressed[K_SPACE] )
	{
		switch(currAtStage)
		{

			case 1: currState = G_Stage1; break;
			case 2: currState = G_Stage2; break;
			case 3: currState = G_Stage3; break;
			/*case 3: currState = G_Stage3; break;
			case 4: currState = G_Stage4; break;*/
		}
		currAtStage = 0;
		renderedChar = false;
		locationSaved = false;
		playerDead = false;
		bossCleared = false;
		drawMapRendChar();
	}
    if ( keyPressed[K_ESCAPE] )
    {
        switch(currAtStage)
        {
            case 1: currState = G_MainMenu; break;
        }
    }
}

// void readLoadScreen(string str,char loadScrnArray[25][78])


void renderLoadScreen()
{
	for (int i = 0; i < 25; ++i)
	{
		    for (int j = 0; j < 78; ++j)
		    {
			   char toBePrinted = loadScrnArray[i][j];
			   renderPrintedText( toBePrinted, j, i );
		    }
    }
}

void drawMenu()
{
	for (int i = 0; i < 25;)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = menuArray[i][j];
			renderPrintedText(toBePrinted,j,i);
		}
		i++;
	}
	if (keyPressed[K_1])
	{
		currState = G_LoadScreen;
		loading = true;
		mainMenu = false;
	}
	else if (keyPressed[K_2])
	{
		currState = G_Tutorial;
	}
	else if (keyPressed[K_3])
	{
		currState = G_Options;
	}
	else if (keyPressed[K_4])
	{
		g_quitGame = true;
	}
}
//void animateLoading()
//{
//	
//	for ( int c = 0; c < 6 ; )
//	{
//		int wait = elapsedTime + 5;
//		switch (c)
//		{
//			case 0: readLoadScreen("LoadScreen_0%.txt"); renderLoadScreen(); break;
//			case 1: readLoadScreen("LoadScreen_15%.txt"); renderLoadScreen(); break;
//			case 2: readLoadScreen("LoadScreen_35%.txt"); renderLoadScreen(); break;
//			case 3: readLoadScreen("LoadScreen_65%.txt"); renderLoadScreen(); break;
//			case 4: readLoadScreen("LoadScreen_80%.txt"); renderLoadScreen(); break;
//			case 5: readLoadScreen("LoadScreen_100%.txt"); renderLoadScreen(); break;
//		}
//		if ( wait < elapsedTime )
//		++c;
//	}
	
	/*while (c < 6)
	{
		renderLoadScreen();
	}*/
//}