#pragma once

// 構造体宣言
struct HelpData
{ // ランキングデータ
	int no;
	char name[11];
	long score;
};

//define定義

// 関数プロトタイプ宣言
void Help_Initialize();//初期化
void Help_Finalize();//終了処理
void Help_Update();//更新
void Help_Draw();//描画

