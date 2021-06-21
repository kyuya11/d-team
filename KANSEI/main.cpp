#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetMainWindowText("DanmakuShooting"),ChangeWindowMode(TRUE),DxLib_Init(),SetDrawScreen(DX_SCREEN_BACK); 

	SceneMgr_Initialize(); // ������
	
	while (ProcessMessage() == 0) { // ���b�Z�[�W����
		
		if (SceneMgr_GameEnd_Status()) {
			break; // ���j���[����I�����I�����ꂽ
		}

		ClearDrawScreen(); // ��ʏ���

		InputKey(); // ����

		SceneMgr_Update(); // �X�V
		SceneMgr_Draw(); // �`��

		ScreenFlip(); // ��ʍX�V

	}
	SceneMgr_Finalize();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}