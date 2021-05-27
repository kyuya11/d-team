#include "End.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Input.h"
#include "Game.h"

static int mImageHandle; //�摜�n���h���i�[�p�ϐ�
static int StopTime;

//������
void End_Initialize() {
	mImageHandle = LoadGraph("images/End.png");//�摜�̃��[�h
	StopTime = 0;
}

//�I������
void End_Finalize() {
	DeleteGraph(mImageHandle);//�摜�̉��
}

//�X�V

//�`��
void End_Draw() {

	DrawGraph(0, 0, mImageHandle, FALSE);

	SetFontSize(24);
	DrawString(360, 480 - 24, "Thank you for Playing", 0xffffff, 0);
	
	//�^�C���̉��Z�������I�� (�Q�b��)
	if (++StopTime > 120) {
		SceneMgr_ChangeScene(eScene_Stop); //�V�[�����Q�[����ʂɕύX
	}
}

