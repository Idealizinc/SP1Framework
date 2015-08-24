#include "exp.h"

unsigned int pLevel = 1;
unsigned int pEXPreq = 500; //EXP Requirement to LEvel
unsigned int pEXP = 0;      //Player's own EXP
unsigned int monEXP;        //Probably dead
unsigned short diffLevel;   //Difficulty Setting
unsigned int EXPmulti = 0;  //EXP multiplier
bool levelUp = false;       //check if player level up

//Here is the monster EXP.
unsigned int batEXP = 1;
unsigned int slimeEXP = 1;

void playerEXP()
{
    //put if player kills something and stuff
    //if (batDead)
    //{
    //    pEXP = batEXP * diffLevel;
    //}
    playerLevel();
}

void playerLevel() //Only call if player defeats a monster.
{
    if ((pEXP >= pEXPreq) && (levelUp = false)) //Check if exp hits requirement.
    {
        levelUp = true;
        ++pLevel;   //adds a level
        if (pEXP == pEXPreq) //if equal.
        {
            pEXP = 0;   //resets player EXP to 0
        }
        else //If above and different.
        {
            pEXP -= pEXPreq; //minus off extra exp and reassign it.
        }
    }
    playerEXPreq(); //call player exp
}

void playerEXPreq()
{
    //pEXPreq = 500; default exp
    if (levelUp == true)
    {
        pEXPreq *= 1.25;
        levelUp == false;
    }
}

void difficulty()
{
    if (diffLevel == 1)
    {
        EXPmulti = 125;
    }
    if (diffLevel == 2)
    {
        EXPmulti = 100;
    }
    if (diffLevel == 3)
    {
        EXPmulti = 75;
    }
}