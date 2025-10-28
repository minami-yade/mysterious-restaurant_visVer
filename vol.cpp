#include "vol.h"

float g_volume = 255.0f; // 実体はここに1つだけ！

float GetVolume()
{
    return g_volume;
}

void SetVolume(float newVolume)
{
    g_volume = std::clamp(newVolume, 0.0f, 255.0f);
}
//std::clamp（すたんだーど・くらんぷ）は、
//「値を一定の範囲に収める」（はみ出さないようにする）ための関数です。