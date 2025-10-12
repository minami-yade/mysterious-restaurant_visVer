#include "hook.h"

Entity2D hook;

// --- �摜�ǂݍ��݊֌W ---
void hookImage()
{

    hook.spriteID = LoadGraph(L"./Data/images/hook_png.png");
    if (hook.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/hook_png.png");
    }

}

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void hookReset(DxPlus::Vec2 playerBasePosition)
{
    hook.position.x = playerBasePosition.x - 100;
    hook.position.y = playerBasePosition.y - 100;

	hook.scale = { 0.5f,0.5f };
	hook.center = { 64.0f, 0.0f };


}

// --- �����̍X�V�i�P���ȎO�p�g�ŏ㉺�j ---
void Updatehook(float deltaTime)
{

}

// --- �`��֐� ---
void hookDraw()
{
    DxPlus::Sprite::Draw(hook.spriteID, hook.position, hook.scale, hook.center);

}

// --- ����֐� ---
void hookDelete()
{

}
