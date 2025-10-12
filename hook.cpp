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
    hook.position.x = playerBasePosition.x - 194;
    hook.position.y = playerBasePosition.y - 173;

	hook.scale = { 0.5f,0.5f };
	hook.center = { 64.0f, 0.0f };

    hook.angle = 12;
}

// --- 動きの更新（単純な三角波で上下） ---
void Updatehook(float deltaTime,int x ,int y)
{
    int mouseX, mouseY;
    DxLib::GetMousePoint(&mouseX, &mouseY);
    hook.pointer = { static_cast<float>(mouseX), static_cast<float>(mouseY) };

    int mousInput = DxLib::GetMouseInput();
    if (mousInput & MOUSE_INPUT_LEFT)
    {
        x = mouseX;y = mouseY;
    }
    hook.position.x = x;
    hook.position.y = y;


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
