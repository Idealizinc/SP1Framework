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