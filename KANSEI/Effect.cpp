#include "DxLib.h"
#include "Effect.h"


/*************************
** 変数 **
*************************/
// 爆発アニメーション（エフェクト）
struct EFFECT mEffect[EFFECT_MAX];
int mImageEffect[EFFECT_IMAGE_MAX];


/***********************************************
* エフェクト 初期化
* 引 数：なし
* 戻り値：なし
***********************************************/
void Effect_Initialize() {
	LoadDivGraph("images/Effect.png", 16, 8, 2, 96, 96, mImageEffect); //爆発アニメーション（エフェクト）画像

		// 爆発アニメーションの初期設定
		for (int i = 0; i < EFFECT_MAX; i++) {
			mEffect[i].flg = FALSE;
		}

}


/***********************************************
* エフェクト 終了処理
* 引 数：なし
* 戻り値：なし
***********************************************/
void Effect_Finalize() {
	for (int i = 0; i < EFFECT_IMAGE_MAX; i++) {
		DeleteGraph(mImageEffect[i]); //画像の解放
	}
}


/***********************************************
* エフェクト 更新
* 引 数：なし
* 戻り値：なし
***********************************************/
void Effect_Update() {
	//爆発アニメーションの処理
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (mEffect[i].flg == TRUE) {

			// 何番目の画像を表示するか計算する
			mEffect[i].img = mEffect[i].time / EFFECT_RATE;
			
			// 最後の画像を表示したかの判断
			if (++mEffect[i].time > EFFECT_RATE * EFFECT_IMAGE_MAX) {
				mEffect[i].flg = false;
			}
		}
	}
}


/***********************************************
* エフェクト 描画処理
* 引 数：なし
* 戻り値：なし
***********************************************/
void Effect_Draw() {
	//爆発アニメーションの処理
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (mEffect[i].flg == TRUE) {

			DrawRotaGraph(mEffect[i].x, mEffect[i].y, 1.0f, 0, mImageEffect
				[mEffect[i].img], TRUE, FALSE);
		}
	}
}


/**********************************
* 爆発アニメーションの生成
* 引 数：x:x座標、y:y座標
* 戻り値：TRUE:成功 FALSE:失敗
**********************************/
int CreateEffect(int x, int y)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (mEffect[i].flg == FALSE) {
			mEffect[i].flg = TRUE;
			mEffect[i].img = 0;
			mEffect[i].x = x;
			mEffect[i].y = y;
			mEffect[i].time = 0;

			// 成功
			return TRUE;
		}
	}

	// 失敗
	return FALSE;
}
