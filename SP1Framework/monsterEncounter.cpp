#include "monsterEncounter.h"

int random_function();
int monsterSelection(int val);
void random();
int randomenc = 0;
int encounterCheck()
{
	int monster = monsterSelection(random_function());
	return monster;
}
void random()
{
	srand(time(NULL));
	randomenc = rand()%50 + 1;
}
int random_function()
{
	int encounterCheck;
	//srand((unsigned)time(0));
	encounterCheck = randomenc;
	return encounterCheck;

}

int monsterSelection(int var)
{
	int noOfMonsters= 1;
	int selectedMonster;
	bool encounter = false;
	bool check = false;
	int encounterUp = 0;
	if ((var >= 30 - encounterUp) && (encounter == false))
	{
		encounter = true;
	}
	else if (encounter == false)
	{
		++encounterUp;
		return 0;
	}
	if (encounter == true && (check == false))
	{
		//Monster Encountered
		check = true;
		selectedMonster = (var - (static_cast<int>(var/noOfMonsters) * noOfMonsters));
		switch (selectedMonster)
		{
			case 1: return 1;
					break;
			default: return 1;
					break;
		}
	}
}