#include "vol.h"
#include <DxLib.h>
#include"DxPlus/DxPlus.h"
#include <algorithm> 



float g_volume = 255.0f; 
 int vol_title_BGM;
 int vol_BGM_gamepaley;

float GetVolume()
{
    return g_volume/2.55f;
}

void SetVolume(float newVolume)
{
    g_volume = std::clamp(newVolume * 2.55f, 0.0f, 255.0f);
}
//std::clamp（すたんだーど・くらんぷ）は、
//「値を一定の範囲に収める」（はみ出さないようにする）ための関数

void Allvol()
{
	vol_title_BGM =LoadSoundMem(L"./Data/Sounds/BGMtitle.wav");
	if (vol_title_BGM == -1)
	{
		DxPlus::Utils::FatalError(L"./Data/Sounds/BGMtitle.wav");

	}
	vol_BGM_gamepaley = DxLib::LoadSoundMem(L"./Data/Sounds/BGMgame.mp3");
	if (vol_BGM_gamepaley == -1)
	{
		DxPlus::Utils::FatalError(L"./Data/Sounds/BGMgame.mp3");
	}
}