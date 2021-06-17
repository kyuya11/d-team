#include "stage.h"
#include "Game.h"
#include "Enemy.h"
#include "Item1.h"
#include <stdlib.h>


/**********************************
* ステージ１
* 引 数：なし
* 戻り値：なし
**********************************/
void Stage1()
{
	int mGameTime = Game_GetmGameTime();

	if (mGameTime < 100);
	else if (mGameTime < 325)
	{
		if (mGameTime % 25 == 0)
		{

			CreateEnemy(2, 0, 180, -10, 45, 45, 100, 0, 1);
			CreateEnemy(1, 0, 280, -10, 45, 45, 100, 0, 1);



		}
		if (mGameTime % 300 == 0)
			CreateItem(1, 1, 230, -10, 66, 50, 0, 1);
	}
	else if (mGameTime < 400);
	else if (mGameTime < 600)
	{
		if (mGameTime % 25 == 0)
		{
			CreateEnemy( 9, 0,   1, 170, 45, 45, 100,  3, 0);	//アイテムを守るよう左から幽霊がでてくる
			CreateEnemy(10, 0, 440, 210, 45, 45, 100, -3, 0);	//アイテムを守るよう右から幽霊がでてくる
			CreateEnemy( 9, 0,   1, 250, 45, 45, 100,  3, 0);	//アイテムを守るよう左から幽霊がでてくる
			CreateEnemy(10, 0, 440, 290, 45, 45, 100, -3, 0);	//アイテムを守るよう右から幽霊がでてくる
		}
	}
	else if (mGameTime < 800)
	{
		if (mGameTime % 25 == 0)
		{
			CreateEnemy(7, 0, 1, -10, 45, 45, 100, 3, 0);
			//CreateEnemy(4, 0, 440, 100, 45, 45, 100, -3, 0);
		}
	}
	else if (mGameTime < 850)
	{
		//敵が一体だけ出てくる
		if (mGameTime % 50 == 0)
		{


		}
	}
	else if (mGameTime < 1000);
	else if (mGameTime < 1200)
	{
		if (mGameTime % 25 == 0)
		{
			CreateItem(2, 2, 230, -10, 66, 50, 0, 1);	//敵が上から出てきてジグザグに下に行く

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
			CreateEnemy(5, 1, 230, -10, 96, 64, 100, 0, 1);

		}
	}

	else if (mGameTime < 3200);
	else if (mGameTime < 3300)
	{
		Game_SetmgameStatus(false);
	}
}
