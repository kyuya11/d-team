#pragma once

/*************************
** 定数 **
*************************/
// 爆発アニメーションの最大数
const int EFFECT_MAX = 20;
const int EFFECT_IMAGE_MAX = 16;


const int EFFECT_RATE = 4; // 1コマ辺りのエフェクト表示時間
/*************************
** 構造体 **
*************************/

// 爆発アニメーション構造体
struct EFFECT {
	bool flg; // 使用フラグ
	int img; // 画像
	int x, y; // 座標x,y
	int time; // 経過時間
};


extern void Effect_Initialize();//初期化
extern void Effect_Finalize();//終了処理
extern void Effect_Update();//更新
extern void Effect_Draw();//描画

//爆発アニメーションの生成
extern int CreateEffect(int x, int y);

