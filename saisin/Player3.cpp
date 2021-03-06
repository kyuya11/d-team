#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"
#include "Effect.h"
#include "ITEM.h"
#include <math.h>

int HitCirclePlayerShot(ENEMY*, PLAYER_SHOT*);	

struct PLAYER mPlayer;
struct PLAYER_SHOT mPlayerShot[PLAYER_SHOT_MAX];

static int mImagePlayer;    
static int mImageHitPoint[2];  
static int mImageHodai[3];  
static int mImageDan[3];    
static int mImageBaria;

static int mSoundsShot;  


int MPlayerHodaiPosion2[2][3][3] = {	
	{
		{0,-48,2}

	},

	{

		{-16, -36, 0},
		{  0, -48, 2},
		{ 16, -36, 0},

	}
};

int MPlayerShotMove2[2][3][2] = {	//弾の動き
	{
		{0,-14}	//{x, y}
	},

	{
		{-1, -13},
		{ 0, -14},
		{ 1, -13}
	}

};

void Player_Initialize(){	//画像分割・ロード・音
	SetTransColor(0, 0, 0);
	mImagePlayer = LoadGraph("images/player3.png");    
	LoadDivGraph("images/playerhantei.png", 2, 2, 1, 60, 60, mImageHitPoint);	
	LoadDivGraph("images/playerHodai1.png", 3, 3, 1, 12, 16, mImageHodai);	
	LoadDivGraph("images/playerDan1.png", 3, 3, 1, 12, 24, mImageDan);	
	mImageBaria = LoadGraph("images/redbaria1.png");

	mSoundsShot = LoadSoundMem("sounds/shoot.wav");  

	//player初期化
	mPlayer.flg = true;
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.w = PLAYER_WIDTH;
	mPlayer.h = PLAYER_HEIGHT;
	mPlayer.angle = 0.0;
	mPlayer.count = 0;
	mPlayer.hp = PLAYER_HP;
	mPlayer.score = 0;
	mPlayer.r = PLAYER_HIT_R;
	mPlayer.up = 0;
	mPlayer.baria = 0;


	//弾初期化
	for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
		mPlayerShot[x].flg = FALSE;
	}
}

void Player_Finalize(){
    DeleteGraph(mImagePlayer); //画像の解放  
	DeleteGraph(mImageBaria); //画像の解放  

}

//player更新
void Player_Update(){

	//上下左右移動
	if (iNowKey & PAD_INPUT_UP)		mPlayer.y -= PLAYER_SPEED;
	if (iNowKey & PAD_INPUT_DOWN)	mPlayer.y += PLAYER_SPEED;
	if (iNowKey & PAD_INPUT_LEFT)	mPlayer.x -= PLAYER_SPEED;
	if (iNowKey & PAD_INPUT_RIGHT)	mPlayer.x += PLAYER_SPEED;

	//画面のどこまでいけるかみたいなやつ
	if (mPlayer.x < SCREEN_WIDTH_L + mPlayer.w/2) mPlayer.x = SCREEN_WIDTH_L + mPlayer.w/2;
	if (mPlayer.x > SCREEN_WIDTH_R - mPlayer.w/2) mPlayer.x = SCREEN_WIDTH_R - mPlayer.w/2;
	if (mPlayer.y < 32)					mPlayer.y = 32;
	if (mPlayer.y > SCREEN_HEIGHT - 32)	mPlayer.y = SCREEN_HEIGHT - 32;

	if (mPlayer.flg) {

		mPlayer.shotCount++;
		if (mPlayer.shotCount > PLAYER_SHOT_INTERVAL) {
			if (iNowKey & PAD_INPUT_1) {	//　Zキーが押されていたら弾生産
				mPlayer.shotCount = 0;

				if (MakePlayerShot()) {
					PlaySoundMem(mSoundsShot, DX_PLAYTYPE_BACK);	//弾打った時、音再生

				}
			}
		}

	}

	MovePlayerShot();

	mPlayer.time++;

}

//Player描画
void Player_Draw() {

	if (mPlayer.flg) {
		//player表示
		DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer, TRUE, FALSE);
		//playerの真ん中の点表示
		DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImageHitPoint[1], TRUE, FALSE);

		if (mPlayer.baria == 1)
		{
			DrawRotaGraph(mPlayer.x, mPlayer.y, 3.0f, 0, mImageBaria, TRUE, FALSE);

		}

		if (iNowKey & PAD_INPUT_1) {	//Zキー押したときの弾の表示
			DrawRotaGraph(mPlayer.x + MPlayerHodaiPosion2[0][0][0],
				mPlayer.y + MPlayerHodaiPosion2[0][0][1],
				1.0f, 0, mImageHodai[MPlayerHodaiPosion2[0][0][2]], TRUE, FALSE);
		}

		DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImageHitPoint[1], TRUE, FALSE);

		if (iNowKey & PAD_INPUT_1 && mPlayer.up == 1) {
			for (int i = 0; i < 3; i++) {
				DrawRotaGraph(mPlayer.x + MPlayerHodaiPosion2[1][i][0],
					mPlayer.y + MPlayerHodaiPosion2[1][i][1],
					1.0f, 0, mImageHodai[MPlayerHodaiPosion2[1][i][2]], TRUE, FALSE);
			}
		}

	}
	else
	{
		if (++mPlayer.count >= 80)	mPlayer.flg = true;
		if (mPlayer.count / 5 % 2 == 0) {
			DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer, TRUE, FALSE);
		}
	}


		DrawPlayerShot();

}

int MakePlayerShot() {	//弾生産

	bool flg = FALSE;

	if (iNowKey & PAD_INPUT_1) {
			for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
				if (mPlayerShot[x].flg == FALSE) {
					flg = TRUE;

					mPlayerShot[x].flg = TRUE;
					mPlayerShot[x].w = 12;
					mPlayerShot[x].h = 14;
					mPlayerShot[x].x = mPlayer.x + MPlayerHodaiPosion2[0][0][0];
					mPlayerShot[x].y = mPlayer.y + MPlayerHodaiPosion2[0][0][1];
					mPlayerShot[x].image = mImageDan[MPlayerHodaiPosion2[0][0][2]];
					mPlayerShot[x].mx = MPlayerShotMove2[0][0][0];
					mPlayerShot[x].my = MPlayerShotMove2[0][0][1];
					break;
				}
			}
	}
	if (iNowKey & PAD_INPUT_1 && mPlayer.up == 1) {
		for (int i = 0; i < 3; i++) {
			for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
				if (mPlayerShot[x].flg == FALSE) {
					flg = TRUE;

					mPlayerShot[x].flg = TRUE;
					mPlayerShot[x].w = 12;
					mPlayerShot[x].h = 14;
					mPlayerShot[x].x = mPlayer.x + MPlayerHodaiPosion2[1][i][0];
					mPlayerShot[x].y = mPlayer.y + MPlayerHodaiPosion2[1][i][1];
					mPlayerShot[x].image = mImageDan[MPlayerHodaiPosion2[1][i][2]];
					mPlayerShot[x].mx = MPlayerShotMove2[1][i][0];
					mPlayerShot[x].my = MPlayerShotMove2[1][i][1];
					break;
				}
			}
		}
	}

	return flg;
}

void MovePlayerShot() {	//弾移動
	for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
		if (mPlayerShot[x].flg == TRUE) {
			mPlayerShot[x].x += mPlayerShot[x].mx;
			mPlayerShot[x].y += mPlayerShot[x].my;

			if (mPlayerShot[x].y < -14) {
				mPlayerShot[x].flg = FALSE;
			}

			for (int y = 0; y < ENEMY_MAX; y++) {
				if (mEnemy[y].flg == false) continue;
				if (HitCirclePlayerShot(&mEnemy[y], &mPlayerShot[x]) == TRUE) {	//敵に当たった時
					if (--mEnemy[y].hp < 0) {
					 //↑一発当たるごとにｈｐ−１して0以下になったら↓
						mEnemy[y].flg = FALSE;	//敵を消す
						mPlayer.score += mEnemy[y].point;	
						CreateEffect(mEnemy[y].x, mEnemy[y].y);	//爆発

					}
					mPlayerShot[x].flg = FALSE;
					break;
				}
			}
		}
	}
}

void DrawPlayerShot() {
	for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
		if (mPlayerShot[x].flg == TRUE) {
			DrawRotaGraph(mPlayerShot[x].x, mPlayerShot[x].y, 1.0f, 0, mPlayerShot[x].image, TRUE, FALSE);
		}
	}

}

int HitCirclePlayerShot(ENEMY* e, PLAYER_SHOT* p)

{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}
