#include "readFunc.h"
extern class Console console;

void readMap(string str,char mapArray[22][78])
{
	string mapline;
    int y2 = 0;
    ifstream mymapfile (str);

    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for (unsigned int x = 0; x < mapline.length(); x++ )
            {
                mapArray[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readEndBattleStats(string str,char endBattleArray[25][78])
{
	string mapline;
    int y2 = 0;
    ifstream mymapfile (str);

    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for (unsigned int x = 0; x < mapline.length(); x++ )
            {
                endBattleArray[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readMenu(string str,char menuArray[22][78])
{
	string line;
    int y2 = 0;
    ifstream menuFile (str);

    if (menuFile.is_open())
    {
        while (getline (menuFile, line))
        {
            for (unsigned int x = 0; x < line.length(); x++ )
            {
                menuArray[y2][x] = line[x];
            }
            ++y2;
        }
    }
    menuFile.close();


}

void readGameCleared(string str,char gameClearedArray[25][78])
{
	string line;
    int y2 = 0;
    ifstream menuFile (str);

    if (menuFile.is_open())
    {
        while (getline (menuFile, line))
        {
            for (unsigned int x = 0; x < line.length(); x++ )
            {
                gameClearedArray[y2][x] = line[x];
            }
            ++y2;
        }
    }
    menuFile.close();
}
 
void readTutorial(string str, char instructionArray[22][78])
{
	string line;
	int y2 = 0;
	ifstream controlfile(str);

	if (controlfile.is_open())
	{
		while (getline(controlfile, line))
		{
			for (unsigned int x = 0; x < line.length(); x++)
			{
				instructionArray[y2][x] = line[x];
			}
			++y2;
		}
	}
	controlfile.close();
}
void readDifficulty(string str, char difficultysetArray[22][78])

{
	string line;
	int y2 = 0;
	ifstream controlfile(str);

	if (controlfile.is_open())
	{
		while (getline(controlfile, line))
		{
			for (unsigned int x = 0; x < line.length(); x++)
			{
				difficultysetArray[y2][x] = line[x];
			}
			++y2;
		}
	}
	controlfile.close();
}

void readOptionsMenu(string str,char optionArray[22][78])
{
	string line;
    int y2 = 0;
    ifstream controlfile (str);

    if (controlfile.is_open())
    {
        while (getline (controlfile, line))
        {
            for (unsigned int x = 0; x < line.length(); x++ )
            {
                optionArray[y2][x] = line[x];
            }
            ++y2;
        }
    }
    controlfile.close();
}
void readPortal(string str,char screenArray[25][78])
{
        string mapline;
        int y2 = 0;
        ifstream stageClr (str);
        if (stageClr.is_open())
        {
            while (getline (stageClr,mapline))
            {
                for (unsigned int x = 0; x < mapline.length(); x++ )
                {
                    screenArray[y2][x] = mapline[x];
                }
                ++y2;
            }
        }
        stageClr.close();
}

void readBattleScreen(string str,char battleArray[20][78])
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile(str);
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for (unsigned int x = 0; x < mapline.length(); x++ )
            {
                battleArray[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readBattleScreen2(string str,char battleArrayALT[20][78])
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile (str);
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for (unsigned int x = 0; x < mapline.length(); x++ )
            {
                battleArrayALT[y2][x] = mapline[x];
            }

            ++y2;
        }
    }
    mymapfile.close();
}

void read2ndBattleScreen(string str,char battleArray2[20][78])
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile(str);
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for (unsigned int x = 0; x < mapline.length(); x++ )
            {
                battleArray2[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void read2ndBattleScreen2(string str,char battleArray2ALT[20][78])
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile (str);
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for (unsigned int x = 0; x < mapline.length(); x++ )
            {
                battleArray2ALT[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readBossScreen(string str,char bossArray[20][78])
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile (str);
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for (unsigned int x = 0; x < mapline.length(); x++ )
            {
                bossArray[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readBossScreen2(string str,char bossArrayALT[20][78])
{
    string mapline;
    int y2 = 0;
    ifstream mymapfile (str);
    if (mymapfile.is_open())
    {
        while (getline (mymapfile,mapline))
        {
            for (unsigned int x = 0; x < mapline.length(); x++ )
            {
                bossArrayALT[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    mymapfile.close();
}

void readGameOver(string str,char ggArray[25][78])
{
    string mapline;
    int y2 = 0;
    ifstream gameOver (str);
    if (gameOver.is_open())
    {
        while (getline (gameOver,mapline))
        {
            for (unsigned int x = 0; x < mapline.length(); x++ )
            {
                ggArray[y2][x] = mapline[x];
            }
            ++y2;
        }
    }
    gameOver.close();
}

void readStoryScreen(string str,char storyArray[25][78])
{
	string line;
    int y = 0;
	
    ifstream scrn(str);
    if (scrn.is_open())
    {
        while (getline (scrn, line))
        {
            for (unsigned int x = 0; x < line.length(); x++ )
            {
                storyArray[y][x] = line[x];
            }
            ++y;
        }
    }
    scrn.close();
}
