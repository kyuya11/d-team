// *** +2lines 
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "stage.h"
#include "Effect.h"
#include "Rank.h"


/*************************
** Game.cpp���ϐ� **
*************************/
static int mImageHandle;		//�摜�n���h���i�[�p�ϐ�
static int mImageBackground;	//�摜�n���h���i�[�p�ϐ�
static int mImageHp;			//�摜�n���h���i�[�p�ϐ�

static int gameScore;	//�Q�[���X�R�A
static int mGameTime;	//�Q�[���o�ߎ���
static int mgameStatus;	//�Q�[�����

static int mScroll1;		//�w�i�X�N���[���pY���W1
static int mScroll2;		//�w�i�X�N���[���pY���W2


/***********************************************
 * �Q�[���@������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Game_Initialize(){
    mImageHandle = LoadGraph("images/Scene_Game.png");    //�摜�̃��[�h
	mImageBackground = LoadGraph("images/stage1.png");    //�摜�̃��[�h
	// *** +1line
	mImageHp = LoadGraph("images/select.png");    //�摜�̃��[�h

	// �Q�[����BGM�Đ�
	PlayMusic("sounds/yukinagori.mp3", DX_PLAYTYPE_LOOP);

	// �w�i���W�ݒ�
	mScroll1 = 0;
	mScroll2 = -960;

	Player_Initialize();
	Enemy_Initialize();
	Effect_Initialize();

	mGameTime = 0;
	mgameStatus = true;

}


/***********************************************
 * �Q�[���@�I������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Game_Finalize(){
    DeleteGraph(mImageHandle);    //�摜�̉��
	
	// �Q�[����BGM��~
	StopMusic();

	Player_Finalize();
	Enemy_Finalize();
	Effect_Finalize();

}


// *** 1-function change
/***********************************************
 * �Q�[���@�X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Game_Update(){
	//Y�{�^���܂���ESC�{�^���Ń��j���[�ɖ߂�
	if (iKeyFlg == PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_ESCAPE) != 0)) {
		SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}

	// �Q�[���v���C���Ȃ�e�������A�b�v�f�[�g
	if (mPlayer.hp > 0) {
		Player_Update();
		Enemy_Update();
		Effect_Update();

		mGameTime++;

		Stage1();
	}
}


/***********************************************
 * �Q�[���@�`�揈��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Game_Draw(){

	BackScroll();

	if (mPlayer.hp > 0) {
		Player_Draw();
		Effect_Draw();
		Enemy_Draw();
	}
	// �Q�[����ʁi�t���[���`��j
	DrawGraph(0, 0, mImageHandle, TRUE);

	if (mgameStatus == FALSE) {
		GameClear();
	}

	if (mPlayer.hp <= 0) {
		GameOver();
	}
	else {
		ScoreDraw();
	}
}


/***********************************************
 * �Q�[���N���A����
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void GameClear(void)
{
	const char* str1 = "---- �w�L�[�������ă����L���O���͉�ʂ� ----";
	const char* str2 = "---- �w�L�[�������ă^�C�g���֖߂� ----";
	char str3[48];

	// �v���C�̃X�R�A�ݒ�
	gameScore = mPlayer.score;

	//�����L���O1�ʂƂ̔�r�@�����L���O���Ȃ烉���L���O���͉�ʂ֗U��
	if (Ranking[0].score < gameScore) {
		if (iKeyFlg == PAD_INPUT_2) { //X�L�[��������Ă�����
			SceneMgr_ChangeScene(eScene_RankInput); //�����L���O��ʓ��͂�
		}

		strcpy(str3, str1);
	}
	//�����L���O�O
	else {
		if (iKeyFlg == PAD_INPUT_2) { //X�L�[��������Ă�����
			SceneMgr_ChangeScene(eScene_Menu); //�V�[�����Q�[����ʂɕύX
		}

		strcpy(str3, str2);
	}
	mgameStatus = true;

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(40);
	DrawString(20, 220, "�f�`�l�d�@�b�k�d�`�q", 0xffffff, 0);

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);
	DrawString(20, 440, str3, 0xffffff, 0);
}


/***********************************************
 * �Q�[���I�[�o�[����
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void GameOver(void)
{
	const char* str1 = "---- �w�L�[�������ă����L���O���͉�ʂ� ----";
	const char* str2 = "---- �w�L�[�������ă^�C�g���֖߂� ----";
	char str3[48];

	// �v���C�̃X�R�A�ݒ�
	gameScore = mPlayer.score;

	if (Ranking[0].score < gameScore) {
		if (iKeyFlg == PAD_INPUT_2) { //X�L�[��������Ă�����
			SceneMgr_ChangeScene(eScene_RankInput); //�����L���O��ʓ��͂�
		}

		strcpy( str3, str1 );
	}
	else {
		if (iKeyFlg == PAD_INPUT_2) { //X�L�[��������Ă�����
			SceneMgr_ChangeScene(eScene_Menu); //�V�[�����Q�[����ʂɕύX
		}

		strcpy( str3, str2 );
	}
	mgameStatus = true;

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(40);
	DrawString(35, 220, "�f�`�l�d�@�n�u�d�q", 0xffffff, 0);

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);
	DrawString(35, 440, str3, 0xffffff, 0);
}


/**********************************
 * �w�i�X�N���[����
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 **********************************/
void BackScroll()
{
	//�w�i�\��
	mScroll1 = mScroll1 + 5;
	if (mScroll1 >= 960) { mScroll1 = -960; }
	mScroll2 = mScroll2 + 5;
	if (mScroll2 >= 960) { mScroll2 = -960; }

	DrawGraph(0, mScroll1, mImageBackground, TRUE);
	DrawGraph(0, mScroll2, mImageBackground, TRUE);
}


/**********************************
 * �X�R�A�̕\��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 **********************************/
void ScoreDraw()
{
	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);

	// �X�R�A�\��
	DrawFormatString(496, 45, GetColor(0, 0, 0), "%010d", Ranking[0].score);
	DrawFormatString(494, 43, GetColor(255, 255, 255), "%010d", Ranking[0].score);
	DrawFormatString(496, 98, GetColor(0, 0, 0), "%010d", mPlayer.score);
	DrawFormatString(494, 96, GetColor(255, 255, 255), "%010d", mPlayer.score);

	//�c�@�\��
	for (int i = 0; i < mPlayer.hp; i++) {
		DrawGraph(455 + i * 25, 255, mImageHp, TRUE);
	}
}


/***********************************************
 * �Q�[���X�R�A�擾
 * ���@���F�Ȃ�
 * �߂�l�FgaemScore
 ***********************************************/
int Game_GetScore() {
	return gameScore;
}


/***********************************************
 * �Q�[�����Ԏ擾
 * ���@���F�Ȃ�
 * �߂�l�FmGameTime
 ***********************************************/
int Game_GetmGameTime() {
	return mGameTime;
}


/***********************************************
 * �Q�[���󋵃Z�b�g
 * ���@���Fflg
 * �߂�l�FmGameTime
 ***********************************************/
void Game_SetmgameStatus( int flg ) {
	mgameStatus = flg;
}
