#pragma once
#include "Entity2D.h"
// --- �摜�ǂݍ��݊֌W ---
void ScoreImage();

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void ScoreReset();

// --- �����̍X�V�i�P���ȎO�p�g�ŏ㉺�j ---
void UpdateScore(float deltaTime);

// --- �`��֐� ---
void ScoreDraw(int score);

// --- ����֐� ---
void ScoreDelete();
