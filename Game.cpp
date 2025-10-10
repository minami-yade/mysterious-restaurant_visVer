#include "DxPlus/DxPlus.h"
#include "Game.h"
#include "WinMain.h"
#include "AllManager.h"

/*memo


*/

//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------
int vegetableSpawnTimer;


int gameState;
float gameFadeTimer;
extern int nextScene;

static unsigned int g_prevMs = 0;





//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------
void Game_Init()
{
	//今の時間を取得
    g_prevMs = GetNowCount();

	GameAllLoad();  

    Game_Reset();
}

//----------------------------------------------------------------------
// リセット
//----------------------------------------------------------------------
void Game_Reset()
{
    vegetableSpawnTimer = 0;

	PlayerReset();
	VegetableReset();

    gameState = 0;
    gameFadeTimer = 1.0f;
    
}


//----------------------------------------------------------------------
// 更新処理
//----------------------------------------------------------------------

void Game_Update()
{
    vegetableSpawnTimer--;

	float delta = GetDeltaTime_DxLib(g_prevMs);
    for (int i = 0; i < VEGETABLE_NUM; i++)
    {
        SpawnTimeVegetable(i, &vegetableSpawnTimer);
        UpdateVegetable(i ,delta);
    }

 



    Game_Fade();
}



//----------------------------------------------------------------------
// 描画処理
//----------------------------------------------------------------------
void Game_Render()
{
	int input = DxPlus::Input::GetButton(DxPlus::Input::PLAYER1);
	int SPACE = input & DxPlus::Input::BUTTON_TRIGGER1;
	//背景
	GameBackDraw({ 0,0 }, { 1.0f,1.0f }, { 0,0 });
	GameFloorDraw({ 0,0 }, { 1.0f,1.0f }, { 0,0 });

	//player
    //仮のため後で変える
    if (input && SPACE)
    {
        PlayerDraw(true);
    }
    else
    {
        PlayerDraw(false);
    }

	//Vegetable
    for (int i = 0; i < VEGETABLE_NUM; i++)
    {
            VegetableDraw(i);
    }
   
    
#if _DEBUG
    wchar_t buf[64];
    swprintf(buf, 64, L"vegetableSpawnTimer: %d", vegetableSpawnTimer);
    DxPlus::Text::DrawString(buf,
        {0,100},
        GetColor(255, 255, 255), DxPlus::Text::TextAlign::MIDDLE_CENTER, { 1.0f, 1.0f });

#endif
    
    FadeDrawGame();
}

void FadeDrawGame()
{
    if (gameFadeTimer > 0.0f) {
        //画面
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * gameFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }
}
void Game_Fade()
{
    switch (gameState) {
    case 0: // フェードイン中 
    {
        gameFadeTimer -= 1 / 60.0f;
        if (gameFadeTimer < 0.0f) {
            gameFadeTimer = 0.0f;
            gameState++;
        }
        break;
    }
    case 1: // 通常時
    {
        // BackSpace キーが押されたらタイトルに戻す 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            gameState++;
        }
        break;
    }
    case 2: // フェードアウト中
    {
        gameFadeTimer += 1 / 60.0f;
        if (gameFadeTimer > 1.0f) {
            gameFadeTimer = 1.0f;
            nextScene = SceneTitle;
        }
        break;
    }
    case 3:
    {
        gameFadeTimer += 1 / 60.0f;
        if (gameFadeTimer > 1.0f) {
            gameFadeTimer = 1.0f;
            nextScene = SceneResult;
        }
        break;
    }
    }

}

void Game_End()
{
	GameAllDelete();
}