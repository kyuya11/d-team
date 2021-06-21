#pragma once

typedef enum {
	eScene_Menu,
	eScene_Game,
	eScene_Help,
	eScene_End,
	eScene_Stop,

	eScene_None,
} eScene ;

void SceneMgr_Initialize();
void SceneMgr_Finalize();
void SceneMgr_Update();
void SceneMgr_Draw();

void SceneMgr_ChangeScene(eScene nextScene);

int SceneMgr_GameEnd_Status();
