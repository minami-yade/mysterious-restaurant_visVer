#include "Result.h"
#include "Back.h"
#include "winmain.h"


int resultState;
float resultFadeTimer;
extern int nextScene;
extern int score;


// 初期化関数
void Result_Init() {
	ResultBackImage();	

    Result_Reset();
}

// リセット関数
void Result_Reset() {
	resultFadeTimer = 1.0f;
	resultState = 0;

	ResultBackReset();
}

// 更新関数
void Result_Update() {	
	int mouX, mouY;
	DxLib::GetMousePoint(&mouX, &mouY);
	ResultBackUpdate(mouX,mouY,&resultState);

    Result_Fade();
}

// 描画関数
void Result_Render() {

	ResultBackDraw({ 0,0 }, { 1.0f,1.0f }, { 0,0 },score);

  

	FadeDrawResult();
}

void FadeDrawResult()
{
	if (resultFadeTimer > 0.0f) {
		//画面
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * resultFadeTimer));
		DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
			DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	}
}

void Result_Fade()
{
    switch (resultState) {
    case 0: // フェードイン中 
    {
        resultFadeTimer -= 1 / 60.0f;
        if (resultFadeTimer < 0.0f) {
            resultFadeTimer = 0.0f;
            resultState++;
        }
        break;
    }
    case 1: // 通常時
    {
      
        break;
    }
    case 2: // フェードアウト中
    {
        resultFadeTimer += 1 / 100.0f;
        if (resultFadeTimer > 0.68f) {
            resultFadeTimer = 0.68f;
            nextScene = SceneTitle;
        }
        break;
    }
  
    }

}

// 終了関数
void Result_End() {
	ResultBackDelete();
}