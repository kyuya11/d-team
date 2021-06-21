#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Item.h"
#include "Player.h"
#include "Effect.h"
#include <math.h>

int HitCircleItem(PLAYER*, ITEM*);

struct ITEM mItem[ITEM_MAX];
int mImageItemPosion[ITEM_IMAGE_MAX];

void Item_Initialize() 
{
	LoadDivGraph("images/aitem3.png", 3, 3, 1, 66, 50, mImageItemPosion); 


	for (int i = 0; i < ITEM_MAX; i++) 
	{
		mItem[i].flg = FALSE;
	}

}

void Item_Finalize() 
{
	for (int i = 0; i < ITEM_IMAGE_MAX; i++) 
	{
		DeleteGraph(mImageItemPosion[i]); 
	}

}

void Item_Update()
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (mItem[i].flg == TRUE)
		{
			mItem[i].x += mItem[i].mx;
			mItem[i].y += mItem[i].my;

			mItem[i].cnt++;

			switch (mItem[i].type)
			{
				case 1: ItemType01(&mItem[i]); break;
				case 2: ItemType02(&mItem[i]); break;
				case 3: ItemType03(&mItem[i]); break;

			}

			if (mItem[i].y > SCREEN_HEIGHT + mItem[i].h)
				mItem[i].flg = FALSE;

			if (HitCircleItem(&mPlayer, &mItem[i]) == TRUE) 
			{
				mItem[i].flg = FALSE;

				if (mItem->type == 1)
				{
					mPlayer.up++;
				}

				if (mItem->type == 2)
				{
					mPlayer.baria = 1;

				}

				if (mItem->type == 3)
				{
					mPlayer.hp++;

				}
			}
		}
	}
}

void Item_Draw() 
{
	for (int i = 0; i < ITEM_MAX; i++) 
	{
		if (mItem[i].flg == TRUE) {
			DrawRotaGraph(mItem[i].x, mItem[i].y, 1.0f, 0, mItem[i].img, TRUE, FALSE);
		}
	}
}

int CreateItem(int type, int img, int x, int y, int w, int h, int mx, int my)
{
	for (int i = 0; i < ITEM_MAX; i++) 
	{
		if (mItem[i].flg == FALSE) 
		{
			mItem[i].flg = TRUE;

			mItem[i].type = type;

			if (type == 1) {
				mItem[i].img = mImageItemPosion[img];
				mItem[i].r = ITEM_HIT_R;
			}
			else if (type == 2) {
				mItem[i].img = mImageItemPosion[img];
				mItem[i].r = ITEM_HIT_R;
			}
			else if (type == 3) {
				mItem[i].img = mImageItemPosion[img];
				mItem[i].r = ITEM_HIT_R;
			}

			mItem[i].x = x;
			mItem[i].y = y;
			mItem[i].w = w;
			mItem[i].h = h;
			mItem[i].mx = mx;
			mItem[i].my = my;
			mItem[i].cnt = 0;
			// ¬Œ÷
			return TRUE;
		}
	}

	// Ž¸”s
	return FALSE;
}

void ItemType01(ITEM* mItem)
{
	if (mItem->cnt == 50)
	{
		mItem->my = 0;
	}

	if (mItem->cnt == 200)
	{
		mItem->my = 1;
		mItem->mx = 1;
	}
	if (mItem->x == 300)
	{
		mItem->mx = -1;
	}
	if (mItem->x == 160)
	{
		mItem->mx = 1;
	}
}

void ItemType02(ITEM* mItem)
{
	if (mItem->cnt == 80) {
		mItem->mx = 1;
	}
	if (mItem->x == 300)
	{
		mItem->mx = -1;
	}
	if (mItem->x == 160)
	{
		mItem->mx = 1;
	}
}

void ItemType03(ITEM* mItem)
{

	if (mItem->cnt == 80) {
		mItem->my = 1;

	}
}

int HitCircleItem(PLAYER* p, ITEM* e)
{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}
