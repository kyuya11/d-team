#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Enemy.h"
#include "Player.h"
#include "Effect.h"
#include <math.h>


int HitCircleEnemy(PLAYER*, ENEMY*);
int HitCircleEnemyShot(PLAYER*, ENEMY_SHOT*);

/*************************
** 変数 **
*************************/
// エネミー
struct ENEMY mEnemy[ENEMY_MAX];
int mImageEnemyZako[ENEMY_IMAGE_MAX];
int mImageEnemyBosu[ENEMY_IMAGE_MAX];
int mImageEnemydoku[ENEMY_IMAGE_MAX];
int mImageEnemymedama;



// エネミー弾
struct ENEMY_SHOT mEnemyShot[ENEMY_SHOT_MAX];
int mImageEnemyShot[ENEMY_SHOT_IMAGE_MAX];

//初期化
void Enemy_Initialize() {
	LoadDivGraph("images/yurei1.png", 1, 1, 1, 23, 26, mImageEnemyZako); //エネミー画像（雑魚：ザコ）
	LoadDivGraph("images/bosu.png", 4, 4, 1, 96, 64, mImageEnemyBosu); //エネミー画像（巫女：ミコ）
	LoadDivGraph("images/EnemyDan.png", 4, 4, 1, 16, 16, mImageEnemyShot); //エネミー弾画像
	mImageEnemymedama = LoadGraph("images/medama2.png");


	// エネミーの初期設定
	for (int i = 0; i < ENEMY_MAX; i++) {
		mEnemy[i].flg = FALSE;
	}

	// エネミー弾の初期設定
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		mEnemyShot[i].flg = FALSE;
	}
}

//終了処理
void Enemy_Finalize() {
	for (int i = 0; i < ENEMY_IMAGE_MAX; i++) {
		DeleteGraph(mImageEnemyZako[i]); //画像の解放
		DeleteGraph(mImageEnemyBosu[i]); //画像の解放	
	}

		DeleteGraph(mImageEnemymedama); //画像の解放	

	for (int i = 0; i < ENEMY_SHOT_IMAGE_MAX; i++) {
		DeleteGraph(mImageEnemyShot[i]); //画像の解放
	}
}

//更新
void Enemy_Update() {
	//エネミー処理
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == TRUE) {

			// エネミー移動
			mEnemy[i].x += mEnemy[i].mx;
			mEnemy[i].y += mEnemy[i].my;

			mEnemy[i].cnt++;

			// パターン別 敵の動き
			switch (mEnemy[i].type) {
				case 1: EnemyType01(&mEnemy[i]); break;
				case 2: EnemyType02(&mEnemy[i]); break;
				case 3: EnemyType03(&mEnemy[i]); break;
				case 4: EnemyType04(&mEnemy[i]); break;
				case 5: EnemyType05(&mEnemy[i]); break;
				//case 6: EnemyType06(&mEnemy[i]); break;
				case 7: EnemyType07(&mEnemy[i]); break;
				case 8:EnemyType08(&mEnemy[i]); break;
				case 9:EnemyType09(&mEnemy[i]); break;
				case 10:EnemyType10(&mEnemy[i]); break;

			}

			// 画面をはみ出したら消去
			if (mEnemy[i].y > SCREEN_HEIGHT + mEnemy[i].h) {
				mEnemy[i].flg = FALSE;
			}
			if (mEnemy[i].x > 440 + mEnemy[i].w) {
				mEnemy[i].flg = FALSE;
			}
			if (mEnemy[i].x < 0 - mEnemy[i].w) {
				mEnemy[i].flg = FALSE;
			}

			if (HitCircleEnemy(&mPlayer, &mEnemy[i]) == TRUE) {
				if (mPlayer.baria == 0)
				{
					mPlayer.flg = FALSE;
					mPlayer.count = 0;
					mPlayer.hp -= 1;
					mEnemy[i].flg = FALSE;
				}
				if (mPlayer.baria == 1)
				{
					mPlayer.count = 0;
					mPlayer.baria = 0;
					mEnemy[i].flg = FALSE;

				}

				CreateEffect(mEnemy[i].x, mEnemy[i].y);
			}
		}
	}

	//エネミー弾処理
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		if (mEnemyShot[i].flg == TRUE) {

			// エネミー弾移動
			mEnemyShot[i].x += mEnemyShot[i].mx;
			mEnemyShot[i].y += mEnemyShot[i].my;
			
			// 画面をはみ出したら消去
			if (mEnemyShot[i].y > SCREEN_HEIGHT + mEnemyShot[i].h) {
				mEnemyShot[i].flg = FALSE;
			}
			if (mEnemy[i].x > 440 + mEnemy[i].w) {
				mEnemy[i].flg = FALSE;
			}
			if (mEnemy[i].x < 0 - mEnemy[i].w) {
				mEnemy[i].flg = FALSE;
			}

			if (mPlayer.flg == false)
				continue;
			if (HitCircleEnemyShot(&mPlayer, &mEnemyShot[i]) == TRUE) {
				if (mPlayer.baria == 0)
				{
					mPlayer.flg = FALSE;
					mPlayer.count = 0;
					mPlayer.hp -= 1;
				}

				if (mPlayer.baria == 1)
				{
					mPlayer.baria = 0;
					mPlayer.flg = FALSE;
					mPlayer.count = 0;
				}

				EraseEnemyShot();
				CreateEffect(mPlayer.x, mPlayer.y);
			}
		}
	}
}

//描画
void Enemy_Draw() {
	//エネミー処理
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == TRUE) {
			DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.0f, 0, mEnemy[i].img, TRUE, FALSE);
		}
	}
	//エネミー弾処理
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		if (mEnemyShot[i].flg == TRUE) {
			DrawRotaGraph(mEnemyShot[i].x, mEnemyShot[i].y, 1.0f, 0, mEnemyShot[i].img, TRUE, FALSE);
		}
	}
}


/**********************************
* エネミーの生成
* 引 数：type:タイプ１－４はザコ、５－７は巫女
* img：１はザコ青、２はザコ赤、1は巫女青。２は巫女赤
*
* 戻り値：TRUE:成功 FALSE:失敗
**********************************/
int CreateEnemy(int type, int img, int x, int y, int w, int h, int point, int mx, int my)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == FALSE) {
			mEnemy[i].flg = TRUE;
			mEnemy[i].type = type;
			if (type == 1 || type == 2 || type == 9 || type == 10) {
				mEnemy[i].img = mImageEnemyZako[img];
				mEnemy[i].hp = ENEMY_ZAKO_LIFE;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}

			//if (type <= 4) {
			//	mEnemy[i].img = mImageEnemyZako[img];
			//	mEnemy[i].hp = ENEMY_ZAKO_LIFE;
			//	mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			//}
			else if(type == 5){
				mEnemy[i].img = mImageEnemyBosu[img];
				mEnemy[i].hp = ENEMY_MIKO_RED_LIFE;
				mEnemy[i].r = ENEMY_MIKO_HIT_R;
			}
			else if (type == 6) {
				mEnemy[i].img = mImageEnemydoku[img];
				mEnemy[i].hp = ENEMY_MIKO_RED_LIFE;
				mEnemy[i].r = ENEMY_MIKO_HIT_R;
			}
			else if (type == 3 || type == 4 || type == 7 || type == 8) {
				mEnemy[i].img = mImageEnemymedama;
				mEnemy[i].hp = ENEMY_MIKO_RED_LIFE;
				mEnemy[i].r = ENEMY_MIKO_HIT_R;
			}

			mEnemy[i].x = x;
			mEnemy[i].y = y;
			mEnemy[i].w = w;
			mEnemy[i].h = h;
			mEnemy[i].point = point;
			mEnemy[i].mx = mx;
			mEnemy[i].my = my;
			mEnemy[i].cnt = 0;

			// 成功
			return TRUE;
		}
	}

	// 失敗
	return FALSE;
}

/**********************************
* エネミータイプ１の移動と攻撃
**********************************/
void EnemyType01(ENEMY* mEnemy)
{

	if (mEnemy->cnt == 80) {
		mEnemy->mx = -1;

	}
}

/**********************************
* エネミータイプ２の移動と攻撃
**********************************/
void EnemyType02(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 1;
	}
}

void EnemyType03(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 1;
		mEnemy->my = 1;
	}

	if (mEnemy->cnt % 80 == 0 && mEnemy->y < 400) {
		CreateTargetShot(mEnemy);
	}
}

void EnemyType04(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = -1;
		mEnemy->my = 1;
	}

	if (mEnemy->cnt % 80 == 0 && mEnemy->y < 400) {
		CreateTargetShot(mEnemy);
	}
}

void EnemyType05(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 90) {
		mEnemy->my = 0;
	}
	else if (mEnemy->cnt == 690) {
		mEnemy->my = 1;
	}

	if (mEnemy->cnt >= 120  && mEnemy->cnt <= 600) 
	{
		if (mEnemy->cnt % 30 == 0)
			CreateNWayShot(mEnemy);

		if (mEnemy->cnt % 60 == 0)
			CreateDirectionShot(mEnemy);
	
	}
}

//void EnemyType06(ENEMY* mEnemy)
//{
//	int i;
//	if (mEnemy->cnt == 80) {
//		mEnemy->my = 0;
//	}
//	else if (mEnemy->cnt == 900) {
//		mEnemy->my = 1;
//	}
//
//	if (mEnemy->cnt >= 120 && mEnemy->cnt <= 600)
//	{
//		if (mEnemy->cnt % 30 == 0)
//			CreateNWayShot(mEnemy);
//
//		if (mEnemy->cnt % 60 == 0)
//			CreateDirectionShot(mEnemy);
//
//	}
//}

void EnemyType07(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 1;
		mEnemy->my = 1;
	}
	if (mEnemy->cnt == 160 || mEnemy->cnt == 500) {
		mEnemy->mx = -1;
	}
	if (mEnemy->cnt == 320) {
		mEnemy->mx = 1;
	}

	if (mEnemy->cnt % 80 == 0 && mEnemy->y < 400) {
		CreateTargetShot(mEnemy);
	}
}

void EnemyType08(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 1;
	}

}

void EnemyType09(ENEMY* mEnemy) {
	if (mEnemy->cnt == 50) {
		mEnemy->mx = 1;
	}
	if (mEnemy->cnt == 150) {
		mEnemy->mx = 2;
	}
}

void EnemyType10(ENEMY* mEnemy) {
	if (mEnemy->cnt == 50) {
		mEnemy->mx = -1;
	}
	if (mEnemy->cnt == 150) {
		mEnemy->mx = -2;
	}
}

void EnemyType11(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 1;
		mEnemy->my = 1;
	}

	if (mEnemy->cnt % 80 == 0 && mEnemy->y < 400) {
		CreateTargetShot(mEnemy);
	}
}


int CreateEnemyShot(int img, double x, double y, double mx, double my)
{
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		if (mEnemyShot[i].flg == FALSE) {
			mEnemyShot[i].flg = TRUE;
			mEnemyShot[i].w = 16;
			mEnemyShot[i].h = 16;

			mEnemyShot[i].img = mImageEnemyShot[img];
			mEnemyShot[i].x = x;
			mEnemyShot[i].y = y;
			mEnemyShot[i].mx = mx;
			mEnemyShot[i].my = my;

			// 成功
			return TRUE;
		}
	}

	// 失敗
	return FALSE;
}


// *** +16lines(1-function)
/***********************************************
* 敵弾 狙い撃ち
* 引 数：*mEnemy
* 戻り値：なし
***********************************************/
void CreateTargetShot(ENEMY* mEnemy)
{
	// 敵機と自機のX,Y方向の角度を求める
	double Angle = atan2((double)(mPlayer.y - (double)mEnemy->y), (double)(mPlayer.x - (double)mEnemy->x));

	// 飛んでいく方向とスピードから、X軸方向への移動速度とY方向への移動速度を得る
	double mx = cos(Angle) * ENEMY_SHOT_SPEED;
	double my = sin(Angle) * ENEMY_SHOT_SPEED;

	CreateEnemyShot(3, mEnemy->x, mEnemy->y, mx, my);
}

void CreateDirectionShot(ENEMY* mEnemy)
{
	CreateEnemyShot(0, mEnemy->x, mEnemy->y, 0, 3);
}

void CreateNWayShot(ENEMY* mEnemy)
{
	int mx[8] = { -3,-3,-2,-1,1,2,3,3 };
	int my[8] = { 1,2,3,4,4,3,2,1 };

	for (int i = 0; i < 8; i++)
	{
		CreateEnemyShot(1, mEnemy->x, mEnemy->y, mx[i], my[i]);
	}
}

int HitCircleEnemy(PLAYER* p, ENEMY* e)
{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}

int HitCircleEnemyShot(PLAYER* p, ENEMY_SHOT* e)
{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}

void EraseEnemyShot()
{
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		mEnemyShot[i].flg = FALSE;
	}
}
