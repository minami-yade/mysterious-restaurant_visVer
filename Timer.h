#pragma once
#include "DxPlus/DxPlus.h"



void Timer_Image();
void Timer_Reset(float& timeLeft);

void Timer_Update(float& timeLeft, float deltaTime,int* gameState);
void Timer_DrawGauge(float timeLeft);

void Timer_Draw(float timeLeft);
void Timer_Delete();