#include "monsterEncounter.h"

int random_function();			//Encounter rate
int monsterSelection(int val);	// Chooses monster to fight
void random();
int randomenc = 0;				//Encounter
int encounterUp = 0;			// Adds to encounter rate
int rate = 250; // Higher rate lower encounter //Default 250.

int encounterCheck()
{
	int monster = monsterSelection(random_function());
	return monster;
}
int random_function()
{
	int encounterCheck;
	srand(static_cast<unsigned int>(time(NULL)));
	encounterCheck = rand()%(rate + encounterUp); //randomenc;
	return encounterCheck;

}

int monsterSelection(int var)
{
	int noOfMonsters= 1;
	int selectedMonster;
	bool encounter = false;
	bool check = false;
	if ((var >= rate) && (encounter == false))
	{
		encounter = true;
		encounterUp = 0;
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