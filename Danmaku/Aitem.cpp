#include "DxLib.h"
#include "Aitem.h"
#include "Player.h"
#include "Enemy.h"
#include "Effect.h"
#include <math.h>

int HitCircleEnemy(PLAYER*, ENEMY*);	//�����蔻��i�~�j
int HitCircleEnemyShot(PLAYER*, ENEMY_SHOT*);	//�����蔻��i�~�j

void Aitem_Initialize() {
	struct ENEMY_SHOT mEnemyShot[ENEMY_SHOT_MAX];
	int mImageEnemyShot[ENEMY_SHOT_IMAGE_MAX];
}

void Finalize() {

}

void Update() {
	//for (int i = 0; i < ENEMY_MAX; i++) {
	//if (mPlayer.flg == false)
	//	continue;
	//if (HitCircleEnemyShot(&mPlayer, &mEnemyShot[i]) == TRUE) {
	//	mPlayer.flg = FALSE;
	//	mPlayer.count = 0;
	//	mPlayer.hp -= 1;
	//	EraseEnemyShot();
	//	CreateEffect(mPlayer.x, mPlayer.y);
}