#pragma once

typedef enum {
    eScene_Menu,    //メニュー画面
    eScene_Game,    //ゲーム画面
    eScene_Help,    //ランキング画面
    eScene_HelpInput,   // ランキング入力画面
    eScene_End,     //エンド画面
    eScene_Stop,    //

    eScene_None,    //無し
} eScene ;

void SceneMgr_Initialize();//初期化
void SceneMgr_Finalize();//終了処理
void SceneMgr_Update();//更新
void SceneMgr_Draw();//描画

// 引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene nextScene);

// ゲーム終了メニューが選択されたかどうかを返す
int SceneMgr_GameEnd_Status();
