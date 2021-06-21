#include "Help.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Input.h"
#include "Game.h"


static int mImageHandle; 
static int WaitTime; 

void Help_Initialize() {
	mImageHandle = LoadGraph("images/Help.png");
	WaitTime = 0;
}

void Help_Finalize() {
	DeleteGraph(mImageHandle);
}

void Help_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) { 
			SceneMgr_ChangeScene(eScene_Menu);
	}
}

void Help_Draw() {
	
	DrawGraph(0, 0, mImageHandle, FALSE);

	SetFontSize(30);
	
	DrawString(100, 150, "・矢印キーで移動。↑↓→←", GetColor(255, 255, 255));
	DrawString(100, 200, "・アイテム効果(ポーション)", GetColor(255, 255, 255));
	DrawString(100, 300, "・ボスを倒したらゲームクリア！", GetColor(255, 255, 255));


	SetFontSize(20);
	DrawString(100, 250, "青→HP1回復  赤→弾数増加  黄→バリア付与", GetColor(255, 255, 255));


	if (++WaitTime < 50) {
		SetFontSize(16);
		DrawString(200, 460, "EscキーまたはBボタンを押すとメニュー画面に戻ります。",
			GetColor(255, 255, 255));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}

