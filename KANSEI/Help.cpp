#include "Help.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Input.h"
#include "Game.h"


static int mImageHandle; 
static int WaitTime; 

void Help_Initialize() {
	mImageHandle = LoadGraph("images/Help.png");
	WaitTime = 0;
}

void Help_Finalize() {
	DeleteGraph(mImageHandle);
}

void Help_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) { 
			SceneMgr_ChangeScene(eScene_Menu);
	}
}

void Help_Draw() {
	
	DrawGraph(0, 0, mImageHandle, FALSE);

	SetFontSize(30);
	
	DrawString(100, 150, "�E���L�[�ňړ��B��������", GetColor(255, 255, 255));
	DrawString(100, 200, "�E�A�C�e������(�|�[�V����)", GetColor(255, 255, 255));
	DrawString(100, 300, "�E�{�X��|������Q�[���N���A�I", GetColor(255, 255, 255));


	SetFontSize(20);
	DrawString(100, 250, "��HP1��  �ԁ��e������  �����o���A�t�^", GetColor(255, 255, 255));


	if (++WaitTime < 50) {
		SetFontSize(16);
		DrawString(200, 460, "Esc�L�[�܂���B�{�^���������ƃ��j���[��ʂɖ߂�܂��B",
			GetColor(255, 255, 255));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}

