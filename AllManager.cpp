#include "AllManager.h"


void GameAllLoad() {
	PlayerImage();
	GameBackImage();
	VegetableImage();
	hookImage();
	EnemyImage();
}

void GameAllDelete() {
	PlayerDelete();
	GameBackDelete();
	for (int i = 0; i < VEGETABLE_NUM; ++i) {
		VegetableDelete(i);
	}
	hookDelete();
	for (int i = 0; i < ENEMY_NUM; ++i) {
		EnemyDelete(i);
	}

}

float GetDeltaTime_DxLib(int g_prevMs)
{
    unsigned int nowMs = GetNowCount();
    unsigned int diff = nowMs - g_prevMs;
    g_prevMs = nowMs;
    float deltaTime = diff / 1000.0f;
    if (deltaTime > 0.5f) deltaTime = 0.5f;
    return deltaTime;
}

DxPlus::Vec2 randamSpawn() {
	DxPlus::Vec2 position;
	position.x = (DxLib::GetRand(2) == 0) ? -50 : 1280;
	position.y = DxLib::GetRand(DxPlus::CLIENT_HEIGHT / 4) + DxPlus::CLIENT_HEIGHT / 6;
	return position;
}
