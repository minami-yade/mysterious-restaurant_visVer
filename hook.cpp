#include "hook.h"

Entity2D hook;

HookState hookState = Idle;


// --- 画像読み込み関係 ---
void hookImage()
{

    hook.spriteID = LoadGraph(L"./Data/images/hook_png.png");
    if (hook.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/hook_png.png");
    }

}

// --- リセット関数（初期配置や状態の初期化） ---
void hookReset(DxPlus::Vec2 playerBasePosition)
{
    int Xoffset = 200;
    int Yoffset = 136;

    hook.HomePositionLeft.x = playerBasePosition.x - Xoffset;
    hook.HomePositionLeft.y = playerBasePosition.y - Yoffset;

	hook.HomePositionRight.x = playerBasePosition.x + Xoffset;
    hook.HomePositionRight.y = playerBasePosition.y - Yoffset;
    hook.position = hook.HomePositionRight;
	hook.target = hook.HomePositionRight;

	hook.scale = { 0.5f,0.5f };
	hook.center = { 49.0f, 62.0f };

    hook.angle = 12;
}

void Updatehook(float deltaTime, int x, int y, DxPlus::Vec2 pointer,bool left)
{
    DxLib::GetMousePoint(&x, &y);
    pointer = { static_cast<float>(x), static_cast<float>(y) };

    hook.angle += 0.5f;
    if (hookState == Idle)
    {
        hook.position = left ? hook.HomePositionRight : hook.HomePositionLeft;
    }

    int mousInput = DxLib::GetMouseInput();
    if (mousInput & MOUSE_INPUT_LEFT && hookState == Idle)
    {
        hook.target = pointer;
        hookState = FlyingOut;
    }

    float dx = hook.target.x - hook.position.x;
    float dy = hook.target.y - hook.position.y;
    float distanceSq = dx * dx + dy * dy;
    float thresholdSq = 40.0f;

    if (distanceSq > thresholdSq)
    {
        float distance = std::sqrt(distanceSq);
        float speed = 20.0f;
        float moveX = (dx / distance) * speed * deltaTime;
        float moveY = (dy / distance) * speed * deltaTime;

        hook.position.x += moveX;
        hook.position.y += moveY;
    }
    else
    {
        // 到達したら位置を固定
        hook.position = hook.target;

        if (hookState == FlyingOut)
        {
            if(left)
                hook.target = hook.HomePositionRight;
			else
                hook.target = hook.HomePositionLeft;
            
            hookState = Returning;
        }
        else if (hookState == Returning)
        {
            hookState = Idle;
        }
    }
}

void checkHookCollider(const DxPlus::Vec2& targetPos, float targetRadius)
{

    float hookRadius = 10.0f;            // フックの半径（任意）

    // 2点間の距離を計算
    float dx = hook.position.x - targetPos.x;
    float dy = hook.position.y - targetPos.y;
    float distanceSq = dx * dx + dy * dy;

    // 半径の合計
    float radiusSum = hookRadius + targetRadius;

    // 当たり判定（距離の2乗と半径の合計の2乗を比較）
    if (distanceSq <= radiusSum * radiusSum)
    {
        // 当たっている
        onHookHit(targetPos); // ヒット時の処理（例：敵にダメージなど）
    }
}

void onHookHit(const DxPlus::Vec2& targetPos)
{
    // フックが何かに当たったときの処理をここに記述
    // 例: 敵にダメージを与える、アイテムを取得するなど
    // ここでは単純にフックを戻すだけの例を示します
    hookState = Returning;
}

// --- 描画関数 ---
void hookDraw()
{
    DxPlus::Sprite::Draw(hook.spriteID, hook.position, hook.scale, hook.center,hook.angle);

}

// --- 解放関数 ---
void hookDelete()
{

}
