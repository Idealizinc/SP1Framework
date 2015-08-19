// This is the main file for the game logic and function
//testing
//hello
#include "game.h"
#include "map.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "conio.h"

using namespace std;

double elapsedTime;
double deltaTime;
bool willCollide;
bool keyPressed[K_COUNT];
int Wall = 0;
COORD charLocation;
COORD consoleSize;


void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"SP1 Framework");

    // Sets the console size, this is the biggest so far.
    setConsoleSize(79, 28);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = consoleSize.X / 2;
    charLocation.Y = consoleSize.Y / 2;

    elapsedTime = 0.0;
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
            Beep(1440, 30);
            charLocation.Y--;
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
        Beep(1440, 30);
        charLocation.X--; 
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        Beep(1440, 30);
        charLocation.Y++; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
        Beep(1440, 30);
        charLocation.X++; 
    }

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;

    //Temporary  wall thingy (Doesn't Work)

    //int detect[100][100];
    //int ch = 0;

    //while(1)
    //{
    //    switch((ch = getch()))
    //    {
    //    case keyPressed[K_UP]:;
    //        if (charLocation.Y > 0 && detect[charLocation.Y - 1][charLocation.X] == '=')
    //        {
    //            charLocation.Y--;
    //        };
    //        break;
    //    }
    //}

    /*Try Look ahead before moving*/
    int aWall[100][100];

    for (int i = 0; i < 75; i++)
    {
        if (aWall[charLocation.Y + 1][charLocation.X + 1] == 1)
        {
            willCollide = true;
            break;
        }
        else
        {
            willCollide = false;
            break;
        }
    }
}

void render()
{
    // clear previous screen
    colour(0x0F);
    //cls();
    // Map Generate
    createMap();
    //render the game

    //Stone Tile Rendering.
    //const WORD color[] = {0x88};

    //for (int i = 0; i < 20; ++i)
    //{
    //    for (int p = 0; p < 75; ++p)
    //    {
    //        //if ( /*Insert Variable Name*/ == "▓")
    //        //{
    //            gotoXY(2 + p, 1 + i);
    //            colour(color[0]);
    //            std::cout << "p"; 
    //            //break;
    //        //}
    //    }
    //}

    //render test screen code (not efficient at all)
 //   const WORD colors[] =   {
	//                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	//                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	//                        };
	//
	//for (int i = 0; i < 32; ++i)
	//{
	//	gotoXY(3*i,i+1);
	//	colour(colors[i]);
	//	std::cout << "WOW";
	//}

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

    // render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;


    //FRAME UI
for (int i = 1; i < 20; ++i)
    {
        for (int p = 2; p < 75; ++p)
        {
            if ((i == 1) || (i == 19))
            {
                gotoXY(p, i);
                //colour(0x1A);
                std::cout << "=";
                //Wall = 1;
            }
            if (p == 2)
            {
                gotoXY(p, i);
                //colour(0x1A);
                std::cout << "|";
                //Wall = 1;
            }
            if (p == 74)
            {
                gotoXY(p, i);
                //colour(0x1A);
                std::cout << "|";
                //Wall = 1;
            }
        }
    }
cout << '\n';

<<<<<<< HEAD
    
=======
    // Map Generate
//string line;
//char s[100][100];
//ifstream myfile;
//myfile.open ("map.txt");
//if (myfile.is_open())
//{
//    //gotoXY(2,2);
//    while (getline(myfile,line))
//    {
//        for (int row = 1; row < 19; row++)
//        {
//            for (int col = 0; col < 74; col++)
//            {
//                gotoXY(col + 1,row);
//                colour(0x1A);
//
//                cout << line[col] << '\n';
//            }
//        }
//         myfile.close();
//    }
//}
//else
//{
//    cout << "Unable to open file";
//}

    
char Map [20][75] = {{1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                     {1 ,2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2 ,1 , 2, 1},
                   };

<<<<<<< Updated upstream
>>>>>>> origin/master
=======
    for (int row = 2; row < 19; row++)
    {
        for (int col = 3; col < 74; col++)
        {
            gotoXY(col,row);
            colour(0x2B);
            char mapCode = Map[row][col];
            mapConvert(mapCode);
            //std::cout << mapCode;
        }
    } 
}
>>>>>>> Stashed changes


void mapConvert(char code)
{
    char S = 219;
    char P = 176;
    if (code == 1)
    {
        code = S;
        std::cout << code;
    }
    else if (code == 2)
    {
        code = P;
        std::cout << code;
    }
}

/* Collision.
Check up [Y - 1][X + 1]
check down [Y + 1][X - 1]
check left [y][x -1]
check right [y][x + 1] */
