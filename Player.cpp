#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"
#include "Effect.h"
#include <math.h>


/*************************
** プロトタイプ宣言 **
*************************/
int HitCirclePlayerShot(ENEMY*, PLAYER_SHOT*);	//エネミー当たり判定（円）

/*************************
** 変数 **
*************************/
// 自機
struct PLAYER mPlayer;
struct PLAYER_SHOT mPlayerShot[PLAYER_SHOT_MAX];

static int mImagePlayer;    //画像ハンドル格納用変数
static int mImageHitPoint[2];  //画像ハンドル格納用変数
static int mImageHodai[3];  //画像ハンドル格納用変数
static int mImageDan[3];    //画像ハンドル格納用変数

static int mSoundsShot;    //音ファイル格納用変数


int MPlayerHodaiPosion[2][7][3] = {
	{
		{-24, -12, 1},
		{-16, -24, 1},
		{ -8, -36, 0},
		{  0, -48, 2},
		{  8, -36, 0},
		{ 16, -24, 1},
		{ 24, -12, 1}
	},
	{
		//{-48, -12, 1},
		//{-32, -24, 1},
		//{-16, -36, 0},
		//{  0, -48, 2},
		//{ 16, -36, 0},
		//{ 32, -24, 1},
		//{ 48, -12, 1}
		{0, -48, 0}
	}
};

int MPlayerShotMove[2][7][2] = {
	{
		{ 0, -14},
		{ 0, -14},
		{ 0, -14},
		{ 0, -14},
		{ 0, -14},
		{ 0, -14},
		{ 0, -14} 

	},
	{
		{-3, -11},
		{-2, -12},
		{-1, -13},
		{ 0, -14},
		{ 1, -13},
		{ 2, -12},
		{ 3, -11}
	}
};


/***********************************************
 * プレイヤー　初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Player_Initialize(){
	SetTransColor(0, 0, 0);
	mImagePlayer = LoadGraph("images/player3.png");    //プレイヤー画像
	LoadDivGraph("images/playerhantei.png", 2, 2, 1, 60, 60, mImageHitPoint);	//プレイヤー当たり判定
	LoadDivGraph("images/playerHodai1.png", 3, 3, 1, 12, 16, mImageHodai);	//プレイヤー砲台画像
	LoadDivGraph("images/playerDan1.png", 3, 3, 1, 12, 24, mImageDan);	//プレイヤー弾画像

	mSoundsShot = LoadSoundMem("sounds/shoot.wav");    //弾発射音のロード

	// プレイヤーの初期設定
	mPlayer.flg = true;
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.w = PLAYER_WIDTH;
	mPlayer.h = PLAYER_HEIGHT;
	mPlayer.angle = 0.0;
	mPlayer.count = 0;
	mPlayer.hp = PLAYER_HP;
	mPlayer.score = 0;
	// *** +1line
	mPlayer.r = PLAYER_HIT_R;

	// プレイヤー弾の初期設定
	for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
		mPlayerShot[x].flg = FALSE;
	}
}


/***********************************************
 * プレイヤー　終了処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Player_Finalize(){
    DeleteGraph(mImagePlayer);    //画像の解放
}


/***********************************************
 * プレイヤー　更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Player_Update(){

	// 上下左右移動
	if (iNowKey & PAD_INPUT_UP)		mPlayer.y -= PLAYER_SPEED;
	if (iNowKey & PAD_INPUT_DOWN)	mPlayer.y += PLAYER_SPEED;
	if (iNowKey & PAD_INPUT_LEFT)	mPlayer.x -= PLAYER_SPEED;
	if (iNowKey & PAD_INPUT_RIGHT)	mPlayer.x += PLAYER_SPEED;

	// 画面をはみ出さないようにする
	if (mPlayer.x < SCREEN_WIDTH_L + mPlayer.w/2) mPlayer.x = SCREEN_WIDTH_L + mPlayer.w/2;
	if (mPlayer.x > SCREEN_WIDTH_R - mPlayer.w/2) mPlayer.x = SCREEN_WIDTH_R - mPlayer.w/2;
	if (mPlayer.y < 32)					mPlayer.y = 32;
	if (mPlayer.y > SCREEN_HEIGHT - 32)	mPlayer.y = SCREEN_HEIGHT - 32;

	// *** +2lines
	// プレイヤーの状態がTRUEの時
	if (mPlayer.flg) {
		//Zキーが押されていたらプレイヤー弾生成
		mPlayer.shotCount++;
		if (mPlayer.shotCount > PLAYER_SHOT_INTERVAL) {
			if (iNowKey & PAD_INPUT_1) {
				mPlayer.shotCount = 0;

				if (MakePlayerShot()) {
					PlaySoundMem(mSoundsShot, DX_PLAYTYPE_BACK);

				}
			}
		}
	// *** +1line
	}

	//プレイヤー弾移動；
	MovePlayerShot();

	//経過時間　（背景スクロール＆エネミー生成時に使用する）
	mPlayer.time++;

}


/***********************************************
 * プレイヤー　描画処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Player_Draw() {

	// プレイヤーの表示
	if (mPlayer.flg) {
		DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer, TRUE, FALSE);
		// *** +2lines
		// プレイヤー当たり判定ポイント
		DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImageHitPoint[1], TRUE, FALSE);

		// ストレート弾（収束ショット）
		if (iNowKey & PAD_INPUT_B) {
			for (int i = 0; i < 7; i++) {
				DrawRotaGraph(mPlayer.x + MPlayerHodaiPosion[0][i][0], 
					          mPlayer.y + MPlayerHodaiPosion[0][i][1],
					          1.0f, 0, mImageHodai[MPlayerHodaiPosion[0][i][2]], TRUE, FALSE);
			}
			DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImageHitPoint[1], TRUE, FALSE);
			} 
		else  {//  ｎ－ｗａｙ弾
				for (int i = 0; i < 7; i++) {
					DrawRotaGraph(mPlayer.x + MPlayerHodaiPosion[1][i][0],
						mPlayer.y + MPlayerHodaiPosion[1][i][1],
						1.0f, 0, mImageHodai[MPlayerHodaiPosion[1][i][2]], TRUE, FALSE);
				}
			}
		}
		else {
			// プレイヤー復活までの時間3秒（180フレーム）
			if (++mPlayer.count >= 80)	mPlayer.flg = true;
			if (mPlayer.count / 5 % 2 == 0) {
				DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer, TRUE, FALSE);
			}
		}

		DrawPlayerShot();

	}


	/***********************************************
	 * プレイヤー弾生成
	 * 引　数：なし
	 * 戻り値：なし
	 ***********************************************/
int MakePlayerShot() {

	bool flg = FALSE;

	// ストレート弾（収束ショット）
	if (iNowKey & PAD_INPUT_B) {
		for (int i = 0; i < 7; i++) {
			// プレイヤー弾の生成
			for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
				if (mPlayerShot[x].flg == FALSE) {
					flg = TRUE;

					mPlayerShot[x].flg = TRUE;
					mPlayerShot[x].w = 12;
					mPlayerShot[x].h = 14;
					mPlayerShot[x].x = mPlayer.x + MPlayerHodaiPosion[0][i][0];
					mPlayerShot[x].y = mPlayer.y + MPlayerHodaiPosion[0][i][1];
					mPlayerShot[x].image = mImageDan[MPlayerHodaiPosion[0][i][2]];
					mPlayerShot[x].mx = MPlayerShotMove[0][i][0];
					mPlayerShot[x].my = MPlayerShotMove[0][i][1];
					break;
				}
			}
		}
	}
	else{//  ｎ－ｗａｙ弾
		for (int i = 0; i < 7; i++) {
			// プレイヤー弾の生成
			for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
				if (mPlayerShot[x].flg == FALSE) {
					flg = TRUE;

					mPlayerShot[x].flg = TRUE;
					mPlayerShot[x].w = 12;
					mPlayerShot[x].h = 14;
					mPlayerShot[x].x = mPlayer.x + MPlayerHodaiPosion[1][i][0];
					mPlayerShot[x].y = mPlayer.y + MPlayerHodaiPosion[1][i][1];
					mPlayerShot[x].image = mImageDan[MPlayerHodaiPosion[1][i][2]];
					mPlayerShot[x].mx = MPlayerShotMove[1][i][0];
					mPlayerShot[x].my = MPlayerShotMove[1][i][1];
					break;
				}
			}
		}
	}

	return flg;
}


/***********************************************
 * プレイヤー弾移動
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void MovePlayerShot() {
	// プレイヤー弾の初期設定
	for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
		if (mPlayerShot[x].flg == TRUE) {
			mPlayerShot[x].x += mPlayerShot[x].mx;
			mPlayerShot[x].y += mPlayerShot[x].my;

			if (mPlayerShot[x].y < -14) {
				mPlayerShot[x].flg = FALSE;
			}

			// 当たり判定
			for (int y = 0; y < ENEMY_MAX; y++) {
				if (mEnemy[y].flg == false) continue;
				if (HitCirclePlayerShot(&mEnemy[y], &mPlayerShot[x]) == TRUE) {
					if (--mEnemy[y].hp < 0) {
						mEnemy[y].flg = FALSE;
						mPlayer.score += mEnemy[y].point;
						CreateEffect(mEnemy[y].x, mEnemy[y].y);

					}
					mPlayerShot[x].flg = FALSE;
					break;
				}
			}
		}
	}
}


/***********************************************
 * プレイヤー弾描画
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void DrawPlayerShot() {
	// プレイヤー弾の初期設定
	for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
		if (mPlayerShot[x].flg == TRUE) {
			DrawRotaGraph(mPlayerShot[x].x, mPlayerShot[x].y, 1.0f, 0, mPlayerShot[x].image, TRUE, FALSE);
		}
	}

}


/**********************************
 * プレイヤー弾当たり判定（円）
 * 引　数：PLAYERポインタ, ENEMY_SHOTポインタ
 * 戻り値：TRUE:当たり, FALSE:なし
 **********************************/
int HitCirclePlayerShot(ENEMY* e, PLAYER_SHOT* p)

{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}
