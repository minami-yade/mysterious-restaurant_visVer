#pragma once
#include "Entity2D.h"

void TitleBackImage();

void GameBackImage();

void TitleBackReset();
void GameBackReset();
void TitleBackUpdate();
int ButtonPosition(DxPlus::Vec2 pos, DxPlus::Vec2 mousePos);
void GameBackUpdate();
void TitleBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center, bool start, bool set, bool fin);
void GameBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center);
void GameFloorDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center);

void TitleBackDelete();

void GameBackDelete();