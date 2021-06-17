#pragma once

#define PI 3.1415926535897932384626433832795f
/*************************
** �萔 **
*************************/
// �G�@�̍ő吔
const int ENEMY_MAX = 40;
const int ENEMY_IMAGE_MAX = 2;

const int ENEMY_SHOT_MAX = 200;
const int ENEMY_SHOT_IMAGE_MAX = 4;
const int ENEMY_SHOT_SPEED = 3;	// �ړ����x
const int ENEMY_ZAKO_HIT_R = 9;	// �Փ˔���̔��a
const int ENEMY_MIKO_HIT_R = 18;// �Փ˔���̔��a
const int ENEMY_ZAKO_LIFE = 5;	// ���C�t
const int ENEMY_MIKO_RED_LIFE = 60;	// ���C�t

/*************************
** �\���� **
*************************/

// �G�l�~�[�̍\����
struct ENEMY {
	bool flg;			// �g�p�t���O
	int type;			// �^�C�v
	int img;			// �摜
	int x, y, w, h;		// ���Wx,y ��w ����h
	int point;			// �X�R�A���Z
	int mx, my;			// �ړ���mx,my
	int cnt;			// �����]���A�e�������Ɏg�p
	int hp;				// �X�^�~�i�i���񓖂����ď������邩�j
	int r;				// ���ar

};

// �G�l�~�[�e�\����
struct ENEMY_SHOT {
	bool flg;			// �g�p�t���O
	int img;			// �摜
	double x, y;		// ���Wx,y
	int	w, h;			// ��w ����h
	double mx, my;		// �ړ���mx,my
	int r;				// ���ar

};

//extern struct PLAYER;

extern struct ENEMY mEnemy[ENEMY_MAX];
extern int mImageEnemy[ENEMY_IMAGE_MAX];
extern int EnemyCount[ENEMY_IMAGE_MAX];

extern void Enemy_Initialize();//������
extern void Enemy_Finalize();//�I������
extern void Enemy_Update();//�X�V
extern void Enemy_Draw();//�`��

//�G�l�~�[�̐���
int CreateEnemy(int type, int img, int x, int y, int w, int h, int point, int mx, int my);

void EnemyType01(ENEMY*);		//�G�l�~�[�^�C�v�P�̈ړ��ƍU��
void EnemyType02(ENEMY*);		//�G�l�~�[�^�C�v�Q�̈ړ��ƍU��
void EnemyType03(ENEMY*);		//�G�l�~�[�^�C�v�R�̈ړ��ƍU��
void EnemyType04(ENEMY*);		//�G�l�~�[�^�C�v�S�̈ړ��ƍU��
void EnemyType05(ENEMY*);		//�G�l�~�[�^�C�v�T�̈ړ��ƍU��

void EnemyType07(ENEMY*);
void EnemyType08(ENEMY*);

void EnemyType09(ENEMY*);
void EnemyType10(ENEMY*);

//�G�l�~�[�e�̐���
int CreateEnemyShot(int, double, double, double, double);

void CreateTargetShot(ENEMY*);			//�_�������e
void CreateDirectionShot(ENEMY*);		//�����e
void CreateNWayShot(ENEMY*);			//N-WAY�e

void EraseEnemyShot();		// �G�l�~�[�e�̍폜
