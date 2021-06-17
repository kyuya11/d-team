#include "DxLib.h"
#include "Game.h"
#include "Help.h"
#include "Menu.h"
#include "End.h"
#include "SceneMgr.h"

static eScene mScene     = eScene_Menu;    //シーン管理変数
static eScene mNextScene = eScene_None;    //次のシーン管理変数

static void SceneMgr_InitializeModule(eScene scene);//指定モジュールを初期化する
static void SceneMgr_FinalizeModule(eScene scene);//指定モジュールの終了処理を行う


/***********************************************
 * シーンマネージャー　初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void SceneMgr_Initialize(){
    SceneMgr_InitializeModule(mScene);
}


/***********************************************
 * シーンマネージャー　終了処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void SceneMgr_Finalize(){
    SceneMgr_FinalizeModule(mScene);
}


/***********************************************
 * シーンマネージャー　更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void SceneMgr_Update(){
    if(mNextScene != eScene_None){    //次のシーンがセットされていたら
        SceneMgr_FinalizeModule(mScene);//現在のシーンの終了処理を実行
        mScene = mNextScene;    //次のシーンを現在のシーンセット
        mNextScene = eScene_None;    //次のシーン情報をクリア
        SceneMgr_InitializeModule(mScene);    //現在のシーンを初期化
    }
    switch(mScene){       //シーンによって処理を分岐
    case eScene_Menu:    //現在の画面がメニューなら
        Menu_Update();   //メニュー画面の更新処理をする
        break;
    case eScene_Game:
        Game_Update();
        break;
    case eScene_Help:
        Help_Update();
        break;
    case eScene_HelpInput:
        break;
    }
}


/***********************************************
 * シーンマネージャー　描画処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void SceneMgr_Draw(){
    switch(mScene){      //シーンによって処理を分岐
    case eScene_Menu:   //現在の画面がメニュー画面なら
        Menu_Draw();    //メニュー画面の描画処理をする
        break;//以下略
    case eScene_Game:
        Game_Draw();
        break;
    case eScene_Help:
        Help_Draw();
        break;
    //case eScene_HelpInput:
    //    Help_Input();
    //    break;
    case eScene_End:
        End_Draw();
        break;
    }
}


/***********************************************
 * シーンの変更処理
 * 引　数：NextScene
 * 戻り値：なし
 ***********************************************/
void SceneMgr_ChangeScene(eScene NextScene){
    mNextScene = NextScene;    //次のシーンをセットする
}


/***********************************************
 * メニューで"ゲームエンド"が選択されたかどうかを返す
 * 引　数：なし
 * 戻り値：1 or 0
 ***********************************************/
int SceneMgr_GameEnd_Status() {
    if (mScene == eScene_Stop) {
        return 1;
    }
    else {
        return 0;
    }
}


/***********************************************
 * 引数sceneを見て、モジュールを初期化する
 * 引　数：scene
 * 戻り値：なし
 ***********************************************/
static void SceneMgr_InitializeModule(eScene scene){
    switch(scene){          //シーンによって処理を分岐
    case eScene_Menu:       //指定画面がメニュー画面なら
        Menu_Initialize();  //メニュー画面の初期化処理をする
        break;//以下略
    case eScene_Game:
        Game_Initialize();
        break;
    case eScene_Help:
    //case eScene_HelpInput:
        Help_Initialize();
        break;
    case eScene_End:
        End_Initialize();
        break;
    }
}


/***********************************************
 * 引数sceneを見て、モジュールの終了処理を行う
 * 引　数：scene
 * 戻り値：なし
 ***********************************************/
static void SceneMgr_FinalizeModule(eScene scene){
    switch(scene){         //シーンによって処理を分岐
    case eScene_Menu:      //指定画面がメニュー画面なら
        Menu_Finalize();   //メニュー画面の終了処理処理をする
        break;//以下略
    case eScene_Game:
        Game_Finalize();
        break;
    case eScene_Help:
    //case eScene_HelpInput:
        Help_Finalize();
        break;
    case eScene_End:
        End_Finalize();
        break;
    }
}
