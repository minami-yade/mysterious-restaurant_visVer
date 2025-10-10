#include "DxPlus/DxPlus.h"
#include "Result.h"
#include "Game.h"
#include "WinMain.h"



extern int nextScene;

int ResultState;

float ResultFadeTimer;



void Result_Init() {

    DxLib::SetBackgroundColor(155, 0, 0);

    Result_Reset();
}

void Result_Reset() {

    ResultState = 0;
    ResultFadeTimer = 1.0f;

}

void Result_Update() {

    
}

void Result_Render() {





}




void Result_End() {

}