#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"
#include "Effect.h"
#include <math.h>


/*************************
** �v���g�^�C�v�錾 **
*************************/
int HitCircleEnemy(PLAYER*, ENEMY*);	//�����蔻��i�~�j
int HitCircleEnemyShot(PLAYER*, ENEMY_SHOT*);	//�����蔻��i�~�j


/*************************
** �ϐ� **
*************************/
// �G�l�~�[
struct ENEMY mEnemy[ENEMY_MAX];
int mImageEnemyZako[ENEMY_IMAGE_MAX];
int mImageEnemyMiko[ENEMY_IMAGE_MAX];

// �G�l�~�[�e
struct ENEMY_SHOT mEnemyShot[ENEMY_SHOT_MAX];
int mImageEnemyShot[ENEMY_SHOT_IMAGE_MAX];


/***********************************************
 * �G ������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Enemy_Initialize(){
	LoadDivGraph("images/yurei1.png", 1, 1, 1, 23, 26, mImageEnemyZako);	//�G�l�~�[�摜�i�G���F�U�R�j
	LoadDivGraph("images/medama2.png", 1, 1, 1, 44, 41, mImageEnemyMiko);	//�G�l�~�[�摜�i�ޏ��F�~�R�j
	LoadDivGraph("images/EnemyDan.png", 4, 4, 1, 16, 16, mImageEnemyShot);	//�G�l�~�[�e�摜
	//LoadDivGraph("images/bosu.png", 16, 4, 4, 96, 64, mImageEnemydoku); //�G�l�~�[�e�摜
	// �G�l�~�[�̏����ݒ�
	for (int i = 0; i < ENEMY_MAX; i++) {
		mEnemy[i].flg = FALSE;
	}

	// �G�l�~�[�e�̏����ݒ�
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		mEnemyShot[i].flg = FALSE;
	}
}


/***********************************************
 * �G �I���X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Enemy_Finalize(){
	for (int i = 0; i < ENEMY_IMAGE_MAX; i++) {
		DeleteGraph(mImageEnemyZako[i]);    //�摜�̉��
		DeleteGraph(mImageEnemyMiko[i]);    //�摜�̉��
	}
	for (int i = 0; i < ENEMY_SHOT_IMAGE_MAX; i++) {
		DeleteGraph(mImageEnemyShot[i]);    //�摜�̉��
	}
}


/***********************************************
 * �G �����X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Enemy_Update(){
	//�G�l�~�[����
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == TRUE) {

			// �G�l�~�[�ړ�
			mEnemy[i].x += mEnemy[i].mx;
			mEnemy[i].y += mEnemy[i].my;

			mEnemy[i].cnt++;
			
			// �p�^�[���ʁ@�G�̓���
			switch (mEnemy[i].type) {
				case 1: EnemyType01(&mEnemy[i]); break;
				case 2: EnemyType02(&mEnemy[i]); break;
				case 3: EnemyType03(&mEnemy[i]); break;
				case 4: EnemyType04(&mEnemy[i]); break;
				case 5: EnemyType05(&mEnemy[i]); break;
			}

			// ��ʂ��͂ݏo���������
			if (mEnemy[i].y > SCREEN_HEIGHT + mEnemy[i].h)
				mEnemy[i].flg = FALSE;

			// �����蔻��
			if (HitCircleEnemy(&mPlayer, &mEnemy[i]) == TRUE) {
				if (mPlayer.baria == 0) {
					mPlayer.flg = FALSE;
					mPlayer.count = 0;
					mPlayer.hp -= 1;
					mEnemy[i].flg = FALSE;
				}
				else if (mPlayer.baria == 1) {
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
			if (mEnemyShot[i].y > SCREEN_HEIGHT + mEnemyShot[i].h)
				mEnemyShot[i].flg = FALSE;

			// �����蔻��
			if (mPlayer.flg == false)
				continue;
			if (HitCircleEnemyShot(&mPlayer, &mEnemyShot[i]) == TRUE) {
				if (mPlayer.baria == 0) {
					mPlayer.flg = FALSE;
					mPlayer.count = 0;
					mPlayer.hp -= 1;
				}
				else if (mPlayer.baria == 1) {
					mPlayer.count = 0;
					mPlayer.baria = 0;
					mEnemy[i].flg = FALSE;
				}
				EraseEnemyShot();
				CreateEffect(mPlayer.x, mPlayer.y);
			}
		}
	}
}


/***********************************************
 * �G �`�揈��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Enemy_Draw(){
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
 * ���@���Ftype:�^�C�v�P�|�S�̓U�R�A�T�|�V�͛ޏ�
 * �@�@�@�@img�F�P�̓U�R�A�Q�̓U�R�ԁA1�͛ޏ��B�Q�͛ޏ���
 * 
 * �߂�l�FTRUE:���� FALSE:���s�@�i�߂�l�͎g�p���Ă��Ȃ��j
 **********************************/
int CreateEnemy(int type, int img, int x, int y, int w, int h, int point, int mx, int my)
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == FALSE) {
			mEnemy[i].flg = TRUE;
			mEnemy[i].type = type;
			if (type <= 4) {
				mEnemy[i].img = mImageEnemyZako[img];
				mEnemy[i].hp = ENEMY_ZAKO_LIFE;
				mEnemy[i].r = ENEMY_ZAKO_HIT_R;
			}
			else {
				mEnemy[i].img = mImageEnemyMiko[img];
				mEnemy[i].hp = ENEMY_MIKO_RED_LIFE;
				mEnemy[i].r = ENEMY_MIKO_HIT_R;
			}

			mEnemy[i].x = x;
			mEnemy[i].y = y;
			mEnemy[i].w = w;
			mEnemy[i].h = h;
			mEnemy[i].point = point;
			mEnemy[i].mx = mx;
			mEnemy[i].my = my;
			mEnemy[i].cnt = 0;

			// ����
			return TRUE;
		}
	}

	// ���s
	return FALSE;
}


/***********************************************
 * �G �^�C�v�P�̈ړ��ƍU��
 * ���@���F*mEnemy
 * �߂�l�F�Ȃ�
 ***********************************************/
void EnemyType01(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = -1;
	}
}


/***********************************************
 * �G �^�C�v�Q�̈ړ��ƍU��
 * ���@���F*mEnemy
 * �߂�l�F�Ȃ�
 ***********************************************/
void EnemyType02(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 1;
	}
}


/***********************************************
 * �G �^�C�v�R�̈ړ��ƍU��
 * ���@���F*mEnemy
 * �߂�l�F�Ȃ�
 ***********************************************/
void EnemyType03(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = 1;
	}
	//�_�������e
	if (mEnemy->cnt % 80 == 0 && mEnemy->y < 400) {
		CreateTargetShot(mEnemy);
	}
}


/***********************************************
 * �G �^�C�v�S�̈ړ��ƍU��
 * ���@���F*mEnemy
 * �߂�l�F�Ȃ�
 ***********************************************/
void EnemyType04(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 80) {
		mEnemy->mx = -1;
	}
	//�_�������e
	if (mEnemy->cnt % 80 == 0 && mEnemy->y < 400) {
		CreateTargetShot(mEnemy);
	}
}


/***********************************************
 * �G �^�C�v�T�̈ړ��ƍU��
 * ���@���F*mEnemy
 * �߂�l�F�Ȃ�
 ***********************************************/
void EnemyType05(ENEMY* mEnemy)
{
	if (mEnemy->cnt == 90) {
		mEnemy->my = 0;
	}
	else if (mEnemy->cnt == 690) {
		mEnemy->my = 1;
	}

	//�U������
	if (mEnemy->cnt >= 120 && mEnemy->cnt <= 600)
	{
		//�m�|�v�����e�i30�t���[���Ԋu�j
		if (mEnemy->cnt % 30 == 0)
			CreateNWayShot(mEnemy);

		//�����e�i60�t���[���Ԋu�j
		if (mEnemy->cnt % 60 == 0)
			CreateDirectionShot(mEnemy);
	}
}


/**********************************
 * �G�l�~�[�e�̐���
 * ���@���Ftype:�^�C�v�P�|�S�̓U�R�A�T�|�V�͛ޏ�
 * �@�@�@�@img�F�P�̓U�R�A�Q�̓U�R�ԁA1�͛ޏ��B�Q�͛ޏ���
 *
 * �߂�l�FTRUE:���� FALSE:���s
 **********************************/
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


/***********************************************
 * �G�e�@�_������
 * ���@���F*mEnemy
 * �߂�l�F�Ȃ�
 ***********************************************/
void CreateTargetShot(ENEMY* mEnemy)
{
	// �G�@�Ǝ��@��X,Y�����̊p�x�����߂�
	double Angle = atan2((double)(mPlayer.y - (int)mEnemy->y), (double)(mPlayer.x - (int)mEnemy->x));

	// ���ł��������ƃX�s�[�h����AX�������ւ̈ړ����x��Y�����ւ̈ړ����x�𓾂�
	double mx = cos(Angle) * ENEMY_SHOT_SPEED;
	double my = sin(Angle) * ENEMY_SHOT_SPEED;

	CreateEnemyShot(3, mEnemy->x, mEnemy->y, mx, my);
}


/***********************************************
 * �G�e�@�����e
 * ���@���F*mEnemy
 * �߂�l�F�Ȃ�
 ***********************************************/
void CreateDirectionShot(ENEMY* mEnemy)
{
	CreateEnemyShot(0, mEnemy->x, mEnemy->y, 0, 3);
}


/***********************************************
 * �G�e�@N-WAY�e
 * ���@���F*mEnemy
 * �߂�l�F�Ȃ�
 ***********************************************/
void CreateNWayShot(ENEMY* mEnemy)
{
	int mx[8] = { -3, -3, -2, -1, 1, 2, 3, 3 };	// �ړ���(x)
	int my[8] = { 1,  2,  3,  4, 4, 3, 2, 1 };	// �ړ���(y)

	for (int i = 0; i < 8; i++)
	{
		CreateEnemyShot(1, mEnemy->x, mEnemy->y, mx[i], my[i]);
	}
}


/**********************************
 * �����蔻��i�~�j
 * ���@���FPLAYER�|�C���^, ENEMY�|�C���^
 * �߂�l�FTRUE:������, FALSE:�Ȃ�
 **********************************/
int HitCircleEnemy(PLAYER* p, ENEMY* e)
{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}


/**********************************
 * �����蔻��i�~�j
 * ���@���FPLAYER�|�C���^, ENEMY_SHOT�|�C���^
 * �߂�l�FTRUE:������, FALSE:�Ȃ�
 **********************************/
int HitCircleEnemyShot(PLAYER* p, ENEMY_SHOT* e)
{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}


/**********************************
 * �G�l�~�[�e�̍폜
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 **********************************/
void EraseEnemyShot()
{
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		//mEnemyShot[i].flg = FALSE;
	}
}
