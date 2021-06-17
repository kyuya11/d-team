#pragma once

#define PI 3.1415926535897932384626433832795f

const int ITEM_MAX = 1;
const int ITEM_IMAGE_MAX = 3;
const int BARIA = 1;

const int ITEM_HIT_R = 18;	// 衝突判定の半径

struct ITEM {
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

extern struct ITEM mItem[ITEM_MAX];
extern int mImageItem[ITEM_IMAGE_MAX];
extern int ItemCount[ITEM_IMAGE_MAX];
extern int redbaria;

int CreateItem(int type, int img, int x, int y, int w, int h, int point, int mx, int my);

void ItemType01(ITEM*);		//アイテム（赤）の移動
void ItemType02(ITEM*);		//アイテム（青）の移動
void ItemType03(ITEM*);		//アイテム（黄）の移動

void Item_Initialize();
void Item_Finalize();
void Item_Update();
void Item_Draw();
