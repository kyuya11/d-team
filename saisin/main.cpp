#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"


int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
    SetMainWindowText("DanmakuShooting");   // �^�C�g����ݒ�
    ChangeWindowMode(TRUE);             // �E�B���h�E���[�h�ύX
    DxLib_Init();                       // DX���C�u����������
    SetDrawScreen(DX_SCREEN_BACK);      // ����ʐݒ�

    SceneMgr_Initialize();  // ������

    while (ProcessMessage() == 0) {    // ���b�Z�[�W����

        if (SceneMgr_GameEnd_Status()) {
            break; // ���j���[����I�����I�����ꂽ
        }

        ClearDrawScreen();	// ��ʏ���

        InputKey();         // ����

        SceneMgr_Update();  // �X�V
        SceneMgr_Draw();    // �`��

        ScreenFlip();	    // ��ʍX�V

    }
    SceneMgr_Finalize();

    DxLib_End(); // DX���C�u�����I������
    return 0;
}