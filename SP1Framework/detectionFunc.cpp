#include "detectionFunc.h"

extern bool bossCleared, inBossFight, battleModeOn;
extern char mapArray[22][78];
extern COORD charLocation;
extern int limitEXP, playerDmg, status, currAtStage, foeHP, foeLVL, monsterHP, monsterXP;
extern struct Hero player;
extern struct Boss BossUnit;
extern struct Monster MonsterUnit;

void bossFightCheck()
{
    if ((mapArray[charLocation.Y][charLocation.X] == 'X') && (bossCleared == false))
    {
        inBossFight = true;
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
	player.damage = 1;
	player.expCap = 50 * player.level;
	limitEXP = player.expCap;
    playerDmg = player.damage;
}

void setPlayerChangableStats()
{
	int rngdamage = rand() % 10 + 50;
	//player.hp = 1000 + ((player.level) * 100);
	player.damage = 1 * 1337;
    //player.chance = 3;
	player.expCap = 50 * player.level;
    playerDmg = player.damage;
}

void initiallizeMonsterStats()
{
	srand((unsigned)time(0));
	MonsterUnit.level = (rand()%(currAtStage * 10 + 1)) + currAtStage;
	MonsterUnit.hp = (MonsterUnit.level * 2);
	MonsterUnit.expgiven = ((rand()%3) + 1) * MonsterUnit.level;
	BossUnit.hp = 300 + (MonsterUnit.level * 100);
	BossUnit.expgiven = 5000;
	monsterHP = MonsterUnit.hp;
	if ( battleModeOn == true )
	{
		monsterXP = MonsterUnit.expgiven;
		foeHP = monsterHP;
	}
	else if ( inBossFight == true )
	{
		monsterXP = BossUnit.expgiven;
		foeHP = BossUnit.hp;
	}
	foeLVL = MonsterUnit.level;
}

void setMonsterChangableStats()
{
	int monsterDamage = rand() % 20 + 50;
	int bossDamage = rand() % 10 + 100;
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
    int rngdamage = rand() % 10 + 50;
    player.level += 1;
    player.exp -= player.expCap;
    player.expCap = 50 * player.level;
}