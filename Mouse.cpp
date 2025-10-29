#include "Mouse.h"
#include "vol.h"

Entity2D mouse;
int vol_mouse_click;

void Mouse_Image() {
    mouse.spriteID = LoadGraph(L"./Data/images/wood_png.png");
    if (mouse.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/wood_png.png");
    }
    mouse.effectID = LoadGraph(L"./Data/images/effect.png");
    if (mouse.effectID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/effect.png");
    }
    //ついでにサウンド
    vol_mouse_click = DxLib::LoadSoundMem(L"./Data/Sounds/click.mp3");
    if (vol_mouse_click == -1)
    {
        DxPlus::Utils::FatalError(L"./Data/Sounds/click.mp3");
    }

    ChangeVolumeSoundMem((int)GetVolume, vol_mouse_click);
}

void Mouse_Reset() {
    mouse.scale = { 0.5f, 0.5f };
    mouse.center = { 1.0f,3.0f };
    mouse.position = { -100.0f, -100.0f }; // 初期位置を画面外に
    mouse.click = false;
    mouse.timer = 0.0f;

}

void Mouse_Update(float delta)
{
    int mouseInput = DxLib::GetMouseInput();
    if (mouseInput & MOUSE_INPUT_LEFT)
    {
        PlaySoundMem(vol_mouse_click, DX_PLAYTYPE_BACK);
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
        DxPlus::Sprite::Draw(mouse.effectID, { mouse.pointer.x ,mouse.pointer.y -30 }, mouse.scale, mouse.center);
	}
}

void Mouse_Delete() {
    if (mouse.spriteID != -1) {
        DxPlus::Sprite::Delete(mouse.spriteID);
        DxPlus::Sprite::Delete(mouse.effectID);
    }
}
