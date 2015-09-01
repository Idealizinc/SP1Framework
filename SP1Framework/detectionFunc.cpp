#include "detectionFunc.h"

extern bool bossCleared, inBossFight, battleModeOn;
extern char mapArray[22][78];
extern COORD charLocation;
extern int limitEXP, playerDmg, status, currAtStage, foeHP, foeLVL, monsterHP, monsterXP;
extern struct Hero player;
extern struct Boss BossUnit;
extern struct Monster MonsterUnit;
extern int yGateCoord, xGateCoord;

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
    player.chance = 3;
    player.exp = 0;
    //player.expCap = 100;
	player.hp = 1000 + ((player.level) * 100);
	player.damage = 2;
	player.expCap = 50 * player.level;
	limitEXP = player.expCap;
    playerDmg = player.damage;
}

void setPlayerChangableStats()
{
	//player.hp = 1000 + ((player.level) * 100);
	//player.damage = 2;
    //player.chance = 3;
	player.expCap = 50 * player.level;
    playerDmg = player.damage;
}

//
//    int level;
//	int hp;
//	int damage;
//	int expgiven;
//};
void initiallizeMonsterStats()
{
	srand((unsigned)time(0));
	MonsterUnit.level = (rand()% 5 + (currAtStage * (player.level + 5) + currAtStage ));
	MonsterUnit.hp = (MonsterUnit.level);   // Got x2
	MonsterUnit.expgiven = ((rand()%3) + 1) * MonsterUnit.level;
    BossUnit.level = 20 + (currAtStage * (player.level * 2));
	BossUnit.hp = BossUnit.level * 2;
	BossUnit.expgiven = 5000;
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
	int monsterDamage = rand() % 20 + 50 /*(20 * (currAtStage + 1) * player.level)*/;
	int bossDamage = rand() % 50 + (100 * ((currAtStage + 1) / 2 ));
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
    player.damage += (7 - currAtStage);
    player.level += 1;
    player.exp -= player.expCap;
    player.expCap = 50 * player.level;
}