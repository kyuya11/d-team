#pragma once

const int ITEM_MAX = 1;
const int ITEM_IMAGE_MAX = 3;

const int ITEM_HIT_R = 18;

struct ITEM {
	bool flg;
	int type;
	int img;
	int x, y, w, h;
	int mx, my;
	int cnt;
	int r;
};

extern struct ITEM mItem[ITEM_MAX];
extern int mImageItem[ITEM_IMAGE_MAX];
extern int ItemCount[ITEM_IMAGE_MAX];

extern void Item_Initialize();
extern void Item_Finalize();
extern void Item_Update();
extern void Item_Draw();

int CreateItem(int, int, int, int, int, int, int, int);

void ItemType01(ITEM*);
void ItemType02(ITEM*); 
void ItemType03(ITEM*);