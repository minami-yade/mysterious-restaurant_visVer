#pragma once
#include "Entity2D.h"
#include "AllManager.h"


// --- �摜�ǂݍ��݊֌W ---
void bowlImage();

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void bowlReset();

void checkbowlCollider(Entity2D& entity, int i);

// --- �`��֐� ---
void bowlDraw();

// --- ����֐� ---
void bowlDelete();
