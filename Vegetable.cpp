#include "Vegetable.h"
#include "AllManager.h"


Entity2D vegetable[VEGETABLE_NUM];
extern Entity2D enemy[ENEMY_NUM];
extern Entity2D hook;

int vegAnim[VEG_ANIM_NUM];
const float VEG_ANIM_INTERVAL = 6.0f; // アニメーション間隔（秒）
const DxPlus::Vec2 wingCenter = { 7.0f, 80.0f };

// --- 画像読み込み関係 ---
void VegetableImage()
{  
    const wchar_t* vagPaths[VEG_ANIM_NUM] = {
       L"./Data/images/W1.png",
       L"./Data/images/W2.png",
       L"./Data/images/W3.png",
    };
    for (int j = 0; j < VEG_ANIM_NUM; ++j) {
        vegAnim[j] = LoadGraph(vagPaths[j]);
        if (vegAnim[j] == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + vagPaths[j]).c_str());
        }
    }

    for (int i = 0; i < VEGETABLE_NUM; ++i)
    {
        switch (i % VEGETABLE_TYPE) {
        case 0: //　キャベツ
            vegetable[i].spriteID = LoadGraph(L"./Data/images/cabbage.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/cabbage.png");
            }
            break;
        case 1://肉
            vegetable[i].spriteID = LoadGraph(L"./Data/images/beef.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/beef.png");
            }
            break;
        case 2://パプリカ
            vegetable[i].spriteID = LoadGraph(L"./Data/images/paprika.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/paprika.png");
            }
            break;
        case 3://毒キノコ
            vegetable[i].spriteID = LoadGraph(L"./Data/images/poison_mushroom.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/poison_mushroom.png");
            }
            break;
        case 4://ニンジン
             vegetable[i].spriteID = LoadGraph(L"./Data/images/carrot.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/carrot.png");
            }
			break;
        case 5: //ナス
            vegetable[i].spriteID = LoadGraph(L"./Data/images/eggplant.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/eggplant.png");
			}
			break;
		case 6://トマト
            vegetable[i].spriteID = LoadGraph(L"./Data/images/tomato.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/tomato.png");
			}   
			break;
      
			break;
        default:
            DxPlus::Utils::FatalError(L"野菜の画像が存在しません！");
            break;
        };
    }
   
}

// --- リセット関数（初期配置や状態の初期化） ---
void VegetableReset()
{
    
    for (int i = 0; i < VEGETABLE_NUM; ++i)
    {
        vegetable[i].isActive = false;
        vegetable[i].havescore = 50;
        vegetable[i].vegAnimNum = 0;
        vegetable[i].timer = 0.0f;
		vegetable[i].position = { -100.0f,-100.0f };
    
        switch (i % VEGETABLE_TYPE) {
		case 0: //　キャベツ
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f; // 100 ピクセル/秒
            vegetable[i].JumpPower = 15.0f;
            vegetable[i].moveVegetable = 0;
            break;
        case 1://肉
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f;
            vegetable[i].JumpPower = 15.0f;
            vegetable[i].moveVegetable = 0;
			break;
        case 2://パプリカ
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f;
            vegetable[i].JumpPower = 15.0f;
            vegetable[i].moveVegetable = 0;
			break;
        case 3://毒キノコ
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f;
            vegetable[i].JumpPower = 15.0f;
            vegetable[i].moveVegetable = 0;
			break;
         case 4://ニンジン
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f;
            vegetable[i].JumpPower = 15.0f;
			vegetable[i].moveVegetable = 0;
            break;
        case 5: //ナス
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f;
			vegetable[i].JumpPower = 15.0f;
            vegetable[i].moveVegetable = 0;
			break;
        case 6://トマト
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
			vegetable[i].speed = 3.0f;
            vegetable[i].JumpPower = 15.0f;
			vegetable[i].moveVegetable = 0;
            break;
     
		default:
			DxPlus::Utils::FatalError(L"野菜の画像が存在しません！");
			break;
        }
    }

}



// --- 動きの更新（単純な三角波で上下） ---
void UpdateVegetable(int i, float deltaTime,HookState hookState)
{
    if (!vegetable[i].isActive) return;

    switch (vegetable[i].moveVegetable)
    {
    case 0: // 通常

        // wing アニメ更新（vegetable ごとの timer / vegAnimNum を使う）
        vegetable[i].timer += deltaTime;
        if (vegetable[i].timer >= VEG_ANIM_INTERVAL) {
            vegetable[i].timer -= VEG_ANIM_INTERVAL;
            vegetable[i].vegAnimNum = (vegetable[i].vegAnimNum + 1) % VEG_ANIM_NUM;
        }

        // 前進
        vegetable[i].position.x += vegetable[i].speed * deltaTime;

        // 重力加速度を加える
        vegetable[i].velocity.y += vegetable[i].gravity * deltaTime;

        // 地面（baseY）に到達したら跳ね返る
        if (vegetable[i].position.y >= vegetable[i].baseY && vegetable[i].velocity.y > 0)
        {
            vegetable[i].position.y = vegetable[i].baseY;
            vegetable[i].velocity.y = -vegetable[i].JumpPower; // 跳ね返り
        }

        // 位置を更新
        vegetable[i].position.y += vegetable[i].velocity.y * deltaTime;
        break;

    case 1: // フックに捕まった
        vegetable[i].position = { hook.position };
        if (hookState == Idle) {
            vegetable[i].moveVegetable = 2;
        }
		vegetable[i].angle -= 6.0f;
        break;

    case 2: // フックに捕まった後放たれた
        vegetable[i].moveVegetable = 3;
        break;
    case 3:
    {
        const float ByeByeSpeed = 5.0f;
        const float AngleSpeed = 0.5f;
        if (vegetable[i].position.x > DxPlus::CLIENT_WIDTH / 2)
        {
            vegetable[i].position.x -= ByeByeSpeed * deltaTime * 1.0f;
            vegetable[i].position.y += ByeByeSpeed * deltaTime * 1.1f;
            vegetable[i].angle += AngleSpeed;
        }
        else
        {
            vegetable[i].position.x += ByeByeSpeed * deltaTime * 1.0f;
            vegetable[i].position.y += ByeByeSpeed * deltaTime * 1.1f;
            vegetable[i].angle += AngleSpeed;
        }
        break;
    }

    default:
        break;
    }

    // 画面外に出たら非アクティブにする
    if (vegetable[i].position.x < -100 || vegetable[i].position.x > DxPlus::CLIENT_WIDTH + 100 
        || vegetable[i].position.y < -100 || vegetable[i].position.y > DxPlus::CLIENT_HEIGHT+ 100)
    {
        vegetable[i].isActive = false;
		vegetable[i].moveVegetable = 0;
		vegetable[i].velocity = { 0,0 };
    }
}


void SpawnTimeVegetable(int i , float* Timer) {
	if (vegetable[i].isActive) return;
    if (*Timer < 0) {
	
        vegetable[i].position        = randamSpawn();                // 画面外からスタート	
        vegetable[i].speed = 3.0f; 
        vegetable[i].speed = (vegetable[i].position.x < DxPlus::CLIENT_WIDTH/2) ? vegetable[i].speed : -vegetable[i].speed; // 右からなら左へ、左からなら右へ
        vegetable[i].isActive        = true;
		*Timer                       = GetRand(60) + 60;
        vegetable[i].baseY           = vegetable[i].position.y;      // 基準高
		vegetable[i].velocity.y = 0;                            // 速度
		vegetable[i].angle = 0;

    } 
}

void onHookHit(const DxPlus::Vec2& targetPos, Entity2D* hookPtr, int i)
{
    // 安全性チェック
    if (i < 0 || i >= VEGETABLE_NUM) return;

    // 野菜をフックにくっつける
    hookPtr->isCarryingVegetable = true;
    hookPtr->carriedVegetable = &vegetable[i];

    if (vegetable[i].moveVegetable == 0) {
        vegetable[i].moveVegetable = 1;
        vegetable[i].velocity = { 0, 0 }; // 必要なら初期化
    }
}


// --- 描画関数 ---
void VegetableDraw(int i)
{
    if (!vegetable[i].isActive) return;
	if (vegetable[i].spriteID == -1) return;

    int frame = vegetable[i].vegAnimNum;
    if (frame < 0) frame = 0;
    frame %= VEG_ANIM_NUM;

    int sprite = vegAnim[frame];
    if (sprite == -1) return;

	// 野菜の描画
    if(vegetable[i].speed > 0)
        DxPlus::Sprite::Draw(vegetable[i].spriteID, vegetable[i].position, vegetable[i].scale, vegetable[i].center,vegetable[i].angle);
    else
        DxPlus::Sprite::Draw(vegetable[i].spriteID, vegetable[i].position, { -vegetable[i].scale.x ,vegetable[i].scale.y }, vegetable[i].center,-vegetable[i].angle);


    //羽の描画（アニメ）
    if (vegetable[i].speed < 0)
        DxPlus::Sprite::Draw(sprite, vegetable[i].position, vegetable[i].scale, wingCenter, vegetable[i].angle);
    else
        DxPlus::Sprite::Draw(sprite, vegetable[i].position, { -vegetable[i].scale.x, vegetable[i].scale.y }, wingCenter, vegetable[i].angle);
}


// --- 解放関数 ---
void VegetableDelete(int i)
{
    if (vegetable[i].spriteID != -1) {
        DxPlus::Sprite::Delete(vegetable[i].spriteID);
        vegetable[i].spriteID = -1;
    }
}
