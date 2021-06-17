#pragma once

#define PI 3.1415926535897932384626433832795f
/*************************
** 定数 **
*************************/

// 画面領域の大きさ
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH_R = 440;
const int SCREEN_WIDTH_L = 10;

const int PLAYER_POS_X = (SCREEN_WIDTH - 200) / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 38;
const int PLAYER_HEIGHT = 48;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 5;
const int PLAYER_SHOT_INTERVAL = 10;

const int PLAYER_HIT_R = 3;

const int PLAYER_SHOT_MAX = 100;

/*************************
** 構造体 **
*************************/
// プレイヤー
struct PLAYER {
	bool flg; // 使用フラグ
	int x, y; // 座標x,y
	int w, h; // 幅w 高さh
	double angle; // 機体の向き
	int count; // 復活間隔
	int shotCount; // 弾間隔
	int hp; // 体力
	int time; // 経過時間
	int score; // スコア
	int r;
	int up;
	int baria;

};

// プレイヤー弾
struct PLAYER_SHOT {
	bool flg; // 使用フラグ
	int x, y; // 座標x,y
	int w, h; // 幅w 高さh
	int mx, my; // 移動量mx,my
	int image; // 画像
	int r;
};

extern struct PLAYER mPlayer;
extern struct PLAYER_SHOT mPlayerShot[PLAYER_SHOT_MAX];

extern void Player_Initialize();//初期化
extern void Player_Finalize();//終了処理
extern void Player_Update();//更新
extern void Player_Draw();//描画

int MakePlayerShot();//プレイヤー弾生成
void MovePlayerShot();//プレイヤー弾移動
void DrawPlayerShot();//プレイヤー弾描画