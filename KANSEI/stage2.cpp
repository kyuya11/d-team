
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

	if (mGameTime % 700 == 0)
	{
		CreateItem(3, 1, rand() % 430 + 50, -10, 66, 50, 0, 1);
	}

	if (mGameTime < 100);
	else if (mGameTime < 325)
	{
		if (mGameTime % 25 == 0)
		{
			//�A�C�e��������Ă���悤�ɏo�Ă���
			CreateEnemy(2, 0, 180, -10, 23, 26, 0, 1);
			CreateEnemy(1, 0, 280, -10, 23, 26, 0, 1);


		}
		if (mGameTime == 200)
		{
			CreateItem(1, 0, 237, -10, 66, 50, 0, 1);

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
			//���ƉE����H�삪�o�Ă��čs�����j��
			CreateEnemy(3, 0, 1, 170, 23, 26, 3, 0);
			CreateEnemy(4, 0, 440, 210, 23, 26, -3, 0);
			CreateEnemy(3, 0, 1, 250, 23, 26, 3, 0);
			CreateEnemy(4, 0, 440, 290, 23, 26, -3, 0);
		}
	}
	else if (mGameTime < 800)
	{
		if (mGameTime == 790)
		{
			CreateItem(2, 2, 237, -10, 66, 55, 0, 1);

		}

		if (mGameTime % 25 == 0)
		{
			//�W�O�U�O�ɉ��Ɉړ����Ȃ���U�����Ă���ڋ�
			CreateEnemy(11, 1, 230, -10, 44, 41, 0, 1);

		}
	}
	else if (mGameTime < 850)
	{
		//�A�C�e����������o�Ă���
		if (mGameTime == 820)
		{
			CreateItem(2, 2, 237, -10, 66, 55, 0, 1);
		}
	}
	else if (mGameTime < 1000);
	else if (mGameTime < 1200)
	{

		if (mGameTime % 25 == 0)
		{
			//�r���Ō�������H��
			CreateEnemy(1, 0, 440, -10, 23, 26, -2, 1);
			CreateEnemy(2, 0, 0, -10, 23, 26, 2, 1);

			CreateItem(1, 0, 230, -10, 66, 50, 0, 1);

		}
		if (mGameTime == 1025)
		{
			CreateItem(1, 0, 230, -10, 66, 50, 0, 1);

		}
	}
	else if (mGameTime < 1300);
	else if (mGameTime < 1340)
	{
		if (mGameTime % 50 == 0)
		{
			//�G���������ĂłĂ�����
			CreateEnemy(9, 0, 1, 50, 44, 41, 4, 0);			//�G��������o�Ă��Ĉ�莞�Ԏ~�܂�
			CreateEnemy(10, 0, 440, 50, 44, 41, -4, 0);		//�G���E����o�Ă��Ĉ�莞�Ԏ~�܂�

			CreateEnemy(9, 0, 1, 100, 44, 41, 1, 0);		//�G��������o�Ă��Ĉ�莞�Ԏ~�܂�
			CreateEnemy(10, 0, 440, 100, 44, 41, -1, 0);		//�G���E����o�Ă��Ĉ�莞�Ԏ~�܂�
		}
	}
	else if (mGameTime < 1750);
	else if (mGameTime < 1950)
	{
		if (mGameTime % 25 == 0)
		{
			//�ォ��������Ȃ��牺�ɍ~��Ă���
			CreateEnemy(5, 0, 180, -10, 23, 26, 0, 2);
			CreateEnemy(6, 0, 280, -10, 23, 26, 0, 2);
		}
		if (mGameTime % 200 == 0)
		{
			//������o�č��ɕ��Ԗڋ�
			CreateEnemy(12, 0, 0, 150, 44, 41, 4, 0);
			CreateEnemy(12, 0, 0, 250, 44, 41, 2, 0);
			CreateEnemy(12, 0, 0, 350, 44, 41, 1, 0);

			//�E����o�ĉE�ɕ��Ԗڋ�
			CreateEnemy(13, 0, 440, 150, 44, 41, -4, 0);
			CreateEnemy(13, 0, 440, 250, 44, 41, -2, 0);
			CreateEnemy(13, 0, 440, 350, 44, 41, -1, 0);
		}

	}
	else if (mGameTime < 2000)
	{
		if (mGameTime % 50 == 0)
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
	else if (mGameTime < 2540)
	{
		if (mGameTime == 2480)
		{
			//�{�X
			CreateEnemy(14, 1, 230, -10, 96, 64, 0, 1);
		}

		if (mGameTime == 2500)
		{
			CreateItem(2, 2, 237, -10, 66, 55, 0, 1);
		}
		
	}

	else if (mGameTime < 3200);
	else if (mGameTime == 5000)
	{
		Game_SetmgameStatus(false);
	}
}