
#include "stage.h"
#include "Game.h"
#include "Enemy.h"
#include "ITEM.h"
#include <stdlib.h>


/**********************************
* ステージ１
* 引 数：なし
* 戻り値：なし
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
			//アイテムを守っているように出てくる
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
			//左と右から幽霊が出てきて行く手を阻む
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
			//ジグザグに下に移動しながら攻撃してくる目玉
			CreateEnemy(11, 1, 230, -10, 44, 41, 0, 1);

		}
	}
	else if (mGameTime < 850)
	{
		//アイテムが一個だけ出てくる
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
			//途中で交差する幽霊
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
			//敵が交差してでてくるやつ
			CreateEnemy(9, 0, 1, 50, 44, 41, 4, 0);			//敵が左から出てきて一定時間止まる
			CreateEnemy(10, 0, 440, 50, 44, 41, -4, 0);		//敵が右から出てきて一定時間止まる

			CreateEnemy(9, 0, 1, 100, 44, 41, 1, 0);		//敵が左から出てきて一定時間止まる
			CreateEnemy(10, 0, 440, 100, 44, 41, -1, 0);		//敵が右から出てきて一定時間止まる
		}
	}
	else if (mGameTime < 1750);
	else if (mGameTime < 1950)
	{
		if (mGameTime % 25 == 0)
		{
			//上から交差しながら下に降りてくる
			CreateEnemy(5, 0, 180, -10, 23, 26, 0, 2);
			CreateEnemy(6, 0, 280, -10, 23, 26, 0, 2);
		}
		if (mGameTime % 200 == 0)
		{
			//左から出て左に並ぶ目玉
			CreateEnemy(12, 0, 0, 150, 44, 41, 4, 0);
			CreateEnemy(12, 0, 0, 250, 44, 41, 2, 0);
			CreateEnemy(12, 0, 0, 350, 44, 41, 1, 0);

			//右から出て右に並ぶ目玉
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
			//ボス
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