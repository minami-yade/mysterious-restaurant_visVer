#include "Vegetable.h"


Entity2D vegetable[12];


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


    // 累積時間を進める
    vegetable[i].timeAcc += deltaTime;


    float t = fmodf(vegetable[i].timeAcc, vegetable[i].period) / vegetable[i].period;
    float triangle = 1.0f - fabsf(2.0f * t - 1.0f);

    // 高さを計算（baseY を下限にして amplitude 分だけ上がる）
    vegetable[i].position.y = vegetable[i].baseY + triangle * vegetable[i].amplitude;

    // 前進
    vegetable[i].position.x += vegetable[i].speed * deltaTime;


    // 画面外に出たら非アクティブにする
    if (vegetable[i].position.x < -100 || vegetable[i].position.x > DxPlus::CLIENT_WIDTH + 100) {
        vegetable[i].isActive = false;
    }

}

DxPlus::Vec2 randamSpawn() {
	DxPlus::Vec2 position;
	position.x = (DxLib::GetRand(2) == 0) ? -50 : 1280;
    position.y = DxLib::GetRand(DxPlus::CLIENT_HEIGHT / 4) + DxPlus::CLIENT_HEIGHT / 6;
	return position;
}

void SpawnTimeVegetable(int i , int* Timer) {
	if (vegetable[i].isActive) return;
    if (*Timer < 0) {
	
        vegetable[i].position        = randamSpawn();                // 画面外からスタート	
        vegetable[i].speed = (vegetable[i].position.x < DxPlus::CLIENT_WIDTH/2) ? vegetable[i].speed : -vegetable[i].speed; // 右からなら左へ、左からなら右へ
        vegetable[i].isActive        = true;
		*Timer                       = GetRand(240) + 60;            //４秒から５秒
        vegetable[i].baseY           = vegetable[i].position.y;      // 基準高
        vegetable[i].amplitude       = GetRand(50) + 50;             // 振幅（最大高さ - baseY）
        vegetable[i].period          = 60;                           // 周期（フレーム）
        vegetable[i].timeAcc         = 0;                            // 累積時間（内部で管理）
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
