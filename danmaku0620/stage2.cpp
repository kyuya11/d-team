#include "stage.h"
#include "Game.h"
#include "Enemy.h"
#include "ITEM.h"
#include <stdlib.h>

//aka.danup  ao.zanki kiro.baria

void Stage1()
{
	int mGameTime = Game_GetmGameTime();

	if (mGameTime % 700 == 0)
	{
		CreateItem(3, 1, rand() % 430 + 50, -10, 66, 50, 0, 1);
	}

	if (mGameTime < 100);
	else if (mGameTime < 325)
	{
		if (mGameTime % 25 == 0)
		{

			CreateEnemy(2, 0, 180, -10, 23, 26, 0, 1);
			CreateEnemy(1, 0, 280, -10, 23, 26 ,0, 1);


		}
		if (mGameTime == 200)
		{
			CreateItem(1, 0, 230, -10, 66, 50, 0, 1);

		}
	}
	else if (mGameTime < 400);
	else if (mGameTime < 600)
	{
		if (mGameTime < 500)
		{

		}
		if (mGameTime % 25 == 0)
		{
			CreateEnemy(3, 0, 1, 170, 23, 26, 3, 0);	
			CreateEnemy(4, 0, 440, 210, 23, 26, -3, 0);	
			CreateEnemy(3, 0, 1, 250, 23, 26, 3, 0);	
			CreateEnemy(4, 0, 440, 290, 23, 26, -3, 0);	
		}
	}
	else if (mGameTime < 800)
	{
		if (mGameTime % 25 == 0)
		{
			CreateItem(2, 1, 220, -10, 66, 55, 0, 1);
			CreateEnemy(9, 1, 230, -10, 44, 41, 0, 1);
		}
	}
	else if (mGameTime < 850)
	{
		//“G‚ªˆê‘Ì‚¾‚¯o‚Ä‚­‚é
		if (mGameTime % 50 == 0)
		{
			CreateItem(2, 1, 220, -10, 66, 55, 0, 1);
		}
	}
	else if (mGameTime < 1000);
	else if (mGameTime < 1200)
	{

		if (mGameTime % 25 == 0)
		{
			CreateEnemy(1, 0, 440, -10, 23, 26, -2, 1);
			CreateEnemy(2, 0, 0, -10, 23, 26, 2, 1);

			CreateItem(1, 0, 220, -10, 66, 50, 0, 1);

		}
	}
	else if (mGameTime < 1300);
	else if (mGameTime < 1340)
	{
		if (mGameTime % 50 == 0)
		{
			//“G‚ªŒð·‚µ‚Ä‚Å‚Ä‚­‚é‚â‚Â
			CreateEnemy(7, 0, 1, 50, 44, 41, 4, 0);			//“G‚ª¶‚©‚ço‚Ä‚«‚Äˆê’èŽžŠÔŽ~‚Ü‚é
			CreateEnemy(8, 0, 440, 50, 44, 41, -4, 0);		//“G‚ª‰E‚©‚ço‚Ä‚«‚Äˆê’èŽžŠÔŽ~‚Ü‚é

			CreateEnemy(7, 0, 1, 100, 44, 41, 1, 0);		//“G‚ª¶‚©‚ço‚Ä‚«‚Äˆê’èŽžŠÔŽ~‚Ü‚é
			CreateEnemy(8, 0, 440, 100, 44, 41, -1, 0);		//“G‚ª‰E‚©‚ço‚Ä‚«‚Äˆê’èŽžŠÔŽ~‚Ü‚é
		}
	}
	else if (mGameTime < 1750);
	else if (mGameTime < 1950)
	{
		if (mGameTime % 25 == 0)
		{

		}
	}
	else if (mGameTime < 2000)
	{
		if (mGameTime % 60 == 0)
		{

		}
	}
	else if (mGameTime < 2100);
	else if (mGameTime < 2140)
	{
		if (mGameTime % 50 == 0)
		{

		}
	}

	else if (mGameTime < 2300);
	else if (mGameTime < 2340)
	{
		if (mGameTime == 2320)
		{
			CreateEnemy(10, 1, 230, -10, 96, 64, 0, 1);
		}
	}

	else if (mGameTime < 3200);
	else if (mGameTime == 5000)
	{
		Game_SetmgameStatus(false);
	}
}
