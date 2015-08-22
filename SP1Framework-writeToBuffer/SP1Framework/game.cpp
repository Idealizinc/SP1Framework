﻿// This is the main file for the game logic and function
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
char battleArray[22][79];
char screenArray[28][79];
int xSpawnCoord = 0, ySpawnCoord = 0;
int xReturnCoord, yReturnCoord;
bool renderedChar = false;

int chest0 = 0;
int chest1 = 0;

//For Battle Scrn & Battle Anim
bool battleModeOn = false; // SET TO FALSE LATER
bool animate = true;
int monsterFound; 
bool playerInputOn = true;

//For Portal End Stage
bool atPortal = false;

// Game specific variables here
COORD charLocation;


// Initialize variables, allocate memory, load data from file, etc. 
// This is called once before entering into your main loop
void init()
{
    // Set precision for floating point output
    elapsedTime = 0.0;

    readMap();
    readPortal();


    charLocation.X = console.getConsoleSize().X / 2;
    charLocation.Y = console.getConsoleSize().Y / 2;
    // sets the width, height and the font name to use in the console
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
		keyPressed[K_UP] = isKeyPressed(VK_UP);
		keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
		keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
		keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	}
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

/*
    This is the render loop
    At this point, you should know exactly what to draw onto the screen.
    Just draw it!
    To get an idea of the values for colours, look at console.h and the URL listed there
*/
void render()
{
	//readBattleScreen();
    clearScreen();      // clears the current screen and draw from scratch 
    renderMap();        // renders the map to the buffer first

    //Portal Screen
    if (mapArray[charLocation.Y][charLocation.X] == 'E')
    {
        atPortal = true;
    }
    if (atPortal == true)
    {
        clearScreen();
        portalrender();
    }

    if (animate == false)
    {
        readBattleScreen();
        animate = true;
    }
    else
    {
        readBattleScreen2();
        animate = false;
    }

	if ((battleModeOn == false) && (renderedChar == true))
	{
		renderCharacter();  // renders the character into the buffer
		xReturnCoord = charLocation.X;
		yReturnCoord = charLocation.Y;
	}
	else if (battleModeOn == true)
	{
		charLocation.X = 100;
		charLocation.Y = 100;
		playerInputOn = false;
	}
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
	if (renderedChar == false)
	{
		charLocation.X = xSpawnCoord;
		charLocation.Y = ySpawnCoord;
		renderedChar = true;
	}
}

void moveCharacter()
{
	int monster;
    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        if ((mapArray[charLocation.Y - 1][charLocation.X] != 'W') && 
            (mapArray[charLocation.Y - 1][charLocation.X] != '1') &&
            (mapArray[charLocation.Y - 1][charLocation.X] != 'T'))
        {

            //Beep(1440, 30);
            charLocation.Y--;
			//monster = encounterCheck();
			//if (monster != 0)
			//{
			//	battleModeOn = true;
			//}
        }
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
        if ((mapArray[charLocation.Y][charLocation.X - 1] != 'W') &&
            (mapArray[charLocation.Y][charLocation.X - 1] != '1') &&
            (mapArray[charLocation.Y][charLocation.X - 1] != 'T'))
        {
            //Beep(1440, 30);
            charLocation.X--;
			//monster = encounterCheck();
			//if (monster != 0)
			//{
			//	battleModeOn = true;
			//}
        }
    }
    if (keyPressed[K_DOWN] && charLocation.Y < console.getConsoleSize().Y - 1)
    {
        if ((mapArray[charLocation.Y + 1][charLocation.X] != 'W') && 
            (mapArray[charLocation.Y + 1][charLocation.X] != '1') &&
            (mapArray[charLocation.Y + 1][charLocation.X] != 'T'))
        {
            //Beep(1440, 30);
            charLocation.Y++;
			//monster = encounterCheck();
			//if (monster != 0)
			//{
			//	battleModeOn = true;
			//}
        }
    }
    if (keyPressed[K_RIGHT] && charLocation.X < console.getConsoleSize().X - 1)
    {
        if ((mapArray[charLocation.Y][charLocation.X + 1] != 'W') && 
            (mapArray[charLocation.Y][charLocation.X + 1] != '1') && 
            (mapArray[charLocation.Y][charLocation.X + 1] != 'T'))
        {
            //Beep(1440, 30);
            charLocation.X++;
			//monster = encounterCheck();
			//if (monster != 0)
			//{
			//	battleModeOn = true;
			//}
        }
    }

    chest();
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    console.clearBuffer(0x0F);
}
void readMap()
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile ("map1.txt");
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for ( int x = 0; x < mapline.length(); x++ )
            {
                mapArray[y2][x] = mapline[x];
				//cout << mapArray[y2][x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readBattleScreen()
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile ("batanimation1.txt");
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for ( int x = 0; x < mapline.length(); x++ )
            {
                battleArray[y2][x] = mapline[x];
				//cout << mapArray[y2][x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readBattleScreen2()
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile ("batanimation2.txt");
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for ( int x = 0; x < mapline.length(); x++ )
            {
                battleArray[y2][x] = mapline[x];
				//cout << mapArray[y2][x];
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
			if (toBePrinted == ' ')
			{
				toBePrinted = 176; // ░
            	console.writeToBuffer(j,i, toBePrinted, 0x8A); // Dirty Green [Grass]
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
			else if (toBePrinted == 'T')
			{
				toBePrinted = 5; // ♣
				console.writeToBuffer(j,i, toBePrinted, 0x8A); // Green [Trees]
			}
			else if (toBePrinted == 'P')
			{
				xSpawnCoord = j; // Obtain spawn coordinates for player
				ySpawnCoord = i;
				toBePrinted = 176; // ░ Fill up space under player.
            	console.writeToBuffer(j,i, toBePrinted, 0x8A); // Dirty Green [Grass]
			}
			else if (toBePrinted == 'C')
			{
				toBePrinted = 254; // ■
				console.writeToBuffer(j,i, toBePrinted, 0x2E); // Gold [Chests]
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
			//else
			//	console.writeToBuffer(j,i, toBePrinted, 0x4A); // Coloration Failed - Red BG Green Txt
		}
		i++;
	}
}

void drawBattleScreen()
{
	for (int i = 0; i < 22;)
	{
		for (int j = 0; j < 79; ++j)
		{
			char toBePrinted = battleArray[i][j];
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
			else
				console.writeToBuffer(j,i, toBePrinted, 0x8F); // Coloration Failed - blk Txt
		}
		i++;
	}
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

	if (battleModeOn == true)
	{
		drawBattleScreen();
	}
	else if (battleModeOn == false)
	{
		drawMap();
	}
	renderCharacter();  // renders the character into the buffer
}

void renderCharacter()
{
    // Draw the location of the character
    console.writeToBuffer(charLocation, (char)2, 0x2F);
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
void chest()
{
    //cout << charLocation.Y;
    if (mapArray[charLocation.Y][charLocation.X] == 'C')
    {
        //(charLocation.Y == 19 && charLocation.X == 43])
        if ((chest0 == 0) && ((charLocation.Y == 19) && (charLocation.X == 43)))
        {
            //Added (random) items!
            cout << "potato gained";
            ++chest0;
        }
        if ((chest1 == 0) &&  ((charLocation.Y == 2) && (charLocation.X == 71)))
        {
            //Added (random) items!
            cout << "potato gained";
            ++chest1;
        }
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
    for (int i = 0; i < 28; ++i)
	    {
		    for (int j = 0; j < 79; ++j)
		    {
			    char EndScreen = screenArray[i][j];
                cout << EndScreen;
                if (EndScreen == ' ')
                {
                    EndScreen = 176;
                    console.writeToBuffer(i,j, EndScreen, 0xB8);
                }
             }
        }
    atPortal = false;
}