#pragma once

#define PI 3.1415926535897932384626433832795f

const int ITEM_MAX = 1;
const int ITEM_IMAGE_MAX = 3;
const int BARIA = 1;

const int ITEM_HIT_R = 18;	// �Փ˔���̔��a

struct ITEM {
	bool flg;			// �g�p�t���O
	int type;			// �^�C�v
	int img;			// �摜
	int x, y, w, h;		// ���Wx,y ��w ����h
	int point;			// �X�R�A���Z
	int mx, my;			// �ړ���mx,my
	int cnt;			// �����]���A�e�������Ɏg�p
	int hp;				// �X�^�~�i�i���񓖂����ď������邩�j
	int r;				// ���ar
};

extern struct ITEM mItem[ITEM_MAX];
extern int mImageItem[ITEM_IMAGE_MAX];
extern int ItemCount[ITEM_IMAGE_MAX];
extern int redbaria;

int CreateItem(int type, int img, int x, int y, int w, int h, int point, int mx, int my);

void ItemType01(ITEM*);		//�A�C�e���i�ԁj�̈ړ�
void ItemType02(ITEM*);		//�A�C�e���i�j�̈ړ�
void ItemType03(ITEM*);		//�A�C�e���i���j�̈ړ�

void Item_Initialize();
void Item_Finalize();
void Item_Update();
void Item_Draw();
