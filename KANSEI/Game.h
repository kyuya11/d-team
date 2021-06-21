#pragma once

#define PI 3.1415926535897932384626433832795f

void Game_Initialize();
void Game_Finalize();
void Game_Update();
void Game_Draw();

void GameClear();
void GameOver(void);
void BackScroll();

int Game_GetmGameTime();
void Game_SetmgameStatus(int);
