#include "Help.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Input.h"
#include "Game.h"

static int mImageHandle; //画像ハンドル格納用変数
static int WaitTime; //ランキング表示時間


/***********************************************
 * ランキング画面 初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Help_Initialize() {
	mImageHandle = LoadGraph("images/Help.png");//画像のロード
	WaitTime = 0;
}


/***********************************************
 * ランキング画面 終了処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Help_Finalize() {
	DeleteGraph(mImageHandle);//画像の解放
}


/***********************************************
 * ランキング画面 更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Help_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Bボタンが押されていたら
			SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
}


/***********************************************
 * ランキングデータ描画
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Help_Draw() {
	//ヘルプ画像表示
	DrawGraph(0, 0, mImageHandle, FALSE);


	// 文字の表示(点滅)
	if (++WaitTime < 50) {
		SetFontSize(16);
		DrawString(200, 460, "EscキーまたはBボタンを押すとメニュー画面に戻ります。",
			GetColor(255, 255, 255));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}