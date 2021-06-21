#include "DxLib.h"
#include "Effect.h"


/*************************
** �ϐ� **
*************************/
// �����A�j���[�V�����i�G�t�F�N�g�j
struct EFFECT mEffect[EFFECT_MAX];
int mImageEffect[EFFECT_IMAGE_MAX];


/***********************************************
* �G�t�F�N�g ������
* �� ���F�Ȃ�
* �߂�l�F�Ȃ�
***********************************************/
void Effect_Initialize() {
	LoadDivGraph("images/Effect.png", 16, 8, 2, 96, 96, mImageEffect); //�����A�j���[�V�����i�G�t�F�N�g�j�摜

		// �����A�j���[�V�����̏����ݒ�
		for (int i = 0; i < EFFECT_MAX; i++) {
			mEffect[i].flg = FALSE;
		}

}


/***********************************************
* �G�t�F�N�g �I������
* �� ���F�Ȃ�
* �߂�l�F�Ȃ�
***********************************************/
void Effect_Finalize() {
	for (int i = 0; i < EFFECT_IMAGE_MAX; i++) {
		DeleteGraph(mImageEffect[i]); //�摜�̉��
	}
}


/***********************************************
* �G�t�F�N�g �X�V
* �� ���F�Ȃ�
* �߂�l�F�Ȃ�
***********************************************/
void Effect_Update() {
	//�����A�j���[�V�����̏���
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (mEffect[i].flg == TRUE) {

			// ���Ԗڂ̉摜��\�����邩�v�Z����
			mEffect[i].img = mEffect[i].time / EFFECT_RATE;
			
			// �Ō�̉摜��\���������̔��f
			if (++mEffect[i].time > EFFECT_RATE * EFFECT_IMAGE_MAX) {
				mEffect[i].flg = false;
			}
		}
	}
}


/***********************************************
* �G�t�F�N�g �`�揈��
* �� ���F�Ȃ�
* �߂�l�F�Ȃ�
***********************************************/
void Effect_Draw() {
	//�����A�j���[�V�����̏���
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (mEffect[i].flg == TRUE) {

			DrawRotaGraph(mEffect[i].x, mEffect[i].y, 1.0f, 0, mImageEffect
				[mEffect[i].img], TRUE, FALSE);
		}
	}
}


/**********************************
* �����A�j���[�V�����̐���
* �� ���Fx:x���W�Ay:y���W
* �߂�l�FTRUE:���� FALSE:���s
**********************************/
int CreateEffect(int x, int y)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (mEffect[i].flg == FALSE) {
			mEffect[i].flg = TRUE;
			mEffect[i].img = 0;
			mEffect[i].x = x;
			mEffect[i].y = y;
			mEffect[i].time = 0;

			// ����
			return TRUE;
		}
	}

	// ���s
	return FALSE;
}
