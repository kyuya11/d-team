#pragma once

// �\���̐錾
struct RankingData
{ // �����L���O�f�[�^
	int no;
	char name[11];
	long score;
};

//define��`
#define RANKCOUNT 7
#define RANKING_FILE "rankingdata.txt"

// �֐��v���g�^�C�v�錾
void Rank_Initialize();//������
void Rank_Finalize();//�I������
void Rank_Update();//�X�V
void Rank_Draw();//�`��
void Rank_Input(); //�����L���O����
void Rank_Sort(); //�����L���O���בւ�
void Rank_Save(); //�����L���O�f�[�^�̕ۑ�
void Rank_Read(); //�����L���O�f�[�^�ǂݍ���

extern struct RankingData Ranking[RANKCOUNT];
