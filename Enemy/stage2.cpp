#include "stage.h"
#include "Game.h"
#include "Enemy.h"
#include "Item1.h"
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

			CreateEnemy(2, 0, 180, -10, 45, 45, 0, 1);
			CreateEnemy(1, 0, 280, -10, 45, 45, 0, 1);



		}
		if (mGameTime % 300 == 0)
			CreateItem(1, 0, 235, -10, 66, 50, 0, 1);
	}
	else if (mGameTime < 400);
	else if (mGameTime < 600)
	{
		if (mGameTime % 25 == 0)
		{
			CreateEnemy( 9, 0,   1, 170, 45, 45, 3, 0);	//�A�C�e�������悤������H�삪�łĂ���
			CreateEnemy(10, 0, 440, 210, 45, 45, -3, 0);	//�A�C�e�������悤�E����H�삪�łĂ���
			CreateEnemy( 9, 0,   1, 250, 45, 45,  3, 0);	//�A�C�e�������悤������H�삪�łĂ���
			CreateEnemy(10, 0, 440, 290, 45, 45, -3, 0);	//�A�C�e�������悤�E����H�삪�łĂ���
		}
	}
	else if (mGameTime < 800)
	{
		if (mGameTime % 25 == 0)
		{
			CreateEnemy(8, 0, 1, -10, 44, 41, 3, 0);	//�G���ォ��o�Ă��ăW�O�U�O�ɉ��ɍs��
			CreateItem(2, 1, 220, -10, 66, 55, 0, 1);
		}
	}
	else if (mGameTime < 850)
	{
		//�G����̂����o�Ă���
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
			CreateEnemy(1, 0, 440, -10, 45, 45, -2, 1);
			CreateEnemy(2, 0,   0, -10, 45, 45,  2, 1);

			CreateItem(1, 0, 220, -10, 66, 50, 0, 1);

		}
	}
	else if (mGameTime < 1300);
	else if (mGameTime < 1340)
	{
		if (mGameTime % 50 == 0)
		{
			//�G���������ĂłĂ�����
			CreateEnemy(6, 0, 1, 50, 44, 41, 4, 0);			//�G��������o�Ă��Ĉ�莞�Ԏ~�܂�
			CreateEnemy(7, 0, 440, 50, 44, 41, -4, 0);		//�G���E����o�Ă��Ĉ�莞�Ԏ~�܂�

			CreateEnemy(6, 0,   1, 100, 44, 41,  1, 0);		//�G��������o�Ă��Ĉ�莞�Ԏ~�܂�
			CreateEnemy(7, 0, 440, 100, 44, 41, -1, 0);		//�G���E����o�Ă��Ĉ�莞�Ԏ~�܂�
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
			CreateEnemy(5, 1, 230, -10, 96, 64, 0, 1);

		}
	}

	else if (mGameTime < 3200);
	else if (mGameTime < 3300)
	{
		Game_SetmgameStatus(false);
	}
}
