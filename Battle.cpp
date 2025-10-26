#include "DxPlus/DxPlus.h"
#include "Battle.h"
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

int battleState;
float battleFadeTimer;
extern int nextScene;

//----------------------------------------------------------------------
// 初期設定
//----------------------------------------------------------------------
void Battle_Init()
{
    SetBackgroundColor(0,0, 255);

    Battle_Reset();
}

//----------------------------------------------------------------------
// リセット
//----------------------------------------------------------------------
void Battle_Reset()
{
    battleState = 0;
    battleFadeTimer = 1.0f;

}
//----------------------------------------------------------------------
// 更新処理
//----------------------------------------------------------------------
void Battle_Update()
{
   
   
    Battle_Fade();

}

//----------------------------------------------------------------------
// 描画処理
//----------------------------------------------------------------------
void Battle_Render()
{
    DxPlus::Text::DrawString(L"ばとる",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.33f },
        DxLib::GetColor(255, 255, 255), DxPlus::Text::TextAlign::MIDDLE_center, { 3.0f, 3.0f });

    // フェードイン / フェードアウト用 
    if (battleFadeTimer > 0.0f) {
        //画面
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * battleFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }



}



void Battle_Fade()
{
    switch (battleState) {
    case 0: // フェードイン中 
    {
        battleFadeTimer -= 1 / 60.0f;
        if (battleFadeTimer < 0.0f) {
            battleFadeTimer = 0.0f;
            battleState++;
        }
        break;
    }
    case 1: // 通常時
    {
        // BackSpace キーが押されたらタイトルに戻す 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            battleState++;
        }
        break;
    }
    case 2: // フェードアウト中
    {
        battleFadeTimer += 1 / 60.0f;
        if (battleFadeTimer > 1.0f) {
            battleFadeTimer = 1.0f;
            nextScene = SceneTitle;
        }
        break;
    }
    //ゲームオーバー
    case 3:
    {
        battleFadeTimer += 1 / 60.0f;
        if (battleFadeTimer > 1.0f) {
            battleFadeTimer = 1.0f;
            nextScene = SceneResult;
        }
        break;
    }
    //クリア
    case 4:
    {
        battleFadeTimer += 1 / 60.0f;
        if (battleFadeTimer > 1.0f) {
            battleFadeTimer = 1.0f;
            nextScene = SceneSetting;
        }
        break;
    }
    //Game
    case 5:
    {
        battleFadeTimer += 1 / 60.0f;
        if (battleFadeTimer > 1.0f) {
            battleFadeTimer = 1.0f;
            nextScene = SceneGame;
        }
        break;
    }
    }

}


//----------------------------------------------------------------------
void Battle_End()
{

}
