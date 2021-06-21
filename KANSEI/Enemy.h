#pragma once
//#include "Player.h"

#define PI 3.1415926535897932384626433832795f
/*************************
** 定数 **
*************************/
// 敵機の最大数
const int ENEMY_MAX = 100;
const int ENEMY_IMAGE_MAX = 2;

const int ENEMY_SHOT_MAX = 200;
const int ENEMY_SHOT_IMAGE_MAX = 4;
const int ENEMY_SHOT_SPEED = 3; 
const int ENEMY_ZAKO_HIT_R = 9; 
const int ENEMY_MEDAMA_HIT_R = 18;
const int ENEMY_BOSU_HIT_R = 27;
const int ENEMY_ZAKO_LIFE = 5; 
const int ENEMY_MEDAMA_LIFE = 10;
const int ENEMY_BOSU_LIFE = 150;



/*************************
** 構造体 **
*************************/

// エネミーの構造体
struct ENEMY {
	bool flg; // 使用フラグ
	int type; // タイプ
	int img; // 画像
	int x, y, w, h; // 座標x,y 幅w 高さh
	int mx, my; // 移動量mx,my
	int cnt; // 方向転換、弾生成時に使用
	int hp; // スタミナ（何回当たって消去するか）
	int r; // 半径r
	int bosu;
};

// エネミー弾構造体
struct ENEMY_SHOT {
	bool flg; // 使用フラグ
	int img; // 画像
	double x, y; // 座標x,y
	int w, h; // 幅w 高さh
	double mx, my; // 移動量mx,my
	int r; // 半径r
};


extern struct ENEMY mEnemy[ENEMY_MAX];
extern int mImageEnemy[ENEMY_IMAGE_MAX];
extern int EnemyCount[ENEMY_IMAGE_MAX];

extern void Enemy_Initialize();//初期化
extern void Enemy_Finalize();//終了処理
extern void Enemy_Update();//更新
extern void Enemy_Draw();//描画

//エネミーの生成
int CreateEnemy(int, int, int, int, int, int, int, int);

//幽霊
void EnemyType01(ENEMY*);		//エネミータイプ１の移動と攻撃
void EnemyType02(ENEMY*);		//エネミータイプ２の移動と攻撃
void EnemyType03(ENEMY*);		//エネミータイプ３の移動と攻撃
void EnemyType04(ENEMY*);		//エネミータイプ４の移動と攻撃
void EnemyType05(ENEMY*);		//エネミータイプ５の移動と攻撃
void EnemyType06(ENEMY*);		//エネミータイプ6の移動と攻撃

//目玉
void EnemyType07(ENEMY*);		//エネミータイプ7の移動と攻撃
void EnemyType08(ENEMY*);		//エネミータイプ8の移動と攻撃
void EnemyType09(ENEMY*);		//エネミータイプ9の移動と攻撃
void EnemyType10(ENEMY*);		//エネミータイプ１0の移動と攻撃
void EnemyType11(ENEMY*);		//エネミータイプ１1の移動と攻撃
void EnemyType12(ENEMY*);		//エネミータイプ１2の移動と攻撃
void EnemyType13(ENEMY*);		//エネミータイプ１3の移動と攻撃

//ボス
void EnemyType14(ENEMY*);		//エネミータイプ１4の移動と攻撃



int CreateEnemyShot(double x, double y, double mx, double my);

void CreateTargetShot(ENEMY*);
void CreateDirectionShot(ENEMY*);
void CreateNWayShot(ENEMY*);

void EraseEnemyShot();
