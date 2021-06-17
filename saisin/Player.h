#pragma once

#define PI 3.1415926535897932384626433832795f
/*************************
** �萔 **
*************************/

// ��ʗ̈�̑傫��
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH_R = 440;
const int SCREEN_WIDTH_L = 10;

const int PLAYER_POS_X = (SCREEN_WIDTH - 200) / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 38;
const int PLAYER_HEIGHT = 48;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 5;
const int PLAYER_SHOT_INTERVAL = 10;

const int PLAYER_HIT_R = 3;

const int PLAYER_SHOT_MAX = 100;

/*************************
** �\���� **
*************************/
// �v���C���[
struct PLAYER {
	bool flg; // �g�p�t���O
	int x, y; // ���Wx,y
	int w, h; // ��w ����h
	double angle; // �@�̂̌���
	int count; // �����Ԋu
	int shotCount; // �e�Ԋu
	int hp; // �̗�
	int time; // �o�ߎ���
	int score; // �X�R�A
	int r;
	int up;
	int baria;

};

// �v���C���[�e
struct PLAYER_SHOT {
	bool flg; // �g�p�t���O
	int x, y; // ���Wx,y
	int w, h; // ��w ����h
	int mx, my; // �ړ���mx,my
	int image; // �摜
	int r;
};

extern struct PLAYER mPlayer;
extern struct PLAYER_SHOT mPlayerShot[PLAYER_SHOT_MAX];

extern void Player_Initialize();//������
extern void Player_Finalize();//�I������
extern void Player_Update();//�X�V
extern void Player_Draw();//�`��

int MakePlayerShot();//�v���C���[�e����
void MovePlayerShot();//�v���C���[�e�ړ�
void DrawPlayerShot();//�v���C���[�e�`��