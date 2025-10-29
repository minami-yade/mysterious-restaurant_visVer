#include "DxPlus/DxPlus.h"
#include "Credit.h"
#include "WinMain.h"

/*
memo

*/
extern int fontID1;

//----------------------------------------------------------------------
// 定数
//----------------------------------------------------------------------

float textPos = -1200.0f;
//----------------------------------------------------------------------
// 変数
//----------------------------------------------------------------------

int CreditState;
float CreditFadeTimer;
extern int nextScene;

//----------------------------------------------------------------------
// 初期設定
//----------------------------------------------------------------------
void Credit_Init()
{


    Credit_Reset();
}

//----------------------------------------------------------------------
// リセット
//----------------------------------------------------------------------
void Credit_Reset()
{
    CreditState = 0;
    CreditFadeTimer = 1.0f;

}
//----------------------------------------------------------------------
// 更新処理
//----------------------------------------------------------------------
void Credit_Update()
{
    textPos += 1;

    Credit_Fade();

}

//----------------------------------------------------------------------
// 描画処理
//----------------------------------------------------------------------
void Credit_Render()
{
    const float lineSpacing = 250.0f; // 行間隔を設定
    for (int i = 0; i < 6; i++) {
        float yPos = textPos + i * lineSpacing; // 各行のY座標を計算
        switch (i)
        {
        case 0:
            DxPlus::Text::DrawString(
                L"0",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
            );
            break;
        case 1:
            DxPlus::Text::DrawString(
                L"Producer: Your Name",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
            );
            break;
        case 2:
            DxPlus::Text::DrawString(
                L"Thanks for playing!",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
            );
            break;
        case 3:
            DxPlus::Text::DrawString(
                L"Press SELECT to return to Title",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
            );
            break;
        case 4:
            DxPlus::Text::DrawString(
                L"Game Development Team",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
			);
			break;
            case 5:
            DxPlus::Text::DrawString(
                L"Special Thanks to Our Supporters",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
            );
			break;


        default:
			DxPlus::Utils::FatalError(L"Invalid credit line index.");
            break;
        }
   
    }
    // フェードイン / フェードアウト用 
    if (CreditFadeTimer > 0.0f) {
        //画面
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * CreditFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }



}



void Credit_Fade()
{
    switch (CreditState) {
    case 0: // フェードイン中 
    {
        CreditFadeTimer -= 1 / 60.0f;
        if (CreditFadeTimer < 0.0f) {
            CreditFadeTimer = 0.0f;
            CreditState++;
        }
        break;
    }
    case 1: // 通常時
    {
        // BackSpace キーが押されたらタイトルに戻す 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            CreditState++;
        }
        break;
    }
    case 2: // フェードアウト中
    {
        CreditFadeTimer += 1 / 60.0f;
        if (CreditFadeTimer > 1.0f) {
            CreditFadeTimer = 1.0f;
            nextScene = SceneTitle;
        }
        break;
    }
    //ゲームオーバー
    case 3:
    {
        CreditFadeTimer += 1 / 60.0f;
        if (CreditFadeTimer > 1.0f) {
            CreditFadeTimer = 1.0f;
            nextScene = SceneResult;
        }
        break;
    }
    //クリア
    case 4:
    {
        CreditFadeTimer += 1 / 60.0f;
        if (CreditFadeTimer > 1.0f) {
            CreditFadeTimer = 1.0f;
            nextScene = SceneSetting;
        }
        break;
    }
    //Game
    case 5:
    {
        CreditFadeTimer += 1 / 60.0f;
        if (CreditFadeTimer > 1.0f) {
            CreditFadeTimer = 1.0f;
            nextScene = SceneGame;
        }
        break;
    }
    }

}


//----------------------------------------------------------------------
void Credit_End()
{

}
