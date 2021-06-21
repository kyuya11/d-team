#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetMainWindowText("DanmakuShooting"),ChangeWindowMode(TRUE),DxLib_Init(),SetDrawScreen(DX_SCREEN_BACK); 

	SceneMgr_Initialize(); // 初期化
	
	while (ProcessMessage() == 0) { // メッセージ処理
		
		if (SceneMgr_GameEnd_Status()) {
			break; // メニューから終了が選択された
		}

		ClearDrawScreen(); // 画面消去

		InputKey(); // 入力

		SceneMgr_Update(); // 更新
		SceneMgr_Draw(); // 描画

		ScreenFlip(); // 画面更新

	}
	SceneMgr_Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}