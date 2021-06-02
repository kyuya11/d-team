#pragma once

// 構造体宣言
struct RankingData
{ // ランキングデータ
	int no;
	char name[11];
	long score;
};

//define定義
#define RANKCOUNT 7
#define RANKING_FILE "rankingdata.txt"

// 関数プロトタイプ宣言
void Rank_Initialize();//初期化
void Rank_Finalize();//終了処理
void Rank_Update();//更新
void Rank_Draw();//描画
void Rank_Input(); //ランキング入力
void Rank_Sort(); //ランキング並べ替え
void Rank_Save(); //ランキングデータの保存
void Rank_Read(); //ランキングデータ読み込み

extern struct RankingData Ranking[RANKCOUNT];
