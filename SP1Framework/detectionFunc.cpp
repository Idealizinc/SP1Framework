#include "detectionFunc.h"

extern bool bossCleared, inBossFight, battleModeOn;
extern char mapArray[22][78];
extern COORD charLocation;
extern int limitEXP, playerDmg, status, currAtStage, foeHP, foeLVL, monsterHP, monsterXP;
extern struct Hero player;
extern struct Boss BossUnit;
extern struct Monster MonsterUnit;
extern int yGateCoord, xGateCoord;
extern int leverFlip;

extern unsigned int difficultySet;

void bossFightCheck()
{
    if ((mapArray[charLocation.Y][charLocation.X] == 'X') && (bossCleared == false))
    {
        inBossFight = true;
    }
}

void leverpull()
{
	if (mapArray[charLocation.Y][charLocation.X] == 'K')
	{
		mapArray[yGateCoord][xGateCoord] = 'V';
		mapArray[charLocation.Y][charLocation.X] = 'V';
        leverFlip += 20;
	}
}

void chestOpen()
{
    if (mapArray[charLocation.Y][charLocation.X] == 'C')
    {
        //insert item codes
        mapArray[charLocation.Y][charLocation.X] = 'V';
        status += 20;
        player.hp += 200;
		player.exp += 50*player.level;
    }
	if (mapArray[charLocation.Y][charLocation.X] == 'R')
    { 
        //insert item codes
        mapArray[charLocation.Y][charLocation.X] = 'V';
        status -= 20;
        player.hp -= 100;
    }
}

void initiallizePlayerStats()
{
	int rngdamage = rand() % 10 + 50;
	player.level = 1;
    player.chance = 7 - difficultySet;
    player.exp = 0;
	player.hp = 1000;
	player.damage = 2;
	player.expCap = 50 * player.level;
	limitEXP = player.expCap;
    playerDmg = player.damage;
}

void setPlayerChangableStats()
{
	player.expCap = 50 * player.level;
    playerDmg = player.damage;
}

void initiallizeMonsterStats()
{
    //difficultySet 1 2 3.
	srand((unsigned)time(0));
	MonsterUnit.level = (rand()% 5 + (currAtStage * (difficultySet + 2) + player.level));
	MonsterUnit.hp = ((currAtStage * (player.level * (difficultySet + 1))) * difficultySet + (player.level * 2));   // previously x2
	MonsterUnit.expgiven =rand()%20 + (4 - difficultySet) * (MonsterUnit.level + (4 - difficultySet));

    BossUnit.level = 20 + (difficultySet * currAtStage) + player.level;
	BossUnit.hp = ((currAtStage * 3) * (player.level * difficultySet)) * 2;
	BossUnit.expgiven = 200 * (currAtStage * (difficultySet + 1));

	monsterHP = MonsterUnit.hp;
	if ( battleModeOn == true )
	{
		monsterXP = MonsterUnit.expgiven;
		foeHP = monsterHP;
        foeLVL = MonsterUnit.level;
	}
	else if ( inBossFight == true )
	{
		monsterXP = BossUnit.expgiven;
		foeHP = BossUnit.hp;
        foeLVL = BossUnit.level;
	}
}

void setMonsterChangableStats()
{
	int monsterDamage = rand() % 20 + ((60 * (difficultySet + 1)) + (player.level * 5))/*(20 * (currAtStage + 1) * player.level)*/;
	int bossDamage = rand() % 50 + (100 * ((currAtStage * player.level + difficultySet) / 2 ));
	MonsterUnit.damage = 10 + monsterDamage;
	BossUnit.damage = bossDamage;
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
    player.damage += ((difficultySet + player.level) * 3) / ((player.level + 1) * difficultySet);
    player.level += 1;
    player.exp -= player.expCap;
    player.expCap = 50 * player.level;
    player.hp += 150;
}