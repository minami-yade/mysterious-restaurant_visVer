#pragma once
#include "Entity2D.h"

void TitleBackImage();

void GameBackImage();

void TitleBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center);
void GameBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center);
void GameFloorDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center);

void TitleBackDelete();

void GameBackDelete();