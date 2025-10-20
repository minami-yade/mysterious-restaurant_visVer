#pragma once

#include "Entity2D.h"


// --- �摜�ǂݍ��݊֌W ---
void EnemyImage();

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void EnemyReset();



// --- �����̍X�V ---
void UpdateEnemy(int i, float deltaTime,HookState& hookState);

void SpawnTimeEnemy(int i, int* Timer);

void onHookEnemyHit(const DxPlus::Vec2& targetPos, Entity2D* hook, int i);

// --- �`��֐� ---
void EnemyDraw(int i);

// --- ����֐� ---
void EnemyDelete(int i);
