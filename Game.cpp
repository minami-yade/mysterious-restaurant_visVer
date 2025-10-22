#include "DxPlus/DxPlus.h"
#include "Game.h"
#include "WinMain.h"
#include "AllManager.h"


float MainGameTimer = 0.0f;
//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------
int vegetableSpawnTimer,enemySpawnTimer;


int hookX = 0;
int hookY = 0;

float mousePosX = 0;
float mousePosY = 0;

float delta;
bool isReturning;

int gameState;
float gameFadeTimer;
extern int nextScene;

int score = 0;


static unsigned int g_prevMs = 0;

extern DxPlus::Vec2 playerBasePosition;
extern HookState hookState;
bool isRight = true;


extern Entity2D vegetable[VEGETABLE_NUM];
extern HookState hookState;

extern Entity2D enemy[ENEMY_NUM];
bool veg = true;

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
    enemySpawnTimer = 300;
    isReturning = false;
	GameBackReset();

	PlayerReset();
	VegetableReset();
	hookReset(playerBasePosition);
	EnemyReset();
	bowlReset();
    score = 0;
    ScoreReset();
    MainGameTimer = 0.0f;
	Timer_Reset(MainGameTimer);

    gameState = 0;
    gameFadeTimer = 1.0f;
	veg = true;
}


//----------------------------------------------------------------------
// 更新処理
//----------------------------------------------------------------------

void Game_Update()
{
	Timer_Update(MainGameTimer, 1 / 60.0f,gameState);
    GameBackUpdate();

    delta = GetDeltaTime_DxLib(g_prevMs);
    vegetableSpawnTimer--;
    enemySpawnTimer--;

    int mouseX, mouseY;
    DxLib::GetMousePoint(&mouseX, &mouseY);
    mousePosX = { static_cast<float>(mouseX) };
    mousePosY = { static_cast<float>(mouseY) };

    Updatehook(delta, mouseX, mouseY, { mousePosX,mousePosY },isRight);
   
	
    for (int i = 0; i < VEGETABLE_NUM; i++)
    {
		veg = true;
        SpawnTimeVegetable(i, &vegetableSpawnTimer);
        UpdateVegetable(i ,delta,hookState);
        checkHookCollider(vegetable[i].position, vegetable[i].radius, i,veg);
        checkbowlCollider(vegetable[i], i);
       
    }
    for (size_t i = 0; i < ENEMY_NUM; i++)
    {
		veg = false;
        SpawnTimeEnemy(i, &enemySpawnTimer);
        checkbowlCollider(enemy[i], i);
        checkHookCollider(enemy[i].position, enemy[i].radius, i,veg);
		UpdateEnemy(i, delta, hookState);
    }



    Game_Fade();
}




//----------------------------------------------------------------------
// 描画処理
//----------------------------------------------------------------------
void Game_Render()
{

    //背景
    GameBackDraw({ 0,0 }, { 1.0f,1.0f }, { 0,0 });
	Timer_Draw(MainGameTimer);
    GameFloorDraw({ 0,0 }, { 1.0f,1.0f }, { 0,0 });
    ScoreDraw(score);

  
    //player
    if (hookState == Idle) {
        if (!(mousePosX > DxPlus::CLIENT_WIDTH / 3 && mousePosX < DxPlus::CLIENT_WIDTH - DxPlus::CLIENT_WIDTH / 3)) {

        
            if (mousePosX > DxPlus::CLIENT_WIDTH / 2)
            {
                isRight = true;
            }
            else {
                isRight = false;
            }
        }
    }

  
	
       PlayerDraw(isRight);
	   bowlDraw();

    //hook
    hookDraw(isRight);
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        EnemyDraw(i);
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
        {250,400},
        GetColor(255, 255, 255), DxPlus::Text::TextAlign::MIDDLE_center, { 1.0f, 1.0f });
    wchar_t buf2[64];

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