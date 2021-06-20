#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Enemy.h"
#include "Player.h"
#include "Effect.h"
#include "Game.h"
#include <math.h>


int HitCircleEnemy(PLAYER*, ENEMY*);
int HitCircleEnemyShot(PLAYER*, ENEMY_SHOT*);

/*************************
** �ϐ� **
*************************/
// �G�l�~�[
struct ENEMY mEnemy[ENEMY_MAX];
int mImageEnemyYurei;
int mImageEnemyBosu[ENEMY_IMAGE_MAX];
int mImageEnemyMedama;
int mImageEnemyTakara[ENEMY_IMAGE_MAX];

// �G�l�~�[�e
struct ENEMY_SHOT mEnemyShot[ENEMY_SHOT_MAX];
int mImageEnemyShot[ENEMY_SHOT_IMAGE_MAX];

//������
void Enemy_Initialize() {
	mImageEnemyYurei = LoadGraph("images/yurei1.png");
	LoadDivGraph("images/bosu.png", 4, 4, 1, 96, 64, mImageEnemyBosu); //�G�l�~�[�摜�i�ޏ��F�~�R�j
	LoadDivGraph("images/EnemyDan.png", 4, 4, 1, 16, 16, mImageEnemyShot); //�G�l�~�[�e�摜
	mImageEnemyMedama = LoadGraph("images/medama2.png");	//��44 �c41
	LoadDivGraph("images/reazako.png", 3, 3, 1, 24, 30, mImageEnemyTakara);

	// �G�l�~�[�̏����ݒ�
	for (int i = 0; i < ENEMY_MAX; i++) {
		mEnemy[i].flg = FALSE;
	}

	// �G�l�~�[�e�̏����ݒ�
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		mEnemyShot[i].flg = FALSE;
	}
}

//�I������
void Enemy_Finalize() {
	for (int i = 0; i < ENEMY_IMAGE_MAX; i++) {
		DeleteGraph(mImageEnemyTakara[i]); //�摜�̉��	
		DeleteGraph(mImageEnemyBosu[i]); //�摜�̉��	
	}
		DeleteGraph(mImageEnemyYurei); //�摜�̉��
		DeleteGraph(mImageEnemyMedama); //�摜�̉��	

	for (int i = 0; i < ENEMY_SHOT_IMAGE_MAX; i++) {
		DeleteGraph(mImageEnemyShot[i]); //�摜�̉��
	}
}

//�X�V
void Enemy_Update() {
	//�G�l�~�[����
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == TRUE) {

			// �G�l�~�[�ړ�
			mEnemy[i].x += mEnemy[i].mx;
			mEnemy[i].y += mEnemy[i].my;

			mEnemy[i].cnt++;

			// �p�^�[���� �G�̓���
			switch (mEnemy[i].type) {
				case 1: EnemyType01(&mEnemy[i]); break;
				case 2: EnemyType02(&mEnemy[i]); break;
				case 3: EnemyType03(&mEnemy[i]); break;
				case 4: EnemyType04(&mEnemy[i]); break;
				case 5: EnemyType05(&mEnemy[i]); break;
				case 6: EnemyType06(&mEnemy[i]); break;
				case 7: EnemyType07(&mEnemy[i]); break;
				case 8:EnemyType08(&mEnemy[i]); break;
				case 9:EnemyType09(&mEnemy[i]); break;
				case 10:EnemyType10(&mEnemy[i]); break;
				case 11:EnemyType11(&mEnemy[i]); break;
				case 12:EnemyType12(&mEnemy[i]); break;
				case 13:EnemyType13(&mEnemy[i]); break;
				case 14:EnemyType14(&mEnemy[i]); break;
			}

			// ��ʂ��͂ݏo���������
			if (mEnemy[i].y > SCREEN_HEIGHT + mEnemy[i].h) {
				mEnemy[i].flg = FALSE;
			}

			if (mEnemy[i].y < 0 - mEnemy[i].h) {
				mEnemy[i].flg = FALSE;
			}
			
			if (mEnemy[i].x > 440 + mEnemy[i].w) {
				mEnemy[i].flg = FALSE;
			}
			if (mEnemy[i].x < 0 - mEnemy[i].w) {
				mEnemy[i].flg = FALSE;
			}

			if (HitCircleEnemy(&mPlayer, &mEnemy[i]) == TRUE) {
				if (mPlayer.baria == 0)
				{
					mPlayer.flg = FALSE;
					mPlayer.count = 0;
					mPlayer.hp -= 1;
					mEnemy[i].flg = FALSE;
				}
				if (mPlayer.baria == 1)
				{
					mPlayer.count = 0;
					mPlayer.baria = 0;
					mEnemy[i].flg = FALSE;

				}

				CreateEffect(mEnemy[i].x, mEnemy[i].y);
			}
		}
	}

	//�G�l�~�[�e����
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		if (mEnemyShot[i].flg == TRUE) {

			// �G�l�~�[�e�ړ�
			mEnemyShot[i].x += mEnemyShot[i].mx;
			mEnemyShot[i].y += mEnemyShot[i].my;
			
			// ��ʂ��͂ݏo���������
			if (mEnemyShot[i].y > SCREEN_HEIGHT + mEnemyShot[i].h) {
				mEnemyShot[i].flg = FALSE;
			}

			if (mEnemyShot[i].y < 0 - mEnemyShot[i].h) {
				mEnemyShot[i].flg = FALSE;
			}

			if (mEnemyShot[i].x > 440 + mEnemyShot[i].w) {
				mEnemyShot[i].flg = FALSE;
			}
			if (mEnemyShot[i].x < 0 - mEnemyShot[i].w) {
				mEnemyShot[i].flg = FALSE;
			}

			if (mPlayer.flg == false)
				continue;
			if (HitCircleEnemyShot(&mPlayer, &mEnemyShot[i]) == TRUE) {
				if (mPlayer.baria == 0)
				{
					mPlayer.flg = FALSE;
					mPlayer.count = 0;
					mPlayer.hp -= 1;
				}

				if (mPlayer.baria == 1)
				{
					mPlayer.baria = 0;
					mPlayer.flg = FALSE;
					mPlayer.count = 0;
				}

				EraseEnemyShot();
				CreateEffect(mPlayer.x, mPlayer.y);
			}
		}
	}
}

//�`��
void Enemy_Draw() {
	//�G�l�~�[����
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == TRUE) {
			DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.0f, 0, mEnemy[i].img, TRUE, FALSE);
		}
	}
	//�G�l�~�[�e����
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		if (mEnemyShot[i].flg == TRUE) {
			DrawRotaGraph(mEnemyShot[i].x, mEnemyShot[i].y, 1.0f, 0, mEnemyShot[i].img, TRUE, FALSE);
		}
	}
}


/**********************************
* �G�l�~�[�̐���
* �� ���Ftype:�^�C�v�P�|�S�̓U�R�A�T�|�V�͛ޏ�
* img�F�P�̓U�R�A�Q�̓U�R�ԁA1�͛ޏ��B�Q�͛ޏ���
*
* �߂�l�FTRUE:���� FALSE:���s
**********************************/
int CreateEnemy(int type, int img, int x, int y, int w, int h, int mx, int my)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == FALSE) {
			mEnemy[i].flg = TRUE;
			mEnemy[i].type = type;

			if (type == 1 || type == 2 || type == 3 || type == 4 || type == 5 || type == 6) {
				mEnemy[i].img = mImageEnemyYurei;
				mEnemy[i].hp = ENEMY_ZAKO_LIFE;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}
			else if (type == 7 || type == 8 || type == 9 || type == 10 || type == 11 || type == 12 || type == 13) {
				mEnemy[i].img = mImageEnemyMedama;
				mEnemy[i].hp = ENEMY_MEDAMA_LIFE;
				mEnemy[i].r = ENEMY_MEDAMA_HIT_R;
			}
			//else if (type == ) {
			//	mEnemy[i].img = mImageEnemyTakara[img];
			//	mEnemy[i].hp = ENEMY_ZAKO_LIFE;
			//	mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			//}
			else if (type == 14) {
				mEnemy[i].img = mImageEnemyBosu[img];
				mEnemy[i].hp = ENEMY_BOSU_LIFE;
				mEnemy[i].r = ENEMY_BOSU_HIT_R;
			}

			mEnemy[i].x = x;
			mEnemy[i].y = y;
			mEnemy[i].w = w;
			mEnemy[i].h = h;
			mEnemy[i].mx = mx;
			mEnemy[i].my = my;
			mEnemy[i].cnt = 0;
			mEnemy[i].bosu = 0;


			// ����
			return TRUE;
		}
	}

	// ���s
	return FALSE;
}

/**********************************
* �G�l�~�[�^�C�v1�`6�̃U�R�G�̈ړ��ƍU��
**********************************/
void EnemyType01(ENEMY* mEnemy)
{

	if (mEnemy->cnt == 80) {
		mEnemy->mx = -1;

	}
}

void EnemyType02(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 1;
	}
}

void EnemyType03(ENEMY* mEnemy) {
	if (mEnemy->cnt == 50) {
		mEnemy->mx = 1;
	}
	if (mEnemy->cnt == 150) {
		mEnemy->mx = 2;
	}
}


void EnemyType04(ENEMY* mEnemy) {
	if (mEnemy->cnt == 50) {
		mEnemy->mx = -1;
	}
	if (mEnemy->cnt == 150) {
		mEnemy->mx = -2;
	}
}


void EnemyType05(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 30) {
		mEnemy->mx = 1;
	}
	if (mEnemy->cnt == 160 || mEnemy->cnt == 500) {
		mEnemy->mx = -1;
	}
	if (mEnemy->cnt == 320) {
		mEnemy->mx = 1;
	}
}

void EnemyType06(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 30) {
		mEnemy->mx = -1;
	}
	if (mEnemy->cnt == 160 || mEnemy->cnt == 500) {
		mEnemy->mx = 1;
	}
	if (mEnemy->cnt == 320) {
		mEnemy->mx = -1;
	}
}

/**********************************
* �G�l�~�[�^�C�v�V�`13�̖ڋʂ̈ړ��ƍU��
**********************************/
void EnemyType07(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 1;
		mEnemy->my = 1;
	}

	if (mEnemy->cnt % 80 == 0 && mEnemy->y < 400) {
		CreateTargetShot(mEnemy);
	}
}

void EnemyType08(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = -1;
		mEnemy->my = 1;
	}

	if (mEnemy->cnt % 80 == 0 && mEnemy->y < 400) {
		CreateTargetShot(mEnemy);
	}
}

void EnemyType09(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 0;
	}
	else if (mEnemy->cnt == 900) {
		mEnemy->mx = -1;
	}

	if (mEnemy->cnt % 20 == 0 && mEnemy->cnt >= 120 && mEnemy->cnt <= 900)
	{
		CreateTargetShot(mEnemy);
	}

}
void EnemyType10(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 0;
	}
	else if (mEnemy->cnt == 900) {
		mEnemy->mx = 1;
	}

	if (mEnemy->cnt % 20 == 0 && mEnemy->cnt >= 120 && mEnemy->cnt <= 900)
	{
		CreateTargetShot(mEnemy);
	}

}

void EnemyType11(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 1;
		mEnemy->my = 1;
	}
	if (mEnemy->cnt == 160 || mEnemy->cnt == 500) {
		mEnemy->mx = -1;
	}
	if (mEnemy->cnt == 320) {
		mEnemy->mx = 1;
	}

	if (mEnemy->cnt % 80 == 0 && mEnemy->cnt < 400) {
		CreateTargetShot(mEnemy);
	}
}

void EnemyType12(ENEMY* mEnemy) {
	if (mEnemy->cnt == 30) {
		mEnemy->mx = 0;
	}

	if (mEnemy->cnt == 900) {
		mEnemy->mx = -1;
	}

	if (mEnemy->cnt % 50 == 0 && mEnemy->cnt < 900) {
		CreateTargetShot(mEnemy);
	}

}

void EnemyType13(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 30) {
		mEnemy->mx = 0;
	}

	if (mEnemy->cnt == 900) {
		mEnemy->mx = 1;
	}

	if (mEnemy->cnt % 50 == 0 && mEnemy->cnt < 900) {
		CreateTargetShot(mEnemy);
	}
}

/**********************************
* �G�l�~�[�^�C�v14�̃{�X�̈ړ��ƍU��
**********************************/
void EnemyType14(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 90) {
		mEnemy->my = 0;
		mEnemy->mx = 3;
	}
	else if (mEnemy->cnt == 2500) {
		mEnemy->my = -1;
		mEnemy->mx = 0;
	}

	if (mEnemy->x == 380)
	{
		mEnemy->mx = -3;
	}
	if (mEnemy->x == 80)
	{
		mEnemy->mx = 3;
	}

	if (mEnemy->cnt >= 120 && mEnemy->cnt <= 2400)
	{
		if (mEnemy->cnt % 30 == 0)
			CreateNWayShot(mEnemy);

		if (mEnemy->cnt % 60 == 0)
			CreateDirectionShot(mEnemy);

	}
}


int CreateEnemyShot(int img, double x, double y, double mx, double my)
{
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		if (mEnemyShot[i].flg == FALSE) {
			mEnemyShot[i].flg = TRUE;
			mEnemyShot[i].w = 16;
			mEnemyShot[i].h = 16;

			mEnemyShot[i].img = mImageEnemyShot[img];
			mEnemyShot[i].x = x;
			mEnemyShot[i].y = y;
			mEnemyShot[i].mx = mx;
			mEnemyShot[i].my = my;

			// ����
			return TRUE;
		}
	}

	// ���s
	return FALSE;
}


// *** +16lines(1-function)
/***********************************************
* �G�e �_������
* �� ���F*mEnemy
* �߂�l�F�Ȃ�
***********************************************/
void CreateTargetShot(ENEMY* mEnemy)
{
	// �G�@�Ǝ��@��X,Y�����̊p�x�����߂�
	double Angle = atan2((double)(mPlayer.y - (double)mEnemy->y), (double)(mPlayer.x - (double)mEnemy->x));

	// ���ł��������ƃX�s�[�h����AX�������ւ̈ړ����x��Y�����ւ̈ړ����x�𓾂�
	double mx = cos(Angle) * ENEMY_SHOT_SPEED;
	double my = sin(Angle) * ENEMY_SHOT_SPEED;

	CreateEnemyShot(3, mEnemy->x, mEnemy->y, mx, my);
}

void CreateDirectionShot(ENEMY* mEnemy)
{
	CreateEnemyShot(0, mEnemy->x, mEnemy->y, 0, 3);
}

void CreateNWayShot(ENEMY* mEnemy)
{
	int mx[8] = { -3,-3,-2,-1,1,2,3,3 };
	int my[8] = { 1,2,3,4,4,3,2,1 };

	for (int i = 0; i < 8; i++)
	{
		CreateEnemyShot(1, mEnemy->x, mEnemy->y, mx[i], my[i]);
	}
}

int HitCircleEnemy(PLAYER* p, ENEMY* e)
{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}

int HitCircleEnemyShot(PLAYER* p, ENEMY_SHOT* e)
{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}

void EraseEnemyShot()
{
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		mEnemyShot[i].flg = FALSE;
	}
}
