#pragma once
#include "Entity2D.h"



// --- �摜�ǂݍ��݊֌W ---
void hookImage();

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void hookReset(DxPlus::Vec2 playerBasePosition);

// --- �����̍X�V ---
void Updatehook(float deltaTime,int x ,int y,DxPlus::Vec2 pointer, bool left);

void checkHookCollider(const DxPlus::Vec2& targetPos, float targetRadius, int i,bool veg);

// --- �`��֐� ---
void hookDraw(bool left);

// --- ����֐� ---
void hookDelete();
