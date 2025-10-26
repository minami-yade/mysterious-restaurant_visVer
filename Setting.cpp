#include "DxPlus/DxPlus.h"
#include "Setting.h"
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

int SettingState;
float SettingFadeTimer;
extern int nextScene;

//----------------------------------------------------------------------
// 初期設定
//----------------------------------------------------------------------
void Setting_Init()
{
    SetBackgroundColor(120, 123, 74);

    Setting_Reset();
}

//----------------------------------------------------------------------
// リセット
//----------------------------------------------------------------------
void Setting_Reset()
{
    SettingState = 0;
    SettingFadeTimer = 1.0f;

}
//----------------------------------------------------------------------
// 更新処理
//----------------------------------------------------------------------
void Setting_Update()
{
 
    Setting_Fade();

}

//----------------------------------------------------------------------
// 描画処理
//----------------------------------------------------------------------
void Setting_Render()
{

    DxPlus::Text::DrawString(L"せっていやで",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.33f },
        DxLib::GetColor(255, 255, 255), DxPlus::Text::TextAlign::MIDDLE_center, { 3.0f, 3.0f });

    if (DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1) & DxPlus::Input::BUTTON_TRIGGER1) {


        SettingState = 2;
    }
    else
    {
        DxPlus::Text::DrawString(L"SPACEでぇもどるよ",
            { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.66f },
            DxLib::GetColor(255, 255, 0), DxPlus::Text::TextAlign::MIDDLE_center, { 2.0f, 2.0f });
	}

    // フェードイン / フェードアウト用 
    if (SettingFadeTimer > 0.0f) {
        //画面
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * SettingFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }



}



void Setting_Fade()
{
    switch (SettingState) {
    case 0: // フェードイン中 
    {
        SettingFadeTimer -= 1 / 60.0f;
        if (SettingFadeTimer < 0.0f) {
            SettingFadeTimer = 0.0f;
            SettingState++;
        }
        break;
    }
    case 1: // 通常時
    {
        // BackSpace キーが押されたらタイトルに戻す 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            SettingState++;
        }
        break;
    }
    case 2: // フェードアウト中
    {
        SettingFadeTimer += 1 / 60.0f;
        if (SettingFadeTimer > 1.0f) {
            SettingFadeTimer = 1.0f;
            nextScene = SceneTitle;
        }
        break;
    }
    
    //ゲームオーバー
    case 3:
    {
        SettingFadeTimer += 1 / 60.0f;
        if (SettingFadeTimer > 1.0f) {
            SettingFadeTimer = 1.0f;
            nextScene = SceneResult;
        }
        break;
    }
    //Game
    case 4:
    {
        SettingFadeTimer += 1 / 60.0f;
        if (SettingFadeTimer > 1.0f) {
            SettingFadeTimer = 1.0f;
            nextScene = SceneGame;
        }
        break;
    }
    //バトル
    case 5:
    {
        SettingFadeTimer += 1 / 60.0f;
        if (SettingFadeTimer > 1.0f) {
            SettingFadeTimer = 1.0f;
            nextScene = SceneSetting;
        }
        break;
    }
    }
  

}


//----------------------------------------------------------------------
void Setting_End()
{

}
