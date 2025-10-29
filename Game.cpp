#include "DxPlus/DxPlus.h"
#include "Game.h"
#include "WinMain.h"
#include "AllManager.h"


float MainGameTimer = 0.0f;
//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------
float vegetableSpawnTimer,enemySpawnTimer;


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

//そうさせつめええええええええええええええええええええええおおおおおおおおおおおおいいい
bool GamePlayStart = false;
Entity2D GamePlays[2];
DxPlus::Vec2 ButtonBasePos = { 1145.0f,650.0f };
int offsetX = 112;
int offsetY = 46;

//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------
void Game_Init()
{
	GamePlays[0].spriteID = DxLib::LoadGraph(L"./Data/Images/operation.png");
    if (GamePlays[0].spriteID == -1) {
        DxPlus::Utils::FatalError(L"Failed to load start game image.");
	}
	GamePlays[1].spriteID = DxLib::LoadGraph(L"./Data/Images/start_game.png");
    if (GamePlays[1].spriteID == -1) {
        DxPlus::Utils::FatalError(L"Failed to load start game image.");
	}

 
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
	

	PlayerReset();
	VegetableReset();
	hookReset(playerBasePosition);
	EnemyReset();
	bowlReset();
    score = 0;
    ScoreReset();
	Timer_Reset(MainGameTimer);

    gameState = 0;
    gameFadeTimer = 1.0f;
	veg = true;

	//ゲームスタート時のそうさせつめええええええええええええええええええええええおおおおおおおおおおおおいいい
    GamePlayStart = true;
	GamePlays[1].scale = {1.0f,1.0f};
	GamePlays[1].center = { 115.0f,60.0f };
	GamePlays[1].position = { ButtonBasePos.x,ButtonBasePos.y };
	GamePlays[1].angle = 0.2f;
}


//----------------------------------------------------------------------
// 更新処理
//----------------------------------------------------------------------
extern int GameMode;

void Game_Update()
{
    int mouseX, mouseY;
    DxLib::GetMousePoint(&mouseX, &mouseY);
    mousePosX = { static_cast<float>(mouseX) };
    mousePosY = { static_cast<float>(mouseY) };


	//ゲームスタート時のそうさせつめい]
    if (GamePlayStart) {

        int left = ButtonBasePos.x - offsetX;
        int right = ButtonBasePos.x + offsetX;
        int top = ButtonBasePos.y - offsetY;
        int bottom = ButtonBasePos.y + offsetY;

        bool isMouseOver = (mousePosX > left && mousePosX < right &&
            mousePosY > top && mousePosY < bottom);

        if(isMouseOver) {

            GamePlays[1].angle = 0.0f;
            if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				gameFadeTimer = 1.1f;
				gameState = 0; // フェード
				if (gameFadeTimer >= 0.0f)
	            GamePlayStart = false; 
            }
           
		}
        else
            GamePlays[1].angle = 0.2f;


    }
    else {
      
      
        ScoreUpdate(score);
        Timer_Update(MainGameTimer, 1 / 60.0f, &gameState);
        delta = GetDeltaTime_DxLib(g_prevMs);

        //ノーマルが基準
        int BaseTime = 1;
		int easyTime = 1.2;
		int hardTime = 0.7;
        if (GameMode == 0)
        {
            vegetableSpawnTimer -=BaseTime * easyTime;
            enemySpawnTimer -= BaseTime * easyTime;
        }
        else if (GameMode == 1)
        {
            vegetableSpawnTimer -= BaseTime;
            enemySpawnTimer -= BaseTime;
        }
        else if (GameMode == 2)
        {
            vegetableSpawnTimer -= BaseTime * hardTime;
            enemySpawnTimer -= BaseTime * hardTime;
        }
     

		if (gameFadeTimer == 0.0f)
        Updatehook(delta, mouseX, mouseY, { mousePosX,mousePosY }, isRight);


        for (int i = 0; i < VEGETABLE_NUM; i++)
        {
            veg = true;
            SpawnTimeVegetable(i, &vegetableSpawnTimer);
            UpdateVegetable(i, delta, hookState);
            checkHookCollider(vegetable[i].position, vegetable[i].radius, i, veg);
            checkbowlCollider(vegetable[i], i);

        }
        for (size_t i = 0; i < ENEMY_NUM; i++)
        {
            veg = false;
            SpawnTimeEnemy(i, &enemySpawnTimer);
            checkbowlCollider(enemy[i], i);
            checkHookCollider(enemy[i].position, enemy[i].radius, i, veg);
            UpdateEnemy(i, delta, hookState, &score);
        }


    }
    GameBackUpdate();
    Game_Fade();
}




//----------------------------------------------------------------------
// 描画処理
//----------------------------------------------------------------------
void Game_Render()
{
    if (GamePlayStart) {
        DxPlus::Sprite::Draw(GamePlays[0].spriteID,
            { 0.0f, 0.0f },
            {GamePlays[0].scale},
            { 0.0f, 0.0f },
            0.0f,
			DxLib::GetColor(255, 255, 255));

        DxPlus::Sprite::Draw(GamePlays[1].spriteID,
            GamePlays[1].position,
            {GamePlays[1].scale},
            GamePlays[1].center,
			GamePlays[1].angle,
			DxLib::GetColor(255, 255, 255));
 
#if _DEBUG
        int left = ButtonBasePos.x - offsetX;
        int right = ButtonBasePos.x + offsetX;
        int top = ButtonBasePos.y - offsetY;
        int bottom = ButtonBasePos.y + offsetY;

        // ボタン描画（マウスが乗っているときは色を変える）
        int boxColor = (mousePosX > left && mousePosX < right &&
            mousePosY > top && mousePosY < bottom) ? GetColor(255, 200, 200) : GetColor(200, 200, 255);
        DrawBox(left, top, right, bottom, boxColor, false);

#endif
    }
    else {
        //背景
        GameBackDraw();
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



    }
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