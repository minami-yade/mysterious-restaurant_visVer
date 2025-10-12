#include "hook.h"

Entity2D hook;

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
    hook.position.x = playerBasePosition.x - 100;
    hook.position.y = playerBasePosition.y - 100;

	hook.scale = { 0.5f,0.5f };
	hook.center = { 64.0f, 0.0f };


}

// --- 動きの更新（単純な三角波で上下） ---
void Updatehook(float deltaTime)
{

}

// --- 描画関数 ---
void hookDraw()
{
    DxPlus::Sprite::Draw(hook.spriteID, hook.position, hook.scale, hook.center);

}

// --- 解放関数 ---
void hookDelete()
{

}
