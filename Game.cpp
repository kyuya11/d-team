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
#include "ITEM.h"


/*************************
** �ϐ� **
*************************/
static int mImageHandle; //�摜�n���h���i�[�p�ϐ�
static int mImageBackground;
static int mImageHp;

static int gameScore; //�Q�[���X�R�A
static int mGameTime;
static int mgameStatus;

static int mScroll1;
static int mScroll2;


//������
void Game_Initialize() {
	mImageHandle = LoadGraph("images/Scene_Game.png"); //�摜�̃��[�h

	mImageBackground = LoadGraph("images/haikei.jpg");

	mImageHp = LoadGraph("images/select.png");

	// *** +4lines
	// �Q�[����BGM�Đ�
	PlayMusic("sounds/yukinagori.mp3", DX_PLAYTYPE_LOOP);
	
	mScroll1 = 0;
	mScroll2 = -960;

	Player_Initialize();
	Enemy_Initialize();
	Effect_Initialize();
	Item_Initialize();


	mGameTime = 0;

	mgameStatus = true;
}

//�I������
void Game_Finalize() {
	DeleteGraph(mImageHandle); //�摜�̉��

// *** +4lines
	// �Q�[����BGM��~
	StopMusic();

	Player_Finalize();
	Enemy_Finalize();
	Effect_Finalize();
	Item_Finalize();


}

//�X�V
void Game_Update() {
	//B�{�^���܂���ESC�{�^���Ń��j���[�ɖ߂�
	if (iKeyFlg == PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_ESCAPE) != 0)) {
		SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}

	if (mPlayer.hp > 0) {
		Player_Update();
		Enemy_Update();
		Effect_Update();
		Item_Update();


		mGameTime++;

		Stage1();
		//Stage2();
	}
}



//�`��
void Game_Draw() {

	BackScroll();

	if (mPlayer.hp > 0) {
		Player_Draw();
		Effect_Draw();
		Enemy_Draw();
		Item_Draw();

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
* �Q�[���I�[�o�[����
* �� ���F�Ȃ�
* �߂�l�F�Ȃ�
***********************************************/

void GameClear(void)
{
	const char* str1 = "---- X�L�[�������ă����L���O���͉�ʂ� ----";
	const char* str2 = "---- X�L�[�������ă^�C�g���֖߂� ----";
	char str3[48];

	gameScore = mPlayer.score;

	if (Ranking[0].score < gameScore) {
		if (iKeyFlg == PAD_INPUT_2) {
			SceneMgr_ChangeScene(eScene_RankInput);
		}

		strcpy(str3, str1);
	}
	else {
		if (iKeyFlg == PAD_INPUT_2) {
			SceneMgr_ChangeScene(eScene_Menu);
		}

		strcpy(str3, str2);
	}
	mgameStatus = true;

	SetFontSize(40);
	DrawString(20, 220, "�f�`�l�d�@�b�k�d�`�q", 0xffffff, 0);

	SetFontSize(20);
	DrawString(20, 440, str1, 0xffffff, 0);
}

void GameOver(void)
{
	const char* str1 = "---- X�L�[�������ă����L���O���͉�ʂ� ----";
	const char* str2 = "---- X�L�[�������ă^�C�g���֖߂� ----";
	char str3[48];

	gameScore = mPlayer.score;

	if (Ranking[0].score < gameScore) {
		if (iKeyFlg == PAD_INPUT_2) { //X�L�[��������Ă�����
			SceneMgr_ChangeScene(eScene_RankInput); //�����L���O��ʓ��͂�
		}

		strcpy(str3, str1);
	}
	else {
		if (iKeyFlg == PAD_INPUT_2) { //X�L�[��������Ă�����
			SceneMgr_ChangeScene(eScene_Menu); //�V�[�����Q�[����ʂɕύX
		}

		strcpy(str3, str2);
	}
	mgameStatus = true;

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(40);
	DrawString(35, 220, "�f�`�l�d �n�u�d�q", 0xffffff, 0);
	
	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);
	DrawString(35, 440, str3, 0xffffff, 0);
}

void BackScroll()
{
	mScroll1 = mScroll1 + 5;
	if (mScroll1 >= 960) { mScroll1 = -960; }
	mScroll2 = mScroll2 + 5;
	if (mScroll2 >= 960) { mScroll2 = -960; }

	DrawGraph(0, mScroll1, mImageBackground, TRUE);
	DrawGraph(0, mScroll2, mImageBackground, TRUE);

}

void ScoreDraw()
{
	SetFontSize(20);

	DrawFormatString(496, 45, GetColor(0, 0, 0), "%010d", Ranking[0].score);
	DrawFormatString(494, 43, GetColor(255,255,255), "%010d", Ranking[0].score);
	DrawFormatString(496, 98, GetColor(0, 0, 0), "%010d", mPlayer.score);
	DrawFormatString(494, 96, GetColor(255,255,255), "%010d", mPlayer.score);

	for (int i = 0; i < mPlayer.hp; i++) {
		DrawGraph(455 + i * 25, 255, mImageHp, TRUE);
	}
}

//�Q�[���X�R�A�擾
int Game_GetScore() {
	return gameScore;
}


int Game_GetmGameTime() {
	return mGameTime;
}

void Game_SetmgameStatus(int flg) {
	mgameStatus = flg;
}