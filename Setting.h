#pragma once

void Setting_Init();

void Setting_Reset();

void Setting_Update();

void Setting_Button_CI(DxPlus::Vec2 pos, float radius,int* upDown,bool plus);
void Setting_Button_SQ(DxPlus::Vec2 pos, DxPlus::Vec2 length, int mode);


void Setting_Render();
	 
void Setting_Fade();
	
void Setting_End();


