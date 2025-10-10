#include "DxPlus/DxPlus.h"
#include "Clear.h"
#include "WinMain.h"

/*
memo

*/

//----------------------------------------------------------------------
// 定数
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// 変数
//----------------------------------------------------------------------

int clearState;
float clearFadeTimer;
extern int nextScene;

//----------------------------------------------------------------------
// 初期設定
//----------------------------------------------------------------------
void Clear_Init()
{
    SetBackgroundColor(120, 123, 74);

    Clear_Reset();
}

//----------------------------------------------------------------------
// リセット
//----------------------------------------------------------------------
void Clear_Reset()
{
    clearState = 0;
    clearFadeTimer = 1.0f;

}
//----------------------------------------------------------------------
// 更新処理
//----------------------------------------------------------------------
void Clear_Update()
{

    Clear_Fade();

}

//----------------------------------------------------------------------
// 描画処理
//----------------------------------------------------------------------
void Clear_Render()
{

    DxPlus::Text::DrawString(L"くりあ",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.33f },
        DxLib::GetColor(255, 255, 255), DxPlus::Text::TextAlign::MIDDLE_CENTER, { 3.0f, 3.0f });



    // フェードイン / フェードアウト用 
    if (clearFadeTimer > 0.0f) {
        //画面
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * clearFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }



}



void Clear_Fade()
{
    switch (clearState) {
    case 0: // フェードイン中 
    {
        clearFadeTimer -= 1 / 60.0f;
        if (clearFadeTimer < 0.0f) {
            clearFadeTimer = 0.0f;
            clearState++;
        }
        break;
    }
    case 1: // 通常時
    {
        // BackSpace キーが押されたらタイトルに戻す 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            clearState++;
        }
        break;
    }
    case 2: // フェードアウト中
    {
        clearFadeTimer += 1 / 60.0f;
        if (clearFadeTimer > 1.0f) {
            clearFadeTimer = 1.0f;
            nextScene = SceneTitle;
        }
        break;
    }
    
    //ゲームオーバー
    case 3:
    {
        clearFadeTimer += 1 / 60.0f;
        if (clearFadeTimer > 1.0f) {
            clearFadeTimer = 1.0f;
            nextScene = SceneResult;
        }
        break;
    }
    //Game
    case 4:
    {
        clearFadeTimer += 1 / 60.0f;
        if (clearFadeTimer > 1.0f) {
            clearFadeTimer = 1.0f;
            nextScene = SceneGame;
        }
        break;
    }
    //バトル
    case 5:
    {
        clearFadeTimer += 1 / 60.0f;
        if (clearFadeTimer > 1.0f) {
            clearFadeTimer = 1.0f;
            nextScene = SceneClear;
        }
        break;
    }
    }
  

}


//----------------------------------------------------------------------
void Clear_End()
{

}
