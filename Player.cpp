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
int HitCirclePlayerShot(ENEMY*, PLAYER_SHOT*);	//�G�l�~�[�����蔻��i�~�j

/*************************
** �ϐ� **
*************************/
// ���@
struct PLAYER mPlayer;
struct PLAYER_SHOT mPlayerShot[PLAYER_SHOT_MAX];

static int mImagePlayer;    //�摜�n���h���i�[�p�ϐ�
static int mImageHitPoint[2];  //�摜�n���h���i�[�p�ϐ�
static int mImageHodai[3];  //�摜�n���h���i�[�p�ϐ�
static int mImageDan[3];    //�摜�n���h���i�[�p�ϐ�

static int mSoundsShot;    //���t�@�C���i�[�p�ϐ�


int MPlayerHodaiPosion[2][7][3] = {
	{
		{-24, -12, 1},
		{-16, -24, 1},
		{ -8, -36, 0},
		{  0, -48, 2},
		{  8, -36, 0},
		{ 16, -24, 1},
		{ 24, -12, 1}
	},
	{
		//{-48, -12, 1},
		//{-32, -24, 1},
		//{-16, -36, 0},
		//{  0, -48, 2},
		//{ 16, -36, 0},
		//{ 32, -24, 1},
		//{ 48, -12, 1}
		{0, -48, 0}
	}
};

int MPlayerShotMove[2][7][2] = {
	{
		{ 0, -14},
		{ 0, -14},
		{ 0, -14},
		{ 0, -14},
		{ 0, -14},
		{ 0, -14},
		{ 0, -14} 

	},
	{
		{-3, -11},
		{-2, -12},
		{-1, -13},
		{ 0, -14},
		{ 1, -13},
		{ 2, -12},
		{ 3, -11}
	}
};


/***********************************************
 * �v���C���[�@������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Player_Initialize(){
	SetTransColor(0, 0, 0);
	mImagePlayer = LoadGraph("images/player3.png");    //�v���C���[�摜
	LoadDivGraph("images/playerhantei.png", 2, 2, 1, 60, 60, mImageHitPoint);	//�v���C���[�����蔻��
	LoadDivGraph("images/playerHodai1.png", 3, 3, 1, 12, 16, mImageHodai);	//�v���C���[�C��摜
	LoadDivGraph("images/playerDan1.png", 3, 3, 1, 12, 24, mImageDan);	//�v���C���[�e�摜

	mSoundsShot = LoadSoundMem("sounds/shoot.wav");    //�e���ˉ��̃��[�h

	// �v���C���[�̏����ݒ�
	mPlayer.flg = true;
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.w = PLAYER_WIDTH;
	mPlayer.h = PLAYER_HEIGHT;
	mPlayer.angle = 0.0;
	mPlayer.count = 0;
	mPlayer.hp = PLAYER_HP;
	mPlayer.score = 0;
	// *** +1line
	mPlayer.r = PLAYER_HIT_R;

	// �v���C���[�e�̏����ݒ�
	for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
		mPlayerShot[x].flg = FALSE;
	}
}


/***********************************************
 * �v���C���[�@�I������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Player_Finalize(){
    DeleteGraph(mImagePlayer);    //�摜�̉��
}


/***********************************************
 * �v���C���[�@�X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Player_Update(){

	// �㉺���E�ړ�
	if (iNowKey & PAD_INPUT_UP)		mPlayer.y -= PLAYER_SPEED;
	if (iNowKey & PAD_INPUT_DOWN)	mPlayer.y += PLAYER_SPEED;
	if (iNowKey & PAD_INPUT_LEFT)	mPlayer.x -= PLAYER_SPEED;
	if (iNowKey & PAD_INPUT_RIGHT)	mPlayer.x += PLAYER_SPEED;

	// ��ʂ��͂ݏo���Ȃ��悤�ɂ���
	if (mPlayer.x < SCREEN_WIDTH_L + mPlayer.w/2) mPlayer.x = SCREEN_WIDTH_L + mPlayer.w/2;
	if (mPlayer.x > SCREEN_WIDTH_R - mPlayer.w/2) mPlayer.x = SCREEN_WIDTH_R - mPlayer.w/2;
	if (mPlayer.y < 32)					mPlayer.y = 32;
	if (mPlayer.y > SCREEN_HEIGHT - 32)	mPlayer.y = SCREEN_HEIGHT - 32;

	// *** +2lines
	// �v���C���[�̏�Ԃ�TRUE�̎�
	if (mPlayer.flg) {
		//Z�L�[��������Ă�����v���C���[�e����
		mPlayer.shotCount++;
		if (mPlayer.shotCount > PLAYER_SHOT_INTERVAL) {
			if (iNowKey & PAD_INPUT_1) {
				mPlayer.shotCount = 0;

				if (MakePlayerShot()) {
					PlaySoundMem(mSoundsShot, DX_PLAYTYPE_BACK);

				}
			}
		}
	// *** +1line
	}

	//�v���C���[�e�ړ��G
	MovePlayerShot();

	//�o�ߎ��ԁ@�i�w�i�X�N���[�����G�l�~�[�������Ɏg�p����j
	mPlayer.time++;

}


/***********************************************
 * �v���C���[�@�`�揈��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Player_Draw() {

	// �v���C���[�̕\��
	if (mPlayer.flg) {
		DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer, TRUE, FALSE);
		// *** +2lines
		// �v���C���[�����蔻��|�C���g
		DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImageHitPoint[1], TRUE, FALSE);

		// �X�g���[�g�e�i�����V���b�g�j
		if (iNowKey & PAD_INPUT_B) {
			for (int i = 0; i < 7; i++) {
				DrawRotaGraph(mPlayer.x + MPlayerHodaiPosion[0][i][0], 
					          mPlayer.y + MPlayerHodaiPosion[0][i][1],
					          1.0f, 0, mImageHodai[MPlayerHodaiPosion[0][i][2]], TRUE, FALSE);
			}
			DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImageHitPoint[1], TRUE, FALSE);
			} 
		else  {//  ���|�������e
				for (int i = 0; i < 7; i++) {
					DrawRotaGraph(mPlayer.x + MPlayerHodaiPosion[1][i][0],
						mPlayer.y + MPlayerHodaiPosion[1][i][1],
						1.0f, 0, mImageHodai[MPlayerHodaiPosion[1][i][2]], TRUE, FALSE);
				}
			}
		}
		else {
			// �v���C���[�����܂ł̎���3�b�i180�t���[���j
			if (++mPlayer.count >= 80)	mPlayer.flg = true;
			if (mPlayer.count / 5 % 2 == 0) {
				DrawRotaGraph(mPlayer.x, mPlayer.y, 1.0f, 0, mImagePlayer, TRUE, FALSE);
			}
		}

		DrawPlayerShot();

	}


	/***********************************************
	 * �v���C���[�e����
	 * ���@���F�Ȃ�
	 * �߂�l�F�Ȃ�
	 ***********************************************/
int MakePlayerShot() {

	bool flg = FALSE;

	// �X�g���[�g�e�i�����V���b�g�j
	if (iNowKey & PAD_INPUT_B) {
		for (int i = 0; i < 7; i++) {
			// �v���C���[�e�̐���
			for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
				if (mPlayerShot[x].flg == FALSE) {
					flg = TRUE;

					mPlayerShot[x].flg = TRUE;
					mPlayerShot[x].w = 12;
					mPlayerShot[x].h = 14;
					mPlayerShot[x].x = mPlayer.x + MPlayerHodaiPosion[0][i][0];
					mPlayerShot[x].y = mPlayer.y + MPlayerHodaiPosion[0][i][1];
					mPlayerShot[x].image = mImageDan[MPlayerHodaiPosion[0][i][2]];
					mPlayerShot[x].mx = MPlayerShotMove[0][i][0];
					mPlayerShot[x].my = MPlayerShotMove[0][i][1];
					break;
				}
			}
		}
	}
	else{//  ���|�������e
		for (int i = 0; i < 7; i++) {
			// �v���C���[�e�̐���
			for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
				if (mPlayerShot[x].flg == FALSE) {
					flg = TRUE;

					mPlayerShot[x].flg = TRUE;
					mPlayerShot[x].w = 12;
					mPlayerShot[x].h = 14;
					mPlayerShot[x].x = mPlayer.x + MPlayerHodaiPosion[1][i][0];
					mPlayerShot[x].y = mPlayer.y + MPlayerHodaiPosion[1][i][1];
					mPlayerShot[x].image = mImageDan[MPlayerHodaiPosion[1][i][2]];
					mPlayerShot[x].mx = MPlayerShotMove[1][i][0];
					mPlayerShot[x].my = MPlayerShotMove[1][i][1];
					break;
				}
			}
		}
	}

	return flg;
}


/***********************************************
 * �v���C���[�e�ړ�
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void MovePlayerShot() {
	// �v���C���[�e�̏����ݒ�
	for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
		if (mPlayerShot[x].flg == TRUE) {
			mPlayerShot[x].x += mPlayerShot[x].mx;
			mPlayerShot[x].y += mPlayerShot[x].my;

			if (mPlayerShot[x].y < -14) {
				mPlayerShot[x].flg = FALSE;
			}

			// �����蔻��
			for (int y = 0; y < ENEMY_MAX; y++) {
				if (mEnemy[y].flg == false) continue;
				if (HitCirclePlayerShot(&mEnemy[y], &mPlayerShot[x]) == TRUE) {
					if (--mEnemy[y].hp < 0) {
						mEnemy[y].flg = FALSE;
						mPlayer.score += mEnemy[y].point;
						CreateEffect(mEnemy[y].x, mEnemy[y].y);

					}
					mPlayerShot[x].flg = FALSE;
					break;
				}
			}
		}
	}
}


/***********************************************
 * �v���C���[�e�`��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void DrawPlayerShot() {
	// �v���C���[�e�̏����ݒ�
	for (int x = 0; x < PLAYER_SHOT_MAX; x++) {
		if (mPlayerShot[x].flg == TRUE) {
			DrawRotaGraph(mPlayerShot[x].x, mPlayerShot[x].y, 1.0f, 0, mPlayerShot[x].image, TRUE, FALSE);
		}
	}

}


/**********************************
 * �v���C���[�e�����蔻��i�~�j
 * ���@���FPLAYER�|�C���^, ENEMY_SHOT�|�C���^
 * �߂�l�FTRUE:������, FALSE:�Ȃ�
 **********************************/
int HitCirclePlayerShot(ENEMY* e, PLAYER_SHOT* p)

{
	double x = (double)p->x - (double)e->x;
	double y = (double)p->y - (double)e->y;

	int r = (int)sqrt(x * x + y * y);

	if (r <= p->r + e->r) return TRUE;

	return FALSE;

}
