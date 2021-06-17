#pragma once

#define PI 3.1415926535897932384626433832795f

/*************************
** 定数 **
*************************/

void Game_Initialize();//初期化
void Game_Finalize();//終了処理
void Game_Update();//更新
void Game_Draw();//描画

void GameClear();		// ゲームクリア
void GameOver(void);	//ゲームオーバー処理
void BackScroll();		// 背景描画

int Game_GetScore();			// スコアデータ取得
int Game_GetmGameTime();		// ゲーム時間取得
void Game_SetmgameStatus(int);	// ゲーム状況セット

// *** +1line
void ScoreDraw();