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
#include "ITEM.h"

static int mImageHandle; 
static int mImageBackground;
static int mImageHp;
static int mgameStatus;


static int gameScore; 
static int mGameTime;

static int mScroll1;
static int mScroll2;


void Game_Initialize() {
	mImageHandle = LoadGraph("images/Scene_Game.png"); 

	mImageBackground = LoadGraph("images/haikei.png");

	mImageHp = LoadGraph("images/select.png");


	PlayMusic("sounds/Stage.mp3", DX_PLAYTYPE_LOOP);
	
	mScroll1 = 0;
	mScroll2 = -960;

	Player_Initialize();
	Enemy_Initialize();
	Effect_Initialize();
	Item_Initialize();


	mGameTime = 0;

	mgameStatus = TRUE;
}

void Game_Finalize() {
	DeleteGraph(mImageHandle);

	StopMusic();

	Player_Finalize();
	Enemy_Finalize();
	Effect_Finalize();
	Item_Finalize();


}

void Game_Update() {
	if (iKeyFlg == PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_ESCAPE) != 0)) {
		SceneMgr_ChangeScene(eScene_Menu);//ƒV[ƒ“‚ðƒƒjƒ…[‚É•ÏX
	}

	if (mPlayer.hp > 0) {
		Player_Update();
		Enemy_Update();
		Effect_Update();
		Item_Update();


		mGameTime++;

		Stage1();
	}
}

void Game_Draw() {

	BackScroll();

	if (mPlayer.hp > 0) {
		Player_Draw();
		Effect_Draw();
		Item_Draw();
		Enemy_Draw();
	}

	DrawGraph(0, 0, mImageHandle, TRUE);

	if (mEnemy->bosu == 1) {
		GameClear();
	}
	else if (mPlayer.hp <= 0 || mgameStatus == FALSE) {
		GameOver();
	}
	else
	{
		for (int i = 0; i < mPlayer.hp; i++) {
			DrawGraph(455 + i * 25, 255, mImageHp, TRUE);
		}
	}

}

void GameClear(void)
{
	const char* str2 = "---- XƒL[‚ð‰Ÿ‚µ‚Äƒ^ƒCƒgƒ‹‚Ö–ß‚é ----";
	char str3[48];

	if (iKeyFlg == PAD_INPUT_2) {
		SceneMgr_ChangeScene(eScene_Menu);
	}

	strcpy(str3, str2);


	SetFontSize(40);
	DrawString(20, 220, "‚f‚`‚l‚d@‚b‚k‚d‚`‚q", 0xffffff, 0);

	SetFontSize(20);
	DrawString(20, 440, str3, 0xffffff, 0);
}

void GameOver(void)
{
	const char* str2 = "---- XƒL[‚ð‰Ÿ‚µ‚Äƒ^ƒCƒgƒ‹‚Ö–ß‚é ----";

	char str3[48];

	if (iKeyFlg == PAD_INPUT_2) { 
		SceneMgr_ChangeScene(eScene_Menu); 
	}

	strcpy(str3, str2);

	SetFontSize(40);
	DrawString(35, 220, "‚f‚`‚l‚d ‚n‚u‚d‚q", 0xffffff, 0);
	
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

int Game_GetmGameTime() {
	return mGameTime;
}

void Game_SetmgameStatus(int flg) {
	mgameStatus = flg;
}