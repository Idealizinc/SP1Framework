#include "readFunc.h"


void readMap(string str,char mapArray[22][79])
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

void readMenu(string str,char menuArray[22][79])
{
	string line;
    int y2 = 0;
    ifstream menuFile (str);

    if (menuFile.is_open())
    {
        while (getline (menuFile, line))
        {
            for ( int x = 0; x < line.length(); x++ )
            {
                menuArray[y2][x] = line[x];
            }
            ++y2;
        }
    }
    menuFile.close();
}
 
void readPortal(string str,char screenArray[25][79])
{
        string mapline;
        int y2 = 0;
        ifstream stageClr (str);
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

void readBattleScreen(string str,char battleArray[20][79])
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

void readBattleScreen2(string str,char battleArrayALT[20][79])
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

void readBossScreen(string str,char bossArray[20][79])
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

void readBossScreen2(string str,char bossArrayALT[20][79])
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

void readGameOver(string str,char ggArray[25][79])
{
    string mapline;
    int y2 = 0;
    ifstream gameOver (str);
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

void readLoadScreen(string str,char loadScrnArray[25][79])
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