#pragma once
#include "Entity2D.h"



// --- �摜�ǂݍ��݊֌W ---
void hookImage();

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void hookReset(DxPlus::Vec2 playerBasePosition);

// --- �����̍X�V ---
void Updatehook(float deltaTime);


// --- �`��֐� ---
void hookDraw(bool right);

// --- ����֐� ---
void hookDelete();
