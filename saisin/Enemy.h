#pragma once

#define PI 3.1415926535897932384626433832795f
/*************************
** 定数 **
*************************/
// 敵機の最大数
const int ENEMY_MAX = 40;
const int ENEMY_IMAGE_MAX = 2;

const int ENEMY_SHOT_MAX = 200;
const int ENEMY_SHOT_IMAGE_MAX = 4;
const int ENEMY_SHOT_SPEED = 3;	// 移動速度
const int ENEMY_ZAKO_HIT_R = 9;	// 衝突判定の半径
const int ENEMY_MIKO_HIT_R = 18;// 衝突判定の半径
const int ENEMY_ZAKO_LIFE = 5;	// ライフ
const int ENEMY_MIKO_RED_LIFE = 60;	// ライフ

/*************************
** 構造体 **
*************************/

// エネミーの構造体
struct ENEMY {
	bool flg;			// 使用フラグ
	int type;			// タイプ
	int img;			// 画像
	int x, y, w, h;		// 座標x,y 幅w 高さh
	int point;			// スコア加算
	int mx, my;			// 移動量mx,my
	int cnt;			// 方向転換、弾生成時に使用
	int hp;				// スタミナ（何回当たって消去するか）
	int r;				// 半径r

};

// エネミー弾構造体
struct ENEMY_SHOT {
	bool flg;			// 使用フラグ
	int img;			// 画像
	double x, y;		// 座標x,y
	int	w, h;			// 幅w 高さh
	double mx, my;		// 移動量mx,my
	int r;				// 半径r

};

//extern struct PLAYER;

extern struct ENEMY mEnemy[ENEMY_MAX];
extern int mImageEnemy[ENEMY_IMAGE_MAX];
extern int EnemyCount[ENEMY_IMAGE_MAX];

extern void Enemy_Initialize();//初期化
extern void Enemy_Finalize();//終了処理
extern void Enemy_Update();//更新
extern void Enemy_Draw();//描画

//エネミーの生成
int CreateEnemy(int type, int img, int x, int y, int w, int h, int point, int mx, int my);

void EnemyType01(ENEMY*);		//エネミータイプ１の移動と攻撃
void EnemyType02(ENEMY*);		//エネミータイプ２の移動と攻撃
void EnemyType03(ENEMY*);		//エネミータイプ３の移動と攻撃
void EnemyType04(ENEMY*);		//エネミータイプ４の移動と攻撃
void EnemyType05(ENEMY*);		//エネミータイプ５の移動と攻撃

void EnemyType07(ENEMY*);
void EnemyType08(ENEMY*);

void EnemyType09(ENEMY*);
void EnemyType10(ENEMY*);

//エネミー弾の生成
int CreateEnemyShot(int, double, double, double, double);

void CreateTargetShot(ENEMY*);			//狙い撃ち弾
void CreateDirectionShot(ENEMY*);		//方向弾
void CreateNWayShot(ENEMY*);			//N-WAY弾

void EraseEnemyShot();		// エネミー弾の削除
