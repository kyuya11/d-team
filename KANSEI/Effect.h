#pragma once

/*************************
** �萔 **
*************************/
// �����A�j���[�V�����̍ő吔
const int EFFECT_MAX = 20;
const int EFFECT_IMAGE_MAX = 16;


const int EFFECT_RATE = 4; // 1�R�}�ӂ�̃G�t�F�N�g�\������
/*************************
** �\���� **
*************************/

// �����A�j���[�V�����\����
struct EFFECT {
	bool flg; // �g�p�t���O
	int img; // �摜
	int x, y; // ���Wx,y
	int time; // �o�ߎ���
};


extern void Effect_Initialize();//������
extern void Effect_Finalize();//�I������
extern void Effect_Update();//�X�V
extern void Effect_Draw();//�`��

//�����A�j���[�V�����̐���
extern int CreateEffect(int x, int y);

