#include "stage.h"
#include "Game.h"
#include "Enemy.h"


/**********************************
 * ステージ１
 * 引　数：なし
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
			//ザコ（青）左側出現　下へ移動　⇒　左下へ移動　
			CreateEnemy(1, 0, 180, -10, 30, 30, 10, 0, 2);
			//ザコ（青）右側出現　下へ移動　⇒　右下へ移動　
			CreateEnemy(2, 0, 280, -10, 30, 30, 10, 0, 2);
		}
	}
	else if (mGameTime < 400);
	else if (mGameTime < 600)
	{
		if (mGameTime % 25 == 0)
		{
			//ザコ（赤）左側出現　下へ移動　⇒　右下へ移動　
			CreateEnemy(3, 1, 100, -10, 30, 30, 10, 0, 2);
		}
	}
	else if (mGameTime < 800)
	{
		if (mGameTime % 25 == 0)
		{
			//ザコ（赤）右側出現　下へ移動　⇒　左下へ移動　
			CreateEnemy(4, 1, 360, -10, 30, 30, 10, 0, 2);
		}
	}
	else if (mGameTime < 850)
	{
		if (mGameTime % 50 == 0)
		{
			//巫女（赤）下へ移動　⇒　一時停止10秒　　⇒　下へ移動右下）　
			CreateEnemy(5, 1, 230, -10, 40, 45, 100, 0, 1);
		}
	}
	else if (mGameTime < 1000);
	else if (mGameTime < 1200)
	{
		if (mGameTime % 25 == 0)
		{
			//ザコ（赤）左側出現　下へ移動　⇒　右下へ移動　
			CreateEnemy(3, 1, 100, -10, 30, 30, 10, 0, 2);
			//ザコ（赤）右側出現　下へ移動　⇒　左下へ移動　
			CreateEnemy(4, 1, 360, -10, 30, 30, 10, 0, 2);
		}
	}
	else if (mGameTime < 1300);
	else if (mGameTime < 1340)
	{
		if (mGameTime % 50 == 0)
		{
			//巫女（赤）下へ移動　⇒　一時停止10秒　　⇒　下へ移動右下）　
			CreateEnemy(5, 1, 120, -10, 40, 45, 100, 0, 1);
			//巫女（赤）下へ移動　⇒　一時停止10秒　　⇒　下へ移動右下）　
			CreateEnemy(5, 1, 340, -10, 40, 45, 100, 0, 1);
		}
	}
	else if (mGameTime < 1750);
	else if (mGameTime < 1950)
	{
		if (mGameTime % 25 == 0)
		{
			//ザコ（赤）左側出現　下へ移動　⇒　右下へ移動　
			CreateEnemy(3, 1, 100, -10, 30, 30, 10, 0, 2);
			//ザコ（青）左側出現　下へ移動　⇒　左下へ移動　
			CreateEnemy(1, 0, 180, -10, 30, 30, 10, 0, 2);
			//ザコ（青）右側出現　下へ移動　⇒　右下へ移動　
			CreateEnemy(2, 0, 280, -10, 30, 30, 10, 0, 2);
			//ザコ（赤）右側出現　下へ移動　⇒　左下へ移動　
			CreateEnemy(4, 1, 360, -10, 30, 30, 10, 0, 2);
		}
	}
	else if (mGameTime < 2000)
	{
		if (mGameTime % 60 == 0)
		{
			//巫女（赤）下へ移動　⇒　一時停止10秒　　⇒　下へ移動右下）　
			CreateEnemy(5, 1, 230, -10, 40, 45, 100, 0, 1);
		}
	}
	else if (mGameTime < 2100);
	else if (mGameTime < 2140)
	{
		if (mGameTime % 50 == 0)
		{
			//巫女（赤）下へ移動　⇒　一時停止10秒　　⇒　下へ移動右下）　
			CreateEnemy(5, 1, 120, -10, 40, 45, 100, 0, 1);
			//巫女（赤）下へ移動　⇒　一時停止10秒　　⇒　下へ移動右下）　
			CreateEnemy(5, 1, 340, -10, 40, 45, 100, 0, 1);
		}
	}
	else if (mGameTime < 3200);
	else if (mGameTime < 3300)
	{
		Game_SetmgameStatus( false );
	}
}