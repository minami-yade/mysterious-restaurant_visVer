#pragma once
#include "Entity2D.h"

// TitleŠÖ˜A
void TitleBackImage();
void TitleBackReset();
int ButtonPosition(DxPlus::Vec2 pos, DxPlus::Vec2 mousePos);
void TitleBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center, bool start, bool set, bool fin, bool* gamePlay);
void TitleBackDelete();

void AnimeSomething();
void AniSomethingUpdate(bool* gameplay);
void AniSomethingDraw();



// GameŠÖ˜A
void GameBackImage();
void GameBackUpdate();
void GameBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center);
void GameFloorDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center);
void GameBackDelete();

// ResultŠÖ˜A
void ResultBackImage();
void ResultBackReset();
void ResultBackUpdate(int mouX,int mouY, int *resultState);
void ResultBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center, int score);
void ResultBackDelete();