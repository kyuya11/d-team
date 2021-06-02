#include "stage.h"
#include "Game.h"
#include "Enemy.h"


/**********************************
 * �X�e�[�W�P
 * ���@���F�Ȃ�
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
			//�U�R�i�j�����o���@���ֈړ��@�ˁ@�����ֈړ��@
			CreateEnemy(1, 0, 180, -10, 30, 30, 10, 0, 2);
			//�U�R�i�j�E���o���@���ֈړ��@�ˁ@�E���ֈړ��@
			CreateEnemy(2, 0, 280, -10, 30, 30, 10, 0, 2);
		}
	}
	else if (mGameTime < 400);
	else if (mGameTime < 600)
	{
		if (mGameTime % 25 == 0)
		{
			//�U�R�i�ԁj�����o���@���ֈړ��@�ˁ@�E���ֈړ��@
			CreateEnemy(3, 1, 100, -10, 30, 30, 10, 0, 2);
		}
	}
	else if (mGameTime < 800)
	{
		if (mGameTime % 25 == 0)
		{
			//�U�R�i�ԁj�E���o���@���ֈړ��@�ˁ@�����ֈړ��@
			CreateEnemy(4, 1, 360, -10, 30, 30, 10, 0, 2);
		}
	}
	else if (mGameTime < 850)
	{
		if (mGameTime % 50 == 0)
		{
			//�ޏ��i�ԁj���ֈړ��@�ˁ@�ꎞ��~10�b�@�@�ˁ@���ֈړ��E���j�@
			CreateEnemy(5, 1, 230, -10, 40, 45, 100, 0, 1);
		}
	}
	else if (mGameTime < 1000);
	else if (mGameTime < 1200)
	{
		if (mGameTime % 25 == 0)
		{
			//�U�R�i�ԁj�����o���@���ֈړ��@�ˁ@�E���ֈړ��@
			CreateEnemy(3, 1, 100, -10, 30, 30, 10, 0, 2);
			//�U�R�i�ԁj�E���o���@���ֈړ��@�ˁ@�����ֈړ��@
			CreateEnemy(4, 1, 360, -10, 30, 30, 10, 0, 2);
		}
	}
	else if (mGameTime < 1300);
	else if (mGameTime < 1340)
	{
		if (mGameTime % 50 == 0)
		{
			//�ޏ��i�ԁj���ֈړ��@�ˁ@�ꎞ��~10�b�@�@�ˁ@���ֈړ��E���j�@
			CreateEnemy(5, 1, 120, -10, 40, 45, 100, 0, 1);
			//�ޏ��i�ԁj���ֈړ��@�ˁ@�ꎞ��~10�b�@�@�ˁ@���ֈړ��E���j�@
			CreateEnemy(5, 1, 340, -10, 40, 45, 100, 0, 1);
		}
	}
	else if (mGameTime < 1750);
	else if (mGameTime < 1950)
	{
		if (mGameTime % 25 == 0)
		{
			//�U�R�i�ԁj�����o���@���ֈړ��@�ˁ@�E���ֈړ��@
			CreateEnemy(3, 1, 100, -10, 30, 30, 10, 0, 2);
			//�U�R�i�j�����o���@���ֈړ��@�ˁ@�����ֈړ��@
			CreateEnemy(1, 0, 180, -10, 30, 30, 10, 0, 2);
			//�U�R�i�j�E���o���@���ֈړ��@�ˁ@�E���ֈړ��@
			CreateEnemy(2, 0, 280, -10, 30, 30, 10, 0, 2);
			//�U�R�i�ԁj�E���o���@���ֈړ��@�ˁ@�����ֈړ��@
			CreateEnemy(4, 1, 360, -10, 30, 30, 10, 0, 2);
		}
	}
	else if (mGameTime < 2000)
	{
		if (mGameTime % 60 == 0)
		{
			//�ޏ��i�ԁj���ֈړ��@�ˁ@�ꎞ��~10�b�@�@�ˁ@���ֈړ��E���j�@
			CreateEnemy(5, 1, 230, -10, 40, 45, 100, 0, 1);
		}
	}
	else if (mGameTime < 2100);
	else if (mGameTime < 2140)
	{
		if (mGameTime % 50 == 0)
		{
			//�ޏ��i�ԁj���ֈړ��@�ˁ@�ꎞ��~10�b�@�@�ˁ@���ֈړ��E���j�@
			CreateEnemy(5, 1, 120, -10, 40, 45, 100, 0, 1);
			//�ޏ��i�ԁj���ֈړ��@�ˁ@�ꎞ��~10�b�@�@�ˁ@���ֈړ��E���j�@
			CreateEnemy(5, 1, 340, -10, 40, 45, 100, 0, 1);
		}
	}
	else if (mGameTime < 3200);
	else if (mGameTime < 3300)
	{
		Game_SetmgameStatus( false );
	}
}