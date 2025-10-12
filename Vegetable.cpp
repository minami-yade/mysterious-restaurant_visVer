#include "Vegetable.h"
#include "AllManager.h"


Entity2D vegetable[VEGETABLE_NUM];


// --- 画像読み込み関係 ---
void VegetableImage()
{
       
    for (int i = 0; i < VEGETABLE_NUM; ++i)
    {
        switch (i % VEGETABLE_TYPE) {
        case 0: //　キャベツ
            vegetable[i].spriteID = LoadGraph(L"./Data/images/cabbage.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/cabbage.png");
            }
            break;

        default:
            DxPlus::Utils::FatalError(L"野菜の画像が存在しません！");
            break;
        }
    }

   
}

// --- リセット関数（初期配置や状態の初期化） ---
void VegetableReset()
{
    for (int i = 0; i < VEGETABLE_NUM; ++i)
    {
        vegetable[i].isActive = false;
        vegetable[i].havescore = 50;
    
        switch (i % VEGETABLE_TYPE) {
		case 0: //　キャベツ
            vegetable[i].type = 0;
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 141.0f, 81.0f };
            vegetable[i].speed = 3.0f; // 100 ピクセル/秒
            break;
		default:
			DxPlus::Utils::FatalError(L"野菜の画像が存在しません！");
			break;
        }
    }

}



// --- 動きの更新（単純な三角波で上下） ---
void UpdateVegetable(int i, float deltaTime)
{
    if (!vegetable[i].isActive) return;

    // 前進
    vegetable[i].position.x += vegetable[i].speed * deltaTime;

    // 重力加速度を加える
    vegetable[i].velocity.y += vegetable[i].gravity * deltaTime;

    // 地面（baseY）に到達したら跳ね返る
    if (vegetable[i].position.y >= vegetable[i].baseY)
    {
        // 位置を更新
        vegetable[i].position.y =  vegetable[i].baseY;
        vegetable[i].velocity.y += -vegetable[i].JumpPower;
    }

    // 位置を更新
    vegetable[i].position.y += vegetable[i].velocity.y * deltaTime;

    // 画面外に出たら非アクティブにする
    if (vegetable[i].position.x < -100 || vegetable[i].position.x > DxPlus::CLIENT_WIDTH + 100)
    {
        vegetable[i].isActive = false;
    }
}


void SpawnTimeVegetable(int i , int* Timer) {
	if (vegetable[i].isActive) return;
    if (*Timer < 0) {
	
        vegetable[i].position        = randamSpawn();                // 画面外からスタート	
        vegetable[i].speed = (vegetable[i].position.x < DxPlus::CLIENT_WIDTH/2) ? vegetable[i].speed : -vegetable[i].speed; // 右からなら左へ、左からなら右へ
        vegetable[i].isActive        = true;
		*Timer                       = GetRand(240) + 60;            //４秒から５秒
        vegetable[i].baseY           = vegetable[i].position.y;      // 基準高
    } 
}

// --- 描画関数 ---
void VegetableDraw(int i)
{
    if (!vegetable[i].isActive) return;
	if (vegetable[i].spriteID == -1) return;
    if(vegetable[i].speed > 0)
    DxPlus::Sprite::Draw(vegetable[i].spriteID, vegetable[i].position, vegetable[i].scale, vegetable[i].center);
    else
        DxPlus::Sprite::Draw(vegetable[i].spriteID, vegetable[i].position, { -vegetable[i].scale.x ,vegetable[i].scale.y }, vegetable[i].center);
}

// --- 解放関数 ---
void VegetableDelete(int i)
{
    if (vegetable[i].spriteID != -1) {
        DxPlus::Sprite::Delete(vegetable[i].spriteID);
        vegetable[i].spriteID = -1;
    }
}
