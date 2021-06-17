#include "Help.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Input.h"
#include "Game.h"

static int mImageHandle; //�摜�n���h���i�[�p�ϐ�
static int WaitTime; //�����L���O�\������


/***********************************************
 * �����L���O��� ������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Help_Initialize() {
	mImageHandle = LoadGraph("images/Help.png");//�摜�̃��[�h
	WaitTime = 0;
}


/***********************************************
 * �����L���O��� �I������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Help_Finalize() {
	DeleteGraph(mImageHandle);//�摜�̉��
}


/***********************************************
 * �����L���O��� �X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Help_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //B�{�^����������Ă�����
			SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}


/***********************************************
 * �����L���O�f�[�^�`��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Help_Draw() {
	//�w���v�摜�\��
	DrawGraph(0, 0, mImageHandle, FALSE);


	// �����̕\��(�_��)
	if (++WaitTime < 50) {
		SetFontSize(16);
		DrawString(200, 460, "Esc�L�[�܂���B�{�^���������ƃ��j���[��ʂɖ߂�܂��B",
			GetColor(255, 255, 255));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}