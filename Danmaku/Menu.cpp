#include "DxLib.h"
#include "SceneMgr.h"
#include "Menu.h"
#include "Input.h"

static int mImageHandle;  //画像ハンドル格納用変数
static int mImageSelect;  //画像ハンドル格納用変数
static int MenuNumber = 0;  //メニューカーソル管理用変数

static int mSoundsSelect;  //音ファイル格納用変数
static int mSoundsMove;    //音ファイル格納用変数


/***********************************************
 * メニュー　初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Menu_Initialize(){
    mImageHandle = LoadGraph("images/Scene_Menu.png");    //画像のロード
    mImageSelect = LoadGraph("images/select.png");    //画像のロード

    mSoundsSelect = LoadSoundMem("sounds/tm2_power000.wav");    //決定音のロード
    mSoundsMove = LoadSoundMem("sounds/botan.wav");    //移動音のロード

    // ＢＧＭ再生
    PlayMusic("sounds/yamiyouen.mp3", DX_PLAYTYPE_LOOP);
}


/***********************************************
 * メニュー　終了処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Menu_Finalize(){
    DeleteGraph(mImageHandle);    //画像の解放
    DeleteGraph(mImageSelect);    //画像の解放

    StopSoundMem(mSoundsSelect);    //画像の解放
    StopSoundMem(mSoundsMove);    //画像の解放

    // ＢＧＭ停止
    StopMusic();

}


/***********************************************
 * メニュー　更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Menu_Update() {
    //メニューカーソル移動処理
    if (iKeyFlg & PAD_INPUT_DOWN) {
        PlaySoundMem(mSoundsMove, DX_PLAYTYPE_BACK);
        if (++MenuNumber > 2) MenuNumber = 0;
    }
    if (iKeyFlg & PAD_INPUT_UP) {
        PlaySoundMem(mSoundsMove, DX_PLAYTYPE_BACK);
        if (--MenuNumber < 0) MenuNumber = 2;
    }

    if (iKeyFlg == PAD_INPUT_1) { //Zキーが押されていたら
        PlaySoundMem(mSoundsSelect, DX_PLAYTYPE_BACK);
        WaitTimer(500);
        switch (MenuNumber) {       //シーンによって処理を分岐
        case 0:    //現在の画面がメニューなら
            SceneMgr_ChangeScene(eScene_Game); //シーンをゲーム画面に変更
            break;
        case 1:
            SceneMgr_ChangeScene(eScene_Rank); //シーンをゲーム画面に変更
            break;
        case 2:
            SceneMgr_ChangeScene(eScene_End); //シーンをゲーム画面に変更
            break;

        }
    }
    
}

//描画
void Menu_Draw(){
    DrawGraph(0,0,mImageHandle,FALSE);

    // メニューカーソル
    DrawRotaGraph(340, 230 + MenuNumber * 67, 1.0f, 1.0f, mImageSelect, TRUE);

}
