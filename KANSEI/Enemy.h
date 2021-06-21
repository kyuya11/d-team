#pragma once
//#include "Player.h"

#define PI 3.1415926535897932384626433832795f
/*************************
** �萔 **
*************************/
// �G�@�̍ő吔
const int ENEMY_MAX = 100;
const int ENEMY_IMAGE_MAX = 2;

const int ENEMY_SHOT_MAX = 200;
const int ENEMY_SHOT_IMAGE_MAX = 4;
const int ENEMY_SHOT_SPEED = 3; 
const int ENEMY_ZAKO_HIT_R = 9; 
const int ENEMY_MEDAMA_HIT_R = 18;
const int ENEMY_BOSU_HIT_R = 27;
const int ENEMY_ZAKO_LIFE = 5; 
const int ENEMY_MEDAMA_LIFE = 10;
const int ENEMY_BOSU_LIFE = 150;



/*************************
** �\���� **
*************************/

// �G�l�~�[�̍\����
struct ENEMY {
	bool flg; // �g�p�t���O
	int type; // �^�C�v
	int img; // �摜
	int x, y, w, h; // ���Wx,y ��w ����h
	int mx, my; // �ړ���mx,my
	int cnt; // �����]���A�e�������Ɏg�p
	int hp; // �X�^�~�i�i���񓖂����ď������邩�j
	int r; // ���ar
	int bosu;
};

// �G�l�~�[�e�\����
struct ENEMY_SHOT {
	bool flg; // �g�p�t���O
	int img; // �摜
	double x, y; // ���Wx,y
	int w, h; // ��w ����h
	double mx, my; // �ړ���mx,my
	int r; // ���ar
};


extern struct ENEMY mEnemy[ENEMY_MAX];
extern int mImageEnemy[ENEMY_IMAGE_MAX];
extern int EnemyCount[ENEMY_IMAGE_MAX];

extern void Enemy_Initialize();//������
extern void Enemy_Finalize();//�I������
extern void Enemy_Update();//�X�V
extern void Enemy_Draw();//�`��

//�G�l�~�[�̐���
int CreateEnemy(int, int, int, int, int, int, int, int);

//�H��
void EnemyType01(ENEMY*);		//�G�l�~�[�^�C�v�P�̈ړ��ƍU��
void EnemyType02(ENEMY*);		//�G�l�~�[�^�C�v�Q�̈ړ��ƍU��
void EnemyType03(ENEMY*);		//�G�l�~�[�^�C�v�R�̈ړ��ƍU��
void EnemyType04(ENEMY*);		//�G�l�~�[�^�C�v�S�̈ړ��ƍU��
void EnemyType05(ENEMY*);		//�G�l�~�[�^�C�v�T�̈ړ��ƍU��
void EnemyType06(ENEMY*);		//�G�l�~�[�^�C�v6�̈ړ��ƍU��

//�ڋ�
void EnemyType07(ENEMY*);		//�G�l�~�[�^�C�v7�̈ړ��ƍU��
void EnemyType08(ENEMY*);		//�G�l�~�[�^�C�v8�̈ړ��ƍU��
void EnemyType09(ENEMY*);		//�G�l�~�[�^�C�v9�̈ړ��ƍU��
void EnemyType10(ENEMY*);		//�G�l�~�[�^�C�v�P0�̈ړ��ƍU��
void EnemyType11(ENEMY*);		//�G�l�~�[�^�C�v�P1�̈ړ��ƍU��
void EnemyType12(ENEMY*);		//�G�l�~�[�^�C�v�P2�̈ړ��ƍU��
void EnemyType13(ENEMY*);		//�G�l�~�[�^�C�v�P3�̈ړ��ƍU��

//�{�X
void EnemyType14(ENEMY*);		//�G�l�~�[�^�C�v�P4�̈ړ��ƍU��



int CreateEnemyShot(double x, double y, double mx, double my);

void CreateTargetShot(ENEMY*);
void CreateDirectionShot(ENEMY*);
void CreateNWayShot(ENEMY*);

void EraseEnemyShot();
