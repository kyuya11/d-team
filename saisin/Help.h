#pragma once

// �\���̐錾
struct HelpData
{ // �����L���O�f�[�^
	int no;
	char name[11];
	long score;
};

//define��`

// �֐��v���g�^�C�v�錾
void Help_Initialize();//������
void Help_Finalize();//�I������
void Help_Update();//�X�V
void Help_Draw();//�`��

