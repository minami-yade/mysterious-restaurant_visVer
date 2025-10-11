#include "Mouse.h"

Entity2D mouse;

void Mouse_Image() {
    mouse.spriteID = LoadGraph(L"./Data/images/wood_png.png");
    if (mouse.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/wood_png.png");
    }
    mouse.effectID = LoadGraph(L"./Data/images/effect.png");
    if (mouse.effectID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/effect.png");
    }
}

void Mouse_Reset() {
    mouse.scale = { 0.75f, 0.75f };
    mouse.center = { 1.0f,3.0f };
    mouse.position = { -100.0f, -100.0f }; // ‰ŠúˆÊ’u‚ð‰æ–ÊŠO‚É
    mouse.click = false;
    mouse.timer = 0.0f;

}

void Mouse_Update(float delta)
{
    int mouseInput = DxLib::GetMouseInput();
    if (mouseInput & MOUSE_INPUT_LEFT)
    {
        mouse.click = true;
    }

    if (mouse.click)
    {     
        mouse.timer += delta;
    }

    if (mouse.timer >= 15.0f)
    {
        mouse.click = false;
        mouse.timer = 0.0f;
    }

    int mouseX, mouseY;
    DxLib::GetMousePoint(&mouseX, &mouseY);
    mouse.pointer = { static_cast<float>(mouseX), static_cast<float>(mouseY) };
}

void Mouse_Draw() {
    DxPlus::Sprite::Draw(mouse.spriteID, mouse.pointer, mouse.scale, mouse.center);
    if(mouse.click) {
        DxPlus::Sprite::Draw(mouse.effectID, { mouse.pointer.x ,mouse.pointer.y -40 }, mouse.scale, mouse.center);
	}
}

void Mouse_Delete() {
    if (mouse.spriteID != -1) {
        DxPlus::Sprite::Delete(mouse.spriteID);
        DxPlus::Sprite::Delete(mouse.effectID);
    }
}
