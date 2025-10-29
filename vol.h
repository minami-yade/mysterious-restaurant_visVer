#pragma once
#include<algorithm>//td::clamp 用
				   //このヘッダを読み込むのはこれ使わないでねってやつらしいね
extern float vol_Sounds;

float GetVolume();

void SetVolume(float newvolume);