// *** +2lines 
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
#include "Help.h"
#include "Item.h"


/*************************
** Game.cpp内変数 **
*************************/
static int mImageHandle;		//画像ハンドル格納用変数
static int mImageBackground;	//画像ハンドル格納用変数
static int mImageHp;			//画像ハンドル格納用変数

static int gameScore;	//ゲームスコア
static int mGameTime;	//ゲーム経過時間
static int mgameStatus;	//ゲーム状態

static int mScroll1;		//背景スクロール用Y座標1
static int mScroll2;		//背景スクロール用Y座標2


/***********************************************
 * ゲーム　初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Game_Initialize(){
    mImageHandle = LoadGraph("images/Scene_Game2.png");    //画像のロード
	mImageBackground = LoadGraph("images/Haikei.png");    //画像のロード
	// *** +1line
	mImageHp = LoadGraph("images/select.png");    //画像のロード

	// ゲーム中BGM再生
	//PlayMusic("sounds/yukinagori.mp3", DX_PLAYTYPE_LOOP);

	// 背景座標設定
	mScroll1 = 0;
	mScroll2 = -960;

	Player_Initialize();
	Enemy_Initialize();
	Effect_Initialize();
	Item_Initialize();

	mGameTime = 0;
	mgameStatus = true;

}


/***********************************************
 * ゲーム　終了処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Game_Finalize(){
    DeleteGraph(mImageHandle);    //画像の解放
	
	// ゲーム中BGM停止
	StopMusic();

	Player_Finalize();
	Enemy_Finalize();
	Effect_Finalize();
	Item_Finalize();
}


// *** 1-function change
/***********************************************
 * ゲーム　更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Game_Update(){
	//YボタンまたはESCボタンでメニューに戻る
	if (iKeyFlg == PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_ESCAPE) != 0)) {
		SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
	}

	// ゲームプレイ中なら各処理をアップデート
	if (mPlayer.hp > 0) {
		Player_Update();
		Enemy_Update();
		Effect_Update();
		Item_Update();

		mGameTime++;

		Stage1();
	}
}


/***********************************************
 * ゲーム　描画処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Game_Draw(){

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
		for (int i = 0; i < mPlayer.hp; i++) {
			DrawGraph(455 + i * 25, 255, mImageHp, TRUE);
		}
	}
}


/***********************************************
 * ゲームクリア処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void GameClear(void)
{
	const char* str1 = "---- Ｘキーを押してタイトルへ戻る ----";
	char str2[48];

	if (iKeyFlg == PAD_INPUT_2) { //Xキーが押されていたら
		SceneMgr_ChangeScene(eScene_Menu); //シーンをゲーム画面に変更
	}

	strcpy(str2, str1);

	mgameStatus = true;

	// フォントサイズの設定
	SetFontSize(40);
	DrawString(20, 220, "ＧＡＭＥ　ＣＬＥＡＲ", 0xffffff, 0);

	// フォントサイズの設定
	SetFontSize(20);
	DrawString(20, 440, str2, 0xffffff, 0);
}


/***********************************************
 * ゲームオーバー処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void GameOver(void)
{
	const char* str1 = "---- Ｘキーを押してタイトルへ戻る ----";
	char str2[48];

	if (iKeyFlg == PAD_INPUT_2) { //Xキーが押されていたら
		SceneMgr_ChangeScene(eScene_Menu); //シーンをゲーム画面に変更
	}

	strcpy(str2, str1);

	mgameStatus = true;

	// フォントサイズの設定
	SetFontSize(40);
	DrawString(35, 220, "ＧＡＭＥ　ＯＶＥＲ", 0xffffff, 0);

	// フォントサイズの設定
	SetFontSize(20);
	DrawString(35, 440, str2, 0xffffff, 0);
}


/**********************************
 * 背景スクロール等
 * 引　数：なし
 * 戻り値：なし
 **********************************/
void BackScroll()
{
	//背景表示
	mScroll1 = mScroll1 + 5;
	if (mScroll1 >= 960) { mScroll1 = -960; }
	mScroll2 = mScroll2 + 5;
	if (mScroll2 >= 960) { mScroll2 = -960; }

	DrawGraph(0, mScroll1, mImageBackground, TRUE);
	DrawGraph(0, mScroll2, mImageBackground, TRUE);
}

/***********************************************
 * ゲーム時間取得
 * 引　数：なし
 * 戻り値：mGameTime
 ***********************************************/
int Game_GetmGameTime() {
	return mGameTime;
}


/***********************************************
 * ゲーム状況セット
 * 引　数：flg
 * 戻り値：mGameTime
 ***********************************************/
void Game_SetmgameStatus( int flg ) {
	mgameStatus = flg;
}
