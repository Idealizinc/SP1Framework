﻿#include "rendFunc.h"
#include "Framework\console.h"

extern class Console console;
extern bool playerDead, mainMenu, loading, inBossFight, bossCleared, battleModeOn, atPortal, renderedChar, playerInputOn, locationSaved, animate, animate2, keyPressed[K_COUNT], initializeHP;
extern COORD charLocation;
extern enum GameStates currState;
extern int xSpawnCoord, ySpawnCoord, xReturnCoord, yReturnCoord, status, randomsign, randomNo2, randomNo1, currAtStage, monsterHP, foeHP, foeLVL;
extern char screenArray[25][78], loadScrnArray[25][78], menuArray[25][78], mapArray[22][78], ggArray[25][78], bossArray[20][78], bossArrayALT[20][78], battleArray[20][78], battleArrayALT[20][78], instructionArray[25][78], battleArray2[20][78], battleArray2ALT[20][78];
extern struct Hero player;
extern struct Boss BossUnit;
extern double deltaTime, elapsedTime, attkTime;
extern bool selectionMade;
extern int selection;

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

void animateBSNorm() // Battle Screen Anims
{
	if (selectionMade == false)
	{
		srand(elapsedTime);
		selection = rand()%2 + 1;
		selectionMade = true;
	}
	if (selection == 1)
	{
		std::cout << "CAT" << std::endl;
		if (animate == false)
		{
			drawBattleScreen2();
			animate = true;
		}
		else
		{
			drawBattleScreen2ALT();
			animate = false;
		}
	}
	else if (selection == 2)
	{
		std::cout << "DEVIL" << std::endl;
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
	}
		
	printBattleStats();
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
			case 4: currState = G_StageCleared; break;
		}
		atPortal = false;
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
			case 4: currState = G_Stage4; break;
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
	if ( keyPressed[K_ESCAPE] )
    {
        currState = G_MainMenu;
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
	string text = "Press 'escape' to return to the main menu.";
	console.writeToBuffer(X, text, 0xFC);
}