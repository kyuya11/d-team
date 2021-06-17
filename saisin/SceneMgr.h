#pragma once

typedef enum {
    eScene_Menu,    //���j���[���
    eScene_Game,    //�Q�[�����
    eScene_Help,    //�����L���O���
    eScene_HelpInput,   // �����L���O���͉��
    eScene_End,     //�G���h���
    eScene_Stop,    //

    eScene_None,    //����
} eScene ;

void SceneMgr_Initialize();//������
void SceneMgr_Finalize();//�I������
void SceneMgr_Update();//�X�V
void SceneMgr_Draw();//�`��

// ���� nextScene �ɃV�[����ύX����
void SceneMgr_ChangeScene(eScene nextScene);

// �Q�[���I�����j���[���I�����ꂽ���ǂ�����Ԃ�
int SceneMgr_GameEnd_Status();
