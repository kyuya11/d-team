#include "Rank.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Input.h"
#include "Game.h"

static int mImageHandle; //�摜�n���h���i�[�p�ϐ�
static int WaitTime; //�����L���O�\������
struct RankingData Ranking[RANKCOUNT]; // �����L���O�f�[�^�ϐ��錾


/***********************************************
 * �����L���O��� ������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Rank_Initialize() {
	mImageHandle = LoadGraph("images/Scene_Rank.png");//�摜�̃��[�h
	WaitTime = 0;
	Rank_Read();
}


/***********************************************
 * �����L���O��� �I������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Rank_Finalize() {
	DeleteGraph(mImageHandle);//�摜�̉��
}


/***********************************************
 * �����L���O��� �X�V
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Rank_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //B�{�^����������Ă�����
			SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}


/***********************************************
 * �����L���O�f�[�^�`��
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Rank_Draw() {
	//�����L���O�摜�\��
	DrawGraph(0, 0, mImageHandle, FALSE);
	// �����L���O�ꗗ��\��
	SetFontSize(24);
	for (int i = 0; i < RANKCOUNT; i++) {
		DrawFormatString(240, 180 + i * 25, GetColor(255, 255, 255), "%2d %10s %12d",
			Ranking[i].no, Ranking[i].name, Ranking[i].score);
	}

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


/***********************************************
 * �����L���O���͏���
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Rank_Input()
{
	//�����L���O�摜�\��
	DrawGraph(0, 0, mImageHandle, FALSE);

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);
	// ���O���͎w��������̕`��
	DrawString(150, 240, "�����L���O�ɓo�^���܂�", GetColor(0, 0, 0));
	DrawString(150, 270, "���O���p��(10�����ȓ�)�œ��͂��Ă�������", GetColor(0, 0, 0));

	// ���O�̓���
	DrawString(150, 310, "> ", GetColor(0, 0, 0));
	DrawBox(160, 305, 300, 335, GetColor(0, 0, 0), TRUE);
	KeyInputSingleCharString(170, 310, 10, Ranking[(RANKCOUNT - 1)].name, FALSE);
	Ranking[(RANKCOUNT - 1)].score = Game_GetScore(); //�����L���O�f�[�^�̍Ō�ɃX�R�A��o�^
	Ranking[(RANKCOUNT - 1)].no = RANKCOUNT; //�����L���ONo.�͍Ō�ɂ��Ă���

	Rank_Sort(); // �����L���O���בւ�
	Rank_Save(); // �����L���O�f�[�^�̕ۑ�

	SceneMgr_ChangeScene(eScene_Rank); //�����L���O�\����ʂֈڍs
}


/***********************************************
 * �����L���O���בւ�
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Rank_Sort()
{
	int i, j;
	RankingData work;
	// �I��@�\�[�g
	for (i = 0; i < RANKCOUNT; i++) {
		for (j = i + 1; j < RANKCOUNT; j++) {
			if (Ranking[i].score <= Ranking[j].score) {
				work = Ranking[i];
				Ranking[i] = Ranking[j];
				Ranking[j] = work;
			}
		}
	}
	// ���ʕt��
	for (i = 0; i < RANKCOUNT; i++) {
		Ranking[i].no = 1;
	}
	// ���_�������ꍇ�́A�������ʂƂ���
	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
	for (i = 0; i < RANKCOUNT; i++) {
		for (j = i + 1; j < RANKCOUNT; j++) {
			if (Ranking[i].score > Ranking[j].score) {
				Ranking[j].no++;
			}
		}
	}
}


/***********************************************
 * �����L���O�f�[�^�̕ۑ�
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Rank_Save()
{
	FILE* fp;
	// �t�@�C���I�[�v��
	fopen_s(&fp, RANKING_FILE, "w");;
	if (fp != NULL) {
		// �����L���O�f�[�^���z��f�[�^����������
		for (int i = 0; i < RANKCOUNT; i++) {
			fprintf(fp, "%s %d %d\n", Ranking[i].name, Ranking[i].no, Ranking[i].score);
		}
		//�t�@�C���N���[�Y
		fclose(fp);
	}
	else {
		//�G���[���� (�K�v�ɉ����č쐬�j
		// printf("Ranking Data Error\n");
	}
}

/***********************************************
 * �����L���O�f�[�^�ǂݍ���
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void Rank_Read()
{
	FILE* fp;
	int i;
	//�t�@�C���I�[�v��
	fopen_s(&fp, RANKING_FILE, "r");
	if (fp != NULL) {
		//�����L���O�f�[�^�z����f�[�^��ǂݍ���
		for (int i = 0; i < RANKCOUNT; i++) {
			fscanf_s(fp, "%s %d %d", Ranking[i].name, 10, &Ranking[i].no, &Ranking
				[i].score);
		}
		fclose(fp);
	}
	else { //�t�@�C�����I�[�v���ł��Ȃ�or�ǂݍ��߂Ȃ�
	//�G���[���� (�K�v�ɉ����č쐬�j
	// printf("Ranking Data Error\n");
	// �����L���O�f�[�^�̏�����
		for (i = 0; i < RANKCOUNT; i++) {
			Ranking[i].no = (i + 1);
			sprintf_s(Ranking[i].name, "...");
			Ranking[i].score = 1;
		}
	}
}
