#include "stage.h"
#include "Game.h"
#include "Enemy.h"
#include "ITEM.h"
#include <stdlib.h>


/**********************************
* �X�e�[�W�P
* �� ���F�Ȃ�
* �߂�l�F�Ȃ�
**********************************/
void Stage1()
{
	int mGameTime = Game_GetmGameTime();

	if (mGameTime < 100);
	else if (mGameTime < 325)
	{
		if (mGameTime % 25 == 0)
		{
			CreateItem(3, 1, 230, -10, 66, 50, 0, 1);
			CreateEnemy(7, 1, 230, -10, 45, 45, 100, 0, 1);

		}
	}
	else if (mGameTime < 400);
	else if (mGameTime < 600)
	{
		if (mGameTime % 25 == 0)
		{
		}
	}
	else if (mGameTime < 800)
	{
		if (mGameTime % 25 == 0)
		{

		}
	}
	else if (mGameTime < 850)
	{
		if (mGameTime % 50 == 0)
		{
			//�ޏ��i�ԁj���ֈړ� �� �ꎞ��~10�b �� ���ֈړ��E���j
			CreateEnemy(5, 1, 230, -10, 96, 64, 100, 0, 1);

		}
	}
	else if (mGameTime < 1000);
	else if (mGameTime < 1200)
	{
		if (mGameTime % 25 == 0)
		{
			CreateItem(2, 2, 230, -10, 66, 50, 0, 1);

		}
	}
	else if (mGameTime < 1300);
	else if (mGameTime < 1340)
	{
		if (mGameTime % 50 == 0)
		{

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
		if (mGameTime % 50 == 0)
		{

		}
	}

	else if (mGameTime < 3200);
	else if (mGameTime < 3300)
	{
		Game_SetmgameStatus(false);
	}
}
