#include "DxPlus/DxPlus.h"
#include "Credit.h"
#include "WinMain.h"
#include "Entity2D.h"
/*
memo

*/


//----------------------------------------------------------------------
// 定数
//----------------------------------------------------------------------
Entity2D creditBack[2];
Entity2D creditButtonda;
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

	creditBack[0].spriteID = DxPlus::Sprite::Load(L"./Data/images/b1 (1).png");
    if(creditBack[0].spriteID == -1) {
        DxPlus::Utils::FatalError(L"data/Tex/credit_jpn.pngの読み込みに失敗しました");
	}

	creditBack[1].spriteID = DxPlus::Sprite::Load(L"./Data/images/credit_ita.png");
    if(creditBack[1].spriteID == -1) {
        DxPlus::Utils::FatalError(L"data/Tex/credit_ita.pngの読み込みに失敗しました");
	}

	creditButtonda.spriteID = DxPlus::Sprite::Load(L"./Data/images/back_titleto.png");
    if (creditButtonda.spriteID == -1) {
        DxPlus::Utils::FatalError(L"data/Tex/creditbutton.pngの読み込みに失敗しました");
    }

    Credit_Reset();
}

//----------------------------------------------------------------------
// リセット
//----------------------------------------------------------------------
void Credit_Reset()
{
    creditButtonda.position = { 525.0f, 626.0f };
    creditButtonda.scale = { 1.0f, 1.0f }; // スケールを初期化
    creditButtonda.center = { 0.0f, 0.0f }; // 中心点も初期化

    CreditState = 0;
    CreditFadeTimer = 1.0f;

}
//----------------------------------------------------------------------
// 更新処理
//----------------------------------------------------------------------
void Credit_Update()
{


    Credit_Fade();

}

//----------------------------------------------------------------------
// 描画処理
//----------------------------------------------------------------------
void Credit_Render()
{
	static bool isHits = false;

    for (int i = 0; i < 2; ++i) {
        DxPlus::Sprite::Draw(creditBack[i].spriteID, { 0,0 });
    }
    float alpha = 255.0f;
    float crick = 100.0f;
    if (isHits) {
        alpha = crick; // 暗く
    }

	DxPlus::Sprite::Draw(creditButtonda.spriteID, creditButtonda.position, creditButtonda.scale, creditButtonda.center, creditButtonda.angle,GetColor(alpha,alpha,alpha));

	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	DxPlus::Text::DrawString(L"Back to Title",
        40,
        15,
        GetColor(255, 255, 255),
        DxPlus::Text::BOTTOM_center,
        0,
        -1
    );


    bool wasMousePressed = false;
    // マウスの位置を取得
    DxPlus::Vec2 mousePos = { static_cast<float>(mouseX), static_cast<float>(mouseY) };

    DxPlus::Vec2 pos = creditButtonda.position ;
    DxPlus::Vec2 length = { creditButtonda.scale.x * 220.0f, creditButtonda.scale.y * 55.0f };
    // 当たり判定
    isHits = (mousePos.x > pos.x && mousePos.x < pos.x + length.x &&
        mousePos.y > pos.y && mousePos.y < pos.y + length.y);

#if _DEBUG
    // デバッグ表示: ボタンの矩形境界を描画
    int color = isHits ? GetColor(255, 255, 255) : GetColor(255, 0, 0);
    DrawBox(static_cast<int>(pos.x), static_cast<int>(pos.y),
        static_cast<int>(pos.x + length.x), static_cast<int>(pos.y + length.y),
        color, FALSE);
#endif

    // マウスクリック状態を取得
    wasMousePressed = false; // 前回のクリック状態を保持
    int mouseInput = GetMouseInput();
    bool isMouseClicked = (mouseInput & MOUSE_INPUT_LEFT) != 0;

    // スケール変更
    //creditButtonda.angle = creditButtondas ? creditButtonda.angle = 0.0f : creditButtonda.angle = 0.2f;

    // 当たり判定が成立し、かつクリックが押された瞬間のみ処理を実行
    if (isHits && isMouseClicked && !wasMousePressed && CreditState == 1) {
        CreditState = 2;
    }

    // 現在のクリック状態を保存
    wasMousePressed = isMouseClicked;

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
            nextScene = SceneCredit;
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
