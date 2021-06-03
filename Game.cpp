#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "stage.h"
#include "Effect.h"
#include "Rank.h"
#include "ITEM.h"


/*************************
** 変数 **
*************************/
static int mImageHandle; //画像ハンドル格納用変数
static int mImageBackground;
static int mImageHp;

static int gameScore; //ゲームスコア
static int mGameTime;
static int mgameStatus;

static int mScroll1;
static int mScroll2;


//初期化
void Game_Initialize() {
	mImageHandle = LoadGraph("images/Scene_Game.png"); //画像のロード

	mImageBackground = LoadGraph("images/haikei.jpg");

	mImageHp = LoadGraph("images/select.png");

	// *** +4lines
	// ゲーム中BGM再生
	PlayMusic("sounds/yukinagori.mp3", DX_PLAYTYPE_LOOP);
	
	mScroll1 = 0;
	mScroll2 = -960;

	Player_Initialize();
	Enemy_Initialize();
	Effect_Initialize();
	Item_Initialize();


	mGameTime = 0;

	mgameStatus = true;
}

//終了処理
void Game_Finalize() {
	DeleteGraph(mImageHandle); //画像の解放

// *** +4lines
	// ゲーム中BGM停止
	StopMusic();

	Player_Finalize();
	Enemy_Finalize();
	Effect_Finalize();
	Item_Finalize();


}

//更新
void Game_Update() {
	//BボタンまたはESCボタンでメニューに戻る
	if (iKeyFlg == PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_ESCAPE) != 0)) {
		SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
	}

	if (mPlayer.hp > 0) {
		Player_Update();
		Enemy_Update();
		Effect_Update();
		Item_Update();


		mGameTime++;

		Stage1();
		//Stage2();
	}
}



//描画
void Game_Draw() {

	BackScroll();

	if (mPlayer.hp > 0) {
		Player_Draw();
		Effect_Draw();
		Enemy_Draw();
		Item_Draw();

	}

	// ゲーム画面（フレーム描画）
	DrawGraph(0, 0, mImageHandle, TRUE);

	if (mgameStatus == FALSE) {
		GameClear();
	}
	if (mPlayer.hp <= 0) {
		GameOver();
	}
	else {
		ScoreDraw();
	}
}


/***********************************************
* ゲームオーバー処理
* 引 数：なし
* 戻り値：なし
***********************************************/

void GameClear(void)
{
	const char* str1 = "---- Xキーを押してランキング入力画面へ ----";
	const char* str2 = "---- Xキーを押してタイトルへ戻る ----";
	char str3[48];

	gameScore = mPlayer.score;

	if (Ranking[0].score < gameScore) {
		if (iKeyFlg == PAD_INPUT_2) {
			SceneMgr_ChangeScene(eScene_RankInput);
		}

		strcpy(str3, str1);
	}
	else {
		if (iKeyFlg == PAD_INPUT_2) {
			SceneMgr_ChangeScene(eScene_Menu);
		}

		strcpy(str3, str2);
	}
	mgameStatus = true;

	SetFontSize(40);
	DrawString(20, 220, "ＧＡＭＥ　ＣＬＥＡＲ", 0xffffff, 0);

	SetFontSize(20);
	DrawString(20, 440, str1, 0xffffff, 0);
}

void GameOver(void)
{
	const char* str1 = "---- Xキーを押してランキング入力画面へ ----";
	const char* str2 = "---- Xキーを押してタイトルへ戻る ----";
	char str3[48];

	gameScore = mPlayer.score;

	if (Ranking[0].score < gameScore) {
		if (iKeyFlg == PAD_INPUT_2) { //Xキーが押されていたら
			SceneMgr_ChangeScene(eScene_RankInput); //ランキング画面入力へ
		}

		strcpy(str3, str1);
	}
	else {
		if (iKeyFlg == PAD_INPUT_2) { //Xキーが押されていたら
			SceneMgr_ChangeScene(eScene_Menu); //シーンをゲーム画面に変更
		}

		strcpy(str3, str2);
	}
	mgameStatus = true;

	// フォントサイズの設定
	SetFontSize(40);
	DrawString(35, 220, "ＧＡＭＥ ＯＶＥＲ", 0xffffff, 0);
	
	// フォントサイズの設定
	SetFontSize(20);
	DrawString(35, 440, str3, 0xffffff, 0);
}

void BackScroll()
{
	mScroll1 = mScroll1 + 5;
	if (mScroll1 >= 960) { mScroll1 = -960; }
	mScroll2 = mScroll2 + 5;
	if (mScroll2 >= 960) { mScroll2 = -960; }

	DrawGraph(0, mScroll1, mImageBackground, TRUE);
	DrawGraph(0, mScroll2, mImageBackground, TRUE);

}

void ScoreDraw()
{
	SetFontSize(20);

	DrawFormatString(496, 45, GetColor(0, 0, 0), "%010d", Ranking[0].score);
	DrawFormatString(494, 43, GetColor(255,255,255), "%010d", Ranking[0].score);
	DrawFormatString(496, 98, GetColor(0, 0, 0), "%010d", mPlayer.score);
	DrawFormatString(494, 96, GetColor(255,255,255), "%010d", mPlayer.score);

	for (int i = 0; i < mPlayer.hp; i++) {
		DrawGraph(455 + i * 25, 255, mImageHp, TRUE);
	}
}

//ゲームスコア取得
int Game_GetScore() {
	return gameScore;
}


int Game_GetmGameTime() {
	return mGameTime;
}

void Game_SetmgameStatus(int flg) {
	mgameStatus = flg;
}