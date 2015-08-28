// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "monsterEncounter.h"



// Console object
Console console(78, 25, "SP1 Framework");

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
char mapArray[22][79];
char battleArray[20][79];
char battleArrayALT[20][79];
char bossArray[20][79];
char bossArrayALT[20][79];
char screenArray[25][79];
char ggArray[25][79];
int xSpawnCoord = 0, ySpawnCoord = 0;
int xReturnCoord, yReturnCoord;
bool renderedChar = false;
int chest0 = 0;
int chest1 = 0;
int playerxp = 0;
int playerlv = 1;
bool randomEncountersOn = true; // SET TO TRUE LATER

//Read Values
string normal_Monster1;
string normal_Monster1ALT;
string boss_Monster1;
string boss_Monster1ALT;
string stage_Map;

//Game State
double loadTimer;
bool loading = false;
char loadScrnArray[25][79];
GameStates currState = G_LoadScreen; // G_Intro
bool atLoad = false;

//For Battle Scrn & Battle Anim 
bool battleModeOn = false; // SET TO FALSE LATER
bool animate = true;
int monsterFound; 
bool playerInputOn = true;
int answerIsDifferent;
string battleAnswer;
bool locationSaved =  false;

//For Portal End Stage
bool atPortal = false; //Set To FALSE

//For Game Over Screen
bool playerDead = false;

//For Boss Fight
bool animate2 = true;
bool bossCleared = false; //Set To FALSE
bool inBossFight = false;
bool initializeHP = false; // To initialise monster/boss HP

//For Battle Systems
bool playerInputted = false;
bool questionMade = false;
bool allowNumInput = true;
double storedTime;
double waitTime = 0.05;
bool limiterSet = false;
int randomNo1;
int randomNo2;
int randomsign;
string answer;
int currAtStage = 0;
int stageVal = 21; //Random unrelated value

//For Game Over Screen
bool playerDead = false;

//Movement
bool keyPress;

//Status
int status = 0;


//For Portal End Stage
bool atPortal = false; //Set To FALSE

// Game specific variables here
COORD charLocation;

Hero player;
Monster MonsterUnit;
Boss BossUnit;
int charHP, HP, HP2, limitEXP, Damage, Damage2, monsterXP, monsterHP;

// Initialize variables, allocate memory, load data from file, etc. 
// This is called once before entering into your main loop
void init()
{
    // Set precision for floating point output
    elapsedTime = 0.0;
	readPortal();
    readGameOver();
	readLoadScreen("LoadScreen_100%.txt");

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
	}
	readMap(stage_Map);
	readBattleScreen(normal_Monster1);
	readBattleScreen2(normal_Monster1ALT);
	readBossScreen(boss_Monster1);
	readBossScreen2(boss_Monster1ALT);
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
		case G_MainMenu:;		//Implemented Later
		case G_Tutorial:;		//Implemented Later
		case G_StageSelect:;	//Implemented Later
		case G_LoadScreen: loading = true; drawMapRendChar(); break;
		case G_Stage1: currAtStage = 1; drawMapRendChar(); break;
		case G_Stage2: currAtStage = 2; drawMapRendChar(); break;
		/*case G_Stage3: currAtStage = 3; drawMapRendChar(); break;
		case G_Stage4: currAtStage = 4; drawMapRendChar(); break;
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
	renderMap();
	renderCharacter();
}

void renderSelection()
{
	if ((renderedChar == false) && (loading == false))
	{
		drawMap();
		renderCharacter();  // renders the character into the buffer
		playerInputOn = true;
		charLocation.X = xSpawnCoord;
		charLocation.Y = ySpawnCoord;
		renderedChar = true;
		
	}
	if ((battleModeOn == false) && (inBossFight == false) && (renderedChar == true) && (atPortal == false) && (playerDead == false) && (loading == false))
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
    else if ((playerDead == true))
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
		if(  keyPressed[K_SPACE] )
		{
		loading = false;
		currState = G_Stage1;
		}
    }
	}
	else if (atPortal == true)
    {
		clearScreen();
        charLocation.X = 100;
		charLocation.Y = 100;
		playerInputOn = false;
		portalrender();
    }
    else if (playerDead == true)
    {
		clearScreen();
        charLocation.X = 100;
		charLocation.Y = 100;
		playerInputOn = false;
		renderGameOver();
    }

    if (renderedChar == false)
	{
		charLocation.X = xSpawnCoord;
		charLocation.Y = ySpawnCoord;
		renderedChar = true;
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
	else if (toBePrinted == 'S')
	{
		toBePrinted = 176; // ░
		console.writeToBuffer(j,i, toBePrinted, 0x80); // Dark Grey [Walls]
	}
	else if (toBePrinted == 'G')
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
	if (toBePrinted == '1')
	{
		toBePrinted = 178; // ▓
		console.writeToBuffer(j,i, toBePrinted, 0x7F); // White [Walls]
	}
	else if (toBePrinted == 'W')
	{
		toBePrinted = 176; // ░
		console.writeToBuffer(j,i, toBePrinted, 0x80); // Grey [Walls]
	}
	else if (toBePrinted == '=')
	{
		toBePrinted = 176; // ░
		console.writeToBuffer(j,i, toBePrinted, 0xCB); // Red [LoadBar]
	}
	else if ((loading == true) || (atPortal == true))
	{
		console.writeToBuffer(j,i, toBePrinted, 0x0B); // Color The Underscores dases and so, Blue.
	}
	else if (battleModeOn == true || inBossFight == true)
	{
		console.writeToBuffer(j,i, toBePrinted, 0x0F); // Coloration Failed - blk Txt
	}
}
void moveCharacter()
{
	checkMove();
	detectChest();
	bossFightCheck();
}

void checkMove()
{
	int Y = charLocation.Y;
	int X = charLocation.X;

	if ((keyPressed[K_UP] || keyPressed[K_W]) && charLocation.Y > 0)
	{
		if ((mapArray[Y - 1][X] != 'W') && (mapArray[Y - 1][X] != '1') &&
			(mapArray[Y - 1][X] != 'T') && (mapArray[Y - 1][X] != 'S'))
		{
			charLocation.Y--;
			monsterCheck();
		}
	}

	if ((keyPressed[K_LEFT] || keyPressed[K_A]) && charLocation.X > 0)
	{
		if ((mapArray[Y][X - 1] != 'W') && (mapArray[Y][X - 1] != '1') &&
			(mapArray[Y][X - 1] != 'T') && (mapArray[Y][X - 1] != 'S'))
		{
			charLocation.X--;
			monsterCheck();
		}
	}
	if ((keyPressed[K_DOWN] || keyPressed[K_S]) && charLocation.Y < console.getConsoleSize().Y - 1)
	{
		if ((mapArray[Y + 1][X] != 'W') && (mapArray[Y + 1][X] != '1') &&
			(mapArray[Y + 1][X] != 'T') && (mapArray[Y + 1][X] != 'S'))
		{
			charLocation.Y++;
			monsterCheck();
		}
	}
	if ((keyPressed[K_RIGHT] || keyPressed[K_D]) && charLocation.X < console.getConsoleSize().X - 1)
	{
		if ((mapArray[Y][X + 1] != 'W') && (mapArray[Y][X + 1] != '1') &&
			(mapArray[Y][X + 1] != 'T') && (mapArray[Y][X + 1] != 'S'))
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
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;
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
		if ( (keyPressed[K_BACKSPACE]) && (answer.length() > 0) )
		{
			answer.erase(answer.length() - 1 );
			allowNumInput = false;
		}
		else if ( keyPressed[K_ENTER] )
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

void initiallizePlayerStats()
{
	int rngdamage = rand() % 10 + 50;
	player.level = 1;
	player.hp = 1000 + ((player.level) * 100);
	player.damage = 10 + rngdamage;
	player.exp = 100 * player.level;
	limitEXP = player.exp;
}

void setPlayerChangableStats()
{
	int rngdamage = rand() % 10 + 50;
	//player.hp = 1000 + ((player.level) * 100);
	player.damage = 10 + rngdamage * 1337;
	player.exp = 100 * player.level;
}

void initiallizeMonsterStats()
{
	srand((unsigned)time(0));
	MonsterUnit.level = (rand()%(currAtStage * 10 + 1)) + currAtStage;
	MonsterUnit.hp = (MonsterUnit.level * 50);
	MonsterUnit.expgiven = ((rand()%3) + 1) * MonsterUnit.level;
	BossUnit.hp = 300 + (MonsterUnit.level * 100);
	BossUnit.expgiven = 5000;
	monsterXP = MonsterUnit.expgiven;
	monsterHP = MonsterUnit.hp;
	HP2 = monsterHP;
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
	std::ostringstream myhp;
	myhp << player.hp;
	string myHP = myhp.str(); //string that contains player hp
	std::ostringstream enemyhp; 
	enemyhp << HP2 ;
	string monhp = enemyhp.str(); //string that contains monster hp
	std::ostringstream exp;
	exp << playerxp;
	string playerExp = exp.str(); // string that contains player exp
	string text;
	text = " My HP: "; 
	text += myHP;
	text += "    Exp: ";
	text += playerExp;
	text += " ";
	//charHP++; testing if changeable 
	c.X = 24;
	c.Y = 21;
	//console.writeToBuffer(c,text.str());
	console.writeToBuffer(c, text, 0xF9);
}
void printBattleStats()
{
	if (questionMade == false)
	{
		srand (elapsedTime);
		randomNo1 = (rand()%9) + 1;
		randomNo2 = (rand()%9) + 1;
		randomsign = (rand()%3) + 1;
		questionMade = true;
		int ans = randomNo1 + randomNo2;
		std::ostringstream theAnswer;
		theAnswer << ans;
		string qnAnswer = theAnswer.str();
		battleAnswer.assign(qnAnswer);
	}
	if (initializeHP == false)
	{
		initiallizeMonsterStats();
		if (battleModeOn == true)
		{
			//problem was here
			HP2 = monsterHP;
		}
		if (inBossFight == true)
		{
			monsterHP = BossUnit.hp;
		}
		initializeHP = true;
	}
	COORD c;
	std::ostringstream myhp;
	myhp << player.hp ;
	string myHP = myhp.str();
	std::ostringstream enemyhp;
	enemyhp << HP2 ;
	string monhp = enemyhp.str();
	string text;
	text = " My HP: ";
	text += myHP;
	text +=	"    Enemy HP: ";
	text +=	monhp;
	text += " ";
	c.X = 23;
	c.Y = 20;
	console.writeToBuffer(c, text, 0x79);

	COORD d;
	string question;
	question = "What is ";
	question += static_cast<char>(randomNo1) + 48;
	question += " + ";
	question += static_cast<char>(randomNo2) + 48;
	question += "?";
	d.X = 24;
	d.Y = 21;
	console.writeToBuffer(d, question, 0x0E);

	
	numberinput();

	if ( (answerIsDifferent == 0) && (playerInputted == true) )
	{
		setPlayerChangableStats();
		setMonsterChangableStats();
		HP2 -= player.damage ;//20;
		playerInputted = false;
		
	}
	else if ( (answerIsDifferent != 0) && (playerInputted == true) )
	{
		setPlayerChangableStats();
		setMonsterChangableStats();
		player.hp -= MonsterUnit.damage ;
		playerInputted = false;
		
	} 
	if (HP2 <= 0) //HP2 is monster hp
	{
		if (battleModeOn == true)
		{
			battleModeOn = false;
		}
		if (inBossFight == true)
		{
			bossCleared = true;
			inBossFight = false;
		}
		playerxp += monsterXP;
		initializeHP = false;
	}
	if (( player.hp <= 0 ) && ((battleModeOn == true) || (inBossFight == true)))
	{
		battleModeOn = false;
		playerDead = true;
	}
}

void readMap(string str)
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile (str);

    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for ( int x = 0; x < mapline.length(); x++ )
            {
                mapArray[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readBattleScreen(string str)
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile(str);
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for ( int x = 0; x < mapline.length(); x++ )
            {
                battleArray[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readBattleScreen2(string str)
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile (str);
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for ( int x = 0; x < mapline.length(); x++ )
            {
                battleArrayALT[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readBossScreen(string str)
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile (str);
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for ( int x = 0; x < mapline.length(); x++ )
            {
                bossArray[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readBossScreen2(string str)
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile (str);
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for ( int x = 0; x < mapline.length(); x++ )
            {
                bossArrayALT[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void drawMap()
{
	for (int i = 0; i < 22;)
	{
		for (int j = 0; j < 79; ++j)
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
		for (int j = 0; j < 79; ++j)
		{
			char toBePrinted = battleArray[i][j];
			renderPrintedText(toBePrinted,j,i);
		}
		i++;
	}
	printBattleStats();
}

void numberinput()
{
	if ( keyPressed[K_1] )
	{
		answer += ( '1' );
	}
	else if ( keyPressed[K_2] )
	{
		answer += ( '2' );
	}
	else if ( keyPressed[K_3] )
	{
		answer += ( '3' );
	}
	else if ( keyPressed[K_4] )
	{
		answer += ( '4' );
	}
	else if ( keyPressed[K_5] )
	{
		answer += ( '5' );
	}
	else if ( keyPressed[K_6] )
	{
		answer += ( '6' );
	}
	else if ( keyPressed[K_7] )
	{
		answer += ( '7' );
	}
	else if ( keyPressed[K_8] )
	{
		answer += ( '8' );
	}
	else if ( keyPressed[K_9] )
	{
		answer += ( '9' );
	}
	else if ( keyPressed[K_0] )
	{
		answer += ( '0' );
	}
	else if ( (keyPressed[K_BACKSPACE]) && (answer.length() > 0) )
	{
		answer.erase(answer.length() - 1 ) ;
	}
	else if ( keyPressed[K_ENTER] )
	{
		if ( answer.compare(battleAnswer) == 0 )
		{
			answerIsDifferent = false;
			playerInputted == true;
			monsterHP -= 15;
		}
		else if ( answer.compare(battleAnswer) != 0 )
		{
			answerIsDifferent = true;
			playerInputted == true;
			charHP -= 30;
		}
	}
	COORD e;
	e.X = 20 ;
	e.Y = 23 ;
	console.writeToBuffer(e, answer, 0x0C);
}

void drawBattleScreenALT()
{
	for (int i = 0; i < 20;)
	{
		for (int j = 0; j < 79; ++j)
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
		for (int j = 0; j < 79; ++j)
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
		for (int j = 0; j < 79; ++j)
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

void renderMap()
{
	// Set up sample colours, and output shadings
	const WORD stage1colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	/*COORD c;
	for (int i = 0; i < 12; ++i)
	{
		c.X = 5 * i;
		c.Y = i + 1;
		colour(colors[i]);
		console.writeToBuffer(c, " °±²Û", colors[i]);
	}*/

	/*if (battleModeOn == true)
	{
		drawBattleScreen();
	}
	else if (battleModeOn == false)
	{
		drawMap();
	}*/
	renderSelection();
}

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
    ss << 1.0 / deltaTime << "fps";
    c.X = console.getConsoleSize().X - 9;
    c.Y = 0;
    console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << elapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    console.writeToBuffer(c, ss.str(), 0x59);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    console.flushBufferToConsole();
}

//Checks if player is at the Chest.
void detectChest()
{
    chestOpen();
}

void chestOpen()
{
    if (mapArray[charLocation.Y][charLocation.X] == 'C')
    {
        //insert item codes
        mapArray[charLocation.Y][charLocation.X] = 'G';
        status += 20;
        player.hp += 200;
    }
	if (mapArray[charLocation.Y][charLocation.X] == 'R')
    {
        //insert item codes
        mapArray[charLocation.Y][charLocation.X] = 'G';
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

void readPortal()
{
        string mapline;
        int y2 = 0;
        ifstream stageClr ("endscreen.txt");
        if (stageClr.is_open())
        {
            while (getline (stageClr,mapline))
            {
                for ( int x = 0; x < mapline.length(); x++ )
                {
                    screenArray[y2][x] = mapline[x];
                }
                ++y2;
            }
        }
        stageClr.close();
}

void portalrender()
{
        for (int i = 0; i < 25; ++i)
	    {
		        for (int j = 0; j < 78; ++j)
		        {
			        char EndScreen = screenArray[i][j];
			        if (EndScreen == '1')
			        {
				        EndScreen = 178; // ▓
				        console.writeToBuffer(j,i, EndScreen, 0x7F); // White [Walls]
			        }
			        else if (EndScreen == 'W')
			        {
				        EndScreen = 176; // ░
				        console.writeToBuffer(j,i, EndScreen, 0x8F); // Grey [Walls]
			        }
			        else if (EndScreen == 'S')
			        {
				        EndScreen = 176; // ░
				        console.writeToBuffer(j,i, EndScreen, 0x00); // Blk [Spaces]
			        }
			        else
			        {
				        console.writeToBuffer(j,i, EndScreen, 0x0B); // Color The Underscores dases and so, Blue.
			        }
		        }
         }
}

void readGameOver()
{
        string mapline;
        int y2 = 0;
        ifstream gameOver ("gameover.txt");
        if (gameOver.is_open())
        {
            while (getline (gameOver,mapline))
            {
                for ( int x = 0; x < mapline.length(); x++ )
                {
                    screenArray[y2][x] = mapline[x];
                }
                ++y2;
            }
        }
        gameOver.close();
}

void renderGameOver()
{
    for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = screenArray[i][j];
			renderPrintedText( toBePrinted,j,i );
		}
     }
	if ((currAtStage == 2) && (atPortal == true))
	{
		currState = G_StageCleared;
	}
	if (  keyPressed[K_SPACE] )
	{
	if ((currAtStage == 1)  && (atPortal == true) )
	{
			currState = G_Stage2;
			atPortal = false;
	}
	}
	//currState = G_Stage2;
	bossCleared = false;
	renderedChar = false;
}
 
void readGameOver()
{
    string mapline;
    int y2 = 0;
    ifstream gameOver ("gameover.txt");
    if (gameOver.is_open())
    {
        while (getline (gameOver,mapline))
        {
            for ( int x = 0; x < mapline.length(); x++ )
            {
                ggArray[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    gameOver.close();
}

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
}

void readLoadScreen(string str)
{
	string line;
    int y = 0;
	
    ifstream loadScrn(str);
    if (loadScrn.is_open())
    {
        while (getline (loadScrn, line))
        {
            for ( int x = 0; x < line.length(); x++ )
            {
                loadScrnArray[y][x] = line[x];
            }
            ++y;
        }
    }
    loadScrn.close();
}

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