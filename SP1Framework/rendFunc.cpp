#include "rendFunc.h"
#include "Framework\console.h"
#include "game.h"

extern class Console console;
extern bool playerDead, mainMenu, loading, inBossFight, bossCleared, 
			battleModeOn, atPortal, renderedChar, playerInputOn, locationSaved, 
			animate, animate2, keyPressed[K_COUNT], initializeHP;
extern COORD charLocation;
extern enum GameStates currState;
extern int  xSpawnCoord, ySpawnCoord, xReturnCoord, yReturnCoord, status, 
			randomsign, randomNo2,DrandomNo2,DrandomNo3, randomNo1, currAtStage, 
			monsterHP, foeHP, foeLVL, playerlv, monsterXP, xGateCoord, yGateCoord, playerchoice;
extern char screenArray[25][78], loadScrnArray[25][78], menuArray[25][78], mapArray[22][78], 
			ggArray[25][78], bossArray[20][78], bossArrayALT[20][78], battleArray[20][78], battleArrayALT[20][78], 
			instructionArray[25][78], battleArray2[20][78], battleArray2ALT[20][78], 
			endBattleArray[25][78], optionArray[25][78], gameClearedArray[25][78], difficultysetArray[25][78];
extern unsigned int difficultySet;
extern struct Hero player;
extern struct Boss BossUnit;
extern double deltaTime, elapsedTime, attkTime;
extern bool selectionMade, mobDown, hpInitiallized;
extern int selection;
extern WORD playercolour;
int selectionPointer = 1;
bool canpress = false;
extern bool allowNumInput, limiterSet;
double storedTime2, storedtime3;
bool timeSet = false;

void renderPrintedText(char toBePrinted ,int j,int i )
{
	if (toBePrinted == 'A')
	{
		console.writeToBuffer(j,i, 176, 0x8A); // Dirty Green [Grass] ░
	}
	else if (toBePrinted == 'M')
	{
		yGateCoord = i;
		xGateCoord = j;
		console.writeToBuffer(j, i, 93, 0x8E); // "]"
	}
	else if (toBePrinted == 'W')
	{
		console.writeToBuffer(j,i, 177, 0x80); // Grey [Walls] ░
	}
	else if (toBePrinted == 'T')
	{
		console.writeToBuffer(j,i, 5, 0x8A); // Green [Trees] ♣
	}
	else if (toBePrinted == 'D')
	{
		console.writeToBuffer(j,i, 176, 0x80); // Dark Grey [Walls] ░
	}
	else if (toBePrinted == 'V')
	{
		console.writeToBuffer(j,i, 176, 0x70); // Light Grey [Floor] ░
	}
	else if (toBePrinted == 'P')
	{
		xSpawnCoord = j; // Obtain spawn coordinates for player
		ySpawnCoord = i;
		console.writeToBuffer(j,i, 176, 0x78);// ░ Fill up space under player.
	}
	else if (toBePrinted == 'C')
	{
		console.writeToBuffer(j,i, 254, 0x8E); // Gold [Chests] ■
	}
	else if (toBePrinted == 'R')
	{
		console.writeToBuffer(j,i, 254, 0x7E); // Gold [Chests] ■
	}
	else if (toBePrinted == 'E')
	{
		console.writeToBuffer(j,i, 10, 0xB8); // Blue [Portal]
	}
	else if (toBePrinted == 'X')
	{
		console.writeToBuffer(j,i, 15, 0x8C); // Red [Boss] Θ
	}
	else if (toBePrinted == '1')
	{
		console.writeToBuffer(j,i, 178, 0x7F); // White [Walls] ▓
	}
	else if (toBePrinted == 'W')
	{
		console.writeToBuffer(j,i, 176, 0x80); // Grey [Walls] ░
	}
	else if (toBePrinted == 'Z')
	{
		console.writeToBuffer(j,i, 176, 0x84); // Reddish Brown [Cave Walls] ░
	}
	else if (toBePrinted == '=')
	{
		console.writeToBuffer(j,i, 176, 0xCB); // Red [LoadBar] ░
	}
	else if (toBePrinted == '3')
	{
		console.writeToBuffer(j,i, 17, 0x0E); // [Gold] Triangles ◄
	}
	else if (toBePrinted == '2')
	{
		console.writeToBuffer(j,i, 16, 0x0E); // [Gold] Triangles ►
	}
	else if (toBePrinted == '4')
	{
		console.writeToBuffer(j,i, 30, 0x0E); // [Gold] Triangles ▲
	}
	else if (toBePrinted == '5')
	{
		console.writeToBuffer(j,i, 31, 0x0E); // [Gold] Triangles ▼
	}
	else if (toBePrinted == 'K')
	{
		console.writeToBuffer(j, i, 92, 0x8E); // "/"
	}
	else if ((loading == true) || (atPortal == true) || (mainMenu == true) || (currState == G_GameCleared) || (currState == G_Difficulty))
	{
		console.writeToBuffer(j,i, toBePrinted, 0x0B); // Color The Underscores dases and so, Blue.
	}
	else if ((playerDead == true))
	{
		console.writeToBuffer(j,i, toBePrinted, 0x0C); // Color The Underscores dashes RED.
	}
	else if ((battleModeOn == true) || ((inBossFight == true)) && (bossCleared == false))
	{
		console.writeToBuffer(j,i, toBePrinted, 0x0F); // Coloration Failed - blk Txt
	} 
}

void renderCharacter()
{
    // Draw the location of the character
    console.writeToBuffer(charLocation, (char)2, playercolour);
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

void printEndScreenText(int XP)
{
	std::ostringstream endStat;
	int lvl = player.level;
	endStat << lvl;
	std::ostringstream currplayerxp;
	std::ostringstream endxpgiven;
	int monxp = XP;
	endxpgiven << monxp;
	std::ostringstream xpremaining;
	int xpleft = player.expCap - player.exp;
	xpremaining << xpleft;
	string endstats1;
	string endstats2;
	string endstats3;
	int currentxp = player.exp;
	if ( xpleft <= 0 )
	{
		++currentxp;
	}
	currplayerxp << currentxp;
	endstats1 = "Current Level: ";
	endstats1 += endStat.str();
	endstats1 += "      Current EXP: ";
	endstats1 += currplayerxp.str();
	endstats2 += "You have gained: ";
	endstats2 += endxpgiven.str();  
	endstats2 += " EXP!";
	endstats3 += "Remaining EXP to the next Level: ";
	endstats3 += xpremaining.str();

	console.writeToBuffer(18,14, endstats1, 0x0B);
	console.writeToBuffer(18,16, endstats2, 0x0A);
	if ( xpleft > 0 )
	{
		console.writeToBuffer(18,18, endstats3, 0x0E);
	}
	if ( xpleft <= 0 )
	{
		console.writeToBuffer(18,18, "Congratulations! You have levelled UP!", 0x0E);
	}
	string text = "<Press 'space' to return to the game map>";
	console.writeToBuffer(17,20, text, 0x0D);
}

void animateBSNorm() // Battle Screen Anims
{
	if (mobDown == false)
	{
		if (selectionMade == false)
		{
			srand(static_cast<unsigned int>(elapsedTime));
			selection = rand()%2 + 1;
			selectionMade = true;
		}
		if (selection == 1)
		{
			if (timeSet == false)
			{
				storedtime3 = elapsedTime + 0.75;
				timeSet = true;
			}
			if (animate == false)
			{
				drawBattleScreen2();
				if (elapsedTime >= storedtime3) 
				{
					timeSet = false;
					animate = true;
				}
			}
			if (animate == true)
			{
				drawBattleScreen2ALT();
				if (elapsedTime >= storedtime3) 
				{
					timeSet = false;
					animate = false;
				}
			}
		}
		else if (selection == 2)
		{
			if (timeSet == false)
			{
				storedtime3 = elapsedTime + 0.75;
				timeSet = true;
			}
			if (animate == false)
			{
				drawBattleScreen();
				if (elapsedTime >= storedtime3) 
				{
					timeSet = false;
					animate = true;
				}
			}
			if (animate == true)
			{
				drawBattleScreenALT();
				if (elapsedTime >= storedtime3) 
				{
					timeSet = false;
					animate = false;
				}
			}
		}
		
		printBattleStats();
	}
	if (mobDown == true)
	{
		int XP = monsterXP;
		drawEndBattleScreen();
		
		printEndScreenText(XP);
		if (keyPressed[K_SPACE])
		{
			mobDown = false;
			battleModeOn = false;
		}
	}
}

void animateBSBoss() // Battle Screen Anims
{
	if (mobDown == false)
	{
		if (timeSet == false)
		{
			storedtime3 = elapsedTime + 0.75;
			timeSet = true;
		}
		if (animate == false)
		{
			drawBattleScreenBoss();
			if (elapsedTime >= storedtime3) 
			{
				timeSet = false;
				animate = true;
			}
		}
		if (animate == true)
		{
			drawBattleScreenBossALT();
			if (elapsedTime >= storedtime3) 
			{
				timeSet = false;
				animate = false;
			}
		}
		printBattleStats();
	}
	if (mobDown == true)
	{
		int XP = BossUnit.expgiven;
		drawEndBattleScreen();
		
		printEndScreenText(XP);
		if (keyPressed[K_SPACE])
		{
			mobDown = false;
			inBossFight = false;
			bossCleared = true;
		}
	}
}

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
	if (keyPressed[K_SPACE])
	{
		switch(currAtStage)
		{
			case 1: currState = G_Stage2; break;
			case 2: currState = G_Stage3; break;
			case 3: currState = G_Stage4; break;
			case 4: currState = G_Stage5; break;
			case 5: currState = G_Stage6; break;
			case 6: currState = G_GameCleared; break;
		}
		atPortal = false;
		//currState = G_Stage2;
		bossCleared = false;
		battleModeOn = false;
		renderedChar = false;
		playerDead = false;
	}
	if ( keyPressed[K_ESCAPE] )
    {
        switch(currAtStage)
        {
            case 1: currState = G_MainMenu; break;
        }
    }
	COORD X;
	X.X = 17;
	X.Y = 22;
	string text = "Press 'space' to go to the next stage.";
	console.writeToBuffer(X, text, 0x0B);
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
	if ( keyPressed[K_SPACE] )
	{
		switch(currAtStage)
		{
			case 1: currState = G_Stage1; break;
			case 2: currState = G_Stage2; break;
			case 3: currState = G_Stage3; break;
			case 4: currState = G_Stage4; break;
			case 5: currState = G_Stage5; break;
			case 6: currState = G_StageCleared; break;
		}
		currAtStage = 0;
		renderedChar = false;
		locationSaved = false;
		playerDead = false;
		bossCleared = false;
		hpInitiallized = false;
		battleModeOn = false;
		inBossFight = false;
		drawMapRendChar();
	}
    if ( keyPressed[K_ESCAPE] )
    {
        currState = G_MainMenu;
		currAtStage = 0;
		renderedChar = false;
		locationSaved = false;
		playerDead = false;
		bossCleared = false;
    }
}

void renderGameClear()
{
    for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = gameClearedArray[i][j];
			renderPrintedText( toBePrinted,j,i );
		}
     }
	if (keyPressed[K_SPACE])
	{
		currState = G_MainMenu;
		atPortal = false;
		bossCleared = false;
		battleModeOn = false;
		renderedChar = false;
		playerDead = false;
	}
	COORD X;
	X.X = 17;
	X.Y = 22;
	string text = "Press 'space' to return to the main menu.";
	console.writeToBuffer(X, text, 0x0A);
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

    //std::ostringstream mydmg;
    //mydmg << player.damage;
    //string myDMG = mydmg.str(); // string that contains player dmg

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
    //text += "    Damage: ";
    //text += myDMG;
	text += "    Exp: ";
	text += playerExp;
	text += " / ";
    text += mylvlCap;
	//charHP++; testing if changeable 
	c.X = 13;
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

void printBattleStats()
{
    double attackSpeed = attkTime - elapsedTime;
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

    //std::ostringstream mydmg;
    //mydmg << player.damage;
    //string myDMG = mydmg.str(); // string that contains player dmg

	string text;

	text = " My HP: ";
	text += myHP;
    //text += "    My DMG: ";
    //text += myDMG;
    text += "    Chance Left: ";
    text += myChance;
	text += " ";
	c.X = 20;
	c.Y = 19;
	console.writeToBuffer(c, text, 0xF9);

    //0xF0 (blak txt wite bg)

    //attk speed.
    COORD enemyStats;
    string Time;
    std::ostringstream attktime;
    attktime << std::fixed << std::setprecision(0);
    attktime << attackSpeed;
    Time = attktime.str();

    std::ostringstream enemylvl;
    enemylvl << foeLVL;
    string enemyLVL = enemylvl.str(); // string that contains enemy lvl

	std::ostringstream enemyhp;
	enemyhp << foeHP ;
	string monhp = enemyhp.str(); // string that contains enemy hp


    string textEnemyStat;
    textEnemyStat = " Enemy Level: ";
    textEnemyStat += enemyLVL;
	textEnemyStat += "    Enemy HP: ";
	textEnemyStat += monhp;
    textEnemyStat += "    Time till Attack: ";
    textEnemyStat += Time;
    textEnemyStat += " ";
    enemyStats.X = 12;
    enemyStats.Y = 20;
    console.writeToBuffer(enemyStats, textEnemyStat, 0xF4);


	COORD d;
	string question;
	
	switch (randomsign)
	{
		case 1: 
			question = "What is ";
			question += static_cast<char>(randomNo1) + 48;
			question += " + "; 
			question += static_cast<char>(randomNo2) + 48;
			question += " ?";
			break;
		case 2: 
			question = "What is ";
			question += static_cast<char>(randomNo1) + 48;
			question += " - "; 
			question += static_cast<char>(randomNo2) + 48;
			question += " ?";
			break;
		case 3: 
			question = "What is ";
			question += static_cast<char>(randomNo1) + 48;
			question += " x "; 
			question += static_cast<char>(randomNo2) + 48;
			question += " ?";
			break;
		case 4: 
			question = "What is ";
			string val1, val2;
			int Num1,Num2;
			if ( DrandomNo3 > 9 )
			{
				for ( unsigned int i = 0; i < 2 ;++i  )
				{
					if ( i == 0 )
					{
						Num1 = DrandomNo3 / 10;
						val1 = static_cast<char>(Num1) + 48;
					}
					else if ( i == 1 )
					{
						Num2 = DrandomNo3 - (Num1 * 10);
						val2 = static_cast<char>(Num2) + 48;
					}
				}
			}
			else if ( DrandomNo3 <= 9 )
			{
				Num2 = DrandomNo3;
				val2 = static_cast<char>(Num2) + 48;
			}
			question += val1;
			question += val2;
			question += " / "; 
			question += static_cast<char>(DrandomNo2) + 48;
			question += " ?";
			break;
	}
	d.X = 24;
	d.Y = 21;
	console.writeToBuffer(d, question, 0x0E);

	numberinput();
	checkPlayerAnswer();
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

void drawEndBattleScreen()
{
	for (int i = 0; i < 25;)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = endBattleArray[i][j];
			renderPrintedText(toBePrinted,j,i);
		}
		i++;
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

void drawBattleScreen2()
{
	for (int i = 0; i < 20;)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = battleArray2[i][j];
			renderPrintedText(toBePrinted,j,i);
		}
		i++;
	}
}

void drawBattleScreen2ALT()
{
	for (int i = 0; i < 20;)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = battleArray2ALT[i][j];
			renderPrintedText(toBePrinted,j,i);
		}
		i++;
	}
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
	else if ((playerDead == true) && (renderedChar == true))
    {
        charLocation.X = 100;
		charLocation.Y = 100;
		playerInputOn = false;
		currState = G_GameOver;
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
	else if (loading == true)
    {
		renderLoadScreen();
        charLocation.X = 100;
		charLocation.Y = 100;
		playerInputOn = false;
    }
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
	if(keyPressed[K_SPACE])
	{
		loading = false;
		currState = G_Stage1;
	}
	else if ( keyPressed[K_ESCAPE] )
    {
        currState = G_MainMenu;
    }
	if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
	{
		
		if (canpress == false)
		{
			storedTime2 = elapsedTime + 0.5;
			canpress = true;
		}
		if ((elapsedTime >= storedTime2) && (canpress == true))
		{
			allowNumInput = true;
			canpress = false;
			currState = G_StoryScreen;
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
	
	console.writeToBuffer(30,15, "<1>  Game Start", 0x0A);
	console.writeToBuffer(30,16, "<2>  Instruction", 0x0B );
	console.writeToBuffer(30,17, "<3>  Options", 0x0D );
	console.writeToBuffer(30,18, "<4>  Quit Game", 0x0E);

	if (keyPressed[K_UP])
	{
		if (selectionPointer != 1)
		{
			selectionPointer--;
		}
	}
	else if (keyPressed[K_DOWN])
	{
		if (selectionPointer != 4)
		{
			selectionPointer++;
		}
	}
	else if (keyPressed[K_1])
	{
		selectionPointer = 1;
	}
	else if (keyPressed[K_2])
	{
		selectionPointer = 2;
	}
	else if (keyPressed[K_3])
	{
		selectionPointer = 3;
	}
	else if (keyPressed[K_4])
	{
		selectionPointer = 4;
	}
	switch (selectionPointer)
	{
		case 1: console.writeToBuffer(28, 15, (char)16, 0x0F); break;
		case 2: console.writeToBuffer(28, 16, (char)16, 0x0F); break;
		case 3: console.writeToBuffer(28, 17, (char)16, 0x0F); break;
		case 4: console.writeToBuffer(28, 18, (char)16, 0x0F); break;
	}
	if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
	{
		switch (selectionPointer)
		{
		case 1: currState = G_Difficulty;
				loading = true;
				mainMenu = false;
				break;
		case 2: currState = G_Tutorial;
				break; 
		case 3: currState = G_Options;
				break;
		case 4: g_quitGame = true;
				break;
		}
	}
}

void renderOptionsMenu()
{
	for (int i = 0; i < 25; ++i)
	{
		    for (int j = 0; j < 78; ++j)
		    {
			   char toBePrinted = optionArray[i][j];
			   renderPrintedText( toBePrinted, j, i );
		    }
    }
	console.writeToBuffer(20,12, "The default character is white", 0x0F );
	console.writeToBuffer(20,13, "Press 1 for a Red Character ", 0x0C );
	console.writeToBuffer(20,14, "Press 2 for a Blue Character ", 0x09 );
	console.writeToBuffer(20,15, "Press 3 for a White Character ", 0x0F );
	console.writeToBuffer(20,16, "Press 4 for a Teal Character ", 0x0B );
	console.writeToBuffer(20,17, "Press 5 for a Yellow Character ", 0x0E );
	console.writeToBuffer(20,18, "Press 6 for a Pink Character ", 0x0D );
	console.writeToBuffer(20,19, "Press 7 for a Green Character ", 0x0A );
	console.writeToBuffer(20,20, "Press 8 for a Black Character ", 0xF0 );
	console.writeToBuffer(20,21, "Press ENTER to confirm ", 0x0F );
	if (keyPressed[K_UP])
	{
		if (playerchoice != 1)
		{
			playerchoice--;
		}
	}
	else if (keyPressed[K_DOWN])
	{
		if (playerchoice != 8)
		{
			playerchoice++;
		}
	}
	else if (keyPressed[K_1])
	{
		playerchoice = 1;
	}
	else if (keyPressed[K_2])
	{
		playerchoice = 2;
	}
	else if (keyPressed[K_3])
	{
		playerchoice = 3;
	}
	else if (keyPressed[K_4])
	{
		playerchoice = 4;
	}
	else if (keyPressed[K_5])
	{
		playerchoice = 5;
	}
	else if (keyPressed[K_6])
	{
		playerchoice = 6;
	}
	else if (keyPressed[K_7])
	{
		playerchoice = 7;
	}
	else if (keyPressed[K_8])
	{
		playerchoice = 8;
	}
	switch (playerchoice)
	{
		case 1: console.writeToBuffer(18,13, (char)16, 0x0F ); break;
		case 2:	console.writeToBuffer(18,14, (char)16, 0x0F ); break;
		case 3:	console.writeToBuffer(18,15, (char)16, 0x0F ); break;
		case 4:	console.writeToBuffer(18,16, (char)16, 0x0F ); break;
		case 5:	console.writeToBuffer(18,17, (char)16, 0x0F ); break;
		case 6:	console.writeToBuffer(18,18, (char)16, 0x0F ); break;
		case 7:	console.writeToBuffer(18,19, (char)16, 0x0F ); break;
		case 8: console.writeToBuffer(18,20, (char)16, 0x0F ); break;
	}

	if ( keyPressed[K_ENTER] )
	{
		switch ( playerchoice )
		{
			case  1  : playercolour = 0x7C; break;
			case  2  : playercolour = 0x79; break;
			case  3  : playercolour = 0x7F; break;
			case  4  : playercolour = 0x7B; break;
			case  5  : playercolour = 0x7E; break;
			case  6  : playercolour = 0x7D; break;
			case  7  : playercolour = 0x7A; break;
			case  8  : playercolour = 0x70; break;
			default :  playercolour = 0x7F; break;
		}
	}
	console.writeToBuffer(20,22,"This is how you will look like in game: ",0x0F );
	console.writeToBuffer(60,22,(char)2,playercolour );
	COORD X;
	X.X = 17;
	X.Y = 24;
	string text = "Press 'escape' to return to the main menu.";
	console.writeToBuffer(X, text, 0xFC);
	if ( keyPressed[K_ESCAPE] )
    {
        currState = G_MainMenu;
    }
}

void renderdifficultyset()
{
	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 78; ++j)
		{
			char toBePrinted = difficultysetArray[i][j];
			renderPrintedText(toBePrinted, j, i);
		}
	}

	for (unsigned int i = K_1; i <= K_3; i++)
	{
		if ((keyPressed[i]))
		{
			playerchoice = i;
			switch (playerchoice)
			{
			case  1:playerchoice = 1; difficultySet = 1; break;
			case  2:playerchoice = 2; difficultySet = 2; break;
			case  3:playerchoice = 3; difficultySet = 3; break;
			}
		}
	}
	console.writeToBuffer(20, 12, "The default difficulty is Easy", 0x0F);
	console.writeToBuffer(20, 13, "Press 1 for Easy Difficulty ", 0x0A);
	console.writeToBuffer(20, 14, "Press 2 for Normal Difficulty ", 0x0E);
	console.writeToBuffer(20, 15, "Press 3 for Hard Difficulty", 0x0C);
	console.writeToBuffer(20, 20, "Difficulty is set to: ", 0x0F);
	if (playerchoice == 1)
	{
		console.writeToBuffer(43, 20, "Easy", 0x0A);
        difficultySet = 1;
	}
	if (playerchoice == 2)
	{
		console.writeToBuffer(43, 20, "Normal", 0x0E);
        difficultySet = 2;
	}
	if (playerchoice == 3)
	{
		console.writeToBuffer(43, 20, "Hard", 0x0C);
        difficultySet = 3;
	}
	
	COORD X;
	X.X = 17;
	X.Y = 24;
	string text = "<Press 'escape' to return to the main menu>";
	
	
	if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
	{
		
		if (canpress == false)
		{
			storedTime2 = elapsedTime + 1;
			canpress = true;
		}
		if ((elapsedTime >= storedTime2) && (canpress == true))
		{
			allowNumInput = true;
			canpress = false;
			currState = G_StoryScreen;
		}
	}
	
	
	console.writeToBuffer(X, text, 0xFC);
	if (keyPressed[K_ESCAPE])
	{
		currState = G_MainMenu;
	}
	else if(keyPressed[K_SPACE])
	{
		//currState = G_LoadScreen;
	}
}

void renderTutorialScreen()
{
	for (int i = 0; i < 25; ++i)
	{
		    for (int j = 0; j < 78; ++j)
		    {
			   char toBePrinted = instructionArray[i][j];
			   renderPrintedText( toBePrinted, j, i );
		    }
    }
	if ( keyPressed[K_ESCAPE] )
    {
        currState = G_MainMenu;
    }
	COORD X;
	X.X = 17;
	X.Y = 24;
	string text = "<Press 'escape' to return to the main menu>";
	console.writeToBuffer(X, text, 0xFC);
	if ( keyPressed[K_ESCAPE] )
    {
        currState = G_MainMenu;
    }
}

void renderStoryScreen()
{
	string storytext1, storytext2, storytext3;

	for (int i = 0; i < 25; ++i)
	{
		    for (int j = 0; j < 78; ++j)
		    {
			   char toBePrinted = storyArray[i][j];
			   renderPrintedText( toBePrinted, j, i );
		    }
    }
	switch ( currAtStage )
	{
		case  1 : storytext1 = "The Demon King is planning on taking over on Goliath's Kingdom!";
					storytext2 = "King Goliath ventures out to slay the Demon King Jedric.";
					storytext3 = "Finding the levers [\] are key to disabling Jedric's Barriers!";
					break;
		case  2 : storytext1 = "Upon getting out of the forest, Goliath reaches a cave.";
					storytext2 = "Entering the cave, Goliath realizes the cave is full of bats.";
					storytext3 = "The king now has to fight off the bats with his magical powers.";
					break;
		case  3 : storytext1 = "After fighting off the bats and getting out of the cave.";
					storytext2 = "Goliath finds that he is now in a canyon.";
					storytext3 = "The king now has to find his way out of the huge maze-like canyon.";
					break;
		case  4 : storytext1 = "Unable to get out of the Canyon.";
					storytext2 = "Goliath starts to encounter even stronger monsters in the canyon.";
					storytext3 = "The king is now closer to getting out of the canyon.";
					break;
		case  5 : storytext1 = "Goliath has reached the Demon Castle after coming out of the canyon.";
					storytext2 = "Upon entering the castle, Goliath needs to find his way to Jedric.";
					storytext3 = "The king is now almost upon the Demon King.";
					break;
		case  6 : storytext1 = "King Goliath has now reached the top of the Demon Castle.";
					storytext2 = "He is now on the floor where Jedric supposedly resides.";
					storytext3 = "It is now up to Goliath to find and take down the Demon King!";
					break;
	}
	console.writeToBuffer(17,15, storytext1, 0xFC);
	console.writeToBuffer(17,16, storytext2, 0xFC);
	console.writeToBuffer(17,27, storytext3, 0xFC);
	string text = "<Press 'space' to go to the next stage>";
	COORD X;
	X.X = 17;
	X.Y = 24;
	console.writeToBuffer(X, text, 0xFC);
	if (keyPressed[K_ENTER] || keyPressed[K_SPACE])
	{
		
		if (canpress == false)
		{
			storedTime2 = elapsedTime + 0.5;
			canpress = true;
		}
		if ((elapsedTime >= storedTime2) && (canpress == true))
		{
			allowNumInput = true;
			canpress = false;
			currState = G_Stage1;
		}
	}
	if ( keyPressed[K_ESCAPE] )
    {
        currState = G_MainMenu;
    }
}