#pragma once

#define PI 3.1415926535897932384626433832795f
/*************************
** è **
*************************/

// æÊÌæÌå«³
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH_R = 440;
const int SCREEN_WIDTH_L = 10;

const int PLAYER_POS_X = (SCREEN_WIDTH - 200) / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 38;
const int PLAYER_HEIGHT = 48;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 3;
const int PLAYER_SHOT_INTERVAL = 10;
// *** +1line
const int PLAYER_HIT_R = 3;	// ÕË»èÌ¼a

const int PLAYER_SHOT_MAX = 100;

/*************************
** \¢Ì **
*************************/
// vC[
struct PLAYER {
	bool flg;			// gptO
	int x, y;			// ÀWx,y
	int w, h;			// w ³h
	double angle;		// @ÌÌü«
	int count;			// Ôu
	int shotCount;		// eÔu
	int hp;				// ÌÍ
	int time;			// oßÔ
	int score;			// XRA
	int r;				// ¼a
};

// vC[e
struct PLAYER_SHOT {
	bool flg;			// gptO
	int x, y;			// ÀWx,y
	int w, h;			// w ³h
	int mx, my;			// Ú®Êmx,my
	int image;			// æ
	int r;				// ¼a
};

extern struct PLAYER mPlayer;
extern struct PLAYER_SHOT mPlayerShot[PLAYER_SHOT_MAX];

extern void Player_Initialize();//ú»
extern void Player_Finalize();//I¹
extern void Player_Update();//XV
extern void Player_Draw();//`æ

int MakePlayerShot();//vC[e¶¬
void MovePlayerShot();//vC[eÚ®
void DrawPlayerShot();//vC[e`æ

