#pragma once

#define PI 3.1415926535897932384626433832795f

/*************************
** �萔 **
*************************/

void Game_Initialize();//������
void Game_Finalize();//�I������
void Game_Update();//�X�V
void Game_Draw();//�`��

void GameClear();		// �Q�[���N���A
void GameOver(void);	//�Q�[���I�[�o�[����
void BackScroll();		// �w�i�`��

int Game_GetScore();			// �X�R�A�f�[�^�擾
int Game_GetmGameTime();		// �Q�[�����Ԏ擾
void Game_SetmgameStatus(int);	// �Q�[���󋵃Z�b�g

// *** +1line
void ScoreDraw();