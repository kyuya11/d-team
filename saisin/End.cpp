#include "End.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Input.h"
#include "Game.h"

static int mImageHandle;    //画像ハンドル格納用変数
static int StopTime;


/***********************************************
 * 終了　初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void End_Initialize(){
    mImageHandle = LoadGraph("images/End.png");//画像のロード
    StopTime = 0;
}


/***********************************************
 * 終了　終了処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void End_Finalize(){
    DeleteGraph(mImageHandle);//画像の解放
}

//更新用関数はなし
// void End_Update(){}

/***********************************************
 * 終了　描画処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void End_Draw(){

    DrawGraph(0,0,mImageHandle,FALSE);

    SetFontSize(24);
    DrawString(360, 480 - 24, "Thank you for Playing", 0xffffff, 0);

    //タイムの加算処理＆終了 (２秒後)
    if (++StopTime > 120) {
        SceneMgr_ChangeScene(eScene_Stop); //シーンをゲーム画面に変更
    }
}

