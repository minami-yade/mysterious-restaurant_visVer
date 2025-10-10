#include "AllManager.h"

void GameAllLoad() {
	PlayerImage();
	GameBackImage();
	VegetableImage();
}

void GameAllDelete() {
	PlayerDelete();
	GameBackDelete();
	for (int i = 0; i < VEGETABLE_NUM; ++i) {
		VegetableDelete(i);
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
